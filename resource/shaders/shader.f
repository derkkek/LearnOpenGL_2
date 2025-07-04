#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct SpotLight {
     vec3 position;
     vec3 direction;
     float cutOff;
     float outerCutOff;
   
     float constant;
     float linear;
     float quadratic;

     vec3 ambient;
     vec3 diffuse;
     vec3 specular;       
 };

uniform sampler2D texture_diffuse1;
uniform SpotLight spotLight; 
uniform vec3 viewPos;
uniform vec3 velocity;


 vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
 {
     vec3 lightDir = normalize(light.position - fragPos);
     // diffuse shading
     float diff = max(dot(normal, lightDir), 0.0);
     // specular shading
     vec3 reflectDir = reflect(-lightDir, normal);
     float spec = pow(max(dot(viewDir, reflectDir), 0.0), 512);
     // attenuation
     float distance = length(light.position - fragPos);
     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
     // spotlight intensity
     float theta = dot(lightDir, normalize(-light.direction)); 
     float epsilon = light.cutOff - light.outerCutOff;
     float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
     // combine results
     vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
     vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
     vec3 specular = light.specular * spec;

     return (ambient + diffuse + specular + clamp(velocity, 0.0f, 0.8f));
 }

void main()
{   
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = CalcSpotLight(spotLight, norm, FragPos, viewDir);


    FragColor = vec4(result, 1.0f);
}
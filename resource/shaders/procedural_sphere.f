#version 330 core
out vec4 FragColor;




struct DirLight {
     vec3 direction;
 	
     vec3 ambient;
     vec3 diffuse;
     vec3 specular;
 };

 uniform DirLight dirLight;
 uniform vec3 Color;
 uniform vec3 viewPos;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
 
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) 
{
    vec3 lightDir = normalize(-light.direction);
    
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(Color);
    
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * spec * Color; // Removed Color
    
    // Ambient
    vec3 ambient = light.ambient * vec3(Color);
    
    return (ambient + diffuse + specular);
}
void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
	FragColor = vec4(result, 1.0f);
}

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
 
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Sphere.h"
#include "Grid.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "Cube.h"
#include "Skybox.h"

#include "DirectionalLight.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(float(SCR_WIDTH) / (float)(SCR_HEIGHT), glm::vec3(0.0f, 0.0f, 20.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 computeForce(Cube* cube)
{
    return glm::vec3(0.0f, -9.8f, 0.0f);
}
void InitParticles(Renderer* renderer)
{
    for (RenderableObject* object : renderer->sceneObjects)
    {
        Cube* cube = dynamic_cast<Cube*>(object);

        if (cube == nullptr)
        {
            continue;
        }

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0.0f, 10.0f); // define the range

        float rand = distr(gen);
        cube->position.x = rand;
        cube->position.y = rand;

        cube->Translate(deltaTime);
        std::cout << glm::to_string(static_cast<Cube*>(object)->position) << "\n";
    }
}
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    Renderer *renderer = new Renderer;
    ResourceManager::LoadShader("resource/shaders/6.1.cubemaps.v", "resource/shaders/6.1.cubemaps.f", nullptr, "textured_cubes");
    renderer->Init(ResourceManager::GetShader("textured_cubes"), camera);
    //RenderableObject* cube = new Cube("resource/shaders/6.1.cubemaps.v", "resource/shaders/6.1.cubemaps.f");
    renderer->AddScene(new Cube(glm::vec3(5.0f, 1.0f, 1.0f)));
    renderer->AddScene(new Cube(glm::vec3(8.0f, 5.0f, 1.0f)));
    renderer->AddScene(new Cube(glm::vec3(3.0f, 7.0f, 1.0f)));
    renderer->AddScene(new Cube(glm::vec3(1.0f, 3.0f, 1.0f)));
    renderer->AddScene(new Cube(glm::vec3(10.0f, 5.0f, 1.0f)));
    //renderer.AddScene(new Sphere("resource/shaders/procedural_sphere.v", "resource/shaders/procedural_sphere.f"));
    //renderer.AddScene(new Grid(1000.0f, 100.0f, "resource/shaders/grid.v", "resource/shaders/grid.f"));
    //renderer->AddScene(new Skybox("resource/shaders/6.1.skybox.v", "resource/shaders/6.1.skybox.f"));

    //Grid* gridCast = dynamic_cast<Grid*>(grid);
    //std::vector<Sphere*> spheres;
    //spheres.push_back(dynamic_cast<Sphere*>(sphere));
    // render loop
    // -----------
    InitParticles(renderer);
    



    std::cout << "TEST FOR GITHUB";
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        //gridCast->UpdateGridVertices(spheres, 4.0f, 100.0f);
        //gridCast->UpdateBuffer();
        
        for (RenderableObject* object : renderer->sceneObjects)
        {
            Cube* cube = dynamic_cast<Cube*>(object);

            if (cube == nullptr)
            {
                continue;
            }

            //glm::vec3 force = computeForce(cube);
            
            glm::vec3 acc = glm::vec3(0.0f, -3.27f, 0.0f);

            cube->velocity += acc * deltaTime;
            cube->Translate(deltaTime);
            glm::mat4 modelPrint = cube->GetModel();
            glm::to_string(modelPrint);

        }


        renderer->RenderScene(camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    delete renderer;
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

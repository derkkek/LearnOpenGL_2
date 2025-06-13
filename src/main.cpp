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
#include "Square.h"
#include "Circle.h"
#include "PhysicsEngine.h"

#include "DirectionalLight.h"

#include <iostream>
#include <chrono>
#include <thread>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(float(SCR_WIDTH) / (float)(SCR_HEIGHT), glm::vec3(0.0f, 10.0f, 10.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
static std::random_device rd;
static std::mt19937 gen(rd());
float GetRandomNumber(float min, float max, bool isInteger) {


    if (isInteger) {
        // Properly cast to int and ensure correct bounds
        int imin = static_cast<int>(std::ceil(min));
        int imax = static_cast<int>(std::floor(max));
        std::uniform_int_distribution<> dis(imin, imax);
        return static_cast<float>(dis(gen));
    } else {
        std::uniform_real_distribution<float> dis(min, max);
        return dis(gen);
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
    glfwSwapInterval(0); // or 1 for VSync
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



    

    PhysicsEngine* physicsEngine = new PhysicsEngine();
    Renderer* renderer = new Renderer;


    for (int i = 0; i < physicsEngine->MaxUnits; i++)
    {
        // X: Random between -5 and 5
        float posX = GetRandomNumber(-8.0f, 8.0f, false);

        // Y: Random between 0 and 10 (adjust based on your needs)
        float posY = GetRandomNumber(0.0f, 5.0f, false);

        RenderableObject* circle = new Circle(0.25f, 128, glm::vec3(posX, posY, 0.0f));
        //RenderableObject* circle2 = new Circle(0.5f, 128, glm::vec3(3.0f, 5.0f, 0.0f));

        renderer->AddScene(circle);
        //renderer->AddScene(circle2);

        Rigidbody* circleCast = dynamic_cast<Rigidbody*>(circle);
        circleCast->ApplyForce(glm::vec3(GetRandomNumber(-5.0f, 5.0f, false) * circleCast->mass, GetRandomNumber(-5.0f, 5.0f, false) * circleCast->mass, 0.0f), circleCast->globalCentroid);
        //Circle* circle2_cast = dynamic_cast<Circle*>(circle2);

        physicsEngine->AddRigidBody(circleCast);
        //physicsEngine->AddRigidBody(circle2_cast->rigidbody);

    }

    //renderer->AddSkybox(new Skybox());

    renderer->SetupMeshes();

    int frameCount = 0;
    double elapsedTime = 0.0;
    auto lastTime = std::chrono::high_resolution_clock::now();

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


        physicsEngine->StepWorld(deltaTime);


        renderer->RenderScene(camera);

        static double lastTime = glfwGetTime();

        frameCount++;
        if (currentFrame - lastTime >= 1.0) {
            double fps = frameCount / (currentFrame - lastTime);
            std::string title = "FPS: " + std::to_string((int)fps);
            glfwSetWindowTitle(window, title.c_str());
            frameCount = 0;
            lastTime = currentFrame;
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    delete renderer;
    delete physicsEngine;

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

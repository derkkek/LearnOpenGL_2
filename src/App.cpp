#include "App.h"
void App::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->instance_framebuffer_size_callback(width, height);
    }
}

void App::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->instance_mouse_callback(xposIn, yposIn);
    }
}

void App::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->instance_scroll_callback(yoffset);
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly

void App::processInput(GLFWwindow* window)
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

void App::instance_framebuffer_size_callback(int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
// height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void App::instance_scroll_callback(double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
void App::instance_mouse_callback(double xposIn, double yposIn)
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

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------


// glad: load all OpenGL function pointers
const int App::LoadOpenGL()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
}
// configure global opengl state
void App::OpenGLSettings()
{
    glEnable(GL_DEPTH_TEST);
}
const int App::WindowCheck()
{
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
}


void App::Init()
{
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
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwSetWindowUserPointer(window, this);

    WindowCheck();

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, &App::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, &App::mouse_callback);
    glfwSetScrollCallback(window, &App::scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    LoadOpenGL();
    OpenGLSettings();

    renderer.AddScene(new Cube("resource/shaders/6.1.cubemaps.v", "resource/shaders/6.1.cubemaps.f"));
    renderer.AddScene(new Sphere("resource/shaders/procedural_sphere.v", "resource/shaders/procedural_sphere.f"));
    renderer.AddScene(new Grid(1000.0f, 100.0f, "resource/shaders/grid.v", "resource/shaders/grid.f"));
    renderer.AddScene(new Skybox("resource/shaders/6.1.skybox.v", "resource/shaders/6.1.skybox.f"));
}

void App::Update()
{
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

        renderer.RenderScene(camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::Terminate()
{
    glfwTerminate();
}





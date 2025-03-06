#include "Core/Window.h"

class EngineInitException : public std::runtime_error {
public:
    EngineInitException(const std::string& message) : std::runtime_error(message) {}
};

bool InitImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true) || !ImGui_ImplOpenGL3_Init()) {
        SimpleLogger logger = SimpleLogger("Logs/fatal-errors.txt");
        logger.Log("Failed to initialize ImGui");
        return false;
    }
    return true;
}

bool InitGLFW() {
    if (!glfwInit())
    {
        SimpleLogger logger = SimpleLogger("Logs/fatal-errors.txt");
        logger.Log("Failed to initialize GLFW!");
        return false;
    }
    return true;
}

bool CreateWindow(GLFWwindow*& window, int width, int height, const char* title) {
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        SimpleLogger logger = SimpleLogger("Logs/fatal-errors.txt");
        logger.Log("Failed to create GLFW window!");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    return true;
}

bool InitGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SimpleLogger logger = SimpleLogger("Logs/fatal-errors.txt");
        logger.Log("Failed to initialize GLEW!");
        return false;
    }
    return true;
}

void cleanupGraphicsResources(GLFWwindow* window) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Clear(Core::Window* Window) {
    cleanupGraphicsResources(Window->GetWindow());
}

GLFWwindow* Core::Window::GetWindow() { return this->window; }

Core::Window::Window(int width, int height, const char* title) {
    try {
        if (!InitGLFW()) {
            throw EngineInitException("Failed to initialize GLFW");
        }

        if (!CreateWindow(window, width, height, title)) {
            throw EngineInitException("Failed to create window");
        }

        if (!InitGLEW()) {
            throw EngineInitException("Failed to initialize GLEW");
        }
        if (!InitImGui(this->window)) {
            throw EngineInitException("Failed to initialize ImGui");
        }
    }
    catch (const EngineInitException& e) {
        Clear(this);
        throw;
    }
}
Core::Window::~Window() {
    Clear(this);
}

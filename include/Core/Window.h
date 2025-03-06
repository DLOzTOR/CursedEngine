//OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//another libs
#include "SimpleLogger.h"

namespace Core {
	class Window {
	private:
		GLFWwindow* window;
	public:
		Window(int width, int height, const char* title);
		GLFWwindow* GetWindow();
		~Window();
	};
}
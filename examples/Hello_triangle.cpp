#include "Core/Game.h"
#include "Render/Shader.h"
class MyGame : public Core::Game {
	const char* vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		void main()
		{
		    gl_Position = vec4(aPos.x+0.1, aPos.y, aPos.z, 1.0);
		}
		)";

	const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;
		uniform vec3 uColor;
		void main()
		{
		    FragColor = vec4(uColor, 1.0);
		}
		)";
	float vertices[9] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f };

	float color[3] = { 1.0f, 0.5f, 0.2f };
	Render::Shader* program;
	GLuint VBO, VAO;
public:
	MyGame(int width, int height, const char* title) : Game(width, height, title) {

	}
	void Start() {

		program = new Render::Shader(vertexShaderSource, fragmentShaderSource);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
		while (!glfwWindowShouldClose(GetWindow()))
		{
			Update();
		}
	}
	void Update() {
		glClear(GL_COLOR_BUFFER_BIT);

		program->UseProgram();
		program->SetUniform3fv(color, "uColor");

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Triangle settings");
		ImGui::ColorEdit3("Color", color);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwPollEvents();

		glfwSwapBuffers(GetWindow());
	}
	void Exit() {

	}
};

int main() {
	MyGame myGame = MyGame(800, 600, "Hello triangle");
	myGame.Start();
}
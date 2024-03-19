#include "main.h"
#include "circle.h"

void frameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

struct
{
	int width = 1280, height = 720;
	const char *const title = "Circle and Ball";

	GLFWwindow *window;

	ImVec4 backgroundColor;

	bool init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!window)
		{
			printf("Failed to create window.\n");
			return false;
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(true);

		glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("Failed to initialize GLAD.\n");
			return false;
		}

		glViewport(0, 0, width, height);
		glEnable(GL_DEPTH_TEST);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");

		return true;
	}

	void beginDraw()
	{
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void endDraw()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	bool exit()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();

		return 0;
	}
} App;

int main()
{
	if (!App.init())
		return -1;

	int points = 5;

	cab::Circle circle(points);
	circle.createShaderBuffer();

	while (!glfwWindowShouldClose(App.window))
	{
		static bool showObjectConfig = false;

		static GLenum drawMode[] = {
			GL_POINTS, 
			GL_LINE_STRIP, 
			GL_LINE_LOOP, 
			GL_LINES, 
			GL_LINE_STRIP_ADJACENCY, 
			GL_LINES_ADJACENCY, 
			GL_TRIANGLE_STRIP, 
			GL_TRIANGLE_FAN, 
			GL_TRIANGLES, 
			GL_TRIANGLE_STRIP_ADJACENCY, 
			GL_TRIANGLES_ADJACENCY
		};
		static int selectedDrawMode = 8;

		App.beginDraw();

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("Exit"))
					break;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Tools"))
			{
				ImGui::MenuItem("Config", NULL, &showObjectConfig);

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		if (showObjectConfig)
		{
			ImGui::Begin("Circle/Ball config", &showObjectConfig);

			if (ImGui::SliderInt("Points", &points, 3, 64))
			{
				circle = cab::Circle(points);
				circle.createShaderBuffer();
			}

			ImGui::Combo(
				"Draw mode",
				&selectedDrawMode,
				"GL_POINTS\0GL_LINE_STRIP\0GL_LINE_LOOP\0GL_LINES\0GL_LINE_STRIP_ADJACENCY\0GL_LINES_ADJACENCY\0GL_TRIANGLE_STRIP\0GL_TRIANGLE_FAN\0GL_TRIANGLES\0GL_TRIANGLE_STRIP_ADJACENCY\0GL_TRIANGLES_ADJACENCY"
			);

			ImGui::End();
		}

		circle.draw(drawMode[selectedDrawMode]);

		App.endDraw();
	}

	return App.exit();
}
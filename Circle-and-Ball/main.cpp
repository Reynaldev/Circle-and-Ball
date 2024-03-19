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

			if (ImGui::DragInt("Points", &points, 1.0f, 3, 64))
			{
				circle = cab::Circle(points);
				circle.createShaderBuffer();
			}

			ImGui::End();
		}

		circle.draw(GL_TRIANGLES);

		App.endDraw();
	}

	return App.exit();
}
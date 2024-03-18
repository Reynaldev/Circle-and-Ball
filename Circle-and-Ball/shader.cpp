#include "shader.h"

using namespace cab;

void Shader::genShaders()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
}

void Shader::createShader(const char *vf, const char *ff)
{
	char *cVertex, *cFragment;
	std::ifstream fileVert, fileFrag;

	fileVert.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fileFrag.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		fileVert.open(vf);
		fileFrag.open(ff);

		std::stringstream strVert, strFrag;

		strVert << fileVert.rdbuf();
		strFrag << fileFrag.rdbuf();

		fileVert.close();
		fileFrag.close();

		strcpy(cVertex, strVert.str().c_str());
		strcpy(cFragment, strFrag.str().c_str());
	}
	catch (const std::ifstream::failure e)
	{
		printf("Failed to read shader files.\n%s\n", e.what());
		return;
	}

	GLuint vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &cVertex, nullptr);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		printf("%s\n", infoLog);
		return;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &cFragment, nullptr);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		printf("%s\n", infoLog);
		return;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertex);
	glAttachShader(programID, fragment);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, nullptr, infoLog);
		printf("%s\n", infoLog);
		return;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

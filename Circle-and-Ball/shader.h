#pragma once

#include "main.h"
#include <fstream>
#include <sstream>

namespace cab
{
	class Shader
	{
	private:
		GLuint VAO, VBO, EBO;
		int programID;

	public:
		void genShaders();
		void createShader(const char *vf, const char *ff);

		int getProgramID() { return this->programID; }

		GLuint getVAO() { return this->VAO; }
		GLuint getVBO() { return this->VBO; }
		GLuint getEBO() { return this->EBO; }

	};
}

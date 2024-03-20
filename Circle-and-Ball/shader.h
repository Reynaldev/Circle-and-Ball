#pragma once

#include "main.h"
#include <fstream>
#include <sstream>

namespace cab
{
	enum Shader_State
	{
		SHADER_GENERATED	= 1 << 0,
		SHADER_COMPILED		= 1 << 1
	};

	class Shader
	{
	private:
		int shaderState;

		GLuint VAO, VBO, EBO;
		int programID;

	protected:
		void genShaders();
		void createShader(const char *vf, const char *ff);
		
		virtual void createShaderBuffer() {};

		int getProgramID() { return this->programID; }

		GLuint getVAO() { return this->VAO; }
		GLuint getVBO() { return this->VBO; }
		GLuint getEBO() { return this->EBO; }

	};
}

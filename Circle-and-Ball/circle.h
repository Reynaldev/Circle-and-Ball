#pragma once

#include "main.h"
#include "shader.h"

namespace cab
{
	class Circle : protected Shader
	{
	private:
		std::vector<float> vertices;
		std::vector<uint32_t> indices;

	public:
		Circle(uint32_t points);

		void createShaderBuffer() override;

		void draw(GLenum mode);

	};
}

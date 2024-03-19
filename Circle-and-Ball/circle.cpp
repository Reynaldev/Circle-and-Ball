#include "circle.h"

using namespace cab;

Circle::Circle(uint32_t points)
{
	if ((points < 3) || (points > 64))
	{
		printf(
			"Error in Circle class.\n"
			"Points cannot be less than 3 or more than 64.\n"
		);

		return;
	}

	// Center
	vertices.push_back(0.0f);		// X
	vertices.push_back(0.0f);		// Y
	vertices.push_back(0.0f);		// Z

	// Vertices
	int step = 360 / points;

	for (int i = 0; i < 360; i += step)
	{
		float angle = (float)(i * PI / 180);
		float x = cosf(angle);
		float y = sinf(angle);

		vertices.push_back(x);			// X
		vertices.push_back(y);			// Y
		vertices.push_back(0.0f);		// Z
	}

	printf("Vertices:\n");
	for (int i = 0; i < (vertices.size() - 2); i++)
		printf("\t%.1f\t%.1f\t%.1f\n", vertices[i], vertices[i + 1], vertices[i + 2]);

	// Indices
	printf("Indices:\n");
	for (int i = 1; i <= (points + 1); i++)
	{
		indices.push_back(0);		// Center
		indices.push_back(i);
		indices.push_back(((i + 1) % points) + 1);

		printf("\t%d\t%d\t%d\n", 0, i, (i + 1) % points);
	}

	genShaders();
}

void Circle::createShaderBuffer()
{
	createShader("circle.vert", "circle.frag");

	glBindVertexArray(getVAO());

	glBindBuffer(GL_ARRAY_BUFFER, getVBO());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), std_vec_to_ptr_arr(vertices), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getEBO());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), std_vec_to_ptr_arr(indices), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(NULL);
}

void Circle::draw(GLenum mode)
{
	glBindVertexArray(getVAO());

	glDrawElements(mode, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(NULL);
}
#pragma once

#ifndef CAB		// Circle and Ball
#define CAB

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "libs/imgui/imgui.h"
#include "libs/imgui/imgui_impl_glfw.h"
#include "libs/imgui/imgui_impl_opengl3.h"

#define PI 3.14

typedef std::string String;

namespace cab
{
	template <typename T>
	T * std_vec_to_ptr_arr(const std::vector<T> &vec)
	{
		T *arr = new T[vec.size()];

		for (int i = 0; i < vec.size(); i++)
			*(arr + i) = vec[i];

		return arr;
	}
}

#endif // CAB
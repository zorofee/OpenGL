#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <learnopengl/shader.h>

namespace PBR_Practice
{

	void FramebufferSizeCallbackFunction(GLFWwindow*,int,int);
	void RenderSphere();

	const unsigned int SCR_WIDTH = 400;
	const unsigned int SCR_HEIGHT = 300;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	int pbr_main()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		//create window
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"hi pbr",NULL,NULL);
		if (window == NULL)
		{
			return -1;
		}

		//bind callback function
		glfwSetFramebufferSizeCallback(window, FramebufferSizeCallbackFunction);

		//load GLLoader
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return -1;
		}

		glEnable(GL_DEPTH_TEST);

		Shader shader("PBR/pbr.vs", "PBR/pbr.fs");
		shader.use();

		while (!glfwWindowShouldClose(window))
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			glClearColor(0.1f,0.1f,0.1f,0.1f);
			shader.use();

		}

		return 0;
	}


	void RenderCube()
	{
		float vertices[] = {
			// first triangle
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f,  0.5f, 0.0f,  // top left 
			// second triangle
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left
		};

		unsigned int indices[] = {
			0,1,3,
			1,2,3
		};

		/*
		VBO : vertex buffer object
		VAO : vertex array object
		EBO : element buffer object
		*/
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	unsigned int sphereVAO = 0;
	void RenderSphere()
	{
		if (sphereVAO == 0)
		{
			glGenVertexArrays(1,&sphereVAO);
			unsigned int vbo, ebo;
			glGenBuffers(1,&vbo);
			glGenBuffers(1,&ebo);

			std::vector<glm::vec3> positions;
			std::vector<glm::vec2> uv;
			std::vector<glm::vec3> normals;
			std::vector<unsigned int> indices;

			const unsigned int X_SEGMENTS = 64;
			const unsigned int Y_SEGMENTS = 64;
			const float PI = 3.1415926;
			
			for (unsigned int y = 0; y < Y_SEGMENTS; y++)
			{
				for (unsigned int x = 0; x < X_SEGMENTS; x++)
				{
					float x_segment = (float)x/(float)X_SEGMENTS;
					float y_segment = (float)y/(float)Y_SEGMENTS; 
					float x_pos = std::cos(x_segment * 2.0f * PI) * std::sin(y_segment * PI);
					float y_pos = std::cos(y_segment * PI);

					float z_pos = std::sin(x_segment * 2.0f *PI) * std::sin(y_segment * PI);

					positions.push_back(glm::vec3(x_pos, y_pos, z_pos));
					normals.push_back(glm::vec3(x_pos, y_pos, z_pos));
					uv.push_back(glm::vec2(x_segment,y_segment));
				}
			}

			glBindVertexArray(sphereVAO);
			glBindBuffer(GL_ARRAY_BUFFER,vbo);
		}
	}
}
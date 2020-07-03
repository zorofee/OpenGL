#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

namespace Triangle_Practice 
{
	
	const unsigned int SCR_WIDTH = 400;
	const unsigned int SCR_HEIGHT = 300;

	void framebuffer_size_callback(GLFWwindow*, int, int);
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"out vec3 vColor;\n"
		"uniform float noise;\n"
		"void main()\n"
		"{\n"
		"	vColor=aPos;\n"
		"   gl_Position = vec4(aPos.x * noise, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 OutColor;\n"
		"in vec3 vColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(vColor,1);\n"  //vec4(1.0f, 0.5f, 0.2f, 1.0f) * OutColor
		"}\n\0";


	float vertices[] = {
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};




	float vertices2[] = {
			0.8f,  0.8f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices2[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};




	int main()
	{
		glfwInit();
		glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		GLFWwindow* window = glfwCreateWindow(400, 300, "opengl", NULL, NULL);
		if (window == NULL)
		{
			return -1;
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return -1;
		}

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
		glCompileShader(vertexShader);

		unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragShader);

		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram,vertexShader);
		glAttachShader(shaderProgram, fragShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);


		//-------VAO 1-------

		unsigned int VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1,&VBO);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);




		//-------VAO 2-------

		unsigned int VAO2, VBO2, EBO2;
		glGenVertexArrays(1, &VAO2);
		glGenBuffers(1, &VBO2);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);






		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.4,0,0,1);

			glUseProgram(shaderProgram);
			glBindVertexArray(VAO2);
			glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
			//glDrawArrays(GL_TRIANGLES, 0, 3);    // 直接用VBO数组，不用index数组


			//glGetTime
			//glGetUniformLocation
			//glUniform4f
			glfwGetTime();
			float time = glfwGetTime();
			float value = sin(time) * cos(time);

			int location_color = glGetUniformLocation(shaderProgram, "OutColor");
			int location_noise = glGetUniformLocation(shaderProgram,"noise");
			glUniform4f(location_color,0,value,0,1);
			glUniform1f(location_noise, value);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();
	}

	void framebuffer_size_callback(GLFWwindow*, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	/*
	We have to repeat this process every time we want to draw an object. 
	It may not look like that much, but imagine if we have over 5 vertex attributes and perhaps 100s of different objects (which is not uncommon). 
	Binding the appropriate buffer objects and configuring all vertex attributes for each of those objects quickly becomes a cumbersome process.
	What if there was some way we could store all these state configurations into an object and simply bind this object to restore its state?

	Vertex Array Object
	A vertex array object (also known as VAO) can be bound just like a vertex buffer object and any subsequent vertex attribute calls from that point on will be stored inside the VAO. 
	This has the advantage that when configuring vertex attribute pointers you only have to make those calls once and whenever we want to draw the object, we can just bind the corresponding VAO.
	This makes switching between different vertex data and attribute configurations as easy as binding a different VAO. 
	All the state we just set is stored inside the VAO.
	*/
}
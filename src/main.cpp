#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
GLFWwindow *window; 

int main(void)
{
	if( !glfwInit())//Initialise GLFW
	{
		std::cout<<"Failed to initialize GLFW"<<std::endl;
		
		return -1;
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//open a window for OpenGL
	window = glfwCreateWindow(800, 600, "Tutorials", NULL, NULL);
	if(window == NULL)
	{
		std::cout<<"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials."<<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	//Initialize GLEW
	glewExperimental = true;//core profile
	if(glewInit() != GLEW_OK)
	{
		std::cout<<"Failed to initialize GLEW"<<std::endl;
		glfwTerminate();
		return -1;
	}
	
	//keyboard
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);//background color
	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	//An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = 
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	
	
	//indentify our vertex buffer
	GLuint vertexbuffer;
	
	//generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	
	//talks about our vertexbuffer buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	
	//give vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);
	do
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
		
		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);
		
	}while(glfwGetKey(window,GLFW_KEY_ESCAPE)!= GLFW_PRESS && glfwWindowShouldClose(window)==0);
	
	glfwTerminate();
	
	return 0;
}
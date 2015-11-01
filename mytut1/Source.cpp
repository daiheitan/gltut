
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <vector>
#include <algorithm>
#include "framework.h"

GLuint program, positionBufferObj, vao;

void init()
{
	const float vertexPositions[] = {
		0.75f, 0.75f, 0.0f, 1.0f,
		0.75f, -0.75f, 0.0f, 1.0f,
		-0.75f, -0.75f, 0.0f, 1.0f,
	};
	// Compile shaders
	std::vector<GLuint> shaderList;
	shaderList.push_back(Framework::makeShader(GL_VERTEX_SHADER, "vertexShader.glsl"));
	shaderList.push_back(Framework::makeShader(GL_FRAGMENT_SHADER, "fragmentShader.glsl"));
	// Create program
	program = glCreateProgram();
	for (size_t i = 0; i < shaderList.size(); i++) {
		glAttachShader(program, shaderList[i]);
	}
	glLinkProgram(program);
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* log = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, log);
		fprintf(stderr, "Linker failure: %s\n", log);
		delete[] log;
	}
	// Detach shaders
	for (size_t i = 0; i < shaderList.size(); i++) {
		glDetachShader(program, shaderList[i]);
	}
	// Delete shaders
	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

	// Create buffer
	glGenBuffers(1, &positionBufferObj);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	// Clear bind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	// We claim that positionBufferObj is an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObj);
	// We bind the buffer to vertex attribute location 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Clean up
	glDisableVertexAttribArray(0);
	glUseProgram(0);

	// Force openGL use our buffers
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void keyboard(unsigned char key, int x, int y)
{

}

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <vector>
#include "framework.h"

GLuint program;

void init()
{
	std::vector<GLuint> shaderList;
	shaderList.push_back(Framework::makeShader(GL_VERTEX_SHADER, "vertexShader.glsl"));
}

void display()
{}

void reshape(int w, int h)
{

}

void keyboard(unsigned char key, int x, int y)
{

}
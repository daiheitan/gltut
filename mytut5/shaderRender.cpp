
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <vector>
#include "framework.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))
const float vertexPositions[] = {
	0.25f, 0.25f, 0.0f, 1.0f,
	0.25f, -0.25f, 0.0f, 1.0f,
	-0.25f, -0.25f, 0.0f, 1.0f,
};

GLuint program, positionBufferObj, offsetPosition;
GLuint vao;

void initializeProgram()
{
	std::vector<GLuint> shaderList;
	shaderList.push_back(Framework::makeShader(GL_VERTEX_SHADER, "vertexShader.glsl"));
	shaderList.push_back(Framework::makeShader(GL_FRAGMENT_SHADER, "fragmentShader.glsl"));

	program = Framework::createProgram(shaderList);
	offsetPosition = glGetUniformLocation(program, "offset");
}

void initializeVertexBuffer()
{
	glGenBuffers(1, &positionBufferObj);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void init()
{
	initializeProgram();
	initializeVertexBuffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void computePositionOffsets(float &fXOffset, float &fYOffset)
{
	const float fLoopDuration = 5.0f;
	const float fScale = 3.14159f * 2.0f / fLoopDuration;

	float fElapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
	fXOffset = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
	fYOffset = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
}

void display()
{
	float fXOffset = 0.0f, fYOffset = 0.0f;
	computePositionOffsets(fXOffset, fYOffset);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glUniform2f(offsetPosition, fXOffset, fYOffset);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObj);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	glUseProgram(0);

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void keyboard(unsigned char key, int x, int y)
{

}
// Supress fopen errors on Windows
#define _CRT_SECURE_NO_WARNINGS


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include "framework.h"

// Just function prototypes (aka declarations), we
// could define the functions later in each tutorials

void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

// Add this to force NVidia GPU rendering
// Ref: http://stackoverflow.com/questions/30024364/any-ways-to-run-program-debugging-in-visual-studio-on-nvidia-graphics-card
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

// Used mainly to load GLSL files,
// from: https://github.com/jckarter/hello-gl/blob/master/util.c

// this is a c++ conversion of the original c style method
// it is test to be as fast as the C implementation
// http://insanecoding.blogspot.hk/2011/11/how-to-read-in-file-in-c.html
std::string get_file_contents(const char *filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

GLuint Framework::makeShader(GLenum type, const char* filename)
{
	GLuint shader = glCreateShader(type);
	GLint length, shader_ok;
	const std::string content = get_file_contents(filename);
	glShaderSource(shader, 1, (const char**)content.c_str(), NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);

	if (shader_ok == GL_FALSE) {
		fprintf(stderr, "Error to compile shader: %s", filename);
		
	}

	return shader;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("The very first openGL window");

	// Check current openGL version
	printf("Your loaded OpenGL version is %s\n", glGetString(GL_VERSION));
	// Glew init must be called before any glew related call, or it will crash
	// http://stackoverflow.com/questions/12329082/glcreateshader-is-crashing
	glewInit();
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}

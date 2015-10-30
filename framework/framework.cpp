// Supress fopen errors on Windows
#define _CRT_SECURE_NO_WARNINGS

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <codecvt>
#include <iostream>
#include "framework.h"

#define ENCODING_ASCII      0
#define ENCODING_UTF8       1
#define ENCODING_UTF16LE    2
#define ENCODING_UTF16BE    3

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

std::string ReplaceString(std::string subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

namespace Framework {
	// Used mainly to load GLSL files,
	// from: https://github.com/jckarter/hello-gl/blob/master/util.c

	// this is a c++ conversion of the original c style method
	// it is test to be as fast as the C implementation
	// http://insanecoding.blogspot.hk/2011/11/how-to-read-in-file-in-c.html
	std::string getFileContents(const std::string path)
	{
		std::string result;
		std::ifstream ifs(path.c_str(), std::ios::binary);
		std::stringstream ss;
		int encoding = ENCODING_ASCII;

		if (!ifs.is_open()) {
			// Unable to read file
			result.clear();
			return result;
		}
		else if (ifs.eof()) {
			result.clear();
		}
		else {
			int ch1 = ifs.get();
			int ch2 = ifs.get();
			if (ch1 == 0xff && ch2 == 0xfe) {
				// The file contains UTF-16LE BOM
				encoding = ENCODING_UTF16LE;
			}
			else if (ch1 == 0xfe && ch2 == 0xff) {
				// The file contains UTF-16BE BOM
				encoding = ENCODING_UTF16BE;
			}
			else {
				int ch3 = ifs.get();
				if (ch1 == 0xef && ch2 == 0xbb && ch3 == 0xbf) {
					// The file contains UTF-8 BOM
					encoding = ENCODING_UTF8;
				}
				else {
					// The file does not have BOM
					encoding = ENCODING_ASCII;
					ifs.seekg(0);
				}
			}
		}
		ss << ifs.rdbuf() << "";
		if (encoding == ENCODING_UTF16LE) {
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> utfconv;
			result = utfconv.to_bytes(std::wstring((wchar_t *)ss.str().c_str()));
		}
		else if (encoding == ENCODING_UTF16BE) {
			std::string src = ss.str();
			std::string dst = src;
			// Using Windows API
			_swab(&src[0u], &dst[0u], src.size() + 1);
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> utfconv;
			result = utfconv.to_bytes(std::wstring((wchar_t *)dst.c_str()));
		}
		else if (encoding == ENCODING_UTF8) {
			result = ss.str();
		}
		else {
			result = ss.str();
		}
		result = ReplaceString(result, "\r\n", "\n");
		return result;
	}

	GLuint makeShader(GLenum type, const char* filename)
	{
		GLuint shader = glCreateShader(type);
		GLint length, shader_ok;
		const std::string content = getFileContents(filename);
		const char* str = content.c_str();
		glShaderSource(shader, 1, &str, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);

		if (shader_ok == GL_FALSE) {
			fprintf(stderr, "Error to compile shader: %s: ", filename);
			GLint logInfoLengh;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logInfoLengh);
			GLchar* log = new GLchar[logInfoLengh + 1];
			glGetShaderInfoLog(shader, logInfoLengh, NULL, log);
			fprintf(stderr, "%s", log);
		}

		return shader;
	}
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

// Supress fopen errors on Windows
#define _CRT_SECURE_NO_WARNINGS


#include <GL\freeglut.h>
#include <stdio.h>

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
void *file_contents(const char *filename, GLint *length)
{
	FILE *f = fopen(filename, "r");
	void *buffer;

	if (!f) {
		fprintf(stderr, "Unable to open %s for reading\n", filename);
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	*length = ftell(f);
	fseek(f, 0, SEEK_SET);

	buffer = malloc(*length + 1);
	*length = fread(buffer, 1, *length, f);
	fclose(f);
	((char*)buffer)[*length] = '\0';

	return buffer;
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
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}

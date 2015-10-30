#ifndef __FRAMEWORK__
#define __FRAMEWORK__

namespace Framework {
	GLuint makeShader(GLenum type, const char* filename);
	std::string getFileContents(const std::string filename);
}

#endif //__FRAMEWORK__
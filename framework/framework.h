#ifndef __FRAMEWORK__
#define __FRAMEWORK__

namespace Framework {
	GLuint makeShader(GLenum type, const char* filename);
	std::string getFileContents(const std::string filename);
	GLuint createProgram(const std::vector<GLuint>& shaderList);
}

#endif //__FRAMEWORK__
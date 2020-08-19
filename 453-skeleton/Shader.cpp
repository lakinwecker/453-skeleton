#include "Shader.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>


Shader::Shader(std::string path, GLenum type) :
	shaderID{type},
	type(type),
	path(path)
{
	if (!compile()) {
		throw ShaderCompileException("Shader did not compile");
	}
}

bool Shader::compile() {

	// read shader source
	std::string sourceString;
	std::ifstream file;

	// ensure ifstream objects can throw exceptions:
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		// open file
		file.open(path);
		std::stringstream sourceStream;

		// read file buffer contents into stream
		sourceStream << file.rdbuf();

		// close file handler
		file.close();

		// convert stream into string
		sourceString = sourceStream.str();
	}
	catch (std::ifstream::failure &e) {
		std::cerr << "ERROR::SHADER reading " << path << ":" << std::endl;
		std::cerr << strerror(errno) << std::endl;
		return false;
	}
	const GLchar* sourceCode = sourceString.c_str();


	// compile shader
	glShaderSource(shaderID, 1, &sourceCode, NULL);
	glCompileShader(shaderID);

	// check for errors
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success) {
		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> log((size_t)logLength);
		glGetShaderInfoLog(shaderID, logLength, NULL, log.data());

		std::cerr << "ERROR::SHADER compiling " << path << ":" << std::endl;
		std::cerr << log.data() << std::endl;
	}
	return success;
}

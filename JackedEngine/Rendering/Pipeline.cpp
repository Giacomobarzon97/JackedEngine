#include "Pipeline.h"

Pipeline::Pipeline(std::string vertShaderPath, std::string fragShaderPath) {
	std::vector<char> vertShaderCode = FileIO::readFile(vertShaderPath);
	std::vector<char> fragShaderCode = FileIO::readFile(fragShaderPath);

	std::cout << "Vertex Shader Code Size: " << vertShaderCode.size() << '\n';
	std::cout << "Fragment Shader Code Size: " << fragShaderCode.size() << '\n';
}

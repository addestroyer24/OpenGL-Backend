#include "Shader.h"
#include "Matrix.h"
#include <glad\glad.h>
#include <iostream>

/*
when creating a shader I need :
vertex source
fragment source
atrribArrays [name, data length, data type]
uniforms [name, data type]
*/

//Shader::Shader()
//{
//}
namespace GLBackend
{
	Shader::Shader(unsigned int vertexElements, const char* vertexSource, const char* fragmentSource)
	{
		int success;
		char infoLog[512];

		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		this->id = shaderProgram;
		this->vertexElements = vertexElements;
		this->attributes = std::vector<Attribute*>();
	}

	Shader::~Shader()
	{
		for (auto iter = this->attributes.crbegin(); iter != this->attributes.crend(); iter++) 
		{
			Attribute* attr = *iter;

			delete attr;
		}
		this->attributes.clear();

		for (auto iter = this->uniforms.cbegin(); iter != this->uniforms.cend(); iter++)
		{
			Uniform* uni = iter->second;

			delete uni;
		}
		this->uniforms.clear();
	}

	void Shader::bind() const {
		glUseProgram(this->id);
	}

	void Shader::addAttribute(const char* name, unsigned int elements, unsigned int offset)
	{
		int location = glGetAttribLocation(this->id, name);
		addAttribute(location, name, elements, offset);
	}

	void Shader::addAttribute(int location, const char* name, unsigned int elements, unsigned int offset)
	{
		Attribute* attr = new Attribute{ location, elements, offset };
		this->attributes.push_back(attr);
	}

	const std::vector<Attribute*>& Shader::getAttributes() const
	{
		return this->attributes;
	}



	void Shader::setUniform(std::string name, const Mat2& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniformMatrix2fv(location, 1, GL_TRUE, data.getGLFormat());
		glUseProgram(0);
	}

	void Shader::setUniform(std::string name, const Mat3& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniformMatrix3fv(location, 1, GL_TRUE, data.getGLFormat());
		glUseProgram(0);
	}

	void Shader::setUniform(std::string name, const Mat4& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniformMatrix4fv(location, 1, GL_TRUE, data.getGLFormat());
		glUseProgram(0);
	}



	void Shader::setUniform(std::string name, const Vec2& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform2fv(location, 1, data.getGLFormat());
		glUseProgram(0);
	}

	void Shader::setUniform(std::string name, const iVec2& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform2iv(location, 1, data.getGLFormat());
		glUseProgram(0);
	}

	void Shader::setUniform(std::string name, const uVec2& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform2uiv(location, 1, data.getGLFormat());
		glUseProgram(0);
	}

	//void Shader::setUniform(std::string name, const bVec2 data)
	//{
	//	int location = getUniformLocation(name);

	//	glUseProgram(this->id);
	//	glUniform2iv(location, 1, data.getGLFormat());
	//	glUseProgram(0);
	//}



	void Shader::setUniform(std::string name, const Vec3& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform3fv(location, 1, data.getGLFormat());
		glUseProgram(0);
	}

	void Shader::setUniform(std::string name, const iVec3& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform3iv(location, 1, data.getGLFormat());
		glUseProgram(0);
	}

	void Shader::setUniform(std::string name, const uVec3& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform3uiv(location, 1, data.getGLFormat());
		glUseProgram(0);
	}

	//void Shader::setUniform(std::string name, const bVec3 data)
	//{
	//	int location = getUniformLocation(name);

	//	glUseProgram(this->id);
	//	glUniform3iv(location, 1, data.getGLFormat());
	//	glUseProgram(0);
	//}



	void Shader::setUniform(std::string name, const Vec4& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform4fv(location, 1, data.getGLFormat());
		glUseProgram(0);
	}

	void Shader::setUniform(std::string name, const iVec4& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform4iv(location, 1, data.getGLFormat());
		glUseProgram(0);
	}

	void Shader::setUniform(std::string name, const uVec4& data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform4uiv(location, 1, data.getGLFormat());
		glUseProgram(0);
	}

	//void Shader::setUniform(std::string name, const bVec4 data)
	//{
	//	int location = getUniformLocation(name);

	//	glUseProgram(this->id);
	//	glUniform4iv(location, 1, data.getGLFormat());
	//	glUseProgram(0);
	//}



	void Shader::setUniform(std::string name, float data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform1f(location, data);
		glUseProgram(0);
	}
	
	void Shader::setUniform(std::string name, int data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform1i(location, data);
		glUseProgram(0);
	}

	void Shader::setUniform(std::string name, unsigned int data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform1ui(location, data);
		glUseProgram(0);
	}

	void Shader::setUniform(std::string name, bool data)
	{
		int location = getUniformLocation(name);

		glUseProgram(this->id);
		glUniform1i(location, data);
		glUseProgram(0);
	}

	void Shader::setTexture(int textureSlot, std::string uniformName, int textureId)
	{
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, textureId);
		setUniform(uniformName, textureSlot);
	}



	int Shader::getUniformLocation(std::string name) 
	{
		Uniform* uni;
		auto locationIterator = this->uniforms.find(name);
		if (locationIterator != this->uniforms.end())
		{
			uni = locationIterator->second;
		}
		else
		{//then we dont know the location, so we need to find it
			int location = glGetUniformLocation(this->id, name.c_str());
			uni = new Uniform{ location };
			this->uniforms.emplace(name, uni);
		}
		return uni->location;
	}
}

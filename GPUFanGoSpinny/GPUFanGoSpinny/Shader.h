#pragma once
// Code from learnopengl.com

class Shader
{
public:
	// program ID
	GLuint m_ID = 0;

	// constructor reads and builds shaders from filepaths
	Shader(const std::string& p_vertexPath, const std::string& p_fragmentPath);
	
	// destructor deletes program
	~Shader();

	// use/activate the shader
	void use();

	// set uniform values in the shader
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};


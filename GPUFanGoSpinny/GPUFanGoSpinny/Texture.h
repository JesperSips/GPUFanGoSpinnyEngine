#pragma once
class Texture
{
public:
	Texture();
	Texture(const std::string& p_filePath, bool p_flipTexture);

	~Texture();

private:

	GLuint m_texture = 0;
};


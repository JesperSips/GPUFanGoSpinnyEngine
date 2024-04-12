#pragma once
class Texture
{
public:
	Texture();
	Texture(const std::string& p_filePath, bool p_flipTexture);

	~Texture();

private:
	unsigned char* m_data = nullptr;

	GLuint m_texture = 0;
};


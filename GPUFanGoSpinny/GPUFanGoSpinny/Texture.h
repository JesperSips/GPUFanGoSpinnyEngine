#pragma once
class Texture
{
public:
	Texture();

	void loadTexture(const std::string& p_filePath, bool p_flipTexture);

private:
	unsigned char* m_data = nullptr;

	GLuint m_texture = 0;
};


#pragma once

struct Transform
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);

	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

	float yaw = -90.f;
	float pitch = 0.f;

	const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
};

class Camera
{
public:
	// Include aspect ratio and FOV in degrees
	Camera(float p_aspectRatio, float p_fov);

	glm::mat4 GetView() const { return m_view; }
	glm::mat4 GetProjection() const { return m_projection; }
	glm::mat4 GetViewProjection() const { return m_projection * m_view; }

	void UpdateView();
	void UpdateProjection(float p_aspectRatio);

	void SetNearPlane(float p_near) { m_near = p_near; }
	void SetFarPlane(float p_far) { m_far = p_far; }

	void Update(GLFWwindow* p_window);
private:

	glm::mat4 m_projection = 0;
	glm::mat4 m_view = 0;

	float m_fovDegrees = 80.f;
	float m_near = 0.1f;
	float m_far = 10000.0f;
	float m_aspectRatio = 1.f;

	Transform m_transform;
};


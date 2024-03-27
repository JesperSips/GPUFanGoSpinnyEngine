#include "pch.h"
#include "Camera.h"

Camera::Camera(float p_aspectRatio, float p_fov)
{
	m_aspectRatio = p_aspectRatio;
	m_fovDegrees = p_fov;

	UpdateProjection(m_aspectRatio);
	UpdateView();
}

void Camera::UpdateView()
{
	m_view = glm::lookAt(m_transform.position, m_transform.position + m_transform.forward, m_transform.up);
}

void Camera::UpdateProjection(float p_aspectRatio)
{
	m_aspectRatio = p_aspectRatio;

	m_projection = glm::perspective(glm::radians(m_fovDegrees), m_aspectRatio, m_near, m_far);
}

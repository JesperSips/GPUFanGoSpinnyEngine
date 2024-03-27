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

void Camera::Update(GLFWwindow* p_window)
{
    static bool hideMouse = false;

    // Temporary input code
    if (glfwGetKey(p_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(p_window, true);

    if (glfwGetKey(p_window, GLFW_KEY_P) == GLFW_PRESS)
    {
        hideMouse = true;

        // tell GLFW to capture our mouse
        glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else if(glfwGetKey(p_window, GLFW_KEY_O) == GLFW_PRESS)
    {
        hideMouse = false;

        // tell GLFW to capture our mouse
        glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    float cameraSpeed = static_cast<float>(2.5 * global::deltaTime);
    if (glfwGetKey(p_window, GLFW_KEY_W) == GLFW_PRESS)
        m_transform.position += cameraSpeed * m_transform.forward;
    if (glfwGetKey(p_window, GLFW_KEY_S) == GLFW_PRESS)
        m_transform.position -= cameraSpeed * m_transform.forward;
    if (glfwGetKey(p_window, GLFW_KEY_A) == GLFW_PRESS)
        m_transform.position -= glm::normalize(glm::cross(m_transform.forward, m_transform.up)) * cameraSpeed;
    if (glfwGetKey(p_window, GLFW_KEY_D) == GLFW_PRESS)
        m_transform.position += glm::normalize(glm::cross(m_transform.forward, m_transform.up)) * cameraSpeed;

    // Only move the camera while the mouse is hidden
    if (hideMouse)
    {
        m_transform.yaw += global::mouseOffset.x;
        m_transform.pitch += global::mouseOffset.y;

        if (m_transform.pitch > 89.0f)
            m_transform.pitch = 89.0f;
        if (m_transform.pitch < -89.0f)
            m_transform.pitch = -89.0f;
    }


    glm::vec3 direction;
    direction.x = cos(glm::radians(m_transform.yaw)) * cos(glm::radians(m_transform.pitch));
    direction.y = sin(glm::radians(m_transform.pitch));
    direction.z = sin(glm::radians(m_transform.yaw)) * cos(glm::radians(m_transform.pitch));
    m_transform.forward = glm::normalize(direction);

    UpdateView();
}

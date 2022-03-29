#include "Camera.h"
#include "../Renderer/Renderer.h"

Camera::Camera(Renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector,float yaw,float pitch)
{
	this->currentRenderer = currentRenderer;
	Zoom = ZOOM;
	//TODO agregar propiedades/posibilidad de camara ortogonal
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(Zoom), (float)currentRenderer->getCurrentWindow()->GetWidth() / (float)currentRenderer->getCurrentWindow()->GetHeight(), 0.1f, 500.0f);
	this->currentRenderer->SetProjectionMatrix(projectionMatrix);
	setCameraTransform(position, lookPosition, upVector);
	pos = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	MovementSpeed = SPEED;
	right = (glm::vec3(1.0f, 0.0f, 0.0f));
	WorldUp = (glm::vec3(0.0f, 1.0f, 0.0f));
	targetLook = glm::vec3(10, 0, 0);
	localPos = glm::vec3(0, 0, -20);
	front = glm::vec3(0.f, 0.f, -1.f);
	cameraType = CAMERA_TYPE::FPS;
	distance = 0.f;

	MouseSensitivity = SENSITIVITY;
	//updateCameraVectors();
}
void Camera::setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
{
	pos = startingPosition;
	targetLook = lookPosition;
	up = upVector;
	currentRenderer->SetViewMatrix(glm::lookAt(pos, lookPosition, upVector));
}
void Camera::updateZoom()
{
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(Zoom), (float)currentRenderer->getCurrentWindow()->GetWidth() / (float)currentRenderer->getCurrentWindow()->GetHeight(), 0.1f, 500.0f);
	this->currentRenderer->SetProjectionMatrix(projectionMatrix);
}
void Camera::moveCamera(glm::vec3 movePosition)
{
	pos += movePosition;
	targetLook += movePosition;
	setCameraTransform(pos, targetLook, up);
}
void Camera::moveCameraLookingPoint(glm::vec3 movePosition)
{
	pos += movePosition;
	//look += movePosition;
	setCameraTransform(pos, targetLook, up);
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front = glm::normalize(direction);
	if (cameraType == CAMERA_TYPE::TPS)
	{
		pos = targetLook -front * Zoom;
	}
	UpdateView();
}

void Camera::UpdateView()
{
	switch (cameraType)
	{
	case CAMERA_TYPE::FPS:
		setCameraTransform(pos, pos + targetLook, up);
		break;
	case CAMERA_TYPE::TPS:
		setCameraTransform(pos, targetLook, up);
		break;
	case CAMERA_TYPE::TOP_DOWN:
		break;
	default:
		break;
	}
	
}
void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
	updateZoom();
	setCameraTransform(pos, targetLook, up);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;
	

	Yaw += xoffset;
	Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped

		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	
	std::cout << "x: " << xoffset << " y: " <<yoffset<<std::endl;
	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == Camera_Movement::FORWARD)
		pos += targetLook * velocity;
	if (direction == Camera_Movement::BACKWARD)
		pos -= targetLook * velocity;
	if (direction == Camera_Movement::LEFT)
		pos -= right * velocity;
	if (direction == Camera_Movement::RIGHT)
		pos += right * velocity;
	setCameraTransform(pos, targetLook, up);
}
void Camera::debugCamera()
{
	std::cout << "pos: " << pos.x << ","
		<< pos.y << "," << pos.z
		<< " look: " << targetLook.x << ","
		<< targetLook.y << "," << targetLook.z <<
		"up:" << up.x <<","<<
		up.y << "," <<up.z << std::endl;
}

Camera::~Camera()
{

}

void Camera::SetCameraType(CAMERA_TYPE type)
{
	cameraType = type;
}

CAMERA_TYPE Camera::GetCameraType()
{
	return cameraType;
}

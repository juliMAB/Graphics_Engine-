#include "Camera.h"
#include "../Renderer/Renderer.h"

Camera::Camera(Renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector,float yaw,float pitch)
{
	this->currentRenderer = currentRenderer;
	Zoom = ZOOM;
	//TODO agregar propiedades/posibilidad de camara ortogonal
	projectionMatrix = glm::perspective(glm::radians(Zoom), (float)currentRenderer->getCurrentWindow()->GetWidth() / (float)currentRenderer->getCurrentWindow()->GetHeight(), 0.1f, 500.0f);
	this->currentRenderer->SetProjectionMatrix(projectionMatrix);
	setCameraTransform(position, lookPosition, upVector);
	pos = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	MovementSpeed = SPEED;
	look = (glm::vec3(0.0f, 0.0f, -1.0f));
	Right = (glm::vec3(1.0f, 0.0f, 0.0f));
	WorldUp = (glm::vec3(0.0f, 1.0f, 0.0f));
	localPos = pos;
	targetPos = glm::vec3(0, 0, 0);

	cameraType = CAMERA_TYPE::FPS;
	target = glm::vec3(0.f);
	distance = 0.f;

	MouseSensitivity = SENSITIVITY;
	//updateCameraVectors();
}
void Camera::setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
{
	pos = startingPosition;
	look = lookPosition;
	up = upVector;
	currentRenderer->SetViewMatrix(glm::lookAt(startingPosition, lookPosition, upVector));
}
void Camera::updateZoom()
{
	projectionMatrix = glm::perspective(glm::radians(Zoom), (float)currentRenderer->getCurrentWindow()->GetWidth() / (float)currentRenderer->getCurrentWindow()->GetHeight(), 0.1f, 500.0f);
	this->currentRenderer->SetProjectionMatrix(projectionMatrix);
}
void Camera::moveCamera(glm::vec3 movePosition)
{
	pos += movePosition;
	look += movePosition;
	setCameraTransform(pos, look, up);
}
void Camera::moveCameraLookingPoint(glm::vec3 movePosition)
{
	pos += movePosition;
	//look += movePosition;
	setCameraTransform(pos, look, up);
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	//look = glm::normalize(front);
	// also re-calculate the Right and Up vector
	//Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	//up = glm::normalize(glm::cross(Right, Front));

	switch (cameraType)
	{
	case CAMERA_TYPE::FPS:
		break;
	case CAMERA_TYPE::TPS:
		//pos = target - look * distance;
		front.y = -front.y;
		localPos = glm::normalize(front) * 10.0f;
		pos = targetPos + localPos;
		look = targetPos;
		break;
	case CAMERA_TYPE::TOP_DOWN:
		break;
	default: 
		break;
	}


	UpdateView();


	
}

void Camera::UpdateView()
{
	switch (cameraType)
	{
	case CAMERA_TYPE::FPS:
		setCameraTransform(pos, pos+look, up);
		break;
	case CAMERA_TYPE::TPS:
		setCameraTransform(pos, target, up);
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
	setCameraTransform(pos, look, up);
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
		pos += look * velocity;
	if (direction == Camera_Movement::BACKWARD)
		pos -= look * velocity;
	if (direction == Camera_Movement::LEFT)
		pos -= Right * velocity;
	if (direction == Camera_Movement::RIGHT)
		pos += Right * velocity;
	setCameraTransform(pos, look, up);
}
void Camera::debugCamera()
{
	std::cout << "pos: " << pos.x << ","
		<< pos.y << "," << pos.z
		<< " look: " << look.x << ","
		<< look.y << "," << look.z <<
		"up:" << up.x <<","<<
		up.y << "," <<up.z << std::endl;
	//look = glm::vec3(0,0,0);
}

Camera::~Camera()
{

}
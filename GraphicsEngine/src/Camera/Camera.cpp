#include "Camera.h"
#include "../Renderer/Renderer.h"

Camera::Camera(Renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector)
{
	this->currentRenderer = currentRenderer;

	//TODO agregar propiedades/posibilidad de camara ortogonal
	projectionMatrix = glm::perspective(glm::radians(90.0f), (float)currentRenderer->getCurrentWindow()->GetWidth() / (float)currentRenderer->getCurrentWindow()->GetHeight(), 0.1f, 500.0f);
	this->currentRenderer->SetProjectionMatrix(projectionMatrix);
	setCameraTransform(position, lookPosition, upVector);
}
void Camera::setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
{
	pos = startingPosition;
	look = lookPosition;
	up = upVector;
	viewMatrix = glm::lookAt(startingPosition, lookPosition, upVector);
	currentRenderer->SetViewMatrix(viewMatrix);
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

Camera::~Camera()
{

}
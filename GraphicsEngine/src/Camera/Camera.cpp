#include "Camera.h"
#include "../Renderer/Renderer.h"

Camera::Camera(Renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector,float yaw,float pitch)
{
	this->_render = currentRenderer;
	_fov = ZOOM;
	//TODO agregar propiedades/posibilidad de camara ortogonal
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(_fov), (float)currentRenderer->getCurrentWindow()->GetWidth() / (float)currentRenderer->getCurrentWindow()->GetHeight(), 0.1f, 500.0f);
	this->_render->SetProjectionMatrix(projectionMatrix);
	SetViewMatrix(position, lookPosition, upVector);
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

	MouseSensitivity = SENSITIVITY;
	//updateCameraVectors();
}

void Camera::Init(Renderer* render,float near, float far)
{
	_render = render;
	//--------
	pos = glm::vec3(0.0f);
	localPos = glm::vec3(0.0f);
	//--------
	up = glm::vec3(0, 1, 0);
	right = glm::vec3(0.0f);
	front = glm::vec3(0, 0, -1);
	//--------
	targetLook = glm::vec3(0.0f);
	WorldUp = glm::vec3(0.0f);
	//--------
	cameraType = CAMERA_TYPE::FPS;
	//--------
	Yaw = YAW;
	Pitch = PITCH;
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	_fov = ZOOM;
	_near = near;
	_far = far;
	SetAspect();
	//--------
	UpdateProjection();
	UpdateView();
}
void Camera::Init(Renderer* render)
{
	_render = render;
	//--------
	pos = glm::vec3(0.0f);
	localPos = glm::vec3(0.0f);
	//--------
	up    = glm::vec3(0,1,0);
	right = glm::vec3(0.0f);
	front = glm::vec3(0,0,-1);
	//--------
	targetLook = glm::vec3(0.0f);
	WorldUp = glm::vec3(0.0f);
	//--------
	cameraType = CAMERA_TYPE::FPS;
	//--------
	Yaw = YAW;
	Pitch = PITCH;
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	_fov = ZOOM;
	_near = 0.1f;
	_far = 100.f;
	SetAspect();
	//--------
	UpdateProjection();
	UpdateView();
}
void Camera::SetNear(float near)
{
	_near = near;
}
void Camera::SetAspect()
{
	Window* window = _render->getCurrentWindow();
	float width = window->GetWidth();
	float height = window->GetHeight();
	SetAspect(width, height);
}
void Camera::SetAspect(float width, float height)
{
	_aspect = width / height;
}
Camera::Camera()
{
	_render = NULL;

	localPos = glm::vec3(0.0f);
	pos      = glm::vec3(0.0f);
	up       = glm::vec3(0.0f);
	right    = glm::vec3(0.0f);
	front    = glm::vec3(0.0f);
	//--------
	targetLook = glm::vec3(0.0f);
	WorldUp    = glm::vec3(0.0f);
	//--------
	cameraType = CAMERA_TYPE::FPS;
	//--------
	Yaw		         = 0;
	Pitch	         = 0;
	MovementSpeed    = 0;
	MouseSensitivity = 0;
	_fov              = 0;
	_aspect			 = 0;
	_near             = 0;
	_far              = 0;
	//--------
}
void Camera::SetViewMatrix(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
{
	_render->SetViewMatrix(glm::lookAt(startingPosition, lookPosition, upVector));
}
void Camera::UpdateProjection()
{
	glm::mat4 projection = glm::perspective(glm::radians(_fov), _aspect, _near, _far);
	_render->SetProjectionMatrix(projection);
}
void Camera::moveCamera(glm::vec3 movePosition)
{
	pos += movePosition;
	targetLook += movePosition;
	SetViewMatrix(pos, targetLook, up);
}
void Camera::moveCameraLookingPoint(glm::vec3 movePosition)
{
	pos += movePosition;
	//look += movePosition;
	SetViewMatrix(pos, targetLook, up);
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
		pos = targetLook -front * _fov;
	}
	UpdateView();
}

void Camera::UpdateView()
{
	switch (cameraType)
	{
	case CAMERA_TYPE::FPS:
		SetViewMatrix(pos, pos + targetLook, up);
		return;
	case CAMERA_TYPE::TPS:
		SetViewMatrix(pos, targetLook, up);
		return;
	case CAMERA_TYPE::TOP_DOWN:
		break;
	default:
		break;
	}
	
}
void Camera::ProcessMouseScroll(float yoffset)
{
	_fov -= (float)yoffset;
	if (_fov < 1.0f)
		_fov = 1.0f;
	if (_fov > 45.0f)
		_fov = 45.0f;
	UpdateProjection();
	SetViewMatrix(pos, targetLook, up);
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
	SetViewMatrix(pos, targetLook, up);
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

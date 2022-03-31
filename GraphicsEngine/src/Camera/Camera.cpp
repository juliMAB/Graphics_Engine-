#include "Camera.h"
#include "../Renderer/Renderer.h"

void Camera::Init(Renderer* render,float near, float far)
{
	_render = render;
	BaseInit();
	_near = near;
	_far = far;
	SetAspect();
	//--------
	UpdateProjection();
	UpdateView();
}
void Camera::BaseInit(){
	//--------
	pos = glm::vec3(0.0f);
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
	_sensitivity = SENSITIVITY;
	_fov = ZOOM;
	_near = 0.1f;
	_far = 100.f;
	_offset = OFFSET;
}
void Camera::Init(Renderer* render)
{
	_render = render;
	BaseInit();
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
	_sensitivity = 0;
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
void Camera::SetTarget(Entity* target)
{
	_target = target;
}
void Camera::SetSensitivity(float sensitivity)
{
	_sensitivity = sensitivity;
}
void Camera::SetOffset(float offset) {
	_offset = offset;
}
void Camera::Update()
{
	pos = _target->getPos();
	UpdateCameraVectors();
}
void Camera::UpdateProjection()
{
	glm::mat4 projection = glm::perspective(glm::radians(_fov), _aspect, _near, _far);
	_render->SetProjectionMatrix(projection);
}
void Camera::moveCamera(glm::vec3 movePosition)
{
	//pos += movePosition;
	//targetLook += movePosition;
	//SetViewMatrix(pos, targetLook, up);
}
void Camera::moveCameraLookingPoint(glm::vec3 movePosition)
{
	//pos += movePosition;
	////look += movePosition;
	//SetViewMatrix(pos, targetLook, up);
}

void Camera::UpdateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front = glm::normalize(direction);
	if (cameraType == CAMERA_TYPE::TPS)
	{
		if (_target!=NULL)
			pos = _target->getPos() -front * _offset;
		else
			pos = glm::vec3(0) - front * _offset;
	}
	UpdateView();
}

void Camera::UpdateView()
{
	switch (cameraType)
	{
	case CAMERA_TYPE::FPS:
		SetViewMatrix(pos, pos + front, up);
		return;
	case CAMERA_TYPE::TPS:
		if (_target != NULL)
			SetViewMatrix(pos, _target->getPos(), up);
		else
			SetViewMatrix(pos, glm::vec3(0), up);
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
	if (_target != NULL)
		SetViewMatrix(pos, _target->getPos(), up);
	else
		SetViewMatrix(pos, glm::vec3(0), up);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= _sensitivity;
	yoffset *= _sensitivity;
	

	Yaw += xoffset;
	Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped

		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	
	std::cout << "x: " << xoffset << " y: " <<yoffset<<std::endl;
	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == Camera_Movement::FORWARD)
		pos += _target->getPos() * velocity;
	if (direction == Camera_Movement::BACKWARD)
		pos -= _target->getPos() * velocity;
	if (direction == Camera_Movement::LEFT)
		pos -= right * velocity;
	if (direction == Camera_Movement::RIGHT)
		pos += right * velocity;
	SetViewMatrix(pos, _target->getPos(), up);
}
void Camera::debugCamera()
{
	std::cout << "pos: " << pos.x << ","
		<< pos.y << "," << pos.z << std::endl;
		if (_target!=NULL)
		{
			std::cout << " Target: " << targetLook.x << ","
				<< targetLook.y << "," << targetLook.z << std::endl;
		}
		std::cout << "up:" << up.x <<","<<
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

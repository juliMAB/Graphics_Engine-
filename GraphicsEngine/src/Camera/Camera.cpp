#include "Camera.h"
#include "../Renderer/Renderer.h"

void Camera::Init(Renderer* render,Window* window,float near, float far)
{
	_render = render;
	_window = window;
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
	transform.position = glm::vec3(0.0f);
	//--------
	transform.up = glm::vec3(0, 1, 0);
	transform.right = glm::vec3(0.0f);
	transform.forward = glm::vec3(0, 0, -1);
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
void Camera::Init(Renderer* render,Window* window)
{
	_render = render;
	_window = window;
	BaseInit();
	SetAspect();
	//--------
	UpdateProjection();
	UpdateView();
}
void Camera::SetWindow(Window* window)
{
	_window = window;
}
void Camera::SetNear(float near)
{
	_near = near;
}
void Camera::SetAspect()
{
	float width = _window->GetWidth();
	float height = _window->GetHeight();
	SetAspect(width, height);
}
void Camera::SetAspect(float width, float height)
{
	_aspect = width / height;
}
Camera::Camera()
{
	_render = NULL;

	transform.position      = glm::vec3(0.0f);
	transform.up       = glm::vec3(0.0f);
	transform.right    = glm::vec3(0.0f);
	transform.forward    = glm::vec3(0.0f);
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
	_render->SetView(glm::lookAt(startingPosition, lookPosition, upVector));
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
	if (_target != NULL)
		transform.position = _target->getPos();
	UpdateCameraVectors();
}
void Camera::UpdateProjection()
{
	glm::mat4 projection = glm::perspective(glm::radians(_fov), _aspect, _near, _far);
	_render->SetProjection(projection);
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
	transform.forward= glm::normalize(direction);
	if (cameraType == CAMERA_TYPE::TPS)
	{
		if (_target!=NULL)
			transform.position = _target->getPos() - transform.forward * _offset;
		else
			transform.position = glm::vec3(0) - transform.forward * _offset;
	}
	UpdateView();
}

void Camera::UpdateView()
{
	switch (cameraType)
	{
	case CAMERA_TYPE::FPS:
		SetViewMatrix(transform.position, transform.position + transform.forward, transform.up);
		return;
	case CAMERA_TYPE::TPS:
		if (_target != NULL)
			SetViewMatrix(transform.position, _target->getPos(), transform.up);
		else
			SetViewMatrix(transform.position, glm::vec3(0), transform.up);
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
		SetViewMatrix(transform.position, _target->getPos(), transform.up);
	else
		SetViewMatrix(transform.position, glm::vec3(0), transform.up);
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
	
	//std::cout << "x: " << xoffset << " y: " <<yoffset<<std::endl;
	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == Camera_Movement::FORWARD)
		transform.position += _target->getPos() * velocity;
	if (direction == Camera_Movement::BACKWARD)
		transform.position -= _target->getPos() * velocity;
	if (direction == Camera_Movement::LEFT)
		transform.position -= transform.right * velocity;
	if (direction == Camera_Movement::RIGHT)
		transform.position += transform.right * velocity;
	SetViewMatrix(transform.position, _target->getPos(), transform.up);
}
void Camera::debugCamera()
{
	/*std::cout << "pos: " << pos.x << ","
		<< pos.y << "," << pos.z << std::endl;
		if (_target!=NULL)
		{
			std::cout << " Target: " << targetLook.x << ","
				<< targetLook.y << "," << targetLook.z << std::endl;
		}
		std::cout << "up:" << up.x <<","<<
		up.y << "," <<up.z << std::endl;*/
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

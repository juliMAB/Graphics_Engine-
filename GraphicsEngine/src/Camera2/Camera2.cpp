#include "Camera2.h"
#include <Juli/Jinterface.h>
namespace JuliEngine
{
	Camera2::Camera2(Renderer* render, Window* window) : Entity2(render)
	{
		_renderer = render;
		_window = window;
		Yaw = YAW;
		Pitch = PITCH;
		MovementSpeed = SPEED;
		_sensitivity = SENSITIVITY;
		_fov = ZOOM;
		_near = 0.1f;
		_far = 100.f;
		_offset = OFFSET;
		float width = _window->GetWidth();
		float height = _window->GetHeight();
		SetAspect(width, height);
		UpdateProjection();
		UpdateView();
		_renderer->SetUniform(_uniformViewPos, "viewPos");
		camFrustrum = new Frustum(getTransform(), _aspect, _fov, _near, _far);
	}

	void Camera2::SetAspect(float width, float height)
	{
		_aspect = width / height;
	}

	void Camera2::Update()
	{
		if (_target != NULL && _cameraType == CAMERA_TYPE::TPS)
			getTransform()->getposition() = _target->getPos();
		UpdateCameraVectors();
		_renderer->UseShader();
		_renderer->UpdateVec3(_uniformViewPos, getPos());
	}
	void Camera2::UpdateCameraVectors()
	{
		if (!_ejes)
			return;
		// calculate the new Front vector
		glm::vec3 direction;
		direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		direction.y = sin(glm::radians(Pitch));
		direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		getTransform()->setForward(glm::normalize(direction));
		getTransform()->setRight(glm::cross(getTransform()->getForward(), getTransform()->getUp()));
		if (_target != NULL && _cameraType == CAMERA_TYPE::TPS)
			getTransform()->setposition(getTransform()->getposition() - getTransform()->getForward() * _offset);
		UpdateView();
	}
	void Camera2::UpdateProjection()
	{
		glm::mat4 projection = glm::perspective(glm::radians(_fov), _aspect, _near, _far);
		_renderer->SetProjection(projection);
	}
	void Camera2::UpdateView()
	{
		switch (_cameraType)
		{
		case CAMERA_TYPE::FPS:
			SetViewMatrix(getTransform()->getposition(), getTransform()->getposition() + getTransform()->getForward(), getTransform()->getUp());
			return;
		case CAMERA_TYPE::TPS:
			if (_target != NULL)
				SetViewMatrix(getTransform()->getposition(), _target->getPos(), getTransform()->getUp());
			return;
		case CAMERA_TYPE::FC:
			SetViewMatrix(getTransform()->getposition(), getTransform()->getposition() + getTransform()->getForward(), getTransform()->getUp());
			break;
		}
	}
	void Camera2::ProcessMouseScroll(float yoffset)
	{
		_fov -= (float)yoffset;
		if (_fov < 1.0f)
			_fov = 1.0f;
		if (_fov > 45.0f)
			_fov = 45.0f;
		UpdateProjection();
		if (_target != NULL && _cameraType == CAMERA_TYPE::TPS)
			SetViewMatrix(getPos(), _target->getPos(), getTransform()->getUp());
	}
	void Camera2::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
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
	void Camera2::SetViewMatrix(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
	{
		targetLook = lookPosition;
		WorldUp = upVector;
		_renderer->SetView(glm::lookAt(startingPosition, lookPosition, upVector));
	}
	void Camera2::ToogleEjes()
	{
		_ejes = !_ejes;
		std::cout << "Camera update set (" << _ejes << ")" << std::endl;
	}
	void Camera2::DebugInfo()
	{
		std::cout << "---CAMARA INFO---" << std::endl;
		std::cout << "	Camera pos: " + VecToString::vec3toString(getPos()) << std::endl;
		std::cout << "	Camera look: " + VecToString::vec3toString(targetLook) << std::endl;
		std::cout << "	Camera up: " + VecToString::vec3toString(WorldUp) << std::endl;
	}
}

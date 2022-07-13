#include "Camera2.h"
#include <Juli/Jinterface.h>
namespace JuliEngine
{
	Camera2* Camera2::_mainCamera;
	Camera2::Camera2(Renderer* render, Window* window)
	{
		_render = render;
		_window = window;
		Yaw = YAW;
		Pitch = PITCH;
		_moveSpeed = SPEED;
		_sensitivity = SENSITIVITY;
		_offset = OFFSET;
		_fov = ZOOM;
		_near = 0.1f;
		_far = 100.f;
		float width = _window->GetWidth();
		float height = _window->GetHeight();
		SetAspect(width, height);
		UpdateProjection();
		UpdateView();
		_render->SetUniform(_uniformViewPos, "viewPos");
		_mainCamera = this;
	}

	void Camera2::SetAspect(float width, float height)
	{
		_aspect = width / height;
	}

	void Camera2::Update()
	{
		if (_target != NULL && _cameraType == CAMERA_TYPE::TPS)
			myTransform.setposition(_target->getposition());
		UpdateCameraVectors();
		_render->UseShader();
		_render->UpdateVec3(_uniformViewPos, myTransform.getposition());
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
		myTransform.setForward(glm::normalize(direction));
		myTransform.setRight(glm::cross(myTransform.getForward(), myTransform.getUp()));
		if (_target != NULL && _cameraType == CAMERA_TYPE::TPS)
			myTransform.setposition(myTransform.getposition() - myTransform.getForward() * _offset);
		myTransform.updateLocalModelMatrix();
		myTransform.setWorldModel(myTransform.getLocalModel());
		UpdateView();
	}
	void Camera2::UpdateProjection()
	{
		glm::mat4 projection = glm::perspective(glm::radians(_fov), _aspect, _near, _far);
		_render->SetProjection(projection);
	}
	void Camera2::UpdateView()
	{
		switch (_cameraType)
		{
		case CAMERA_TYPE::FPS:
			SetViewMatrix(myTransform.getposition(), myTransform.getposition() + myTransform.getForward(), myTransform.getUp());
			return;
		case CAMERA_TYPE::TPS:
			if (_target != NULL)
				SetViewMatrix(myTransform.getposition(), _target->getposition(), myTransform.getUp());
			return;
		case CAMERA_TYPE::FC:
			SetViewMatrix(myTransform.getposition(), myTransform.getposition() + myTransform.getForward(), myTransform.getUp());
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
			SetViewMatrix(myTransform.getposition(), _target->getposition(), myTransform.getUp());
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
		_render->SetView(glm::lookAt(startingPosition, lookPosition, upVector));
	}
	void Camera2::ToogleEjes()
	{
		_ejes = !_ejes;
		
		std::cout << "Camera update set (" << _ejes << ")" << std::endl;
	}
	void Camera2::Move(vec3 v)
	{
		myTransform.setposition(myTransform.getposition() + v * _moveSpeed);
	}
	void Camera2::DebugInfo()
	{
		std::cout << "---CAMARA INFO---" << std::endl;
		std::cout << "	Camera pos: " + VecToString::vec3toString(myTransform.getposition()) << std::endl;
		std::cout << "	Camera look: " + VecToString::vec3toString(targetLook) << std::endl;
		std::cout << "	Camera up: " + VecToString::vec3toString(WorldUp) << std::endl;
	}

	glm::vec3 Camera2::GetFront()
	{
		return myTransform.getForward();
	}
	glm::vec3 Camera2::GetRight()
	{
		return myTransform.getRight();
	}
	glm::vec3 Camera2::GetUp()
	{
		return myTransform.getUp();
	}
	glm::vec3 Camera2::getPos()
	{
		return myTransform.getposition();;
	}
}

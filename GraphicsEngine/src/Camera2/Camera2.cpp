#include "Camera2.h"
#include <Juli\Jinterface.h>
namespace JuliEngine
{
	Camera2::Camera2(Renderer* render, Window* window) : Entity2(render)
	{
		_window = window;
		//--------
		targetLook = glm::vec3(0.0f);
		WorldUp = glm::vec3(0.0f);
		//--------
		_cameraType = CAMERA_TYPE::FPS;
		//--------
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
		_aspect = width / height;
		UpdateProjection();
	}

	void Camera2::UpdateProjection()
	{
		glm::mat4 projection = glm::perspective(glm::radians(_fov), _aspect, _near, _far);
		_renderer->SetProjection(projection);
	}
	void Camera2::SetViewMatrix(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
	{
		targetLook = lookPosition;
		WorldUp = upVector;
		_renderer->SetView(glm::lookAt(startingPosition, lookPosition, upVector));
	}
	void Camera2::UpdateView()
	{
		switch (_cameraType)
		{
		case CAMERA_TYPE::FPS:
			SetViewMatrix(getTransform()->getposition(), getTransform()->getposition() + getTransform()->getforward(), getTransform()->getup());
			return;
		case CAMERA_TYPE::TPS:
			if (_target != NULL)
				SetViewMatrix(getTransform()->getposition(), _target->getPos(), getTransform()->getup());
			return;
		case CAMERA_TYPE::FC:
			SetViewMatrix(getTransform()->getposition(), getTransform()->getposition() + getTransform()->getforward(), getTransform()->getup());
			break;
		default:
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
			SetViewMatrix(getTransform()->getposition(), _target->getPos(), getTransform()->getup());
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

		// update Front, Right and Up Vectors using the updated Euler angles
		UpdateCameraVectors();
	}
	void Camera2::ToogleEjes()
	{
		_ejes = !_ejes;
		string a = "FALSE";
		if (_ejes)
			a = "TRUE";
		std::cout << "Camera update set (" << a << ")" << std::endl;
	}
	void Camera2::DebugInfo()
	{
		std::cout << "---CAMARA INFO---" << std::endl;
		std::cout << "	Camera pos: " + VecToString::vec3toString(getTransform()->getposition()) << std::endl;
		std::cout << "	Camera look: " + VecToString::vec3toString(targetLook) << std::endl;
		std::cout << "	Camera up: " + VecToString::vec3toString(WorldUp) << std::endl;
	}
	void Camera2::Update()
	{
		if (_target != NULL && _cameraType == CAMERA_TYPE::TPS)
			getTransform()->setposition(_target->getPos());
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
		getTransform()->setforward(glm::normalize(direction));
		getTransform()->setright(glm::cross(getTransform()->getforward(), getTransform()->getup()));
		if (_target != NULL && _cameraType == CAMERA_TYPE::TPS)
		{
			getTransform()->setposition(_target->getPos() - getTransform()->getforward()* _offset);
		}
		UpdateView();
	}

}

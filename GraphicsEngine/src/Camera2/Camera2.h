#ifndef CAMERA2_H
#define CAMERA2_H
#include "Exports/Exports.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
//#include "Entity2/Entity2.h"
#include "Transform/Transform.h"
#include "Renderer/Renderer.h"
namespace JuliEngine
{

	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;
	const float OFFSET = 10.f;

	enum class CAMERA_TYPE
	{
		FC,
		FPS,
		TPS,
		Max
	};

	class GraficosEngine_API Camera2
	{
	public:
		//--------Builder Destroy Init----------
		Camera2(Renderer* render, Window* window);
		~Camera2() {};
		void SetWindow(Window* v) { _window = v; };
		//--------Seters----------
		void SetAspect(float width, float height);
		void SetViewMatrix(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector);
		void SetTarget(Transform* v) { _target = v; };
		void SetSensitivity(float v) { _sensitivity = v; };
		void SetOffset(float v) { _offset = v; };
		void SetCameraType(CAMERA_TYPE v) { _cameraType = v; };
		void SetPos(vec3 v) { myTransform.setposition(v); };
		//------------------------
		//------Updates-----------
		void Update();
		void UpdateProjection();

		void UpdateCameraVectors();
		void UpdateView();
		void ProcessMouseScroll(float yoffset);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
		void ToogleEjes();

		void Move(vec3 v) { myTransform.setposition(myTransform.getLocalPosition() + v * _moveSpeed); };
		//--------Getters-------
		Transform* GetTarget() { return _target; };
		CAMERA_TYPE GetCameraType() { return _cameraType; };
		float getFOV() { return _fov; };
		float getAspect() { return _aspect; };
		float getFar() { return _far; };
		float getNear() { return _near; };
		//--------Others--------
		void DebugInfo();
		glm::vec3 GetFront();
		glm::vec3 GetRight();
		glm::vec3 GetUp();
		glm::vec3 getPos();
		bool _ejes;
		bool _mouseMoveCamera;
		static Camera2* _mainCamera;
	private:
		friend class MyImGui;

		Transform* _target;
		Window* _window;

		uint _uniformViewPos;

		glm::vec3 targetLook;
		glm::vec3 WorldUp;

		JuliEngine::Transform myTransform;

		CAMERA_TYPE _cameraType;

		Renderer* _render;

		float Yaw;
		float Pitch;
		
		float _fov;

		float _aspect;
		float _near;
		float _far;

		float _moveSpeed;
		float _offset;
		float _sensitivity;

	};
}
#endif
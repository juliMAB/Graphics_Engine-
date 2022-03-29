#ifndef CAMERA_H
#define CAMERA_H
#include "../Exports/Exports.h"
#include "../GLM/glm.hpp"
#include "../GLM/gtc/matrix_transform.hpp"
#include "../GLM/gtc/type_ptr.hpp"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW			= -90.0f;
const float PITCH		= 0.0f;
const float SPEED		= 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM		= 45.0f;
class Renderer;

enum class CAMERA_TYPE
{
	FPS,
	TPS,
	TOP_DOWN
};

class GraficosEngine_API Camera
{
public:
	//--------Builder Destroy Init----------
	Camera(Renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, float yaw, float pitch);
	Camera();
	~Camera();
	void Init(Renderer* render, float near, float far);
	void Init(Renderer* render);
	//--------Seters----------
	void SetNear(float);
	void SetAspect();
	void SetAspect(float width, float height);
	void SetViewMatrix(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector);
	//------------------------
	void UpdateProjection();
	void moveCamera(glm::vec3 movePosition);
	void moveCameraLookingPoint(glm::vec3 movePosition);
	void updateCameraVectors();
	void UpdateView();
	void ProcessMouseScroll(float yoffset);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void debugCamera();
	void SetCameraType(CAMERA_TYPE type);
	CAMERA_TYPE GetCameraType();

private:
	Renderer* _render;

	glm::vec3 localPos;
	glm::vec3 pos;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 front;
	
	glm::vec3 targetLook;
	glm::vec3 WorldUp;

	CAMERA_TYPE cameraType;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float _fov;
	float _aspect;
	float _near;
	float _far;
};
#endif
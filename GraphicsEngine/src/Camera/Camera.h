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
	Camera(Renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, float yaw, float pitch);
	//Camera(Renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector);
	//Camera(Renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f,0.0f,-1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM){;
	void setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector);
	void updateZoom();
	void moveCamera(glm::vec3 movePosition);
	void moveCameraLookingPoint(glm::vec3 movePosition);
	void updateCameraVectors();
	void UpdateView();
	void ProcessMouseScroll(float yoffset);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void debugCamera();
	~Camera();
private:
	//glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::vec3 pos;
	glm::vec3 look;
	glm::vec3 up;
	glm::vec3 localPos;
	glm::vec3 targetPos;

	//glm::vec3 look;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	CAMERA_TYPE cameraType;
	glm::vec3 target;
	float distance;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	Renderer* currentRenderer;
};
#endif
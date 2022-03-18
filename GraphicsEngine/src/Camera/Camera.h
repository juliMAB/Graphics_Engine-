#ifndef CAMERA_H
#define CAMERA_H
#include "../Exports/Exports.h"
#include "../GLM/glm.hpp"
#include "../GLM/gtc/matrix_transform.hpp"
#include "../GLM/gtc/type_ptr.hpp"

class Renderer;

class GraficosEngine_API Camera
{
public:
	Camera(Renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector);
	void setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector);
	void moveCamera(glm::vec3 movePosition);
	void moveCameraLookingPoint(glm::vec3 movePosition);
	~Camera();
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::vec3 pos;
	glm::vec3 look;
	glm::vec3 up;
	Renderer* currentRenderer;
};
#endif
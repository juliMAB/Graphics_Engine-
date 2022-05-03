#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "light.h"
#include "../Camera/Camera.h"


class GraficosEngine_API SpotLight : public Light
{
public:
	SpotLight(Renderer* render);
	void SetUniforms();
	void UpdateLight();

	~SpotLight();
	void SetCamera(Camera* cam);
	void SetCutOff(float cutOff);

	void SetConstant(float constant);
	void SetLinear(float linear);
	void SetQuadratic(float quadratic);

protected:

	Camera* cam;
	float cutOff;

	float constant;
	float linear;
	float quadratic;

	uint _uniformPosition;
	uint _uniformDirection;
	uint _uniformCutOff;

	uint _uniformConstant;
	uint _uniformLinear;
	uint _uniformQuadratic;
};


#endif // !LIGHT_H
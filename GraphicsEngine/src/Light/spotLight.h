#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "pointLight.h"
#include "../Camera/Camera.h"


class GraficosEngine_API SpotLight : public PointLight
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

	uint _uniformDirection;
	uint _uniformCutOff;

};


#endif // !LIGHT_H
#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "pointLight.h"
#include "../Camera/Camera.h"


class GraficosEngine_API SpotLight : public PointLight
{
public:
	SpotLight(Renderer* render);
	void Init();
	void SetUniforms(std::string name) override;
	void UpdateLight() override;

	~SpotLight();
	void SetCamera(Camera* cam);
	void SetCutOff(float cutOff);
	void SetOuterCutOff(float outerCutOff);

protected:

	Camera* _cam;
	float cutOff;
	float outerCutOff;

	uint _uniformDirection;
	uint _uniformCutOff;
	uint _uniformOuterCutOff;

};


#endif // !LIGHT_H
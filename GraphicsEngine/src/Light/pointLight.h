#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"


class GraficosEngine_API PointLight : public Light
{
public:
	PointLight() {};
	PointLight(Renderer* render);
	void SetUniforms() ;
	void UpdateLight() ;

	~PointLight();
	void SetConstant(float constant);
	void SetLinear(float linear);
	void SetQuadratic(float quadratic);

protected:
	vec3 pos;
	static int quantity;
	float constant;
	float linear;
	float quadratic;

	uint _uniformPosition;

	uint _uniformConstant;
	uint _uniformLinear;
	uint _uniformQuadratic;
};


#endif // !LIGHT_H
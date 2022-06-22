#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"

namespace JuliEngine
{

	class GraficosEngine_API PointLight : public Light
	{
	public:
		PointLight(Renderer* render);
		void Init();
		virtual void SetUniforms(std::string name) override;
		virtual void UpdateLight() override;

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
}


#endif // !LIGHT_H
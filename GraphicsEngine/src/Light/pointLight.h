#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "../Exports/Exports.h"
#include <string>
#include "light.h"


	class GraficosEngine_API PointLight : public Light
	{
	public:
		PointLight(Renderer* render);
		~PointLight();

		virtual void Init(int index);
		virtual void UseLight() override;

		void SetConstant(float constant);
		void SetLinear(float linear);
		void SetQuadratic(float quadratic);

		float GetConstant();
		float GetLinear();
		float GetQuadratic();

	protected:
		float constant;
		float linear;
		float quadratic;

		uint uniformConstant;
		uint uniformLinear;
		uint uniformQuadratic;
	};


#endif // !POINT_LIGHT_H

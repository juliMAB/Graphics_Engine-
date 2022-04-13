#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "../Exports/Exports.h"
#include "pointLight.h"


	class GraficosEngine_API SpotLight : public PointLight
	{
	public:
		SpotLight(Renderer* render);
		~SpotLight();

		virtual void Init(int index);
		void UseLight() override;

		void SetDirection(glm::vec3 direction);
		void SetCutOff(float cutOff);
		void SetOuterCutOff(float outerCutOff);

		glm::vec3 GetDirection();
		float GetCutOff();
		float GetOuterCutOff();

	private:
		glm::vec3 direction;
		float cutOff;
		float outerCutOff;

		uint uniformDirection;
		uint uniformCutOff;
		uint uniformOuterCutOff;
	};


#endif // !SPOT_LIGHT_H

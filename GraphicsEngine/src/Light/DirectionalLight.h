#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "../Exports/Exports.h"
#include "light.h"


	class GraficosEngine_API DirectionalLight : public Light
	{
	public:
		DirectionalLight(Renderer* render);
		~DirectionalLight();

		void Init();
		void UseLight() override;

		void SetDirection(glm::vec3 direction);
		glm::vec3 GetDirection();

	private:
		glm::vec3 direction;

		uint uniformDirection;
	};


#endif // !DIRECTIONAL_LIGHT_H

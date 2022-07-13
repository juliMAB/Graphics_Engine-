#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H

#include "light.h"
namespace JuliEngine
{
	class GraficosEngine_API DirectionLight : public Light
	{
	public:
		DirectionLight(Renderer* render);
		void Init();
		void SetUniforms(std::string name) override;
		void UpdateLight() override;

		~DirectionLight();
		void SetDirection(glm::vec3 direction);

	protected:
		glm::vec3 direction;

		uint _uniformDirection;
	};

}



#endif // !LIGHT_H
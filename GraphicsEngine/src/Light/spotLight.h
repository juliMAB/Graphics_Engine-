#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "pointLight.h"
#include "../Camera2/Camera2.h"
namespace JuliEngine
{
	class GraficosEngine_API SpotLight : public PointLight
	{
	public:
		SpotLight(Renderer* render);
		void Init();
		void SetUniforms(std::string name) override;
		void UpdateLight() override;

		~SpotLight();
		void SetCamera(Camera2* cam);
		void SetCutOff(float cutOff);
		void SetOuterCutOff(float outerCutOff);
		static int CuantitySpots;

	protected:

		Camera2* _cam;
		float cutOff;
		float outerCutOff;

		uint _uniformDirection;
		uint _uniformCutOff;
		uint _uniformOuterCutOff;
		static std::list<SpotLight*> SpotLists;
	};
}



#endif // !LIGHT_H
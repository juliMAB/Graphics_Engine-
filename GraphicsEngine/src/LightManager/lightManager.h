#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include "../Exports/Exports.h"
#include "../Light/DirectionalLight.h"
#include "../Light/pointLight.h"
#include "../Light/spotLight.h"


	int const lightMax = 3;

	enum class LIGHT_TYPE
	{
		DIRECTIONAL,
		POINTLIGHT,
		SPOTLIGHT
	};

	class GraficosEngine_API LightManager
	{
	public:
		LightManager(Renderer* render);
		~LightManager();

		void AddLight(LIGHT_TYPE type);
		void UseLights();

		DirectionalLight* GetDirectionalLight();
		PointLight* GetPointLight(int index);
		SpotLight* GetSpotLight(int index);
		PointLight* GetLasPointLightCreated();
		SpotLight* GetLasSpotLightCreated();

	private:
		Renderer* render;
		int pointLightsCreated;
		int spotLightsCreated;

		DirectionalLight* directionalLight;
		PointLight* pointLights[lightMax];
		SpotLight* spotLights[lightMax];
	};


#endif // !LIGHT_MANAGER_H

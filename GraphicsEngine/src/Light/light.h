#ifndef LIGHT_H
#define LIGHT_H

#include "../Exports/Exports.h"
#include "../Entity/Entity.h"
#include "../glm/ext/matrix_transform.hpp"
#include "../Juli/Jinterface.h"


	class GraficosEngine_API Light : public Entity
	{
	public:
		Light(Renderer* render);
		void SetUniforms();
		void SetLight(glm::vec3 pos, glm::vec3 color, float ambientStrength);
		void UpdateLight();
		~Light();

		void SetAmbient(glm::vec3 ambient);
		void SetAmbientStrength(float ambient);
		void SetDiffuse(glm::vec3 diffuse);
		void SetSpecular(glm::vec3 specular);
		void SetEnabled(bool enabled);

		glm::vec3 GetAmbient();
		glm::vec3 GetDiffuse();
		glm::vec3 GetSpecular();
		bool IsEnabled();

	protected:
		glm::vec3 ambient;
		float ambientStrength;
		glm::vec3 diffuse;
		glm::vec3 specular;
		bool enabled;

		uint _uniformColorLight;
		uint _uniformPositionLight;
		uint _uniformAmbient;
		uint uniformDiffuse;
		uint uniformSpecular;
		uint uniformEnabled;
	};


#endif // !LIGHT_H
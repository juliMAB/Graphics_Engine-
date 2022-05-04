#ifndef LIGHT_H
#define LIGHT_H

#include "../Exports/Exports.h"
#include "../Entity/Entity.h"
#include "../glm/ext/matrix_transform.hpp"
#include "../Juli/Jinterface.h"


	class GraficosEngine_API Light : public Entity
	{
	public:
		Light();
		Light(Renderer* render);

		//void  SetUniforms();
		void virtual SetUniforms(std::string name);
		void virtual UpdateLight();

		~Light();


		void SetAmbient(glm::vec3 ambient);
		void SetDiffuse(glm::vec3 diffuse);
		void SetSpecular(glm::vec3 specular);

		glm::vec3 GetAmbient();
		glm::vec3 GetDiffuse();
		glm::vec3 GetSpecular();

	protected:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		uint _uniformAmbient;
		uint _uniformDiffuse;
		uint _uniformSpecular;
	};


#endif // !LIGHT_H
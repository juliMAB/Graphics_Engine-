#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Exports/Exports.h"
#include "../Renderer/Renderer.h"
#include "../glm/ext/matrix_transform.hpp"


	class GraficosEngine_API Material
	{
	public:
		Material(Renderer* render);
		~Material();

		void Init();
		void UpdateShader();

		void SetShininess(float shininess);
		void SetAmbient(glm::vec3 ambient);
		void SetDiffuse(glm::vec3 diffuse);
		void SetSpecular(glm::vec3 specular);

		float GetShininess();
		glm::vec3 GetAmbient();
		glm::vec3 GetDiffuse();
		glm::vec3 GetSpecular();

	private:
		Renderer* render;

		float shininess;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		uint uniformShininess;
		uint uniformAmbient;
		uint uniformDiffuse;
		uint uniformSpecular;
	};


#endif // !MATERIAL_H
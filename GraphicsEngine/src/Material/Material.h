#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Exports/Exports.h"
#include "../Renderer/Renderer.h"
#include "../glm/ext/matrix_transform.hpp"

struct MaterialS
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float Shiness;
};

	class GraficosEngine_API Material
	{
	public:
		Material(Renderer* render);
		~Material();

		void Init();
		void UpdateMaterial();

		void SetShininess(float shininess);
		void SetAmbient(glm::vec3 ambient);
		void SetDiffuse(glm::vec3 diffuse);
		void SetSpecular(glm::vec3 specular);
		void SetMaterial(MaterialS mat);

		float GetShininess();
		glm::vec3 GetAmbient();
		glm::vec3 GetDiffuse();
		glm::vec3 GetSpecular();

	private:
		Renderer* render;
		MaterialS material;

		bool useMaterial;

		uint _uniformUseMaterial;

		uint _uniformShininess;
		uint _uniformAmbient;
		uint _uniformDiffuse;
		uint _uniformSpecular;
	};


#endif // !MATERIAL_H

#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Exports/Exports.h"
#include "../Renderer/Renderer.h"
#include "../GLM/vec3.hpp"

	typedef unsigned int uint;
	class GraficosEngine_API  Material {
		float _specularIntensity;
		float _shininess;
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;

		uint _uniformShininess;
		uint _uniformAmbient;
		uint _uniformDiffuse;
		uint _uniformSpecular;

		Renderer* _renderer;
	public:
		Material(Renderer* rend);
		~Material();
		void SetAmbient(glm::vec3 amb);
		void SetDiffuse(glm::vec3 diff);
		void SetSpecular(glm::vec3 spec);
		void SetShininess(float s);
		glm::vec3 GetAmbient();
		glm::vec3 GetDiffuse();
		glm::vec3 GetSpecular();
		float GetShininess();
		uint GetUniformShininess();
		uint GetUniformAmbient();
		uint GetUniformDiffuse();
		uint GetUniformSpecular();
	};


#endif
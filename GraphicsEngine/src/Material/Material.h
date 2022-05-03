#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Exports/Exports.h"
#include "../Renderer/Renderer.h"
#include "../glm/ext/matrix_transform.hpp"
#include "../Texture/Texture.h"

struct MaterialS
{
	Texture* specular;
	Texture* diffuse;
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
		void SetDiffuse(Texture* diffuse);
		void SetSpecular(Texture* specular);
		void SetMaterial(MaterialS* mat);

		float GetShininess();
		Texture* GetDiffuse();
		Texture* GetSpecular();

	private:
		Renderer* render;
		MaterialS* material;

		bool useMaterial;

		uint _uniformUseMaterial;

		uint _uniformShininess;
		uint _uniformDiffuse;
		uint _uniformSpecular;
	};


#endif // !MATERIAL_H

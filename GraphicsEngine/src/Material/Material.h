#ifndef MATERIAL_H
#define MATERIAL_H

#include "Exports/Exports.h"
#include "Renderer/Renderer.h"
#include "GLM/ext/matrix_transform.hpp"
#include "Texture/MyTexture.h"

struct MaterialS
{
	MyTexture* specular;
	MyTexture* diffuse;
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
		void SetDiffuse(MyTexture* diffuse);
		void SetSpecular(MyTexture* specular);
		void SetMaterial(MaterialS* mat);

		float GetShininess();
		MyTexture* GetDiffuse();
		MyTexture* GetSpecular();

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

#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "../Exports/Exports.h"
#include "../Entity2/Entity2.h"
#include "../Material/Material.h"
#include "../Entity/vertexs.h"
#include <Juli\Jinterface.h>
namespace JuliEngine
{

	class GraficosEngine_API Entity2D : public Entity2 {
	public:
		void Draw();
	
		Entity2D(Renderer* render);
		~Entity2D();

		void SetMateria(MaterialS* mat);
		void UpdateMaterial();


		//color::RGBA _color;
		void AffectedLight(bool value);

	protected:
		Material* _material;

		uint _VAO, _VBO, _EBO, tam, vertices;
		float* vertexs;


		bool useTexture;
		bool useLightMaps;
		bool useMaterial;
		bool affectedLight;

		void SetUniforms();
		void UpdateShader();
	private:
	};
}
	


#endif
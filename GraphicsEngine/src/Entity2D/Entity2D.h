#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "../Exports/Exports.h"
#include "../Entity/Entity.h"
#include "../Material/Material.h"
#include "../Entity/vertexs.h"

class GraficosEngine_API Entity2D : public Entity {
public:

	bool _hasCollider, _moveable;
	glm::vec3 pivot;
	glm::vec3 colliderSize;
	glm::vec3 GetPivot();
	void InitCollider();

	void Draw();
	
	Entity2D();
	Entity2D(Renderer* render);
	~Entity2D();

	void SetMateria(MaterialS mat, Renderer* rend);

	//color::RGBA color;
	void AffectedLight(bool value);

protected:
	Material* _material;
	uint _uniformColor;
	uint _uniformAlpha;
	uint _uniformUseTexture;
	uint _uniformUseMaterial;
	uint _uniformAffectedLight;
	uint _uniformAmmbient;

	uint _VAO, _VBO, _EBO, tam, vertices;
	float* vertexs;


	bool useTexture;
	bool useMaterial;
	bool affectedLight;

	void SetUniforms();
	void UpdateShader();
private:
};
	


#endif
#ifndef SPRITE_H
#define SPRITE_H
#include "../Texture/Texture.h"
#include "../Exports/Exports.h"
#include "../Entity2D/Entity2D.h"
#include "../Renderer/Renderer.h"
#include <../GLM/glm.hpp>
#include <vector>
#include "../Animation/Animation.h"
class GraficosEngine_API Sprite : public Entity2D {
private:
	Texture* _texture;
	uint bufferPosUVs = 0;
	glm::vec2 baseUVCoords[4];
	std::vector<Animation*> animations;
	int lastCoordIndex = 0;

	
	void SetUniforms();
	void DrawTexturePart();
public:
	Sprite(Renderer* render, std::string filePathImage);
	~Sprite();
	void SetSprite(const std::string path);
	void Draw();
	uint GetCurrentTextureIDToDraw();
	void BindCustomUVCoords(int i);
	void BindBaseUVCoords();

	
};

#endif

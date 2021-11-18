#ifndef SPRITE_H
#define SPRITE_H
#include "../Texture/Texture.h"
#include "../Exports/Exports.h"
#include "../Entity2D/Entity2D.h"
#include "../Renderer/Renderer.h"
#include <../GLM/glm.hpp>
class GraficosEngine_API Sprite : public Entity2D {
private:
	Texture* _texture;
	glm::vec2 _pos;
	glm::vec2 _size;
	uint bufferPosUVs = 0;
public:
	Sprite(Renderer* render, std::string filePathImage);
	~Sprite();
	void SetSprite(const std::string path);
	void Draw();
	
};

#endif

#ifndef SPRITE_H
#define SPRITE_H
#include "../Texture/Texture.h"
#include "../Exports/Exports.h"
#include <../GLM/glm.hpp>
class GraficosEngine_API Sprite {
private:
	Texture* texture;
	glm::vec2 _pos;
	glm::vec2 _size;
public:
	Sprite();
	~Sprite();
	void SetSprite();
	
};

#endif

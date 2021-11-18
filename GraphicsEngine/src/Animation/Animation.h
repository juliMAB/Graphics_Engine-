#ifndef ANIMATION_H
#define ANIMATION_H
#include "../Exports/Exports.h"
#include <vector>
#include "../GLM/glm.hpp"
#include "../GLM/gtc/matrix_transform.hpp"
#include "../GLM/gtc/type_ptr.hpp"
#include "../Atlas/Atlas.h"
#include "../Texture/Texture.h"
#include "../Time/Time.h"

class GraficosEngine_API Animation {
public:
	Animation();
	~Animation();
	void SetAnimation();
	bool Update();
	void setAnimation(Texture* animationAtlasData, int columns, int rows);
	bool playing = false;
	glm::vec2* getCurrentFramesCoordinates();
	Texture* GetTexture();
private:
	std::vector<glm::vec2*> framesCoordinates;
	Texture* texture;
	int _actualFrame = 0;
	float _time = 0;
	float _frameTime= 1.f;
	float _speed = 1.f;
	bool repeat = false;
};


#endif

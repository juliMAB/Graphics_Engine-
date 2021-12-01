#ifndef SPRITE_H
#define SPRITE_H
#include "../Texture/Texture.h"
#include "../Exports/Exports.h"
#include "../Entity2D/Entity2D.h"
#include "../Renderer/Renderer.h"
#include <../GLM/glm.hpp>
#include <vector>
#include "../Animation/Animation.h"

enum class ORDER
{
	RIGHTtoLEFT,
	UPtoDOWN
};
class GraficosEngine_API Sprite : public Entity2D {
private:
	
	Texture* _texture;

	Animation* _animation;
	bool _settedAnimsValues;

	void SetUniforms();
	void DrawTexturePart();
public:
	Sprite(Renderer* render, std::string filePathImage);
	void SetAttributers();
	void Init(Renderer* render, std::string filePathImage);
	void InitBinds();
	~Sprite();
	void SetSprite(const std::string path);
	void SetShader();
	void Draw();
	void StartUseAnimation();

	void StartUseAnimation(int rows, int cols, float duration);

	void StartUseAnimation(int rows, int cols, float duration, ORDER o);

	void AddAnimation(int rows, int cols, float duration);

	void AddAnimation(int rows, int cols, float duration, ORDER o);

	void UpdateAnimation(float timer);
	
};

#endif

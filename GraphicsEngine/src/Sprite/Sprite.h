#ifndef SPRITE_H
#define SPRITE_H
#include "../Texture/Texture.h"
#include "../Exports/Exports.h"
#include "../Entity2D/Entity2D.h"
#include "../Renderer/Renderer.h"
#include <../GLM/glm.hpp>
#include <vector>
#include "../Animation/Animation.h"
#include "../Atlas/Atlas.h"

enum class ORDER
{
	RIGHTtoLEFT,
	UPtoDOWN
};
const int tamVerts = 32;//4 * tam1Vert;
class GraficosEngine_API Sprite : public Entity2D {
private:
	Texture* _texture;
	float vertex[tamVerts]
	{
		// positions             colors                 texture coords
		0.5f, 0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, // DownRight
		0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, // TopRight
	   -0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, // TopLeft
	   -0.5f, 0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f  //  DownLeft
	};
	Animation* _animation;
	int animIndex = 0;
	bool _settedAnimsValues;

	void SetUniforms();

	std::vector<Animation*> anim;
public:
	Sprite(Renderer* render, std::string filePathImage,bool flip);
	void SetAttributers();
	void AddAnimation(Atlas atlas, float speed);
	void Init(Renderer* render, std::string filePathImage, bool flip);
	void FlipHorizontal();
	void FlipVertical();
	void InitBinds();
	void ChangeAnimation(int index);
	void SetTexture(Frame f);
	~Sprite();
	void SetSprite(const std::string path, bool flip);
	void SetShader();
	void Draw();
	void StartUseAnimation();

	void StartUseAnimation(int rows, int cols, float duration);

	void StartUseAnimation(int rows, int cols, float duration, ORDER o);

	void SetAnimations(int rows, int cols, float duration);

	void SetAnimations(int rows, int cols, float duration, ORDER o);

	void UpdateAnimation(float timer);

	void UpdateAnimation2(float timer);

	void UpdateAnimation(float timer, int action);

	int SetAction(int firtsFrame, int lastFrame);
	
};

#endif

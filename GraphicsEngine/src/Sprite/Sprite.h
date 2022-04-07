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
#include "../Entity/vertexs.h"

enum class ORDER
{
	RIGHTtoLEFT,
	UPtoDOWN
};

enum class SPRITE_TYPE
{
	QUAD,
	CUBE
};
const int tamVerts = 32;//4 * tam1Vert;
class GraficosEngine_API Sprite : public Entity2D {
private:
	SPRITE_TYPE type;
	Texture* _texture;
	uint uniformTexture;
	uint _UVB;

	int animIndex = 0;
	std::vector<Animation*> anim;
	Frame currFrame;
	bool transparent;

	void SetUniforms();

	//__________________________
	float vertex[tamVerts]
	{
		// positions             colors                 texture coords
		0.5f, 0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, // DownRight
		0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, // TopRight
	   -0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, // TopLeft
	   -0.5f, 0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f  //  DownLeft
	};
	Animation* _animation;
	bool _settedAnimsValues;

	//std::vector<Animation*> anim;
public:
	Sprite();
	Sprite(Renderer* render);
	~Sprite();

	void Init(SPRITE_TYPE type);
	void Update(float timer);
	void Draw();
	void DeInit();

	void SetTexture(Texture* texture);
	void LoadTexture(const char* path, bool invertImage);
	void AddAnimation(Atlas atlas, float speed);
	void AddAnimation(int rows, int cols, float duration);
	void ChangeAnimation(int index);
	void SetTextureCoordinates(Frame f);

	void SetTransparent(bool transparent);
	bool GetTransparent();




	//----------------------------
	/*Sprite();
	~Sprite();


	Sprite(Renderer* render, std::string filePathImage,bool flip);
	void SetAttributers();
	void AddAnimation(Atlas atlas, float speed);
	void Init(Renderer* render, std::string filePathImage, bool flip);
	void SetTexture(std::string filePathImage, bool flip);
	void SetTexture(Texture* tex);
	void setTextureCoordinates(float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);
	void FlipHorizontal();
	void FlipVertical();
	void InitBinds();
	void ChangeAnimation(int index);
	void SetTexture(Frame f);
	void SetSprite(const std::string path, bool flip);
	void SetShader();
	void Draw(Renderer* rend);
	void Draw();
	void StartUseAnimation();

	void Deinit();

	void StartUseAnimation(int rows, int cols, float duration);

	void StartUseAnimation(int rows, int cols, float duration, ORDER o);

	void SetAnimations(int rows, int cols, float duration);

	void SetAnimations(int rows, int cols, float duration, ORDER o);

	void UpdateAnimation(float timer);

	void UpdateAnimation2(float timer);

	void UpdateAnimation(float timer, int action);

	int SetAction(int firtsFrame, int lastFrame);

	void Init(Renderer* render, Texture* tx);*/
	
};

#endif

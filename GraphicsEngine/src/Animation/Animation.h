#ifndef ANIMATION_H
#define ANIMATION_H

#include "../Exports/Exports.h"
#include <vector>

struct UVCords
{
	float u, v;
};

class GraficosEngine_API Frame
{
public:
	Frame();
	~Frame();
	UVCords* GetUVCords();

private:
	UVCords uvcords[4];
};
class GraficosEngine_API Animation
{
public:
	Animation();
	~Animation();

	void Update(float timer);
	void AddFrame(float frameX, float frameY, float frameWidth, float frameHeight,
		float textureWidth, float textureHeight, float duration);
	void AddFrame2(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float duration);
	int GetCurrentFrame();
	std::vector<Frame> GetFrames();

private:
	float currentTime;
	int currentFrame;
	float length;
	std::vector<Frame> frames;
};

	



#endif // !ANIMATION_H
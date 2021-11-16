#ifndef TIME_H
#define TIME_H
#include "../Exports/Exports.h"
static class GraficosEngine_API Time {
private:
	float _deltaTime;
	float _unscaleDeltaTime;
	float _scale;
	float _onTime;

public:
	Time();
	~Time();
	void Update();
	float GetDeltaTime();
	float GetTime();
	
	float GetScale();
	void SetScale(float scale4);
};


#endif
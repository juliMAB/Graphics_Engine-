#ifndef TIME_H
#define TIME_H
#include "../Exports/Exports.h"
class GraficosEngine_API Time {
private:
	float _unscaleDeltaTime;
	float _scale;
	float _onTime;

public:
	static float _deltaTime;
	Time();
	~Time();
	void Update();
	float GetTime();
	static float GetDeltaTime();
	
	float GetScale();
	void SetScale(float scale4);
};


#endif
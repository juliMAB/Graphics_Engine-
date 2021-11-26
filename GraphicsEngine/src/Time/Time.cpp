#include "Time.h"
#include <time.h>
#include <iostream>
float Time::_deltaTime = 0;
Time::Time() {
	_unscaleDeltaTime = 0;
	_scale = 1;
	_onTime = 0;
}
Time::~Time() {
	
}
void Time::Update() {
	float lastTime = _onTime;
	_onTime = glfwGetTime();
	_deltaTime = (_onTime - lastTime) * _scale;
	_unscaleDeltaTime = _deltaTime;
}
float Time::GetTime() {
	return _onTime;
}
double oldT = clock();
float Time::GetDeltaTime()
{
	double t = clock();
	float dt = (float)((t - oldT) / 1000.0f);
	oldT = t;
	return dt;
}
float Time::GetScale() {
	return _scale;
}
void Time::SetScale(float scale4) {
	_scale = scale4;
}
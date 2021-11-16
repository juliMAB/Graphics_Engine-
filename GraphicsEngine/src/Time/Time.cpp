#include "Time.h"
Time::Time() {
	_deltaTime = 0;
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
float Time::GetDeltaTime() {
	return _deltaTime;
}
float Time::GetTime() {
	return _onTime;
}
float Time::GetScale() {
	return _scale;
}
void Time::SetScale(float scale4) {
	_scale = scale4;
}
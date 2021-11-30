#include "Time.h"
#include <time.h>
#include <iostream>
float Time::_deltaTime = 0;
Time::Time() {
	_unscaleDeltaTime = 0;
	_scale = 1;
	_lastTime = glfwGetTime();
}
Time::~Time() {}
void Time::Update() {
	double actualTime = glfwGetTime();
	_unscaleDeltaTime = (actualTime - _lastTime)/1000.0f;
	_deltaTime = _unscaleDeltaTime * _scale;
}
void Time::SetScale(float scale) {
	_scale = scale;
}
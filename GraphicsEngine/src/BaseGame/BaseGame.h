#ifndef GAMEBASE_H
#define GAMEBASE_H
#include "Juli/Jinterface.h"
#include "Window/Window.h"

class GraficosEngine_API BaseGame {
private:
	bool InitEngine(int windowSizeX, int windowSizeY, std::string windowName);
	void DeinitEngine();
protected:
	Window* _window;
public:
	//----------C y D------------
	BaseGame();
	~BaseGame();
	//-----------Main Loop-------
	int Init(int width, int heigth, const char* title);
	bool IsRunning();
	void Deinit();
	void ClearClolor();
	void EndDraw();
	void EndUpdate();
	//---------------------------
	bool InitGlew();
	bool InitWindow(int windowSizeX, int windowSizeY, std::string windowName);
	double getCurrentTime();
	// --------------------
};
#endif
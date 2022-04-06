#ifndef GAMEBASE_H
#define GAMEBASE_H
#include "../Renderer/Renderer.h"
#include "../Input/Input.h"
#include "../Shape/Shape.h"
#include "../Sprite/Sprite.h"
#include "../Time/Time.h"
#include "../Collision/Collision.h"
#include "../Tile/TileMap.h"
#include "../Camera/Camera.h"
#include "../Juli/Jinterface.h"
class GraficosEngine_API BaseGame {
private:
	Window* _window;
	Renderer* _renderer;
	Input* _input;
	void DeinitEngine();
	Window* GetWindow();
	bool InitEngine(int windowSizeX, int windowSizeY, std::string windowName);
protected:
	Time* _time;
	Camera* _mainCamera;
	glm::vec4 backgroundColor;
public:
	Renderer* GetRenderer();
	void ChangeBackgeound();
	//----------C y D------------
	BaseGame();
	~BaseGame();
	//-----------Main Loop-------
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Deinit() = 0;
	//---------------------------
	void StartDraw();
	void EndDraw();
	int StartEngine(int width, int height, const char* windowName);
	bool IsKeyDown(Input::KeyCode key);
	bool IsKeyRelease(Input::KeyCode key);
	bool IsKeyUp(Input::KeyCode key);
	void InitInput();
	void InitCamera();
	double getCurrentTime();
	// --------------------
};
#endif
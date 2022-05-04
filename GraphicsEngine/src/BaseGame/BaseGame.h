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
#include "../LightManager/lightManager.h"
#include "../ImGui/MyImGui.h"
class GraficosEngine_API BaseGame {
private:
	Input* _input;
	void DeinitEngine();
	Window* GetWindow();
	bool InitEngine(int windowSizeX, int windowSizeY, std::string windowName);
	bool imGuiEnabled= false;
protected:
	Window* _window;
	Renderer* _renderer;
	Time* _time;
	Camera* _mainCamera;
	MyImGui* _imgur;
	//glm::vec4 backgroundColor;
public:
	Renderer* GetRenderer();
	//----------C y D------------
	BaseGame();
	~BaseGame();
	//-----------Main Loop-------
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Deinit() = 0;
	//---------------------------
	int StartEngine(int width, int height, const char* windowName);
	bool IsKeyDown(Input::KeyCode key);
	bool IsKeyRelease(Input::KeyCode key);
	bool IsKeyUp(Input::KeyCode key);
	bool InitGlew();
	void InitImgur();
	void InitInput();
	void InitCamera();
	bool InitWindow(int windowSizeX, int windowSizeY, std::string windowName);
	void InitRender();
	void InitTime();
	double getCurrentTime();
	// --------------------
	void SetBackGroundColor(color::RGBA color);
};
#endif
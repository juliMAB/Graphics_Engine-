#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "../Exports/Exports.h"
#include "../Window/Window.h"
struct GLFWmonitor;



	class GraficosEngine_API GameBase {
		Window* _window;
	public:
		GameBase();
		~GameBase();

		int StartEngine();
		void UpdateEngine();
		void EndEngine();

		Window* GetWindow();

		virtual void Start() = 0;
		virtual void Update() = 0;
		void virtual End() = 0;
	};



#endif
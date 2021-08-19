#ifndef GAME_H
#define GAME_H
#include "../../../GraphicsEngine/src/BaseGame/BaseGame.h"


	class Game : GameBase {
		
	public:
		Game();
		~Game();
		void Play();
		void Start() override;
		void Update() override;
		void End() override;
	};


#endif
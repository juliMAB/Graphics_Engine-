#ifndef SPRITE_H
#define SPRITE_H
#include "Texture/MyTexture.h"
#include "Exports/Exports.h"
#include "Entity2D/Entity2D.h"
#include "Renderer/Renderer.h"
#include <GLM/glm.hpp>
#include <vector>
#include "Animation/Animation.h"
#include "Atlas/Atlas.h"
#include "Entity/vertexs.h"
namespace JuliEngine
{

	enum class SPRITE_TYPE
	{
		QUAD,
		CUBE
	};
	class GraficosEngine_API Sprite : public Entity2D {
	private:
		SPRITE_TYPE type;
		uint _uniformDiffuseTexture;
		uint _uniformSpecularTexture;
		uint _UVB;

		int animIndex = 0;
		std::vector<Animation*> anim;
		Frame currFrame;

		void SetUniforms();

		//__________________________
		bool _settedAnimsValues;
	public:
		Sprite(Renderer* render);
		~Sprite();

		void Init(SPRITE_TYPE type);
		void Update(float timer);
		void Draw();
		void DeInit();
		void SetTexture(MyTexture* texture);
		void ChangeAnimation(int index);
		void SetTextureCoordinates(Frame f);
	};

}

#endif

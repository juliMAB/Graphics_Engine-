#ifndef SHAPE_H
#define SHAPE_H
#include "../Entity2D/Entity2D.h"

namespace JuliEngine
{
	enum class SHAPE_TYPE
	{
		TRIANGLE,
		QUAD,
		CUBE
	};

	typedef unsigned int uint;
	class GraficosEngine_API Shape : public Entity2D {
	public:
		Shape(Renderer* render);
		~Shape();

		void Init(SHAPE_TYPE shapeType);
		void Draw();
		void DeInit();
	};
}

#endif
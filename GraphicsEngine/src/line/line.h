#ifndef LINE_H
#define LINE_H

#include "Exports/Exports.h"
#include "Vertex/Vertex2.h"

#include "Renderer/renderer.h"

#include <vector>

namespace JuliEngine
{
	class GraficosEngine_API Line
	{
	public:

		Line(Renderer* render);
		Line(std::vector<Vertex2> vertexs, Renderer* render);
		~Line();

		void Init();
		void Draw();
		void DeInit();

		void SetVertexs(std::vector<Vertex2> vertexs);
		std::vector<Vertex2> GetVertexs();

		glm::vec3 color;
	private:
		Renderer* render;

		uint VAO, VBO, EBO;
		std::vector<Vertex2> vertexs;
		std::vector<uint> indexes;

		uint locationPosition;
		uint locationNormal;
		uint uniformColor;
		uint uniformAlpha;

		void UpdateVertexs();
		void SetUniforms();
		void UpdateShader();
	};
}

#endif // !LINE_H
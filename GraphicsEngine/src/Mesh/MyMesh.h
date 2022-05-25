#ifndef MYMESH_H
#define MYMESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "../Renderer/Renderer.h"

class GraficosEngine_API myMesh
{
public:
    std::vector<myVertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<myTexture>      textures;
    unsigned int VAO, VBO, EBO;
    myMesh(std::vector<myVertex> vertices, std::vector<unsigned int> indices, std::vector<myTexture> textures, unsigned int VAO, unsigned int VBO, unsigned int EBO) 
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		this->VAO = VAO;
		this->VBO = VBO;
		this->EBO = EBO;
	}
   
private:
};
#endif
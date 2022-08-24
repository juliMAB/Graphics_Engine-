#ifndef MESH2_H
#define MESH2_H

#include "Vertex/Vertex.h"
#include "Texture2/Texture2.h"
#include "Exports/Exports.h"
#include "Renderer/Renderer.h"
#include <vector>


namespace JuliEngine
{
    class GraficosEngine_API Mesh {
    public:
        // mesh Data
        vector<Vertex >       vertices;
        vector<uint   >       indices ;
        vector<Texture>       textures;
        //  render data
        uint VAO, VBO, EBO;

        Mesh(vector<Vertex> vertices, vector<uint> indices, vector<Texture> textures)
        {
                this->vertices = vertices;
                this->indices  = indices ;
                this->textures = textures;
                setupMesh();
        }
        void Draw(Renderer* render);
    private:
        void setupMesh();
    };
}

#endif
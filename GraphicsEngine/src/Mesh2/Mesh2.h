#ifndef MESH2_H
#define MESH2_H

#include "Vertex/Vertex2.h"
#include "Texture2/Texture2.h"
#include "Entity2/Entity2.h"
#include <vector>


namespace JuliEngine
{
    class GraficosEngine_API Mesh2 {
    public:
        // mesh Data
        vector<Vertex2>       vertices;
        vector<unsigned int> indices;
        vector<Texture2>      textures;
        unsigned int VAO, VBO, EBO;
        Renderer* _rend;

        // constructor
        Mesh2(vector<Vertex2> vertices, vector<unsigned int> indices, vector<Texture2> textures, Renderer* rend)
        {
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;
            this->_rend = rend;

            // now that we have all the required data, set the vertex buffers and its attribute pointers.
            setupMesh();
        }
        //~Mesh2(){}
        // render the mesh
        void Draw();

    private:
        // initializes all the buffer objects/arrays
        void setupMesh();
    };
}

#endif
#ifndef MODEL_H
#define MODEL_H

#include "Mesh2/Mesh2.h"
#include "Collision/AABB.h"
#include <list>
using namespace std;
namespace JuliEngine 
{
    class GraficosEngine_API Model2 : public Entity2
    {
    public:
        // model data 
        vector<Texture2> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        vector<MeshData>    meshesData;
        list<Mesh2*>    meshes;
        list<Entity2*>  nodes;
        string directory;
        bool gammaCorrection = false;
        static list<Model2*> listModel;

        // constructor, expects a filepath to a 3D model.
        Model2(Renderer* render, bool gamma) : Entity2(render)
        {
            listModel.push_back(this);
            setModelPtr(this);
        }
        //draws the model, and thus all its meshes
        void Draw();
        list<Mesh2*> GetMeshes() { return meshes; };
        friend class MyImGui;
        void generateAABB();

        void drawSelfAndChild(Frustum& frustum);
        
        
    };
}



#endif
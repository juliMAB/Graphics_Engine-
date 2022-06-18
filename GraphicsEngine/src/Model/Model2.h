#ifndef MODEL_H
#define MODEL_H

#include "Mesh2/Mesh2.h"

using namespace std;
namespace JuliEngine 
{
    class GraficosEngine_API Model2 : public Entity2
    {
    public:
        // model data 
        vector<Texture2> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        vector<Mesh2>    meshes;
        string directory;
        bool gammaCorrection = false;

        // constructor, expects a filepath to a 3D model.
        Model2(Renderer* render, bool gamma) : Entity2(render)
        {}

        // draws the model, and thus all its meshes
        void Draw()
        {
            getRender()->UpdateMVP(getTransform().getmodel());
            for (unsigned int i = 0; i < meshes.size(); i++)
                meshes[i].Draw();
        }
        vector<Mesh2> GetMeshes() { return meshes; };      
    };
}



#endif
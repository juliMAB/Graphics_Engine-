#ifndef MODEL_H
#define MODEL_H

#include "Mesh2/Mesh2.h"
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
        string directory;
        bool gammaCorrection = false;

        // constructor, expects a filepath to a 3D model.
        Model2(Renderer* render, bool gamma) : Entity2(render)
        {}

        // draws the model, and thus all its meshes
        void Draw()
        {
            if (getactive())
            {

                //getRender()->UpdateMVP((*it)->getTransform()->getmodel());
            
                for (std::list<Mesh2*>::iterator it = meshes.begin(); it != meshes.end(); it++)
                {
                    (*it)->Draw();
                    getRender()->UpdateMVP((**it).getTransform()->getmodel());
                }
            }
        }
        list<Mesh2*> GetMeshes() { return meshes; };
    };
}



#endif
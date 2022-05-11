/*
        Copyright 2011 Etay Meiri
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BASIC_MESH_H
#define BASIC_MESH_H

#include <map>
#include <vector>
//#include <GL/glew.h>
#include "../GLEW/glew.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include "../Exports/Exports.h"

//#include "ogldev_util.h"
//#include "ogldev_math_3d.h"
//#include "ogldev_texture.h"
//#include "ogldev_world_transform.h"
//#include "ogldev_material.h"

class GraficosEngine_API IRenderCallbacks
{
public:
    virtual void DrawStartCB(uint DrawIndex) = 0;
};


class GraficosEngine_API BasicMesh
{
public:
    BasicMesh() {};

    ~BasicMesh() {};

private:

};


#endif  /* OGLDEV_BASIC_MESH_H */
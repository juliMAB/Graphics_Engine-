#ifndef VERTEX2
#define VERTEX2
    #include <glm/glm.hpp>
namespace JuliEngine
{
    using namespace std;

    #define MAX_BONE_INFLUENCE 4

    struct Vertex2 {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        //glm::vec3 Tangent;
        // bitangent
        //glm::vec3 Bitangent;
        //bone indexes which will influence this vertex
        //int m_BoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        //float m_Weights[MAX_BONE_INFLUENCE];
    };




	const int cube2IndexTam = 36;
	static unsigned int cube2Indexes[cube2IndexTam]
	{
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};
}

#endif // !VERTEX

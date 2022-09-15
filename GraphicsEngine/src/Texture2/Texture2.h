#ifndef TEXTURE2
#define TEXTURE2
#include <string>
namespace JuliEngine
{
    struct Texture{
        unsigned int id;
        float width;
        float height;
        std::string type;
        std::string path;
    };
}
#endif
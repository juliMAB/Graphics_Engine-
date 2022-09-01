#ifndef AABB_H
#define AABB_H
#include "BoundingVolume/BoundingVolume.h"
#include <array>
namespace JuliEngine
{
	class GraficosEngine_API aabb : public volume
	{
	public:
		aabb();
		aabb(glm::vec3 min, glm::vec3 max);
		aabb(glm::vec3 center, float extX, float extY, float extZ);
		~aabb();

		bool isOnFrustum(glm::mat4 worldModel) override;

		glm::vec3 center;
		glm::vec3 extents;
		bool isOnPlane(plane plane) override;
	private:
	};
}
#endif // !aabb

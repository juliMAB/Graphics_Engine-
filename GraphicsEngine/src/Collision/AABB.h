#ifndef AABB_H
#define AABB_H
#include "BoundingVolume/BoundingVolume.h"
#include "Model/Model2.h"
#include <array>
namespace JuliEngine
{
	struct AABB : public BoundingVolume
	{
		glm::vec3 center{ 0.f, 0.f, 0.f };
		glm::vec3 extents{ 0.f, 0.f, 0.f };

		AABB(glm::vec3& min, glm::vec3& max)
			: BoundingVolume{}, center{ (max + min) * 0.5f }, extents{ max.x - center.x, max.y - center.y, max.z - center.z }
		{}

		AABB(glm::vec3& inCenter, float iI, float iJ, float iK)
			: BoundingVolume{}, center{ inCenter }, extents{ iI, iJ, iK }
		{}

		std::array<glm::vec3, 8> getVertice() 
		{
			std::array<glm::vec3, 8> vertice;
			vertice[0] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
			vertice[1] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
			vertice[2] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
			vertice[3] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
			vertice[4] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
			vertice[5] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
			vertice[6] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
			vertice[7] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };
			return vertice;
		}

		//see https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plan.html
		bool isOnOrForwardPlan(Plan& plan)
		{
			// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
			const float r = extents.x * std::abs(plan.normal.x) + extents.y * std::abs(plan.normal.y) +
				extents.z * std::abs(plan.normal.z);

			return -r <= plan.getSignedDistanceToPlan(center);
		}

		bool isOnFrustum(Frustum& camFrustum, Transform& transform)
		{
			//Get global scale thanks to our transform
			glm::vec3 globalCenter{ transform.getModelMatrix() * glm::vec4(center, 1.f) };

			// Scaled orientation
			glm::vec3 right = transform.getRight() * extents.x;
			glm::vec3 up = transform.getUp() * extents.y;
			glm::vec3 forward = transform.getForward() * extents.z;

			float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
				std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
				std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

			float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
				std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
				std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

			float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
				std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
				std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

			AABB globalAABB(globalCenter, newIi, newIj, newIk);

			return (globalAABB.isOnOrForwardPlan(camFrustum.leftFace) &&
				globalAABB.isOnOrForwardPlan(camFrustum.rightFace) &&
				globalAABB.isOnOrForwardPlan(camFrustum.topFace) &&
				globalAABB.isOnOrForwardPlan(camFrustum.bottomFace) &&
				globalAABB.isOnOrForwardPlan(camFrustum.nearFace) &&
				globalAABB.isOnOrForwardPlan(camFrustum.farFace));
		};
	};
	AABB generateAABB(Model2& model)
	{
		glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
		glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());

		for (std::list<Mesh2*>::iterator it = model.meshes.begin(); it != model.meshes.end(); it++)
		{
			MeshData* data = (**it).data;
			for (auto&& vertex : data->vertices)
			{
				minAABB.x = std::min(minAABB.x, vertex.Position.x);
				minAABB.y = std::min(minAABB.y, vertex.Position.y);
				minAABB.z = std::min(minAABB.z, vertex.Position.z);

				maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
				maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
				maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
			}
		}
		return AABB(minAABB, maxAABB);
	}
}
#endif // !AABB

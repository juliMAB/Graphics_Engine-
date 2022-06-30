#ifndef PLAN_H
#define PLAN_H
#include "GLM/glm.hpp"
namespace JuliEngine
{

	struct Plan
	{
		glm::vec3 normal = { 0.f, 1.f, 0.f }; // unit vector
		float     distance = 0.f;        // Distance with origin

		Plan() = default;

		Plan(const glm::vec3& p1, const glm::vec3& norm)
			: normal(glm::normalize(norm)),
			distance(glm::dot(normal, p1))
		{}

		float getSignedDistanceToPlan(const glm::vec3& point) const
		{
			return glm::dot(normal, point) - distance;
		}
	};
}
#endif // !PLAN_H

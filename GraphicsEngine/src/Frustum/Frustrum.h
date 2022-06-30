#ifndef FRUSTRUM_H
#define FRUSTRUM_H
#include "Plan/Plan.h"
#include "Transform/Transform.h"
namespace JuliEngine
{
	struct Frustum
	{
		Plan topFace;
		Plan bottomFace;

		Plan rightFace;
		Plan leftFace;

		Plan farFace;
		Plan nearFace;

		Frustum(Transform* cam, float aspect, float fovY, float zNear, float zFar)
		{
			float halfVSide = zFar * tanf(fovY * .5f);
			float halfHSide = halfVSide * aspect;
			glm::vec3 frontMultFar = zFar * cam->getForward();
			nearFace =   { cam->getposition() + zNear * cam->getForward(), cam->getForward()					};
			farFace =    { cam->getposition() + frontMultFar, -cam->getForward()									};
			rightFace =  { cam->getposition(), glm::cross(cam->getUp(), frontMultFar + cam->getRight() * halfHSide) };
			leftFace =   { cam->getposition(), glm::cross(frontMultFar - cam->getRight() * halfHSide, cam->getUp()) };
			topFace =    { cam->getposition(), glm::cross(cam->getRight(), frontMultFar - cam->getUp() * halfVSide) };
			bottomFace = { cam->getposition(), glm::cross(frontMultFar + cam->getUp() * halfVSide, cam->getRight()) };
		}
	};
}
#endif // !FRUSTRUM_H

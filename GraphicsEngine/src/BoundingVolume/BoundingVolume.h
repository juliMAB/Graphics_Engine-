#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H
#include "Frustum/Frustrum.h"
#include "Transform/Transform.h"
namespace JuliEngine
{
	struct BoundingVolume
	{
		virtual bool isOnFrustum(Frustum* camFrustum, Transform* transform) = 0;

		virtual bool isOnOrForwardPlan(Plan plan) = 0;

		bool isOnFrustum(Frustum* camFrustum)
		{
			return (isOnOrForwardPlan	(camFrustum->leftFace) &&
				isOnOrForwardPlan		(camFrustum->rightFace) &&
				isOnOrForwardPlan		(camFrustum->topFace) &&
				isOnOrForwardPlan		(camFrustum->bottomFace) &&
				isOnOrForwardPlan		(camFrustum->nearFace) &&
				isOnOrForwardPlan		(camFrustum->farFace));
		};
	};
}
#endif // !BOUNDINGVOLUME_H

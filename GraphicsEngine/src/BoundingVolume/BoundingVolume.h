#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H
#include "Frustum/Frustrum.h"
#include "Transform/Transform.h"
#include <line/line.h>
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
		Line* lines;
	};
}
#endif // !BOUNDINGVOLUME_H

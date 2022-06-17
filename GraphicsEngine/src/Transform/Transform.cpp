#include "Transform.h"
namespace JuliEngine
{
	
	vec3 QuatToVec(glm::quat quat, glm::vec3 vec)
	{
		float x2 = quat.x * 2.f;
		float y2 = quat.y * 2.f;
		float z2 = quat.z * 2.f;
		float xx2 = quat.x * x2;
		float yy2 = quat.y * y2;
		float zz2 = quat.z * z2;
		float xy2 = quat.x * y2;
		float xz2 = quat.x * z2;
		float yz2 = quat.y * z2;
		float wx2 = quat.w * x2;
		float wy2 = quat.w * y2;
		float wz2 = quat.w * z2;

		glm::vec3 res;
		res.x = (1.f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
		res.y = (xy2 + wz2) * vec.x + (1.f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
		res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.f - (xx2 + yy2)) * vec.z;
		return res;
	}

	quat EulerToQuat(vec3 euler)
	{
		float deg2rad = (3.14f * 2.0f) / 360.0f;
		euler *= deg2rad;

		float cy = cos(euler.z * 0.5);
		float sy = sin(euler.z * 0.5);
		float cp = cos(euler.x * 0.5);
		float sp = sin(euler.x * 0.5);
		float cr = cos(euler.y * 0.5);
		float sr = sin(euler.y * 0.5);

		glm::quat q;
		q.w = cr * cp * cy + sr * sp * sy;
		q.x = cr * sp * cy + sr * cp * sy;
		q.y = sr * cp * cy - cr * sp * sy;
		q.z = cr * cp * sy - sr * sp * cy;
		return q;
	}

	Transform::Transform(GameObject* gameObject) : Component(this,gameObject)
	{
		 position = vec3(0,0,0);
		 localPosition = vec3(0,0,0);
		 eulerAngles = vec3(0,0,0);
		 right = vec3(1,0,0);
		 up = vec3(0,1,0);
		 forward = vec3(0,0,1);
		 rotation = quat(0,0,0,1);
		 localRotation = quat(0, 0, 0, 1);
		 localScale = vec3(1);
		 lossyScale = vec3(1);
		 parent = nullptr;
		 worldToLocalMatrix = mat4(1);
		 localToWorldMatrix = mat4(1);
		 baseMatrix = mat4(1);
		 translate  = mat4(1);
		 rotationX  = mat4(1);
		 rotationY  = mat4(1);
		 rotationZ  = mat4(1);
		 scale      = mat4(1);
		childs = list<Transform*>();
		setWMatrixTranslate();
		baseRotation(eulerAngles);
		updateTransformRotation();
		updateMatrix();
		AddDescription("-> ||Transform|| ");
	}

	Transform::~Transform()
	{
		if (childs.size()>0)
		{
			for (std::list<Transform*>::iterator it = childs.begin(); it != childs.end(); it++)
				delete *it;
			childs.clear();
		}
	}

	void Transform::updateTransformRotation()
	{
		rotation = EulerToQuat(eulerAngles);
		forward = QuatToVec(rotation, vec3(0.f, 0.f, 1.f));
		up = QuatToVec(rotation, vec3(0.f, 1.f, 0.f));
		right = QuatToVec(rotation, vec3(1.f, 0.f, 0.f));
	}
	void Transform::baseRotation(vec3 v)
	{
		localRotation = v;
		eulerAngles = v;
		rotationX = glm::rotate(glm::mat4(1.f), glm::radians(v.x), glm::vec3(1.f, 0.f, 0.f));
		rotationY = glm::rotate(glm::mat4(1.f), glm::radians(v.y), glm::vec3(0.f, 1.f, 0.f));
		rotationZ = glm::rotate(glm::mat4(1.f), glm::radians(v.z), glm::vec3(0.f, 0.f, 1.f));

	}
}

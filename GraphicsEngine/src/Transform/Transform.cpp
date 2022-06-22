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
		 eulerAngles = vec3(0,0,0);
		 localScale = vec3(1);
		 
		 forward = vec3(0,0,1);
		 right = vec3(1,0,0);
		 up = vec3(0,1,0);
		 
		m_modelMatrix = mat4(1);
		
		parent = nullptr;
		childs = list<Transform*>(0);
		
		updateTransformRotation();
		AddDescription("-> ||Transform|| ");
	}

	Transform::~Transform()
	{
	}

	Transform* Transform::getChilds(int v)
	{
		list<Transform*>::iterator it = childs.begin();
		for (int i = 0; i < v; i++)
		{
			it++;
		}
		return *it;
	}

	glm::mat4 Transform::getLocalModelMatrix()
	{
		updateTransformRotation();
		const mat4 transformX = glm::rotate(mat4(1.0f),radians(eulerAngles.x), vec3(1.0f, 0.0f, 0.0f));
		const mat4 transformY = glm::rotate(mat4(1.0f),radians(eulerAngles.y), vec3(0.0f, 1.0f, 0.0f));
		const mat4 transformZ = glm::rotate(mat4(1.0f),radians(eulerAngles.z), vec3(0.0f, 0.0f, 1.0f));
		// Y * X * Z
		const mat4 roationMatrix = transformY * transformX * transformZ;
		// translation * rotation * scale (also know as TRS matrix)
		return glm::translate(glm::mat4(1.0f), position) * roationMatrix * glm::scale4(mat4(1.0f), localScale);
	}

	void Transform::updateTransformRotation()
	{
		quat rotation = EulerToQuat(eulerAngles);
		forward = QuatToVec(rotation, vec3(0.f, 0.f, 1.f));
		up = QuatToVec(rotation, vec3(0.f, 1.f, 0.f));
		right = QuatToVec(rotation, vec3(1.f, 0.f, 0.f));
	}
	void Transform::updateSelfAndChild()
	{
		if (!m_isDirty)
			return;
		forceUpdateSelfAndChild();
	}
	void Transform::computeModelMatrix()
	{
		m_modelMatrix = getLocalModelMatrix();
	}
	void Transform::computeModelMatrix(const glm::mat4& parentGlobalModelMatrix)
	{
		m_modelMatrix = parentGlobalModelMatrix * getLocalModelMatrix();
	}
	void Transform::forceUpdateSelfAndChild()
	{
		if (parent!=NULL)
			computeModelMatrix(parent->getmodel());
		else
			computeModelMatrix();

		for (int i=0;childs.size()>i;i++)
		{
			getChilds(i)->forceUpdateSelfAndChild();
		}
	}
}


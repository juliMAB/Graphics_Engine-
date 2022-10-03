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
	vec3 toEulerRad(glm::quat rot)
	{
		float sqw = rot.w * rot.w;
		float sqx = rot.x * rot.x;
		float sqy = rot.y * rot.y;
		float sqz = rot.z * rot.z;
		float unit = sqx + sqy + sqz + sqw;
		float test = rot.x * rot.w - rot.y * rot.z;

		glm::vec3 v = glm::vec3();

		if (test > 0.4995f * unit)
		{
			v.y = 2.f * atan2(rot.y, rot.x);
			v.x = glm::pi<float>() / 2.f;
			v.z = 0.f;

			return normalizeAngles(v * 57.29578f);
		}
		if (test < -0.4995f * unit)
		{
			v.y = -2.f * atan2(rot.y, rot.x);
			v.x = -glm::pi<float>() / 2.f;
			v.z = 0.f;

			return normalizeAngles(v * 57.29578f);
		}

		glm::vec4 q = glm::vec4(rot.w, rot.z, rot.x, rot.y);
		v.y = atan2(2.f * q.x * q.w + 2.f * q.y * q.z, 1.f - 2.f * (q.z * q.z + q.w * q.w));
		v.x = asin(2.f * (q.x * q.z - q.w * q.y));
		v.z = atan2(2.f * q.x * q.y + 2.f * q.z * q.w, 1.f - 2.f * (q.y * q.y + q.z * q.z));

		return normalizeAngles(v * 57.29578f);
	}
	vec3 normalizeAngles(vec3 angles)
	{
		angles.x = normalizeAngle(angles.x);
		angles.y = normalizeAngle(angles.y);
		angles.z = normalizeAngle(angles.z);

		return angles;
	}
	float normalizeAngle(float angle)
	{
		while (angle > 360.f)
			angle -= 360.f;
		while (angle < 0.f)
			angle += 360.f;

		return angle;
	}
	Transform::Transform() : Component(this)
	{

		worldModel  = mat4(1);
		localModel  = mat4(1);
		parentModel = mat4(1);

		useLocalMatrix = false;

		updateTransformRotation();
		AddDescription("-> ||Transform|| ");
	}
	Transform::Transform(GameObject* gameObject) : Component(this, gameObject)
	{

		worldModel = mat4(1);
		localModel = mat4(1);
		parentModel = mat4(1);

		updateTransformRotation();
		AddDescription("-> ||Transform|| ");
	}
	Transform::Transform(GameObject* gameObject,Entity2* ourEntity) : Component(this,gameObject, ourEntity)
	{
		 
		 worldModel = mat4(1);
		 localModel = mat4(1);
		 parentModel = mat4(1);
		
		updateTransformRotation();
		AddDescription("-> ||Transform|| ");
	}

	Transform::~Transform()
	{
	}

	void Transform::setPos(vec3 v)
	{
		localPos = v;
		matlocalTranslate = glm::translate(glm::mat4(1.0f), localPos);
		updateModelMatrix();
	}

	void Transform::setRot(vec3 v)
	{
		setRotX(v.x);
		setRotY(v.y);
		setRotZ(v.z);
		updateModelMatrix();
	}

	void Transform::setRotRadians(vec3 v)
	{
		setRotX(glm::radians(v.x));
		setRotY(glm::radians(v.y));
		setRotZ(glm::radians(v.z));
		updateModelMatrix();
	}

	void Transform::setScale(vec3 v)
	{
		localScale = localScale;
		this->matlocalScale = glm::scale4(glm::mat4(1.0f), localScale);
		updateModelMatrix();
	}

	void Transform::setWorldModelWithParentModel(glm::mat4 localModel)
	{
		this->parentModel = parentModel;

		updateModelMatrix();
	}

	void Transform::setMatrix(glm::mat4 mat)
	{
		setPos(getPos(mat));
		setRotRadians(getRot(mat));
		setScale(getScale(mat));
	}

	mat4 Transform::getModel()
	{
		return worldModel;
	}

	mat4 Transform::getLocalModel()
	{
<<<<<<< Updated upstream
		updateTransformRotation();
		const mat4 transformX = glm::rotate(mat4(1.0f),radians(m_eulerRot.x), vec3(1.0f, 0.0f, 0.0f));
		const mat4 transformY = glm::rotate(mat4(1.0f),radians(m_eulerRot.y), vec3(0.0f, 1.0f, 0.0f));
		const mat4 transformZ = glm::rotate(mat4(1.0f),radians(m_eulerRot.z), vec3(0.0f, 0.0f, 1.0f));
		// Y * X * Z
		const mat4 roationMatrix = transformY * transformX * transformZ;
		// translation * rotation * scale (also know as TRS matrix)
		localModel = glm::translate(glm::mat4(1.0f), m_pos) * roationMatrix * glm::scale4(mat4(1.0f), m_scale);
=======
		return localModel;
	}

	vec3 Transform::getPos()
	{
		return localPos;
	}

	vec3 Transform::getRot()
	{
		return localRot;
	}

	vec3 Transform::getScale()
	{
		return localScale;
	}

	vec3 Transform::getPos(glm::mat4 mat)
	{
		return glm::vec3(mat[3][0], mat[3][1], mat[3][2]);
	}

	vec3 Transform::getRot(glm::mat4 mat)
	{
		return toEulerRad(getRotationByMatrix(mat));
	}

	vec3 Transform::getScale(glm::mat4 mat)
	{
		glm::vec4 m0 = glm::vec4(mat[0].x, mat[0].y, mat[0].z, mat[0].w);
		glm::vec4 m1 = glm::vec4(mat[1].x, mat[1].y, mat[1].z, mat[1].w);
		glm::vec4 m2 = glm::vec4(mat[2].x, mat[2].y, mat[2].z, mat[2].w);

		return glm::vec3(glm::length(m0), glm::length(m1), glm::length(m2));
	}

	quat Transform::getRotationByMatrix(glm::mat4 mat)
	{
		glm::vec3 s = getScale(mat);

		float m00 = mat[0].x / s.x;
		float m01 = mat[0].y / s.y;
		float m02 = mat[0].z / s.z;
		float m10 = mat[1].x / s.x;
		float m11 = mat[1].y / s.y;
		float m12 = mat[1].z / s.z;
		float m20 = mat[2].x / s.x;
		float m21 = mat[2].y / s.y;
		float m22 = mat[2].z / s.z;

		glm::quat q = glm::quat();
		q.w = glm::sqrt(glm::max(0.f, 1.f + m00 + m11 + m22)) / 2.f;
		q.x = glm::sqrt(glm::max(0.f, 1.f + m00 - m11 - m22)) / 2.f;
		q.y = glm::sqrt(glm::max(0.f, 1.f - m00 + m11 - m22)) / 2.f;
		q.z = glm::sqrt(glm::max(0.f, 1.f - m00 - m11 + m22)) / 2.f;
		q.x *= glm::sign(q.x * (m21 - m12));
		q.y *= glm::sign(q.y * (m02 - m20));
		q.z *= glm::sign(q.z * (m10 - m01));

		float qMagnitude = glm::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
		q.w /= qMagnitude;
		q.x /= qMagnitude;
		q.y /= qMagnitude;
		q.z /= qMagnitude;

		return q;
	}

	void Transform::updateModelMatrix()
	{
		if (useLocalMatrix)
		{
			localModel = matlocalTranslate * matlocalRotateX * matlocalRotateY * matlocalRotateZ * matlocalScale;
			worldModel = parentModel * localModel;
		}
		else
		{
			worldModel = matlocalTranslate * matlocalRotateX * matlocalRotateY * matlocalRotateZ * matlocalScale;
		}
	}

	void Transform::UseLocalMatrix()
	{
		useLocalMatrix = true;
>>>>>>> Stashed changes
	}

	void Transform::updateTransformRotation()
	{
		quat rotation = EulerToQuat(localRot);
		vec3 forward = QuatToVec(rotation, vec3(0.f, 0.f, 1.f));
		vec3 up = QuatToVec(rotation, vec3(0.f, 1.f, 0.f));
		vec3 right = QuatToVec(rotation, vec3(1.f, 0.f, 0.f));
	}

	glm::vec3 Transform::getRight()
	{
		return worldModel[0];
	}


	glm::vec3 Transform::getUp()
	{
		return worldModel[1];
	}

	glm::vec3 Transform::getBackward()
	{
		return worldModel[2];
	}

	glm::vec3 Transform::getForward()
	{
		return -worldModel[2];
	}
<<<<<<< Updated upstream
=======
	void Transform::setRotX(float x)
	{
		localRot.x = x;
		glm::vec3 axis;

		axis[1] = axis[2] = 0.0f;
		axis[0] = 1.0f;

		matlocalRotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	}
	void Transform::setRotY(float y)
	{
		localRot.y = y;
		glm::vec3 axis;

		axis[0] = axis[2] = 0.0f;
		axis[1] = 1.0f;

		matlocalRotateY = glm::rotate(glm::mat4(1.0f), y, axis);
	}
	void Transform::setRotZ(float z)
	{
		localRot.z = z;
		glm::vec3 axis;

		axis[0] = axis[1] = 0.0f;
		axis[2] = 1.0f;

		matlocalRotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
	}
>>>>>>> Stashed changes
}


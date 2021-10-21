#include "Entity.h"

float deg2rad = ( 3.14f* 2.0f) / 360.0f;
Entity::Entity(Renderer* rend) {
	_renderer = rend;

	model = glm::mat4(1.0f);
	translate = glm::mat4(1.0f);
	rotationX = glm::mat4(1.0f);
	rotationY = glm::mat4(1.0f);
	rotationZ = glm::mat4(1.0f);
	color = glm::vec4(1.0f);
	scaleMat = glm::mat4(1.0f);

	rotationQuaternion = glm::quat(0, 0, 0, 1);
	transformLoc = glGetUniformLocation(GetRenderer()->GetShader(), "transform");
	_uniformProjection = glGetUniformLocation(GetRenderer()->GetShader(), "projection");
	_uniformView = glGetUniformLocation(GetRenderer()->GetShader(), "view");
	_uniformColor = glGetUniformLocation(GetRenderer()->GetShader(), "color");
	_uniformAlpha = glGetUniformLocation(GetRenderer()->GetShader(), "alpha");
	SetPos(0.0f, 0.0f);
	SetRotations(0, 0, 0);
	SetScale(1.0f, 1.0f, 1.0f);
}
Entity::~Entity() {

}
void Entity::SetRenderer(Renderer* r) {
	_renderer = r;
}
Renderer* Entity::GetRenderer() {
	return _renderer;
}
void Entity::UpdateMatrixData() {
	model = translate * rotationX * rotationY * rotationZ * scaleMat;
}

glm::quat EulerToQuat(glm::vec3 euler) {
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

glm::vec3 QuatXVec(glm::quat quat, glm::vec3 vec) {
	float x2 = quat.x * 2.0f;
	float y2 = quat.y * 2.0f;
	float z2 = quat.z * 2.0f;
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
	res.x = (1.0f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
	res.y = (xy2 + wz2) * vec.x + (1.0f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
	res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.0f - (xx2 + yy2)) * vec.z;
	return res;
}
void Entity::UpdateTransformsData() {
	rotationQuaternion = EulerToQuat(rotation);
}
void Entity::SetPos(float x, float y) {
	position = { x, y, 0.0f };
	translate = glm::translate(glm::mat4(1.0f), position);
	UpdateMatrixData();
}
void Entity::SetPos(glm::vec2 pos) {
	SetPos(pos.x, pos.y);
}
void Entity::SetRotX(float x) {
	rotation.x = x;
	rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	UpdateMatrixData();
	UpdateTransformsData();
}

void Entity::SetRotY(float y) {
	rotation.y = y;
	rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	UpdateMatrixData();
	UpdateTransformsData();
}
void Entity::SetRotZ(float z) {
	rotation.z = z;
	rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	UpdateMatrixData();
	UpdateTransformsData();
}
void Entity::SetRotations(float x, float y, float z) {
	x += 180.0f;	// Todo: Fix
	y += 180.0f;
	
	rotation = glm::vec3(x, y, z);
	rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	UpdateMatrixData();
	UpdateTransformsData();
}
void Entity::SetRotations(glm::vec3 rotation)
{
	SetRotations(rotation.x, rotation.y, rotation.z);	
}
void Entity::SetScale(float x, float y, float z)
{
	scale = { x, y, z };
	scaleMat = glm::scale(glm::mat4(1.0f), scale);
	UpdateMatrixData();
}
void Entity::SetScale(float newScale)
{
	scale = { newScale,newScale,newScale };
	scaleMat = glm::scale(glm::mat4(1.0f), scale);
	UpdateMatrixData();
}
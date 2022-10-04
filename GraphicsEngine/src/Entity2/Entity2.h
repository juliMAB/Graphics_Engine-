#ifndef ENTITY2_H
#define ENTITY2_H
#include "Exports/Exports.h"
#include "Renderer/Renderer.h"
#include "GameObject/GameObject.h"
#include "Collision/AABB.h"
#include "Mesh2/Mesh2.h"
namespace JuliEngine
{
	class Model;
	class GraficosEngine_API Entity2 : public GameObject {
	public:
		static int CuantityEntitys;
		static std::list<Entity2*> EntitysLists;
		
		Entity2(Renderer* renderer);
		~Entity2();
		////------------------
		////----SetPos--------
		void SetPos(glm::vec3 pos);
		void SetPos(float x, float y, float z);
		void SetPos(float x, float y);
		void SetPos(glm::vec2 pos);
		////------------------
		////----SetRot--------
		void SetRot(glm::vec3 rot);
		void SetRotX(float x);
		void SetRotY(float y);
		void SetRotZ(float z);
		void SetRot(float x, float y, float z);
		
		////------------------
		////----SetScale------
		void SetScale(glm::vec3 v);
		void SetScale(float x, float y);
		void SetScale(float x, float y, float z);
		void SetScaleAllSame(float v);
		void SetScaleMulty(float v);
		////----Getters-------
		glm::vec3 getPos()		;
		glm::vec3 getRot()		;
		glm::vec3 getScale()	;
		glm::vec3 GetUp()		;
		glm::vec3 GetFront()	;
		glm::vec3 GetRight()	;
		Renderer* getRender()	{ return _renderer; }
		////---other---
		vec3 getColor() { return _color; };
		void SetColor(vec3 v) 
		{ 
			_color = v; _renderer->UpdateColor(_uniformColor, _color); 
		};
		void SetMatrix(glm::mat4 mat);

		void DebugInfo();
		void AddChildren(Entity2* children);
		void Update();
		void setModelPtr(Model* ptr) { _modelPtr = ptr; };
		Model* getModelPtr() { return _modelPtr; };
		aabb* getVolume() { return volume; }
		void setVolume(aabb* vol) { volume = vol; }

		void Move(vec3 v) { SetPos(getPos() + v); };

		void SetMeshes(vector<Mesh*> meshes);
		void AddMesh(Mesh* mesh) { this->meshes.push_back(mesh); };
		void SetParent(Entity2* parent);
		void setChildren(vector<Entity2*> children);
		//void setDraw();
		void Init();

		vector<Entity2*> getChildren() { return children; };
		Entity2* getParent() { return parent; };
		vector<Mesh*> getMeshes() { return meshes; };
		Entity2* GetNode(std::string nodeName);
		Entity2* GetNode(std::string nodeName, std::string data);

		void generateAABB();
		bool canDrawThisFrame();

		void draw();
	private:
		friend class MyImGui;
	protected:
		vec3 _color;
		Renderer* _renderer;
		
		Model* _modelPtr;

		vector<glm::vec3> aabb;
		vector<glm::vec3> localAABB;

		bool drawThisFrame;

		JuliEngine::aabb* volume;
		uint _locationPosition;
		uint _locationNormal;
		uint _locationTexCoord;
		uint _uniformColor;

		virtual void SetUniforms();


		void addBoundsToAABB(vector<glm::vec3> childAABB);

		vector<glm::vec3> getLocalAABB();

		


		vector<Entity2*> children;
		Entity2* parent;

		vector<Mesh*> meshes;
	};
}


#endif
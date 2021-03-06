#include "spotLight.h"
namespace JuliEngine
{
	SpotLight::SpotLight(Renderer* render) : PointLight(render)
	{
		_cam=nullptr;

		cutOff=0;
		outerCutOff=0;

		_uniformDirection=0;
		_uniformCutOff=0;
		_uniformOuterCutOff=0;
	}
	void SpotLight::Init(){
		setName("spotLight");
		SetUniforms(getName());
	}

	void SpotLight::SetUniforms(std::string name)
	{
		PointLight::SetUniforms(name);
		_renderer->SetUniform(_uniformPosition, (name + ".position").c_str());
		_renderer->SetUniform(_uniformDirection, (name + ".direction").c_str());
		_renderer->SetUniform(_uniformCutOff, (name + ".cutOff").c_str());
		_renderer->SetUniform(_uniformOuterCutOff, (name + ".outerCutOff").c_str());
	}
	void SpotLight::UpdateLight()
	{
		PointLight::UpdateLight();

		_renderer->UseShader();

		_renderer->UpdateVec3(_uniformPosition, _cam->getPos());
		_renderer->UpdateVec3(_uniformDirection, _cam->getTransform()->getforward());
		_renderer->UpdateFloatValue(_uniformCutOff, cutOff);
		_renderer->UpdateFloatValue(_uniformOuterCutOff, outerCutOff);

		_renderer->CleanShader();
	}

	SpotLight::~SpotLight()
	{
	}

	void SpotLight::SetCamera(Camera2* cam)
	{
		this->_cam = cam;
	}

	void SpotLight::SetCutOff(float cutOff)
	{
		this->cutOff = cutOff;
	}

	void SpotLight::SetOuterCutOff(float outerCutOff)
	{
		this->outerCutOff = outerCutOff;
	}

}


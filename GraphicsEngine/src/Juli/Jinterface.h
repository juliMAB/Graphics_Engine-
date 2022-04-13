#ifndef JINTERFACE_H
#define JINTERFACE_H
#include <../GLM/glm.hpp>
#include <../GLM/gtc/matrix_transform.hpp>
#include <../GLM/gtc/type_ptr.hpp>
#include "../Exports/Exports.h"
#include <string>
using namespace glm;
namespace  color
{
	GraficosEngine_API typedef struct RGB
	{
		float r;
		float g;
		float b;
		RGB(float r, float g, float b)
		{
			if (r>1||g>1||b>1)
			{
				this->r = r / 255.0f;
				this->g = g / 255.0f;
				this->b = b / 255.0f;
				
				return;
			}
			this->r = 1;
			this->g = 1;
			this->b = 1;
		}
		RGB(std::string hexValue) {
			const char* str = hexValue.c_str();
			int r, g, b;
			sscanf_s(str, "%02x%02x%02x", &r, &g, &b);
			this->r = r / 255.0;  // Extract the RR byte
			this->g = g / 255.0;   // Extract the GG byte
			this->b = b / 255.0;   // Extract the BB byte
		}
		RGB() 
		{
			r = 1;
			g = 1;
			b = 1;
		};
	};

	GraficosEngine_API struct RGB colorConverter(int hexValue);
	GraficosEngine_API vec4 colorConverter(vec4 a);
	GraficosEngine_API vec3 colorConverter(vec3 a);
	 


	GraficosEngine_API typedef struct RGBA
	{
		RGB _RGB;
		float _A;
		GraficosEngine_API vec4 GetColor();
		void SetColor(float r, float g, float b, float a)
		{
			_RGB = RGB(r, g, b);
			_A = a;
		}
		void SetColor(float r, float g, float b)
		{
			_RGB = RGB(r, g, b);
			_A = 1.0f;
		}
		RGBA()
		{
			_RGB = RGB(1, 1, 1);
			_A = 1.0f;
		}
	};
}

#endif //JINTERFACE_H

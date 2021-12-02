#include "Shape.h"
#include <iostream>
#include "../GLEW/glew.h"
#include "glfw3.h"
#include "../GLM/gtc/type_ptr.hpp"


TypeShape typeOfShape;
uint tamVerts;
int cantIndices;
int cantVerts;
const uint tam1Vert=6;
uint indicesTam;

Shape::Shape(Renderer* rend, TypeShape typeShape)
{
	
	_renderer = rend;
	tamVerts = typeShape * tam1Vert;
	indicesTam = Triangle * (typeShape - 2);
	cantVerts = typeShape;
	//InitShape(typeShape);
	//switch (typeShape) {
	//case Triangle:
	//	shapeVertices = new float [tamVerts] {
	//		 0.0f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f,
	//		 0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f,
	//		 0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f
	//	};
	//	break;
	//case Quad:
	//	shapeVertices = new float [tamVerts] {
	//		// positions             colors                 
	//		 0.5f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, // top right
	//		 0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, // bottom right
	//		-0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, // bottom left
	//		-0.5f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f  // top left 
	//	};
	//	break;
	//default:
	//	shapeVertices = new float [tamVerts];
	//	break;
	//}
	InitBinds(typeShape);
	//_renderer->CreateNewBuffers(_vao, _vbo, _ebo);
	//_renderer->BindBuffer(_vao, _vbo, _ebo, shapeVertices, sizeof(shapeVertices) * tamVerts, indices, sizeof(indices) * indicesTam);
	
	

	glUseProgram(_renderer->GetShaderS());
	_uniformPos        = glGetUniformLocation(_renderer->GetShaderS(), "transform" );
	_uniformColor      = glGetUniformLocation(_renderer->GetShaderS(), "color"	  );
	_uniformProjection = glGetUniformLocation(_renderer->GetShaderS(), "projection");
	_uniformView       = glGetUniformLocation(_renderer->GetShaderS(), "view"	  );
	_uniformAlpha      = glGetUniformLocation(_renderer->GetShaderS(), "alpha"	  );
	uint _useTexture = glGetUniformLocation(_renderer->GetShaderS(), "useTexture");
	glUniform1i(_useTexture, false);
	
	glUseProgram(_renderer->GetShaderS());
	_renderer->Setattributes(_posLocation, 2, tam1Vert, 0);
	_renderer->Setattributes(_posColor   , 4, tam1Vert, 3);
}
void Shape::InitBinds(int vertices)
{
	//setShape.Vertices.
	
		tamVerts = vertices * tam1Vert;
		float* shapeVertices;
		int triangles = 3;
		if (vertices < 3)
			vertices = 3;
		if (vertices == 5)
			vertices = 6;
		switch (vertices)
		{
		case 3:
			shapeVertices = new float[tamVerts]
			{
				-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
				 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f
			};

			break;
		case 4:
			shapeVertices = new float[tamVerts]
			{
				 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
				-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f
			};
			break;
		default:
			shapeVertices = new float[tamVerts];
			for (int i = 0; i < tamVerts; i++)
			{
				shapeVertices[i] = 1.0f;
			}
			shapeVertices[0] = 0.0f;
			shapeVertices[1] = 0.0f;
			shapeVertices[1 * tam1Vert] = -0.5f;
			shapeVertices[(1 * tam1Vert) + 1] = 0.0f;
			int midVert;
			//preguntar si int/int da float.
			if (vertices % 2 == 0)
			{
				midVert = (vertices / 2.0f) + 1.0f;
			}
			else
			{
				midVert = (vertices / 2.0f) + 0.5f;
			}
			shapeVertices[midVert * tam1Vert] = 0.5f;
			shapeVertices[(midVert * tam1Vert) + 1] = 0.0f;
			if (vertices % 2 == 0)
			{
				int midmidVert;
				midmidVert = (midVert + 1) / 2;
				shapeVertices[midmidVert * tam1Vert] = 0.0f;
				shapeVertices[(midmidVert * tam1Vert) + 1] = 0.5f;

				int acumX = (abs(shapeVertices[midVert * tam1Vert]) / midVert - 1);
				int acumY = (abs(shapeVertices[(midmidVert * tam1Vert) + 1]) / midmidVert - 1);
				int acumXvar = -0.5f;
				int acumYvar = -0.5f;
				for (int i = 2; i < midVert; i++)
				{
					acumXvar += acumX;
					shapeVertices[i * tam1Vert] = acumXvar;
					if (i <= midmidVert)
					{
						acumYvar += acumY;
					}
					else
					{
						acumYvar -= acumY;
					}
					shapeVertices[i * tam1Vert] = acumXvar;
				}
				acumX = (abs(shapeVertices[midVert * tam1Vert]) / (midVert - 2));
				acumY = (abs(shapeVertices[(midVert * tam1Vert) + 1]) / (midVert - 2));
				for (int i = midVert + 1; i < vertices; i++)
				{
					acumXvar -= acumX;
					shapeVertices[i * tam1Vert] = acumXvar;
					if (i < midVert + midmidVert - 1)
					{
						acumYvar -= acumY;
					}
					else if (i > midVert + midmidVert)
					{
						acumYvar += acumY;
					}
					shapeVertices[(i * tam1Vert) + 1] = acumYvar;
				}
			}
			else
			{
				midVert = (vertices / 2.0f) + 1.0f;

				shapeVertices[((midVert / 2) * tam1Vert) + 1] = 0.5f;
				shapeVertices[(((midVert / 2) + 1) * tam1Vert) + 1] = 0.5f;

				int acumX = ((abs(shapeVertices[midVert * tam1Vert]) * 2) / (midVert - 1));
				int acumY = (abs(shapeVertices[(midVert / 2) * tam1Vert + 1]) / ((midVert / 2) - 1));
				int acumXvar = -0.5f;
				int acumYvar = -0.5f;
				for (int i = 2; i < midVert; i++)
				{
					acumXvar += acumX;
					shapeVertices[i * tam1Vert] = acumXvar;
					if (i <= midVert / 2)
					{
						acumYvar += acumY;
					}
					else if (i != midVert + 1)
					{
						acumYvar -= acumY;
					}
					shapeVertices[i * tam1Vert] = acumXvar;
				}
				for (int i = midVert + 1; i < vertices; i++)
				{
					acumXvar -= acumX;
					shapeVertices[i * tam1Vert] = acumXvar;
					if (i <= midVert + midVert / 2)
					{
						acumYvar -= acumY;
					}
					else if (i != midVert + (midVert / 2) + 1)
					{
						acumYvar += acumY;
					}
					shapeVertices[(i * tam1Vert) + 1] = acumYvar;
				}
			}
			break;
		}
			
		
		

		
	if (vertices < 3)
		vertices = 3;
	if (vertices == 5)
		vertices = 6;
	uint* indices;
	switch (vertices)
	{
	case 3:
		indicesTam = triangles;
		indices = new uint[indicesTam]{ 0, 1, 2 };
		break;
	case 4:
		indicesTam = triangles * 2;
		indices = new uint[indicesTam]{ 0, 1, 3,/**/ 1, 2, 3 };
		break;
	case 6:
		indicesTam = triangles * 5;
		indices = new uint[indicesTam]{ 0, 1, 2,/**/ 0, 2, 3,/**/0, 3, 4,/**/ 0, 4, 5,/**/0, 5, 1 };
		break;
	default:
		indicesTam = triangles * vertices - 1;
		indices = new uint[indicesTam];
		int counterA = 1;
		int counterB = 2;
		bool swicher = false;
		for (int i = 0; i < indicesTam; i++)
		{
			if (i % 3 == 0 || i == 0)
			{
				indices[i] = 0;
			}
			else
			{
				if (!swicher)
				{
					indices[i] = counterA;
					counterA += 2;
					swicher = !swicher;
				}
				else
				{
					indices[i] = counterB;
					counterB += 2;
					swicher = !swicher;
				}
			}
		}
		break;
	}
	int a = 0;
	for (int i = 0; i < tamVerts; i++)
	{
		std::cout << "[" << shapeVertices[i] << "]";
		a++;
		if (a == 6)
		{
			a = 0;
			std::cout << std::endl;
		}
	}
	std::cout << "INDICES: ";
	for (int i = 0; i < indicesTam; i++)
	{
		std::cout << "[" << indices[i] << "]";
	}
	
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	_renderer->BindBaseBufferRequest(_vao, _vbo, _ebo, shapeVertices, sizeof(shapeVertices) * tamVerts, indices, sizeof(indices) * indicesTam);
	//_renderer->BindBuffer2(_vao, _vbo, sizeof(shapeVertices), shapeVertices);
	//_renderer->BindIndexes(_ebo, sizeof(indices), indices);
}
void Shape::InitShape(int vertices) {
	tamVerts = vertices * tam1Vert;
	int triangles = 3;
	if (vertices < 3)
		vertices = 3;
	if (vertices == 5)
		vertices = 6;
	switch (vertices)
	{
	case 3:

	default:
		float* shapeVertices = new float[tamVerts];
		for (int i = 0; i < tamVerts; i++)
		{
			shapeVertices[i] = 1.0f;
		}
		shapeVertices[0] = 0.0f;
		shapeVertices[1] = 0.0f;
		shapeVertices[ 1 * tam1Vert   ] = -0.5f;
		shapeVertices[(1 * tam1Vert)+1] = 0.0f;
		int midVert;
		//preguntar si int/int da float.
		if (vertices%2==0)
		{
			midVert = (vertices / 2.0f) + 1.0f;
		}
		else
		{
			midVert = (vertices / 2.0f) + 0.5f;
		}
		shapeVertices[midVert * tam1Vert     ] = 0.5f;
		shapeVertices[(midVert * tam1Vert) +1] = 0.0f;
		if (vertices % 2 == 0)
		{
			int midmidVert;
			midmidVert = (midVert + 1) / 2;
			shapeVertices[midmidVert * tam1Vert] = 0.0f;
			shapeVertices[(midmidVert * tam1Vert) + 1] = 0.5f;
			
			int acumX = (abs(shapeVertices[midVert* tam1Vert])/midVert-1);
			int acumY = (abs(shapeVertices[(midmidVert * tam1Vert)+1])/midmidVert-1);
			int acumXvar = -0.5f;
			int acumYvar = -0.5f;
			for (int i = 2; i < midVert; i++)
			{
				acumXvar += acumX;
				shapeVertices[i * tam1Vert] = acumXvar;
				if (i<=midmidVert)
				{
					acumYvar += acumY;
				}
				else
				{
					acumYvar -= acumY;
				}
				shapeVertices[i * tam1Vert] = acumXvar;
			}
			acumX = (abs(shapeVertices[midVert * tam1Vert]) / (midVert - 2));
			acumY = (abs(shapeVertices[(midVert * tam1Vert)+1]) / (midVert - 2));
			for (int i = midVert+1; i < vertices; i++)
			{
				acumXvar -= acumX;
				shapeVertices[i * tam1Vert] = acumXvar;
				if (i<midVert+midmidVert-1)
				{
					acumYvar -= acumY;
				}
				else if(i > midVert + midmidVert)
				{
					acumYvar += acumY;
				}
				shapeVertices[(i * tam1Vert)+1] = acumYvar;
			}
		}
		else
		{
			midVert = (vertices / 2.0f) + 1.0f;
			
			shapeVertices[((midVert / 2) * tam1Vert) + 1] = 0.5f;
			shapeVertices[(((midVert / 2)+1) * tam1Vert) + 1] = 0.5f;

			int acumX = ((abs(shapeVertices[midVert * tam1Vert])*2) / (midVert - 1));
			int acumY = (abs(shapeVertices[(midVert / 2) * tam1Vert + 1]) / ((midVert / 2) - 1));
			int acumXvar = -0.5f;
			int acumYvar = -0.5f;
			for (int i = 2; i < midVert; i++)
			{
				acumXvar += acumX;
				shapeVertices[i * tam1Vert] = acumXvar;
				if (i <= midVert/2)
				{
					acumYvar += acumY;
				}
				else if(i!=midVert+1)
				{
					acumYvar -= acumY;
				}
				shapeVertices[i * tam1Vert] = acumXvar;
			}
			for (int i = midVert + 1; i < vertices; i++)
			{
				acumXvar -= acumX;
				shapeVertices[i * tam1Vert] = acumXvar;
				if (i <= midVert + midVert / 2)
				{
					acumYvar -= acumY;
				}
				else if (i != midVert + (midVert / 2)+1)
				{
					acumYvar += acumY;
				}
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			}
		}
		break;
	
	}
}
Shape::~Shape() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
}
void Shape::Draw() 
{
	//_renderer->UpdateMVP(model, _uniformPos, _uniformView, _uniformProjection, _uniformColor, _uniformAlpha, color,_renderer->GetShaderS());
		//_renderer->Draw(indicesTam,_vao);
		
		uint shaderId = _renderer->GetShaderS();
		glUseProgram(shaderId);
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		glUniform3fv(_uniformColor, 1, glm::value_ptr(newColor));
		glUniform1fv(_uniformAlpha, 1, &(color.a));
		_renderer->DrawShape(model, _vao, indicesTam, shaderId);
}

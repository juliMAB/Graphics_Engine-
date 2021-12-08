#include "Shape.h"
#include <iostream>
#include "../GLEW/glew.h"
#include "glfw3.h"
#include "../GLM/gtc/type_ptr.hpp"


TypeShape typeOfShape;
uint tamVerts;
int cantIndices;
int cantVerts;
int tam1Vert=6;
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
	_uniformColor      = glGetUniformLocation(_renderer->GetShaderS(), "tintColor");
	_uniformProjection = glGetUniformLocation(_renderer->GetShaderS(), "projection");
	_uniformView       = glGetUniformLocation(_renderer->GetShaderS(), "view"	  );
	_uniformAlpha      = glGetUniformLocation(_renderer->GetShaderS(), "alpha"	  );

	_renderer->Setattributes(0, 3, tam1Vert, 0);
	_renderer->Setattributes(1, 3, tam1Vert, 3);
}
void Shape::initVerts(int vertices)
{
	int midVert;
	//int midmidVert;
	int cantVertTop;
	int cantVertDown;
	for (int i = 0; i < tamVerts; i++)
	{
		shapeVertices[i] = 0.0f;
	}
	std::cout << "seteo de los vertices" << std::endl;
	if (vertices % 2 == 0)
	{
		midVert = (vertices / 2.0f) + 1.0f;
	}
	else
	{
		midVert = (vertices / 2.0f) + 0.5f;
	}
	//setea los puntos cardinales, 00,-10,10;
	std::cout << "la mitad de los vertices: " << midVert << std::endl;
	//seteo el 00 centro de la figura.
	shapeVertices[0] = 0.0f;
	shapeVertices[1] = 0.0f;
	//seteo el punto menor en x.
	shapeVertices[(1 * tam1Vert)] = -0.5f;
	shapeVertices[(1 * tam1Vert) + 1] = 0.0f;
	//seteo el punto mayor en x.
	shapeVertices[(midVert * tam1Vert)] = 0.5f;
	shapeVertices[(midVert * tam1Vert) + 1] = 0.0f;
	//-----------------------------------------------
	cantVertTop = midVert - 2;//menos los primeros 2 vertices. el 00 y -10.
	cantVertDown = vertices-1 - midVert; //el total de vertices menos todos los de arriba.
	//------------------------------------------------
	float acumX = 1.0f / (cantVertTop+1);
	float acumY = 0.5f / ((cantVertTop) / 2.0f);
	float acumXvar = -0.5f;
	float acumYvar = -0.0f;
	bool goingUp=true;
	//este for es para todos los vertices de la parte de arriba de la figura.
	for (int i = 2; i < cantVertTop+2; i++)
	{
		//set de x
		acumXvar += acumX;
		shapeVertices[i*tam1Vert] = acumXvar;

		if (cantVertTop%2 != 0) //para saber si es impar, lo que significa que va a tener punta y solo va a subir y bajar.
		{
			//set de y
			if (acumYvar < 0.5f && goingUp)
			{
				acumYvar += acumY;
				if (acumYvar >= 0.5f)
				{
					goingUp = false;
				}
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			}
			else
			{
				acumYvar -= acumY;
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			}
		}
		else //en el caso de ser par y no tener punta, cuando llege a 0.5 va a no tener punta.
		{
			//set de y
			if (acumYvar < 0.5f && goingUp)
			{
				acumYvar += acumY;
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			}
			else if (acumYvar == 0.5f&& goingUp)
			{
				goingUp = false;
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			}
			else
			{
				acumYvar -= acumY;
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			}
		}
	}
	acumX = 1.0f / (cantVertDown+1);
	if (vertices%2!=0)
	{
	acumY = 0.5f / ((cantVertDown+1)/2);
	if (vertices % 3 == 0)
	{
		acumY = 0.5f / ((cantVertDown+1) / 2.0f);
	}
	}
	else
	{
		acumY = 0.5f / ((cantVertDown+1) / 2.0f);
		if (vertices % 3 == 0)
		{
			acumY = 0.5f / ((cantVertDown) / 2.0f);
		}
	}
	acumXvar = 0.5f;
	acumYvar = 0.0f;
	//este for es para todos los vertices de la parte de abajo de la figura.
	for (int i = 1 + midVert; i < vertices; i++)
	{
		acumXvar -= acumX;
		shapeVertices[i * tam1Vert] = acumXvar;
		if (cantVertDown % 2 != 0) //para saber si es impar, lo que significa que va a tener punta y solo va a subir y bajar.
		{
			//set de y
			if (!goingUp)
			{
				acumYvar -= acumY;
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
				if (acumYvar == -0.5f)
				{
					goingUp = true;
				}
			}
			else if (goingUp)
			{
				acumYvar += acumY;
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			}
		}
		else //en el caso de ser par y no tener punta, cuando llege a 0.5 va a no tener punta.
		{
			//set de y
			if (acumYvar > -0.5f && !goingUp)
			{
				acumYvar -= acumY;
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			}
			else if (acumYvar >= -0.5f && !goingUp)
			{
				goingUp = true;
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			}
			else if (goingUp)
			{
				acumYvar += acumY;
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			}
		}
	}
	//por ultimo extrudeamos las puntas.
	for (int i = 2; i < vertices; i++)
	{
		if (i < midVert)
		{
			if (shapeVertices[(i * tam1Vert)] < 0)
			{
				shapeVertices[(i * tam1Vert) + 1] = 0.5f + shapeVertices[(i * tam1Vert)];
			}
			else
			{
				shapeVertices[(i * tam1Vert) + 1] = 0.5f - shapeVertices[(i * tam1Vert)];
			}
		}
		if (i>midVert)
		{
			if (shapeVertices[(i * tam1Vert)] < 0)
			{
				shapeVertices[(i * tam1Vert) + 1] = -0.5f - shapeVertices[(i * tam1Vert)];
			}
			else
			{
				shapeVertices[(i * tam1Vert) + 1] = -0.5f + shapeVertices[(i * tam1Vert)];
			}
		}
		
	}
}
void Shape::InitBinds(int vertices)
{
	//setShape.Vertices.
	
		//float* shapeVertices;
		int triangles = 3;
		if (vertices < 3)
			vertices = 3;
		if (vertices == 5)
			vertices = 6;
		tamVerts = vertices * tam1Vert;
		switch (vertices)
		{
		case 3:
			shapeVertices = new float[tamVerts]
			{
				-0.5f, -0.5f, 1.0f,/**/ 1.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 1.0f,/**/ 1.0f, 1.0f, 1.0f,
				 0.0f,  0.5f, 1.0f,/**/ 1.0f, 1.0f, 1.0f
			};

			break;
		case 4:
			shapeVertices = new float[tamVerts]
			{
				 0.5f,  0.5f, 1.0f,/**/ 1.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 1.0f,/**/ 1.0f, 1.0f, 1.0f,
				-0.5f, -0.5f, 1.0f,/**/ 1.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 1.0f,/**/ 1.0f, 1.0f, 1.0f
			};
			break;
		default:
			shapeVertices = new float[tamVerts];
			initVerts(vertices);
			//for (int i = 0; i < tamVerts; i++)
			//{
			//	shapeVertices[i] = 0.0f;
			//}
			//shapeVertices[0] = 0.0f;
			//shapeVertices[1] = 0.0f;
			//shapeVertices[(1 * tam1Vert)] = -0.5f;
			//shapeVertices[(1 * tam1Vert) + 1] = 0.0f;
			//int midVert;
			////preguntar si int/int da float.
			//if (vertices % 2 == 0)
			//{
			//	midVert = (vertices / 2.0f) + 1.0f;
			//}
			//else
			//{
			//	midVert = (vertices / 2.0f) + 0.5f;
			//}
			//shapeVertices[midVert * tam1Vert] = 0.5f;
			//shapeVertices[(midVert * tam1Vert) + 1] = 0.0f;
			//if (vertices % 2 == 0)
			//{
			//	int midmidVert;
			//	midmidVert = (midVert + 1) / 2;
			//	shapeVertices[midmidVert * tam1Vert] = 0.0f;
			//	shapeVertices[(midmidVert * tam1Vert) + 1] =0.5f;

			//	float acumX = 1.0f / (midVert - 1.0f);
			//	float acumY = 0.5f / (midmidVert - 1.0f);
			//	float acumXvar = -0.5f;
			//	float acumYvar = -0.0f;
			//	for (int i = 2; i < midVert; i++)
			//	{
			//		acumXvar += acumX;
			//		shapeVertices[i * tam1Vert] = acumXvar;
			//		if (i <= midmidVert)
			//		{
			//			acumYvar += acumY;
			//		}
			//		else if(i > midmidVert)
			//		{
			//			acumYvar -= acumY;
			//		}
			//		shapeVertices[(i * tam1Vert)+1] = acumYvar;
			//	}
			//	acumX = 1.0f / (midVert - 2.0f);
			//	acumY = 0.5f / (midmidVert - 2.0f);
			//	acumXvar = 0.5f;
			//	acumYvar = 0.0f;
			//	for (int i = midVert + 1; i < vertices; i++)
			//	{
			//		acumXvar -= acumX;
			//		shapeVertices[i * tam1Vert] = acumXvar;
			//		if (i < midVert + midmidVert - 1)
			//		{
			//			acumYvar -= acumY;
			//		}
			//		else if (i >= midVert + midmidVert)
			//		{
			//			acumYvar += acumY;
			//		}
			//		shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			//	}
			//}
			//else
			//{
			//	midVert = (vertices / 2.0f) + 0.5f;
			//	int midmidVert = midVert / 2;
			//	//setea el punto mas largo de la figura, la mitad de la mitad de los vertices.
			//	shapeVertices[midVert * tam1Vert] = 0.0f;
			//	shapeVertices[(midVert * tam1Vert) + 1] = 0.5f;
			//	//setea el punto mas alto de la figura, la mitad de la mitad de la mitad de los vertices.
			//	shapeVertices[midmidVert * tam1Vert] = 0.0f;
			//	shapeVertices[(midmidVert * tam1Vert) + 1] = 0.5f;

			//	float acumX = (1.0f / (midVert - 1.0f));
			//	float acumY = 0.5f / ((midmidVert-1.0f));
			//	float acumXvar = -0.5f;
			//	float acumYvar = -0.0f;
			//	float hightMax = 0;
			//	for (int i = 2; i < midVert; i++)
			//	{
			//		acumXvar += acumX;
			//		shapeVertices[i * tam1Vert] = acumXvar;
			//		if (i <= midmidVert)
			//		{
			//			acumYvar += acumY;
			//			shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			//		}
			//		else if (i==midmidVert+1)
			//		{
			//			shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			//		}
			//		else if (i > (midVert/2)+1)
			//		{
			//			acumYvar -= acumY;
			//			shapeVertices[(i * tam1Vert)+1] = acumYvar;
			//		}
			//	}
			//	//shapeVertices[((midVert/2)+1 * tam1Vert) + 1] = hightMax;
			//	acumX = (1.0f / (midVert - 1.0f));
			//	acumY = 0.5f / ((midmidVert+1 / 2.0f));
			//	acumXvar = 0.5f;
			//	acumYvar = -0.0f;
			//	for (int i = midVert + 1; i < vertices; i++)
			//	{
			//		acumXvar -= acumX;
			//		shapeVertices[i * tam1Vert] = acumXvar;
			//		if (i <= midVert + (midVert / 2))
			//		{
			//			acumYvar -= acumY;
			//		}
			//		else if (i > midVert + (midVert / 2))
			//		{
			//			acumYvar += acumY;
			//		}
			//		shapeVertices[(i * tam1Vert) + 1] = acumYvar;
			//	}
			//}
			break;
		}
			
		//to coment.
		int x=0;
		for (int i = 0; i < vertices; i++)
		{
			shapeVertices[i*tam1Vert+3] = (float) ((rand()% 10)/10.0f);
			shapeVertices[i * tam1Vert+4] = (float)((rand() % 10) / 10.0f);
			shapeVertices[i * tam1Vert+5] = (float)((rand() % 10) / 10.0f);
		}
		shapeVertices[3] = 1.0f;
		shapeVertices[4] = 0.0f;
		shapeVertices[5] = 0.0f;
		//shapeVertices[2*tam1Vert] = 5.0f;
		//shapeVertices[(2 * tam1Vert)+1] = 5.0f;
		//shapeVertices[5] = 0.0f;
		/*shapeVertices[9] = 0.0f;
		
		shapeVertices[10] = 1.0f;
		shapeVertices[11] = 1.0f;
		shapeVertices[16] = 1.0f;
		shapeVertices[17] = 0.0f;
		shapeVertices[18] = 1.0f;*/
		//stop comment.
		

		
	if (vertices < 3)
		vertices = 3;
	if (vertices == 5)
		vertices = 6;
	//uint* indices;
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
		indicesTam = triangles * vertices;
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
					counterA ++;
					swicher = !swicher;
				}
				else
				{
					indices[i] = counterB;
					counterB ++;
					swicher = !swicher;
				}
			}
		}

		indices[indicesTam - 1] = 1;
		indices[indicesTam - 2] = vertices-1;
		break;
	}
	int a = 0;
	int b = 0;
	std::cout << "(" << b << "):";
	for (int i = 0; i < tamVerts; i++)
	{
		std::cout << "[" << shapeVertices[i] << "]";
		a++;
		if (a == 6)
		{
			b++;
			std::cout << std::endl;
			std::cout << "(" << b << "):";
			a = 0;
		}
	}
	std::cout << "INDICES: ";
	std::cout << std::endl;
	for (int i = 0; i < indicesTam; i++)
	{
		std::cout << "[" << indices[i] << "]";
		a++;
		if (a==3)
		{
			a = 0;
			std::cout << std::endl;
		}
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
		
		/*uint shaderId = _renderer->GetShaderS();
		glUseProgram(shaderId);
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		glUniform3fv(_uniformColor, 1, glm::value_ptr(newColor));
		glUniform1fv(_uniformAlpha, 1, &(color.a));*/
		//_renderer->UpdateMVP(model, _uniformPos, _uniformView, _uniformProjection, _uniformColor, _uniformAlpha, color, _renderer->GetShaderS());
		//_renderer->DrawShape(model, _vao, indicesTam,_renderer->GetShaderS());
		//_renderer->UpdateMVP(matrix.model, transformLoc, _uniformView, _uniformProjection);
		//_renderer->Draw(typeOfShape, sizeof(posIndexs) / sizeof(float), _vao, _vbo, _ibo, _vb, tamVerts, TypeShader::Colour);
		_renderer->UpdateMVP(model, _uniformPos, _uniformView, _uniformProjection,_uniformColor,_uniformAlpha,color,_renderer->GetShaderS());
		//_renderer->Draw(sizeof(ind) / sizeof(float), _vao, _vbo, _ebo, shapeVertices, tamVerts, TypeShader::Colour);
		_renderer->DrawM2(_vao ,indicesTam*sizeof(uint), _renderer->GetShaderS());
}

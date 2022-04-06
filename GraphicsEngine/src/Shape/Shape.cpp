#include "Shape.h"
#include <iostream>
#include "../GLEW/glew.h"
#include "glfw3.h"
#include "../GLM/gtc/type_ptr.hpp"


TypeShape typeOfShape;
int tamVerts;
int cantIndices;
int tam1Vert = 6;
uint indicesTam;

Shape::Shape(Renderer* rend, TypeShape typeShape)
{
	
	_renderer = rend;

	InitBinds(typeShape);

	glUseProgram(_renderer->GetShaderS());
	_uniformPos        = glGetUniformLocation(_renderer->GetShaderS(), "transform" );
	_uniformColor      = glGetUniformLocation(_renderer->GetShaderS(), "tintColor");
	_uniformProjection = glGetUniformLocation(_renderer->GetShaderS(), "projection");
	_uniformView       = glGetUniformLocation(_renderer->GetShaderS(), "view"	  );
	_uniformAlpha      = glGetUniformLocation(_renderer->GetShaderS(), "alpha"	  );

	_renderer->Setattributes(0, 3, tam1Vert, 0);
	_renderer->Setattributes(1, 3, tam1Vert, 3);
}
static void showInConsoleVerticesAndIndices(float* shapeVertices, int indicesTam, uint* indices)
{
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
		if (a == 3)
		{
			a = 0;
			std::cout << std::endl;
		}
	}
};
void Shape::initVerts(int vertices)
{
	int midVert;
	//int midmidVert;
	int cantVertTop;
	int cantVertDown;
	for (int i = 0; i < tamVerts; i++)
	{
		shapeVertices[i] = 1.0f;
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
	float acumY;
	if (vertices % 2 != 0)
	{
		if (cantVertTop%2==0)
		{
			acumY = 0.5f / ((cantVertTop) / 2.0f);
		}
		else
		{
			acumY = 0.5f / ((cantVertTop + 1) / 2);
		}
	}
	else
	{
		acumY = 0.5f / ((cantVertTop + 1) / 2.0f);
		if (vertices % 3 == 0)
		{
			acumY = 0.5f / ((cantVertTop) / 2.0f);
		}
	}
	float acumXvar = -0.5f;
	float acumYvar = -0.0f;
	bool goingUp=true;
	int spikeTop = 0;
	int spikeDown = 0;
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
					spikeTop = i;
					shapeVertices[(i * tam1Vert)] = 0.0f;
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
			spikeDown = true;
			//set de y
			if (!goingUp)
			{
				acumYvar -= acumY;
				shapeVertices[(i * tam1Vert) + 1] = acumYvar;
				if (acumYvar == -0.5f)
				{
					goingUp = true;
					spikeDown = i;
					shapeVertices[(i * tam1Vert)] = 0.0f;
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
	//por ultimo extrudeamos las puntas. para esto uso la hipotenusa que es y = x*x + r*r(radio)(0.5f).
	float r = 0.5f;
	for (int i = 2; i < vertices; i++)
	{
		if (i < midVert)
		{
			if (shapeVertices[(i * tam1Vert)] < 0)
			{
				shapeVertices[(i * tam1Vert) + 1] = sqrtf((0.5f*0.5f)-(shapeVertices[(i * tam1Vert)]* shapeVertices[(i * tam1Vert)]));
				//shapeVertices[(i * tam1Vert)] = sqrtf((shapeVertices[(i * tam1Vert)+1] * shapeVertices[(i * tam1Vert)+1])- (0.5f * 0.5f));
				/*float dotX = (-sqrtf(+(r * r) - (shapeVertices[(i * tam1Vert) + 1] * shapeVertices[(i * tam1Vert) + 1])));
				float dotY = (+sqrtf((r * r) - (shapeVertices[(i * tam1Vert)] * shapeVertices[(i * tam1Vert)])));
				shapeVertices[(i * tam1Vert)] = dotX;
				shapeVertices[(i * tam1Vert) + 1] = dotY;*/
			}
			else if  (shapeVertices[(i * tam1Vert)] > 0)
			{
				shapeVertices[(i * tam1Vert) + 1] = sqrtf((0.5f * 0.5f) - (shapeVertices[(i * tam1Vert)] * shapeVertices[(i * tam1Vert)]));
				//shapeVertices[(i * tam1Vert)] = sqrtf((shapeVertices[(i * tam1Vert) + 1] * shapeVertices[(i * tam1Vert) + 1]) - (0.5f * 0.5f));
				/*float dotX = (+sqrtf(+(r * r) - (shapeVertices[(i * tam1Vert) + 1] * shapeVertices[(i * tam1Vert) + 1])));
				float dotY = (+sqrtf((r * r) - (shapeVertices[(i * tam1Vert)] * shapeVertices[(i * tam1Vert)])));
				shapeVertices[(i * tam1Vert)] = dotX;
				shapeVertices[(i * tam1Vert) + 1] = dotY;*/
			}
			else
			{
				float dotX = 0.0f;
				float dotY = 0.5f;
				shapeVertices[(i * tam1Vert)] = dotX;
				shapeVertices[(i * tam1Vert) + 1] = dotY;
			}
		}
		if (i>midVert)
		{
			if (shapeVertices[(i * tam1Vert)] < 0)
			{
				shapeVertices[(i * tam1Vert) + 1] = -sqrtf((0.5f * 0.5f) - (shapeVertices[(i * tam1Vert)] * shapeVertices[(i * tam1Vert)]));
				//shapeVertices[(i * tam1Vert)] = sqrtf((shapeVertices[(i * tam1Vert) + 1] * shapeVertices[(i * tam1Vert) + 1]) - (0.5f * 0.5f));
				/*float dotX = (-sqrtf(+(r * r) - (shapeVertices[(i * tam1Vert) + 1] * shapeVertices[(i * tam1Vert) + 1])));
				float dotY = (-sqrtf((r * r) - (shapeVertices[(i * tam1Vert)] * shapeVertices[(i * tam1Vert)])));
				shapeVertices[(i * tam1Vert)] = dotX;
				shapeVertices[(i * tam1Vert) + 1] = dotY;*/
			}
			else if (shapeVertices[(i * tam1Vert)] > 0)
			{

				shapeVertices[(i * tam1Vert) + 1] = -sqrtf((0.5f * 0.5f) - (shapeVertices[(i * tam1Vert)] * shapeVertices[(i * tam1Vert)]));
				/*float dotX = sqrtf(+(r * r) - (shapeVertices[(i * tam1Vert) + 1] * shapeVertices[(i * tam1Vert) + 1]));
				float dotY = -sqrtf((r * r) - (shapeVertices[(i * tam1Vert)] * shapeVertices[(i * tam1Vert)]));
				shapeVertices[(i * tam1Vert)] = dotX;
				shapeVertices[(i * tam1Vert)+1] = dotY;*/
			}
			else
			{
				float dotX = 0.0f;
				float dotY = -0.5f;
				shapeVertices[(i * tam1Vert)] = dotX;
				shapeVertices[(i * tam1Vert) + 1] = dotY;
			}
		}
		
	}
}
void Shape::ultraHack(int indice, float value)
{
	shapeVertices[(indice * tam1Vert)] = value;
	//_renderer->CreateNewBuffers(_vao, _vbo, _ebo);

	_renderer->BindBaseBufferRequest(_vao, _vbo, _ebo, shapeVertices, sizeof(shapeVertices) * tamVerts, indices, sizeof(indices) * indicesTam);
}
float Shape::ultraHackGetValue(int indice)
{
	return shapeVertices[(indice * tam1Vert)];
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
			break;
		}
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
		indicesTam = triangles * (vertices-1);
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
		showInConsoleVerticesAndIndices(shapeVertices, indicesTam, indices);
		break;
	}
	


	_renderer->GenBuffers(_vao, _vbo, _ebo);

	_renderer->BindBaseBufferRequest(_vao, _vbo, _ebo, shapeVertices, sizeof(shapeVertices) * tamVerts, indices, sizeof(indices) * indicesTam);

}
void Shape::CrazyFunc()
{
	//srand(time(NULL));
	//esta funcion solo se puede aplicar en initBinds y es para testear.
	int a = tamVerts / tam1Vert;
	int x = 0;
	for (int i = 0; i < a; i++)
	{
		shapeVertices[(i * tam1Vert) + 3] = (float)((rand() % 100) / 100.0f);
		shapeVertices[(i * tam1Vert) + 4] = (float)((rand() % 100) / 100.0f);
		shapeVertices[(i * tam1Vert) + 5] = (float)((rand() % 100) / 100.0f);
	}
	shapeVertices[3] = 1.0f;
	shapeVertices[4] = 0.0f;
	shapeVertices[5] = 0.0f;
	_renderer->BindBaseBufferRequest(_vao, _vbo, _ebo, shapeVertices, sizeof(shapeVertices) * tamVerts, indices, sizeof(indices) * indicesTam);
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
		int midmidVert;
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
	_renderer->UpdateMVP(model, _uniformPos, _uniformView, _uniformProjection,_uniformColor,_uniformAlpha,color,_renderer->GetShaderS());
	_renderer->DrawM2(_vao ,indicesTam*sizeof(uint), _renderer->GetShaderS());
}
void Shape::DrawDebug()
{
	_renderer->UpdateMVP(model, _uniformPos, _uniformView, _uniformProjection, _uniformColor, _uniformAlpha, color, _renderer->GetShaderS());
	_renderer->DrawM2Debug(_vao, indicesTam * sizeof(uint), _renderer->GetShaderS());
}
void Shape::ConsoleData()
{
	showInConsoleVerticesAndIndices(shapeVertices, indicesTam, indices);
}



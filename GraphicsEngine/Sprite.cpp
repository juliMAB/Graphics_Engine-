#include "src/Sprite/Sprite.h"


const int tamVerts = 32;//4 * tam1Vert;
int tam1Vert = 8;

	static float verteces[] =
	{
		// positions             colors                 texture coords
		0.5f, 0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, //
		0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, // 
	   -0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, // 
	   -0.5f, 0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f  // 
	};
Sprite::Sprite(Renderer* render, std::string filePathImage)
{
	_animation = nullptr;
	_texture = nullptr;
	std::cout << "-------Create new Sprite:-------"<<std::endl;
	Init(render, filePathImage);
	std::cout  << "-----End Create new Sprite-------"<<std::endl<<std::endl;
}
void Sprite::SetAttributers()
{
	_renderer->Setattributes(_posLocation, 2, tam1Vert, 0);
	_renderer->Setattributes(_posColor, 4, tam1Vert, 2);
	_renderer->Setattributes(_postexture, 2, tam1Vert, 6);
}
void Sprite::Init(Renderer* render, std::string filePathImage)
{
	_renderer = render;
	vertex = verteces;
	tam = sizeof(verteces);
	_texture = new Texture(filePathImage);
	//_animation = new Animation();
	InitBinds();
	SetUniforms();
	SetAttributers();
}
void Sprite::InitBinds()
{
	indicesTam = 6;
	uint indices[]{ 0, 1, 2, 2, 3, 0 };
	_renderer->BindBuffer2(_vao, _vbo, tam, vertex);
	_renderer->BindIndexes(_ebo, sizeof(indices), indices);
}
Sprite::~Sprite() {
	_renderer->DeleteBuffers(_vao, _vbo, _ebo);
	glDeleteTextures(1, &(_texture->_textureID));

	if (_texture != NULL) {
		delete _texture;
		_texture = NULL;
	}
}
void Sprite::SetSprite(const std::string path) {
	if (_texture!=NULL)
	{
		_texture->LoadTexture(path);
	}
	else
	{
		_texture = new Texture(path);
	}
}
void Sprite::SetShader()
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ARRAY_BUFFER, tamVerts, vertex, GL_STATIC_DRAW);
	glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
	unsigned int colorLoc = glGetUniformLocation(_renderer->GetShader(), "color");
	glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

	unsigned int alphaLoc = glGetUniformLocation(_renderer->GetShader(), "alpha");
	glUniform1fv(alphaLoc, 1, &(color.a));

	unsigned int textureLoc = glGetUniformLocation(_renderer->GetShader(), "theTexture");
	glUniform1f(textureLoc, _texture->_textureID);
}
void Sprite::Draw()
{
	uint shaderId = _renderer->GetShader();
	glUseProgram(shaderId);
	glBindTexture(GL_TEXTURE_2D, _texture->_textureID);
	SetShader();
	Entity::Draw(shaderId);
}

void Sprite::StartUseAnimation() {
	if (_animation == nullptr) {
		_animation = new Animation();
		return;
	}

	std::cout << "The sprite already has animation " << std::endl;
}
void Sprite::StartUseAnimation(int rows, int cols, float duration) {
	if (_animation == nullptr) {
		_animation = new Animation();
		AddAnimation(rows, cols, duration);
		return;
	}

	std::cout << "The sprite already has animation " << std::endl;
}
void Sprite::StartUseAnimation(int rows, int cols, float duration,ORDER o) {
	if (_animation == nullptr) {
		_animation = new Animation();
		AddAnimation(rows, cols, duration,o);
		return;
	}

	std::cout << "The sprite already has animation " << std::endl;
}
void Sprite::AddAnimation(int rows, int cols, float duration)
{
	if (_animation == nullptr) {
		_animation = new Animation();
	}
	std::cout << "Creating animation"<< std::endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			_animation->AddFrame(i, j, _texture->_width / cols, _texture->_height / rows, _texture->_width, _texture->_height, duration);
		
		}
	}
}

void Sprite::AddAnimation(int rows, int cols, float duration, ORDER o)
{
	if (_animation == nullptr) {
		_animation = new Animation();
	}
	std::cout << "Creating animation" << std::endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			switch (o)
			{
			case ORDER::RIGHTtoLEFT:
				_animation->AddFrame(j, i, _texture->_width / cols, _texture->_height / rows, _texture->_width, _texture->_height, duration);
				break;
			case ORDER::UPtoDOWN:
				_animation->AddFrame(i, j, _texture->_width / cols, _texture->_height / rows, _texture->_width, _texture->_height, duration);
				break;
			default:
				_animation->AddFrame(j, i, _texture->_width / cols, _texture->_height / rows, _texture->_width, _texture->_height, duration);
				break;
			}

		}
	}
}

void Sprite::UpdateAnimation(float timer)
{
	if (!_animation)
		return;

	_animation->Update(timer);

	int currFrame = _animation->GetCurrentFrame();
	if (currFrame != 0)
	{
		Frame f = _animation->GetFrames()[currFrame];

		float uvCoords[]
		{
			f.GetUVCords()[0].u, f.GetUVCords()[0].v,
			f.GetUVCords()[1].u, f.GetUVCords()[1].v,
			f.GetUVCords()[2].u, f.GetUVCords()[2].v,
			f.GetUVCords()[3].u, f.GetUVCords()[3].v
		};
		/*for (int i = 0; i < tam1Vert; i=+2)
		{
			int xd = (tam1Vert*(i+1)) - (2);
			vertex[xd] = uvCoords[i];
			vertex[xd+1] = uvCoords[i+1];
		}*/
		vertex[6] = uvCoords[0];
		vertex[14] = uvCoords[2];
		vertex[22] = uvCoords[4];
		vertex[30] = uvCoords[6];

		vertex[7] = uvCoords[1];
		vertex[15] = uvCoords[3];
		vertex[23] = uvCoords[5];
		vertex[31] = uvCoords[7];

		/*render->BindTextureBuffer(VBO, sizeof(uvCoords), uvCoords);
		BindAttrib();*/
	}
}

void Sprite::SetUniforms()
{
	glUseProgram(_renderer->GetShader());
	_uniformPos = glGetUniformLocation(_renderer->GetShader(), "transform");
	_uniformColor = glGetUniformLocation(_renderer->GetShader(), "color");
	_uniformProjection = glGetUniformLocation(_renderer->GetShader(), "projection");
	_uniformView = glGetUniformLocation(_renderer->GetShader(), "view");
	_uniformAlpha = glGetUniformLocation(_renderer->GetShader(), "alpha");
	_UniformTexLocation = glGetUniformLocation(_renderer->GetShader(), "theTexture");
	uint _useTexture = glGetUniformLocation(_renderer->GetShader(), "useTexture");
	glUniform1i(_useTexture, true);
}

void Sprite::DrawTexturePart()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture->_textureID);
	glUniform1f(_UniformTexLocation, (GLfloat)_texture->_textureID);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisable(GL_TEXTURE_2D);
}

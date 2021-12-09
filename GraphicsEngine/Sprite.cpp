#include "src/Sprite/Sprite.h"




Sprite::Sprite(Renderer* render, std::string filePathImage,bool flip)
{
	_animation = nullptr;
	_texture = nullptr;
	std::cout << "-------Create new Sprite:-------"<<std::endl;
	Init(render, filePathImage,flip);
	std::cout  << "-----End Create new Sprite-------"<<std::endl<<std::endl;
	anim = std::vector<Animation*>();
}
void Sprite::SetAttributers()
{
	int tam1Vert = 8;
	_renderer->Setattributes(0, 2, tam1Vert, 0);
	_renderer->Setattributes(1, 4, tam1Vert, 2);
	_renderer->Setattributes(2, 2, tam1Vert, 6);
}
void Sprite::AddAnimation(Atlas atlas, float speed)
{
	Animation* a = new Animation();
	a->SetAnimation(_texture, speed);
	a->AddFrames(atlas);
	anim.push_back(a);

	Frame f = anim[animIndex]->GetFrames()[0];
	SetTexture(f);
}
void Sprite::Init(Renderer* render, std::string filePathImage,bool flip)
{
	_renderer = render;
	_texture = new Texture(filePathImage, flip);
	InitBinds();
	SetUniforms();
	SetAttributers();
}
void Sprite::FlipHorizontal()
{
	UVCords a,b,c,d;
	a = { vertex[6], vertex[7] };
	b = { vertex[14], vertex[15] };
	c = { vertex[22], vertex[23] };
	d = { vertex[30], vertex[31] };
	vertex[6]  = d.u; vertex[7]  = d.v;
	vertex[14] = c.u; vertex[15] = c.v;
	vertex[22] = b.u; vertex[23] = b.v;
	vertex[30] = a.u; vertex[31] = a.v;
}
void Sprite::FlipVertical()
{
	UVCords a, b, c, d;
	a = { vertex[6], vertex[7] };
	b = { vertex[14], vertex[15] };
	c = { vertex[22], vertex[23] };
	d = { vertex[30], vertex[31] };
	vertex[6] = b.u; vertex[7] = b.v;
	vertex[14] = a.u; vertex[15] = a.v;
	vertex[22] = d.u; vertex[23] = d.v;
	vertex[30] = c.u; vertex[31] = c.v;
}
void Sprite::InitBinds()
{
	indicesTam = 6;
	uint indices[]{ 0, 1, 3, 1, 2, 3 };
	_renderer->BindBuffer2(_vao, _vbo, sizeof(vertex), vertex);
	_renderer->BindIndexes(_ebo, sizeof(indices), indices);
}
void Sprite::ChangeAnimation(int index)
{
	animIndex = index;
}
void Sprite::SetTexture(Frame f)
{
	float uvCoords[]
	{
		f.GetUVCords()[0].u, f.GetUVCords()[0].v,
		f.GetUVCords()[1].u, f.GetUVCords()[1].v,
		f.GetUVCords()[2].u, f.GetUVCords()[2].v,
		f.GetUVCords()[3].u, f.GetUVCords()[3].v
	};

	vertex[6] = uvCoords[0];
	vertex[14] = uvCoords[2];
	vertex[22] = uvCoords[4];
	vertex[30] = uvCoords[6];

	vertex[7] = uvCoords[1];
	vertex[15] = uvCoords[3];
	vertex[23] = uvCoords[5];
	vertex[31] = uvCoords[7];
}
Sprite::~Sprite() {
	_renderer->DeleteBuffers(_vao, _vbo, _ebo);
	glDeleteTextures(1, &(_texture->_textureID));

	if (_texture != NULL) {
		delete _texture;
		_texture = NULL;
	}
}
void Sprite::SetSprite(const std::string path, bool flip) {
	if (_texture!=NULL)
	{
		_texture->LoadTexture(path, flip);
	}
	else
	{
		_texture = new Texture(path, flip);
	}
}
void Sprite::SetShader()
{
	_renderer->UpdateMVP(model, 
		_uniformPos, _uniformView, _uniformProjection, _uniformColor,
		_uniformAlpha, color, _UniformTexLocation,
		_texture->_textureID, _renderer->GetShaderT());
}
void Sprite::Draw()
{
	SetShader();
	_renderer->DrawM(model, _vao, _vbo, _ebo, indicesTam, sizeof(vertex), vertex, _renderer->GetShaderT());
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
		SetAnimations(rows, cols, duration);
		return;
	}

	std::cout << "The sprite already has animation " << std::endl;
}
void Sprite::StartUseAnimation(int rows, int cols, float duration,ORDER o) {
	if (_animation == nullptr) {
		_animation = new Animation();
		SetAnimations(rows, cols, duration,o);
		return;
	}

	std::cout << "The sprite already has animation " << std::endl;
}
void Sprite::SetAnimations(int rows, int cols, float duration)
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

void Sprite::SetAnimations(int rows, int cols, float duration, ORDER o)
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
	UpdateAnimation(0);
}

void Sprite::UpdateAnimation(float timer)
{
	if (!_animation)
		return;

	_animation->Update(timer);

	int currFrame = _animation->GetCurrentFrame();
	_animation->SetCurrentFrame(currFrame, vertex);
}
void Sprite::UpdateAnimation2(float timer)
{
	if (anim.size() == 0)
		return;

	if (anim[animIndex]->Update2(timer))
	{
		Frame f = anim[animIndex]->GetFrames()[anim[animIndex]->GetCurrentFrame()];
		SetTexture(f);
	}
}
void Sprite::UpdateAnimation(float timer,int action)
{
	if (!_animation)
		return;

	_animation->UpdateAction(timer, action);

	int currFrame = _animation->GetCurrentFrame();
	_animation->SetCurrentFrame(currFrame, vertex);
}
int Sprite::SetAction(int firtsFrame,int lastFrame)
{
	return _animation->SetAnAction(firtsFrame, lastFrame);
}

void Sprite::SetUniforms()
{
	glUseProgram(_renderer->GetShaderT());
	_uniformPos = glGetUniformLocation(_renderer->GetShaderT(), "transform");
	_uniformColor = glGetUniformLocation(_renderer->GetShaderT(), "color");
	_uniformProjection = glGetUniformLocation(_renderer->GetShaderT(), "projection");
	_uniformView = glGetUniformLocation(_renderer->GetShaderT(), "view");
	_uniformAlpha = glGetUniformLocation(_renderer->GetShaderT(), "alpha");
	_UniformTexLocation = glGetUniformLocation(_renderer->GetShaderT(), "theTexture");
	uint _useTexture = glGetUniformLocation(_renderer->GetShaderT(), "useTexture");
	glUniform1i(_useTexture, true);
}



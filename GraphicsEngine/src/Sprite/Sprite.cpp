#include "sprite.h"
#include "../STB/stb_image.h"


	Sprite::Sprite() : Entity2D()
	{
		type = SPRITE_TYPE::QUAD;
		_texture = nullptr;
		_uniformTexture = 0;
		animIndex = 0;
		anim = std::vector<Animation*>();
		currFrame = Frame();
	}

	Sprite::Sprite(Renderer* render) : Entity2D(render)
	{
		type = SPRITE_TYPE::QUAD;
		_texture = nullptr;
		_texture = new Texture();
		affectedLight = true;
		_uniformTexture = 0;
		animIndex = 0;
		anim = std::vector<Animation*>();
		currFrame = Frame();
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::Init(SPRITE_TYPE type)
	{
		_texture = new Texture();
		this->type = type;
		SetUniforms();

		uint* indexes = 0;

		switch (type)
		{
		case SPRITE_TYPE::QUAD:
			indexes = quadIndexes;
			vertices = quadIndexTam;
			vertexs = quadVertex;
			tam = sizeof(vertexs) * quadVertTam;

			break;
		case SPRITE_TYPE::CUBE:
			indexes = cubeIndexes;
			vertices = cubeIndexTam;
			vertexs = cubeVertex;
			tam = sizeof(vertexs) * cubeVertTam;

			break;
		default:
			break;
		}

		_renderer->GenBuffers(_VAO, _VBO, _EBO, _UVB);
		_renderer->BindBuffer(_VAO, _VBO, tam, vertexs);
		_renderer->BindIndexes(_EBO, sizeof(indexes) * vertices, indexes);

		_renderer->SetBaseAttribs(_locationPosition, 3, 6, 0);
		_renderer->SetBaseAttribs(_locationNormal, 3, 6, 3);

		SetTextureCoordinates(currFrame);
		_renderer->SetTextureAttribs(_locationTexCoord, 2, 2, 0);
		//_renderer->SetTextureAttribs(_locationTexCoord, 2, 2, 0);

		useTexture = false;
	}

	void Sprite::Update(float timer)
	{
		if (anim.size() == 0)
			return;

		anim[animIndex]->Update(timer);

	}

	void Sprite::Draw()
	{
		_renderer->BlendEnable();
		_renderer->UseShader();
		UpdateShader();

		_renderer->UpdateTexture(_uniformTexture, _texture->_id);
		_renderer->TextureEnable(_texture->_id);
		Entity2D::Draw();
		_renderer->TextureDisable();
		_renderer->CleanShader();
		_renderer->BlendDisable();
	}

	void Sprite::DeInit()
	{
		_renderer->UnBind(_VAO, _VBO, _EBO, _UVB);
		_renderer->TextureDelete(_uniformTexture, _texture->_id);

		if (_texture != nullptr)
		{
			delete _texture;
			_texture = nullptr;
		}

		for (int i = 0; i < anim.size(); i++)
		{
			delete anim[i];
		}
	}

	void Sprite::SetTexture(Texture* texture)
	{
		_texture = texture;
	}

	void Sprite::LoadTexture(const char* path, bool invertImage)
	{
		if (!_texture)
		{
			_texture = new Texture();
		}
		_texture->LoadTexture(path, invertImage);
		animIndex = 0;
		useTexture = true;
	}

	void Sprite::AddAnimation(Atlas atlas, float speed)
	{
		Animation* a = new Animation();
		a->SetAnimation(_texture, speed);
		a->AddFrames(atlas);
		anim.push_back(a);

		Frame f = anim[animIndex]->GetFrames()[0];
		SetTextureCoordinates(f);
	}

	void Sprite::AddAnimation(int rows, int cols, float speed)
	{
		Animation* a = new Animation();
		a->SetAnimation(_texture, speed);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				a->AddFrame(i, j, _texture->_width / cols, _texture->_height / rows,_texture->_width,_texture->_height, rows * cols);
			}
		}
		anim.push_back(a);

		Frame f = anim[animIndex]->GetFrames()[0];
		SetTextureCoordinates(f);
	}

	void Sprite::ChangeAnimation(int index)
	{
		animIndex = index;
	}

	void Sprite::SetTextureCoordinates(Frame f)
	{
		float quadCoords[8] =
		{
			f.GetUVCords()[0].u, f.GetUVCords()[0].v,
			f.GetUVCords()[1].u, f.GetUVCords()[1].v,
			f.GetUVCords()[2].u, f.GetUVCords()[2].v,
			f.GetUVCords()[3].u, f.GetUVCords()[3].v
		};

		switch (type)
		{
		case SPRITE_TYPE::QUAD:
			_renderer->BindUV(_UVB, sizeof(quadCoords), quadCoords);

			break;
		case SPRITE_TYPE::CUBE:
			float cubeCoords[72] =
			{
				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1],

				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1],

				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1],

				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1],

				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1],

				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1]
			};

			_renderer->BindUV(_UVB, sizeof(cubeCoords), cubeCoords);
			break;
		}
	}

	void Sprite::SetUniforms()
	{
		Entity2D::SetUniforms();
		_renderer->SetUniform(_uniformTexture, "ourTexture");
	}
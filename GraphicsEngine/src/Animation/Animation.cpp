#include "Animation.h"
Animation::Animation() {
	texture = nullptr;
}
Animation::~Animation() {
	for (unsigned int i = 0; i < framesCoordinates.size(); i++)
	{
		delete[] framesCoordinates[i];
	}
}
void Animation::SetAnimation() {
	
}
bool Animation::Update() {
	_time += Time::GetDeltaTime() * _speed;
	if (_time > _frameTime)
	{
		_time -= _frameTime;
		_actualFrame++;
		if (_actualFrame == framesCoordinates.size())
		{
			_actualFrame = 0;
			if (repeat)
			{
				playing = true;
			}
			else
			{
				playing = false;
			}
		}
		return true;
	}
	return false;
}
void Animation::setAnimation(Texture* animationAtlasData, int columns, int rows)
{
	texture = animationAtlasData;
	float spriteWidth = texture->_width / columns;
	float spriteHeight = texture->_height / rows;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			glm::vec2* newCoord = new glm::vec2[4];
			newCoord[0].x = (spriteWidth + (spriteWidth * j)) / texture->_width;			// top right
			newCoord[0].y = (spriteHeight * i) / texture->_height;						// top right
			newCoord[1].x = (spriteWidth + (spriteWidth * j)) / texture->_width; 		// bottom right
			newCoord[1].y = (spriteHeight + (spriteHeight * i)) / texture->_height;		// bottom right
			newCoord[2].x = (spriteWidth * j) / texture->_width;							// bottom left
			newCoord[2].y = (spriteHeight + (spriteHeight * i)) / texture->_height;		// bottom left
			newCoord[3].x = (spriteWidth * j) / texture->_width;							// top left 
			newCoord[3].y = (spriteHeight * i) / texture->_height;						// top left 
			framesCoordinates.push_back(newCoord);
		}
	}
}

glm::vec2* Animation::getCurrentFramesCoordinates()
{
	return framesCoordinates[_actualFrame];
}

Texture* Animation::GetTexture()
{
	return texture;
}

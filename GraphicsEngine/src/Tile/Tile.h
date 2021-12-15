#ifndef TILE_H
#define TILE_H
//============================================
#include "../Sprite/Sprite.h"
#include "../Exports/Exports.h"
//============================================
class Tile : public Sprite
{
public:
	Tile();
	Tile(Renderer* rend);
	~Tile();

	bool isWalkable();
	void walkability(bool bWalkable);

	uint getId();
	void setId(uint id);

	void setPosX(float x);
	void setPosY(float y);

	void draw();


private:
	unsigned int _id;
	bool _walkable;
};
//============================================
#endif


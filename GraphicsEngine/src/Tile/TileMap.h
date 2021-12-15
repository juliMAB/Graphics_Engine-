#ifndef TILEMAP_H
#define TILEMAP_H
//================================================
#include <string>
#include "../Exports/Exports.h"
#include "tinyxml2.h"
#include <iostream>
#include "Tile.h"
#include "../Collision/Collision.h"
//================================================
class TileMap {
public:

	TileMap();
	TileMap(Renderer* rend);
	~TileMap();

	const Tile& tile(unsigned int uiId);
	void setTile(const Tile& rkTile);
	void setMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId);

	void setDimensions(float width, float heigth);
	void setTileDimensions(float tileWidth, float tileHeigth);

	void setTexture(const Texture& rkTexture);
	void setTexture(std::string filePathImage, bool flip);

	void draw();

	bool importTileMap(std::string filePath, Renderer& rkRenderer);
	bool checkCollision(Entity2D& object);

private:
	std::vector<Tile> tiles;
	std::vector<Tile**> _tileMapGrid;

	unsigned int _width;
	unsigned int _height;

	float _tileWidth;
	float _tileHeight;

	Texture _texture;

	float _imageWidth;
	float _imageHeight;

	float convertedPosX;
	float convertedPosY;

	std::string _imagePath;

	Renderer* _render;
};
#endif
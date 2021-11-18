class Atlas
{
public:
	void CutByCount(int columns, int rows, int offsetX, int offsetY, int framesAmount)
	{
		this->columns = columns;
		this->rows = rows;
		this->framesAmount = framesAmount;
		useSize = false;
	}
private:
	int columns = 1;
	int rows = 1;
	int framesAmount = 1;
	bool useSize = false;
	int spriteWidth = 0;
	int spriteHeight = 0;
	friend class animation;
	friend class sprite;
};
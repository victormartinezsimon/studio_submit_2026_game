#pragma once
#include <array>
#include "PainterManager.h"
#include "SpriteSheetController.h"

class NumberManager 
{
public:
	enum class PIVOT {LEFT, RIGHT, CENTER};
public:
	NumberManager(PainterManager* painterManager);

public:
	void PaintNumber(int number, int x, int y, int minDigits, PIVOT pivot);
	void GetSize(unsigned int& w, unsigned int& h)const;
	unsigned int GetWidth()const;
	unsigned int GetHeight()const;

	
private:
	void PaintLeft(int number, int x, int y, int minDigits);
	void PaintRight(int number, int x, int y, int minDigits);
	void PaintCenter(int number, int x, int y, int minDigits);
	int GetSizeNumber(int number, int minDigits);

private:
	PainterManager *_painterManager;
	SpriteSheetController _numbersSprite;
};

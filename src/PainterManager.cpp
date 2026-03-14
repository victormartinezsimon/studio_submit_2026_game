#include "PainterManager.h"
#include "Painter.h"
#include "sprites.h"
#include "Painter.h"

PainterManager::PainterManager()
{
	_sprites[SPRITE_ID::PLAYER] = sprite_player;
	_sprites[SPRITE_ID::ENEMY] = sprite_enemy;
	_sprites[SPRITE_ID::BULLET] = sprite_bullet;
	_sprites[SPRITE_ID::TITLE] = sprite_void;
	_sprites[SPRITE_ID::IMPROVEMENT_SELECTOR_PLAYER] = sprite_selector_player;
	_sprites[SPRITE_ID::IMPROVEMENT_SELECTOR_ENEMY] = sprite_selector_enemy;
	_painter = new Painter();
}

PainterManager::~PainterManager()
{
	delete _painter;
}

void PainterManager::Paint() const
{
	_painter->BeginPaint();

	_painter->PaintBackground();

	for (auto &&d : _toPaint)
	{
		if(d.id == SPRITE_ID::TITLE)
		{
			_painter->PaintItem(sprite_title, d.width, d.height, d.x, d.y);
		}
		else
		{
			_painter->PaintItem(_sprites.at(d.id), d.width, d.height, d.x, d.y);
		}
	}

	_painter->EndPaint();
}

void PainterManager::ClearListPaint()
{
	_toPaint.clear();
}

void PainterManager::AddToPaint(SPRITE_ID id, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{
	data d;
	d.id = id;
	d.width = width;
	d.height = height;
	d.x = x;
	d.y = y;

	_toPaint.push_back(d);
}

void PainterManager::AddUIToPaint(SPRITE_ID id, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{
	AddToPaint(id, width, height, x - width/2, y - height /2);
}
#include "Wall.hpp"

Wall::~Wall()
{
}

bool Wall::isColiding(int xx, int yy, int ww, int hh) const
{
	return ((x         ) *  TextureWidth < xx + ww &&
			(x + width ) *  TextureWidth > xx      &&
			(y         ) * TextureHeight < yy + hh &&
			(y + height) * TextureHeight > yy      );
}

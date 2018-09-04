#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Enemies.h"
#include "map.h"

using namespace sf;

class Snowball :public Entity
{
private:
	int _direction, _speed;
	bool _life;
	void checkCollisionWithMap(float Dx, float Dy, Map map);


public:
	Snowball(String filePath, String Name, float X, float Y, int W, int H, int dir);
	void update(float time, Map &map);

};


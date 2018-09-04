#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "entity.h"

class Enemy :public Entity {
public:
	Enemy(String filePath, float X, float Y, int W, int H, String Name);
	void checkCollisionWithMap(float Dx, float Dy, Map map);
	void update(float time, Map &map);
};
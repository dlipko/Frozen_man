#pragma once

#include <iostream>
#include <list>
#include "Snowball.h"
#include "Enemies.h"
#include "map.h"

class Snowballs
{
public:
	Snowballs() {
	};
	void generate(String filePath,int X, int Y, int W, int H, int direction);
	void update(float time, Map map);
	void draw(sf::RenderWindow &window, float time);
	void checkCollisionsWithEnemies(Enemies &enemies);



private:

	list<Entity*>  _entities;
	list<Entity*>::iterator _it;

};


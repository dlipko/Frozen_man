#pragma once

#include <iostream>
#include <list>
#include "player.h"
#include "Enemy.h"
#include "map.h"

using namespace std;


class Enemies
{
public:
	Enemies() {
	};
	void generate(int enemies, string filePath, int W, int H, string name, Map map);
	void update(float time, Map &map);
	bool intersectWithHero(Player &hero);
	void draw(sf::RenderWindow &window, float time);
	list<Entity*> getEntities()
	{
		return _entities;
	}


private:

	list<Entity*>  _entities;
	list<Entity*>::iterator _it;

};


#include "Enemies.h"



void Enemies::generate(int enemies, string filePath, int W, int H, string name, Map map) {
	srand(time(0));

	for (int i = 0; i < enemies; i++) {
		bool leftSideIsEmpty = false;
		bool rightSideIsEmpty = false;
		int x, j;
		while (!(leftSideIsEmpty && rightSideIsEmpty)) {
			j = rand() % map.getMapWidth();
			x = rand() % map.getMapHeight();
			if (map.isPassage(x, j)) {
				leftSideIsEmpty = map.isPassage(x, j - 1);
				rightSideIsEmpty = map.isPassage(x, j + 1);
			}
		}
		_entities.push_back(new Enemy(filePath, x * 32, j * 32, 22.0, 30.0, name));
	}
}

void Enemies::update(float time, Map &map) {
	for (_it = _entities.begin(); _it != _entities.end();) {
		Entity *b = *_it;
		b->update(time, map);
		if ((*b).getLife() == false) { _it = _entities.erase(_it); delete b; }
		else _it++;
	}
}

bool Enemies::intersectWithHero(Player &hero) {
	for (_it = _entities.begin(); _it != _entities.end(); _it++)
	{
		if ((*_it)->getRect().intersects(hero.getRect()))
		{
				hero.setLife(false);
		}
	}
	return true;
}


void Enemies::draw(sf::RenderWindow &window, float time) {
	for (_it = _entities.begin(); _it != _entities.end(); _it++) {
		window.draw((*_it)->getSprite());
	}
}

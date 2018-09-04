#include "Snowballs.h"

#define center 5

void Snowballs::generate(String filePath,int X, int Y, int W, int H, int direction) {
 	_entities.push_back(new Snowball(filePath, "Snowball", X + center, Y + center, W, H, direction));

}

void Snowballs::update(float time, Map map) {
	for (_it = _entities.begin(); _it != _entities.end();) {
		Entity *b = *_it;
		b->update(time, map);
		if ((*b).getLife() == false) { _it = _entities.erase(_it); delete b; }
		else _it++;
	}
}

void Snowballs::draw(sf::RenderWindow &window, float time) {
	for (_it = _entities.begin(); _it != _entities.end(); _it++) {
		window.draw((*_it)->getSprite());
	}
}


void Snowballs::checkCollisionsWithEnemies(Enemies &enemies) {
	list<Entity*> entities = enemies.getEntities();
	for (_it = _entities.begin(); _it != _entities.end(); _it++) {

		list<Entity*>::iterator it;
		for (it = entities.begin(); it != entities.end(); it++) {
			if (((*_it)->getRect()).intersects((*it)->getRect()))
			{
				(*_it)->setLife(false);
				(*it)->setLife(false);
			}
		}
	}
}





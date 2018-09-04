#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "entity.h"


using namespace sf;
using namespace std;

class Player : public Entity {
public:
	Player(String filePath, float X, float Y, int W, int H, string Name);
	void control(float time);
	void update(float time, Map &map);
	float getPlayerCoordinateX();
	float getPlayerCoordinateY();
	void checkCollisionWithMap(float Dx, float Dy, Map &map);
	bool getShoot();
	void setShoot(bool isShoot);
	int getState();

private:
	enum { left, right, up, down, stay } _state;
	int _playerScore, _snowflakes = 4;
	bool _isShoot;


};


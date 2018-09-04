#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "map.h"

using namespace std;
using namespace sf;


class Entity {
public:
	float _dx, _dy, _x, _y, _speed, _moveTimer, _currentFrame;
	int _width, _height, _health;
	bool _life;
	Texture _texture;
	Sprite _sprite;
	string _name;
	Image _image;

	Entity(String filePath, float X, float Y, int W, int H, String Name);
	virtual void update(float time, Map &map) = 0;

	FloatRect getRect() {
		return FloatRect(_x, _y, _width, _height);
	}

	Sprite getSprite() {
		return _sprite;
	}

	bool getLife() {
		return _life;
	}

	string getName() {
		return _name;
	}

	void changeFrame() {

	}

	void setSpeed(float speed) {
		_speed = speed;
	}

	void setLife(bool life) {
		_life = life;
	}
	
	int getX() {
		return _x;
	}

	int getY() {
		return _y;
	}

};

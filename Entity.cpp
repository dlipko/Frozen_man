#include "entity.h"

Entity::Entity(String filePath, float X, float Y, int W, int H, String Name) {
	_x = X; _y = Y; _width = W; _height = H; _name = Name; _moveTimer = 0;
	_speed = 0; _health = 100; _dx = 0; _dy = 0;
	_life = true;

	_image.loadFromFile(filePath);
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);

	_sprite.setOrigin(_width / 2, _height / 2);
	_currentFrame = 0;
}
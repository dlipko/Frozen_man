#include "Enemy.h"

Enemy::Enemy(String filePath, float X, float Y, int W, int H, String Name) :Entity(filePath, X, Y, W, H, Name) {
	//if (_name == "EasyEnemy") {
		_sprite.setTextureRect(IntRect(0, 0, _width, _height));
		_dx = 0.1;
		_speed = 0.1;
	//}
}


void Enemy::update(float time, Map &map)
{
	//if (_name == "EasyEnemy") {//для персонажа с таким именем логика будет такой

							   
		_moveTimer += time;
		//if (_moveTimer>3000){ _dx *= -1; _moveTimer = 0; }
		_currentFrame += 0.005 * time;
		if (_currentFrame > 3) _currentFrame -= 3;
		//if (_dx < 0)
		//	_sprite.setTextureRect(IntRect(_width * (int(_currentFrame + 1) % 5), _height * int(_currentFrame / 5), -_width, _height));
		//else
		//	_sprite.setTextureRect(IntRect(_width * (int(_currentFrame + 1) % 5), _height * int(_currentFrame / 5), _width, _height));

		_x += _dx*time;
		checkCollisionWithMap(_dx, 0, map);//обрабатываем столкновение по Х
		_sprite.setPosition(_x + _width / 2, _y + _height / 2); 

		if (_health <= 0) { _life = false; }
	//}
}


void Enemy::checkCollisionWithMap(float Dx, float Dy, Map map)
{
	std::vector<int> data(map.getM_data());
	int m_width = map.getMapWidth();
	for (int i = _y / 32; i < (_y + _height) / 32; i++)
		for (int j = _x / 32; j<(_x + _width) / 32; j++)
		{
			if (data[i * m_width + j] == 0)
			{
				if (Dy > 0) { _y = i * 32 - _height;  _dy = 0; }
				if (Dy < 0) { _y = i * 32 + 32;  _dy = 0; }
				if (Dx > 0) { _x = j * 32 - _width; _dx = -0.1; _sprite.scale(-1, 1); }
				if (Dx < 0) { _x = j * 32 + 32; _dx = 0.1; _sprite.scale(-1, 1); }
			}

		}
}
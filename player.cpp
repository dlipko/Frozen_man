#include "player.h"

extern void setPlayerCoordinateForView( float x, float y);

Player::Player(String filePath, float X, float Y, int W, int H, string Name) :Entity(filePath, X, Y, W, H, Name) {
	_playerScore = 0; 
	_state = stay;
	_isShoot = false;
	if (_name == "Player") {
		_sprite.setTextureRect(IntRect(0, 0, _width, _height));
	}

}


void Player::control(float time) 
{
	if (Keyboard::isKeyPressed) {
		_currentFrame += 0.005 * time;

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			_state = left; _speed = 0.1;
			if (_currentFrame > 9) _currentFrame -= 10;
			_sprite.setTextureRect(IntRect(_width * (int(_currentFrame) % 5), _height * int(_currentFrame / 5), -_width, _height));
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				_state = right; _speed = 0.1;
				if (_currentFrame > 9) _currentFrame = 0;
				_sprite.setTextureRect(IntRect(_width * (int(_currentFrame) % 5), _height * int(_currentFrame / 5), _width, _height));
			}
			else {

				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					_state = up; _speed = 0.1;
					if (_currentFrame > 9) _currentFrame -= 10;
					_sprite.setTextureRect(IntRect(_width * (int(_currentFrame) % 5), _height * int(_currentFrame / 5), _width, _height));
				}
				else {

					if (Keyboard::isKeyPressed(Keyboard::Down)) {
						_state = down; _speed = 0.1;
						if (_currentFrame > 9) _currentFrame -= 10;
						_sprite.setTextureRect(IntRect(_width * (int(_currentFrame) % 5), _height * int(_currentFrame / 5), -_width, _height));
					}

					
				}
			}
		}
	
		if (Keyboard::isKeyPressed(Keyboard::Space) && (_snowflakes > 0)) {
			_isShoot = true;
			cout << _snowflakes << std::endl;

		}
	}
	//else _sprite.setTextureRect(IntRect(0, 0, _width, _height));
}


void Player::checkCollisionWithMap(float Dx, float Dy, Map &map)
{
	std::vector<int> data(map.getM_data());
	int m_width = map.getMapWidth();
	for (int i = _y / 32; i < (_y + _height) / 32; i++)//проходимся по элементам карты
		for (int j = _x / 32; j<(_x + _width) / 32; j++)
		{
			if (data[i * m_width + j] == 0)//если элемент наш тайлик земли? то
			{
				if (Dy > 0) { _y = i * 32 - _height;  _dy = 0; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
				if (Dy<0) { _y = i * 32 + 32;  _dy = 0; }//столкновение с верхними краями карты(может и не пригодиться)
				if (Dx > 0) { _x = j * 32 - _width; _dx = 0; }//с правым краем карты
				if (Dx < 0) { _x = j * 32 + 32; _dx = 0; }// с левым краем карты
			}

			if (data[i * m_width + j] == 2)
			{
				_snowflakes++;
				map.setMap(i, j, 1);
			}

			
		}
}


void Player::update(float time, Map &map)
{
	control(time);
	switch (_state)
	{
	case right:_dx = _speed; _dy = 0; break;
	case left:_dx = -_speed; _dy = 0; break;
	case up:_dy = -_speed; _dx = 0; break;
	case down: _dy = _speed; _dx = 0; break;
	case stay: break;		
	}
	_speed = 0;
	_x += _dx*time;
	checkCollisionWithMap(_dx, 0, map);
	_y += _dy*time;
	checkCollisionWithMap(0, _dy, map);
	_sprite.setPosition(_x + _width / 2, _y + _height / 2);
	if (_health <= 0) { _life = false; }




	if (_life) { setPlayerCoordinateForView(_x, _y); }

};


float Player::getPlayerCoordinateX() {	//этим методом будем забирать координату Х	
	return _x;
}


float Player::getPlayerCoordinateY() {	//этим методом будем забирать координату Y 	
	return _y;
}

bool Player::getShoot() {
	return _isShoot;
}
void Player::setShoot(bool isShoot) {
	_isShoot = isShoot;
	_snowflakes--;
}

int Player::getState() {
	return _state;
}
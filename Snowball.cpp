#include "Snowball.h"


Snowball::Snowball(String filePath, String Name, float X, float Y, int W, int H, int dir) : Entity(filePath, X, Y, W, H, Name) {
	_direction = dir;
	_speed  = 0.9;
	_life = true;
	_sprite.setTextureRect(IntRect(0, 0, _width, _height));


}

void Snowball::update(float time, Map &map)
{
	switch (_direction)
	{
		case 0: 
			_dx = -0.2; break;
		case 1: 
			_dx = 0.2; break;
		default:
			setLife(false);
	}

	_x += _dx*time;


	checkCollisionWithMap(_dx, 0, map);
	//for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
	//	if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
	//	{
	//		_life = false;// то пуля умирает
	//	}
	//}

	_sprite.setPosition(_x + _width / 2, _y + _height / 2);//задается позицию пуле
}


void Snowball::checkCollisionWithMap(float Dx, float Dy, Map map)
{
	std::vector<int> data(map.getM_data());
	int m_width = map.getMapWidth();
	for (int i = _y / 32; i < (_y + _height) / 32; i++)//проходимся по элементам карты
		for (int j = _x / 32; j<(_x + _width) / 32; j++)
		{
			if (data[i * m_width + j] == 0)//если элемент наш тайлик земли? то
			{
				setLife(false);
			}
		}
}



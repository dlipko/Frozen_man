#include "Map.h"

extern std::string filePath;

float CurrentFrame = 0;

using namespace sf;
void Map::generate(int roomsCount, int maxW, int maxH) {
	_rooms.clear();
	srand(time(0));
	// второй цикл предотвращает залипание, в случае если на карту уже не помещается ни одной комнаты
	for (int i = 0; i < roomsCount; ++i)
		for (int j = 0; j < 1000; ++j) {

		// ширина и высота комнаты в пределах [10,40]
		const int w = 1 + rand() % maxW,
			h = 1 + rand() % maxH;
		std::cout << w << " " << h << "\n";
		// избегаем "прилипания" комнаты к краю карты
		const Room room = { 3 + rand() % (_width - w - 6), 3 + rand() % (_height - h - 6), w, h };

		// найдем первую комнату, из уже существующих, которая пересекается с новой
		auto intersect = std::find_if(std::begin(_rooms), std::end(_rooms), [&room](const Room &r) {
			return room.intersect(r);
		});

		// если новая комната не имеет пересечений - добавляем ее
		if (intersect == std::end(_rooms)) {
			_rooms.push_back(room);
			break;
		}
	}
	// зануляем карту индексом 0
	_data.assign(_width * _height, 0);
	// пространство комнат заполняем индексом 1
	for (const Room &room : _rooms) {
		for (int x = 0; x < room.w; ++x) for (int y = 0; y < room.h; ++y) {
			_data[(room.x + x) + (room.y + y) * _width] = 1;
		}
	}
}

void Map::print_map() {
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			std::cout << _data[y*_width + x] << " ";
		}
		std::cout << "\n";
	}
}


void Map::add_maze() {
	srand(time(NULL));

	int startX = 1;
	int startY = 1;

	_data[startX * _width + startY] = 1;
	class Coordinates {
	public:
		int x = 0;
		int y = 0;
		void set(int a, int b) {
			x = a;
			y = b;
		}
	};
	std::stack<Coordinates> path;
	Coordinates coord;
	coord.set(startX, startY);
	path.push(coord);
	_data[startX * _width + startY] = 1;



	while (!path.empty())
	{
		Coordinates coord = path.top();

		//смотрим варианты, в какую сторону можно пойти
		std::vector<Coordinates> nextStep;
		Coordinates new_coord;
		if (coord.x - 2 > 0 && !_data[(coord.x - 2) * _width + coord.y]) {
			new_coord.set(coord.x - 2, coord.y);
			nextStep.push_back(new_coord);
		}
		if (coord.x < _width - 2 && !_data[(coord.x + 2) * _width + coord.y]) {
			new_coord.set(coord.x + 2, coord.y);
			nextStep.push_back(new_coord);
		}

		if (coord.y - 2 > 0 && !_data[coord.x * _width + coord.y - 2]) {
			new_coord.set(coord.x, coord.y - 2);
			nextStep.push_back(new_coord);
		}
		if (coord.y < _height - 2 && !_data[coord.x * _width + coord.y + 2]) {
			new_coord.set(coord.x, coord.y + 2);
			nextStep.push_back(new_coord);
		}

		if (!nextStep.empty())
		{
			//выбираем сторону из возможных вариантов
			Coordinates next = nextStep[rand() % nextStep.size()];


			//Открываем сторону, в которую пошли на ячейках
			if (next.x != coord.x)
			{
				if (coord.x - next.x > 0)
					_data[(next.x + 1) * _width + next.y] = 1;
				else
					_data[(next.x - 1) * _width + next.y] = 1;
			}

			if (next.y != coord.y)
			{
				if (coord.y - next.y > 0)
					_data[next.x * _width + next.y + 1] = 1;

				else
					_data[next.x * _width + next.y - 1] = 1;
			}

			_data[next.x * _width + next.y] = 1;
			path.push(next);

		}

		else
		{
			//если пойти никуда нельзя, возвращаемся к предыдущему узлу
			path.pop();
		}
	}
}

Map::Map(int width, int height) : _width(width), _height(height) {

	_map_image.loadFromFile(filePath + "images/map5.png");//загружаем файл для карты

	_map_text.loadFromImage(_map_image);//заряжаем текстуру картинкой

	_map_sprite.setTexture(_map_text);//заливаем текстуру спрайтом
	_map_sprite.setPosition(0, 0);

	_data.resize(width * height, 0);
}


void Map::draw_map(sf::RenderWindow &window, float time) {
	//int frames = 8;
	int spriteSize = 32;
	//CurrentFrame += 0.009 * time;
	//if (CurrentFrame > frames) CurrentFrame -= frames - 1;
	for (int x = 0; x < _height; x++)
		for (int y = 0; y < _width; y++)
		{
			if (_data[x * _width + y] == 1)  _map_sprite.setTextureRect(IntRect(0, 0, spriteSize, spriteSize));
			if (_data[x * _width + y] == 0)  _map_sprite.setTextureRect(IntRect(spriteSize, 0, spriteSize, spriteSize));
			if (_data[x * _width + y] == 2)  _map_sprite.setTextureRect(IntRect(spriteSize*3,0, spriteSize, spriteSize));;


			_map_sprite.setPosition(y * 32, x * 32);

			window.draw(_map_sprite);

		}
}


void Map::randomMapGenerate() {

	int randomElementX = 0;
	int randomElementY = 0;
	srand(time(0));
	int countStone = 30;

	while (countStone>0) {
		randomElementX = 1 + rand() % (_width - 1);
		randomElementY = 1 + rand() % (_height - 1);
		if (_data[randomElementY * _width + randomElementX] == 1) {
			_data[randomElementY * _width + randomElementX] = 2;
			countStone--;
		}
	}
}
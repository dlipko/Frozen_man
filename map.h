#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <stack>

class Map {

public:
	struct Room {
		int x, y, w, h;
		bool intersect(const Room &r) const {
			int distance = 5;
			return !(r.x >= (x + w + distance) || x >= (r.x + r.w + distance) || r.y >= (y + h + distance) || y >= (r.y + r.h + distance));
		}
	};

	Map(int width, int height);
	void generate(int roomsCount, int maxW, int maxH);
	void print_map();
	void add_maze();
	void draw_map(sf::RenderWindow &window, float time);
	std::vector<int> getM_data() {
		return _data;
	}
	int getMapWidth() {
		return _width;
	}

	int getMapHeight() {
		return _height;
	}

	void setMap(int i, int j, int type) {
		_data[i * _width + j] = type;
	}

	void randomMapGenerate();

	bool isVall(int i, int j) {
		return !_data[i * _width + j];
	}

	bool isPassage(int i, int j) {
		return _data[i * _width + j];
	}


private:
	sf::Image _map_image;		//объект изображения для карты
	sf::Texture _map_text;		//текстура карты
	sf::Sprite _map_sprite;			//создаём спрайт для карты
	int _width, _height;		// размеры карты
	std::vector<int> _data;	// финальные данные карты
	std::vector<Room> _rooms;	// комнаты


};


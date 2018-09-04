#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

void setPlayerCoordinateForView(float x, float y) { //функция для считывания координат игрока

	float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < 320) tempX = 320;//убираем из вида левую сторону
	if (y < 240) tempY = 240;//верхнюю сторону
	if (y > 1008) tempY = 1008;//нижнюю сторону	
	if (x > 928) tempX = 928;//убираем из вида левую сторону

	view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты. 
}

void viewmap(float time) { //функция для перемещения камеры по карте. принимает время sfml

	
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.01*time, 0);//скроллим карту вправо 
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.1*time);//скроллим карту вниз
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.1*time, 0);//скроллим карту влево
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.1*time);//скроллим карту вправо
	}


}


void changeview() {


	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view.zoom(1.0100f); //масштабируем, уменьшение
							//view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view.setSize(640, 480);//устанавливает размер камеры (наш исходный)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view.setSize(840, 580);//например другой размер
	}


}


void scroll(sf::RenderWindow &window, float time) {
	sf::Vector2i localPosition = Mouse::getPosition(window);
	sf::Vector2i Position = Mouse::getPosition();
	sf::Vector2i pos = window.getPosition();

	if (localPosition.x < 10 ) { view.move(-0.2*time, 0); }//если пришли курсором в левый край экрана,то двигаем камеру влево
	if (localPosition.x > window.getSize().x - 10) { view.move(0.2*time, 0); }//правый край-вправо
	if (localPosition.y > window.getSize().y - 10) { view.move(0, 0.2*time); }//нижний край - вниз
	if (localPosition.y < 10 && localPosition.x ) { view.move(0, -0.2*time); }//верхний край - вверх


}

#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

void setPlayerCoordinateForView(float x, float y) { //������� ��� ���������� ��������� ������

	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < 320) tempX = 320;//������� �� ���� ����� �������
	if (y < 240) tempY = 240;//������� �������
	if (y > 1008) tempY = 1008;//������ �������	
	if (x > 928) tempX = 928;//������� �� ���� ����� �������

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 
}

void viewmap(float time) { //������� ��� ����������� ������ �� �����. ��������� ����� sfml

	
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.01*time, 0);//�������� ����� ������ 
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.1*time);//�������� ����� ����
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.1*time, 0);//�������� ����� �����
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.1*time);//�������� ����� ������
	}


}


void changeview() {


	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view.zoom(1.0100f); //������������, ����������
							//view.zoom(1.0006f); //���� ����� ����������� ��������������
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view.setSize(640, 480);//������������� ������ ������ (��� ��������)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view.setSize(840, 580);//�������� ������ ������
	}


}


void scroll(sf::RenderWindow &window, float time) {
	sf::Vector2i localPosition = Mouse::getPosition(window);
	sf::Vector2i Position = Mouse::getPosition();
	sf::Vector2i pos = window.getPosition();

	if (localPosition.x < 10 ) { view.move(-0.2*time, 0); }//���� ������ �������� � ����� ���� ������,�� ������� ������ �����
	if (localPosition.x > window.getSize().x - 10) { view.move(0.2*time, 0); }//������ ����-������
	if (localPosition.y > window.getSize().y - 10) { view.move(0, 0.2*time); }//������ ���� - ����
	if (localPosition.y < 10 && localPosition.x ) { view.move(0, -0.2*time); }//������� ���� - �����


}

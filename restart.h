#pragma once

extern string filePath;

bool startGame() {
	RenderWindow window(sf::VideoMode(640, 480), "Santa");
	view.reset(sf::FloatRect(0, 0, 640, 480));

	menu(window);

	Map map(39, 39);
	map.generate(6, 15, 15);
	map.add_maze();
	map.randomMapGenerate();
	map.print_map();


	Player p(filePath + "images/hero_smal_12.png", 33, 33, 24.0, 27.0, "Player");


	Enemies enemies;
	enemies.generate(10, filePath + "images/enemy.png", 22.0, 30.0, "EasyEnemy", map);

	Snowballs snowballs;

	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (p.getShoot() == true) {
				p.setShoot(false);
				snowballs.generate(filePath + "images/Snowball.png", p.getPlayerCoordinateX(), p.getPlayerCoordinateY(), 15, 15, p.getState());
			}

		}

		viewmap(time);
		changeview();

		//scroll(window,time); //скролинг карты мышкой по краю
		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }

		p.update(time, map);

		enemies.update(time, map);
		enemies.intersectWithHero(p);

		snowballs.update(time, map);
		snowballs.checkCollisionsWithEnemies(enemies);

		setPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());

		window.setView(view);
		window.clear();

		if (!p.getLife()) {
			return true;
		}

		map.draw_map(window, time);

		enemies.draw(window, time);
		snowballs.draw(window, time);

		window.draw(p.getSprite());
		window.display();
	}
}


void gameRunning() {
	if (startGame()) { gameRunning(); }
}
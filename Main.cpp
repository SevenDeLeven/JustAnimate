/*
 * Main.cpp
 *
 *  Created on: Mar 30, 2020
 *      Author: Kyle Karnitz
 */

#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "Update.h"
#include "Render.h"

#include <iostream>

int main() {

	Update updater;
	Render renderer;
	sf::Window window(sf::VideoMode(600,600), "Test");

	window.setActive(true);

	glewInit();

	renderer.init();

	renderer.resize(window.getSize());

	float speed = 1.0;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	sf::Clock timer;
	long now = timer.getElapsedTime().asMilliseconds();
	long last = now;
	float delta = 0;
	float tps = 60;

	while (window.isOpen()) {
		sf::Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}
			if (ev.type == sf::Event::Resized) {
				renderer.resize(window.getSize());
				updater.resize(window.getSize());
			}
		}
		now = timer.getElapsedTime().asMilliseconds();
		delta += (now-last)*tps/1000.0;

		if (delta >= 1) {
			std::cout << delta << std::endl;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				renderer.moveCameraGlobal(0,0,5.0f*delta/tps);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				renderer.moveCameraGlobal(-5.0f*delta/tps,0,0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				renderer.moveCameraGlobal(0,0,-5.0f*delta/tps);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				renderer.moveCameraGlobal(5.0f*delta/tps,0,0);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				renderer.rotateCamera(0,-5.0f*delta/tps,0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				renderer.rotateCamera(0,5.0f*delta/tps,0);
			}

			glClearColor(0.0f,0.0f,0.0f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderer.draw();

			window.display();
			delta = 0;
		}

		last = now;
	}
	return 0;
}

/*
 * Update.h
 *
 *  Created on: Mar 30, 2020
 *      Author: Kyle Karnitz
 */

#ifndef UPDATE_H_
#define UPDATE_H_

#include <SFML/Window.hpp>

class Update {
private:

public:
	Update();
	virtual ~Update();

	void resize(sf::Vector2u winSize);

};

#endif /* UPDATE_H_ */

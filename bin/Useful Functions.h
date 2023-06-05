#ifndef MOUSEKEYBOARDSHORTS_H
#define MOUSEKEYBOARDSHORTS_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <cstdlib>
#include <iostream> 
#include <sstream>


bool KPR (int a) {
	return sf::Keyboard::isKeyPressed (static_cast <sf::Keyboard::Key> (a));
}

bool MPR (int a) {
	return sf::Mouse::isButtonPressed (static_cast <sf::Mouse::Button> (a));
}

sf::Vector2i MPos () {
	return sf::Mouse::getPosition ();
}

sf::Vector2i MPos (sf::RenderWindow &window) {
	return sf::Mouse::getPosition (window);
}

bool KBumped (int a) {
	static bool isPressed [128];
	bool returned = false;
	
	if (KPR (a)) {
		if (!isPressed[a]) returned = true;
		isPressed[a] = true;
	}
	
	else {
		isPressed[a] = false;
	}
	
	return returned;
}

bool MBumped (int a) {
	static bool isPressed [8];
	bool returned = false;
	
	if (MPR (a)) {
		if (!isPressed[a]) returned = true;
		isPressed[a] = true;
	}
	
	else {
		isPressed[a] = false;
	}
	
	return returned;
}

int stringToInt (std::string a) {
	int b = 0, multi = 1;
	
	if (a.size() == 0) return 0;
	
	for (int i = a.size() - 1; i >= 0; i--) {
		if (a[i] < '0' || '9' < a[i]) b += 0;
		else b += (a[i] - (int)'0') * multi;
		
		multi *= 10;
	}
	
	return b;
}


// these functions have been written by user named 'Jaclav'
// link to his profile on GitHub:
// https://github.com/Jaclav

// -> from project "Stanczyk"
unsigned char fpsCounter (void) {
    static unsigned char fps, oldfps;
    static sf::Clock clck;

    if (clck.getElapsedTime().asMilliseconds() >= 1000) {
        oldfps = fps;
        fps = 0;
        clck.restart();
    } 
	else fps++;
    
    return oldfps;
}


#endif 

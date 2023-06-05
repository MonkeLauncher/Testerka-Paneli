#ifndef DRAW_INTRO
#define DRAW_INTRO

#include <SFML/Graphics.hpp>
#include <fstream>

struct Intro {
	bool started = false, allowed = false;
	int introFrame = 0;
	
	sf::RectangleShape box, dark;
	sf::Font font;
	sf::Text ML, title;
	
	void prep () {
		std::string check;
		std::ifstream f ("intro package/use_intro.txt");
		f >> check;
		f.close();
		if (check != "true") allowed = false;
		else allowed = true;
	}
	
	void start (sf::RenderWindow &okno, std::string name) {
		if (!allowed) return;
		started = true;
		
		box.setSize (sf::Vector2f (okno.getSize().x / 2 - (okno.getSize().x / 43), okno.getSize().y / 3));
		box.setFillColor (sf::Color (40, 40, 40));
		box.setPosition (okno.getSize().x / 4 + (okno.getSize().x / 85), okno.getSize().y);
		box.setOutlineThickness (1);
		box.setOutlineColor (sf::Color (220, 220, 220));
		
		font.loadFromFile ("intro package/minecraft_font.ttf");
		
		ML.setFont (font);
		ML.setCharacterSize (okno.getSize().y / 24);
		ML.setColor (sf::Color (220, 220, 220));
		ML.setString ("MonkeLauncher presents:");
		ML.setPosition (okno.getSize().x, (okno.getSize().y - 30) / 2 - (okno.getSize().y / 12));
		
		title.setFont (font);
		title.setCharacterSize (okno.getSize().y / 14);
		title.setColor (sf::Color (240, 240, 240));
		title.setString (name.c_str());
		title.setPosition (okno.getSize().x - ((ML.getGlobalBounds().width - title.getGlobalBounds().width) / 2), (okno.getSize().y - 50) / 2 + (okno.getSize().y / 36));
		
		dark.setSize (sf::Vector2f (okno.getSize().x, okno.getSize().y));
		dark.setPosition (0, 0);
		dark.setFillColor (sf::Color (10, 10, 10, 140));
	}
	
	void drawFrame (sf::RenderWindow &okno) {
		if (!started) return;
		
		if ((0 <= introFrame && introFrame < 10) || (130 <= introFrame && introFrame <= 140)) {
			box.setPosition (box.getPosition().x, box.getPosition().y - (okno.getSize().y - (okno.getSize().y - 30) / 2 + (okno.getSize().y / 12)) / 10);
			ML.setPosition (ML.getPosition().x - (okno.getSize().x * 3 / 4 - (okno.getSize().x / 85) - (box.getSize().x - ML.getGlobalBounds().width)) / 10, ML.getPosition().y);
			title.setPosition (title.getPosition().x - (okno.getSize().x * 3 / 4 - (okno.getSize().x / 85) - (box.getSize().x - title.getGlobalBounds().width)) / 10, title.getPosition().y);
		}
		
		else if (10 <= introFrame && introFrame < 130) {
			box.setPosition (box.getPosition().x, box.getPosition().y - (box.getSize().y - (title.getPosition().y - box.getPosition().y) - (okno.getSize().y / 14)) / 120);
			ML.setPosition (ML.getPosition().x - (box.getSize().x - ML.getGlobalBounds().width) / 120, ML.getPosition().y);
			title.setPosition (title.getPosition().x - (box.getSize().x - ML.getGlobalBounds().width) / 120, title.getPosition().y);
		}
		
		else if (140 <= introFrame && introFrame < 150) {
			sf::Color col = dark.getFillColor();
			col.a -= 14;
			dark.setFillColor (col);
		}
		
		
		okno.draw (dark);
		okno.draw (box);
		okno.draw (title);
		okno.draw (ML);
		
		introFrame++;
		if (introFrame == 150) {
			introFrame = 0;
			started = false;
		}
	}
};

#endif

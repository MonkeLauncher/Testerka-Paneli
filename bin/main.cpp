#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <cstdlib>
#include <iostream>
#include <vector>

#include "intro package/draw_intro.hpp"
#include "textBox.h"
#include "Useful Functions.h"

using namespace sf;
using namespace std;


// struct do zapisu opisu klatek
struct setting {
	setting () {}
	
	int hex [20];
};


VideoMode tryb (1280, 720);
RenderWindow okno (tryb, "MonkeLauncher wall panel tester");
Event zdazenie;

CircleShape button (71, 6);
RectangleShape textWindow, dark;
Font minecrafter;
Text buttonText [2], fileText, errorText [2];

string saveName, tempSaveName;
int frame = 0, framesAmount = 0, settingFrame = 0;
double frameTime = 1;
bool changeFrame = true, newFile = false, fileError = false;

Intro intro;
textBox fileInput (20, Color (230, 230, 230), false);

//	szeœciok¹ty i inne wektory
vector <CircleShape> hexagon;
vector <Color> colors;
vector <setting> settings;


// --== Prototypy ==--
void preprocessing ();
void postprocessing ();
void drawAll ();
bool fileReading (string fName);
void reacting ();


// -----===== Int Main =====-----
int main () {
	preprocessing ();


	while (okno.isOpen()) {


        // --== if there is an event ==--
    	while (okno.pollEvent(zdazenie)) {
    		if (newFile && zdazenie.type == Event::TextEntered) {
    			fileInput.typing (zdazenie);
			}
    		
			if (zdazenie.type == Event::Closed) {
				postprocessing ();
				okno.close();
			}
        }
        
        reacting ();
		
		okno.clear();
		drawAll(); 
		okno.display();
	    
    }
}



void preprocessing () {
	
	okno.setFramerateLimit (60);
	
	intro.prep ();
	intro.start (okno, "Tester Paneli");
	
	
	// wczytywanie ostatniego pliku
	ifstream prop ("properties.txt");
	prop >> saveName;
	prop.close();
	
	if (!fileReading (saveName)) {
		exit (-1);
	}
	
	
	// dodawanie hexagonów
	for (int i = 0; i < 20; i++) {
		hexagon.emplace_back (71, 6);
	}
	
	// ustawianie hexagonów
	hexagon[0].setPosition (0 * 71, 2 * 125 + 30);
	hexagon[1].setPosition (1 * 71, 3 * 125 + 30);
	hexagon[2].setPosition (2 * 71, 2 * 125 + 30);
	hexagon[3].setPosition (3 * 71, 1 * 125 + 30);
	hexagon[4].setPosition (4 * 71, 2 * 125 + 30);
	hexagon[5].setPosition (5 * 71, 3 * 125 + 30);
	hexagon[6].setPosition (6 * 71, 2 * 125 + 30);
	hexagon[7].setPosition (7 * 71, 3 * 125 + 30);
	hexagon[8].setPosition (8 * 71, 4 * 125 + 30);
	hexagon[9].setPosition (9 * 71, 3 * 125 + 30);
	hexagon[10].setPosition (10 * 71, 4 * 125 + 30);
	hexagon[11].setPosition (11 * 71, 3 * 125 + 30);
	hexagon[12].setPosition (12 * 71, 2 * 125 + 30);
	hexagon[13].setPosition (13 * 71, 1 * 125 + 30);
	hexagon[14].setPosition (13 * 71, 3 * 125 + 30);
	hexagon[15].setPosition (14 * 71, 0 * 125 + 30);
	hexagon[16].setPosition (15 * 71, 1 * 125 + 30);
	hexagon[17].setPosition (15 * 71, 3 * 125 + 30);
	hexagon[18].setPosition (16 * 71, 0 * 125 + 30);
	hexagon[19].setPosition (16 * 71, 2 * 125 + 30);
	
	
	// guzik
	button.setFillColor (Color (10, 10, 10));
	button.setPosition (14 * 71, 2 * 125 + 30);
	
	// po prostu ciemnosc
	dark.setSize (sf::Vector2f (okno.getSize().x, okno.getSize().y));
	dark.setPosition (0, 0);
	dark.setFillColor (sf::Color (10, 10, 10, 140));
	
	// okno (wal magika)
	textWindow.setSize (sf::Vector2f (okno.getSize().x / 3, okno.getSize().y / 3));
	textWindow.setFillColor (sf::Color (40, 40, 40));
	textWindow.setPosition (okno.getSize().x / 3, okno.getSize().y / 3);
	textWindow.setOutlineThickness (1);
	textWindow.setOutlineColor (sf::Color (220, 220, 220));
	
	// teksty
	//buttonText [2], fileText, errorText [2];
	
	minecrafter.loadFromFile ("minecraft_font.ttf");
	
	buttonText[0].setFillColor (Color (230, 230, 230));
	buttonText[0].setCharacterSize (15);
	buttonText[0].setFont (minecrafter);
	buttonText[0].setString ("Nowa");
	buttonText[0].setPosition (button.getPosition().x + (button.getRadius() - (buttonText[0].getLocalBounds().width / 2)), button.getPosition().y + 45);
	
	buttonText[1].setFillColor (Color (230, 230, 230));
	buttonText[1].setCharacterSize (15);
	buttonText[1].setFont (minecrafter);
	buttonText[1].setString ("Konfiguracja");
	buttonText[1].setPosition (button.getPosition().x + (button.getRadius() - (buttonText[1].getLocalBounds().width / 2)), buttonText[0].getPosition().y + 20);
	
	fileText.setFillColor (Color (230, 230, 230));
	fileText.setCharacterSize (30);
	fileText.setFont (minecrafter);
	fileText.setString ("Wpisz nazwe pliku:");
	fileText.setPosition (textWindow.getPosition().x + (textWindow.getSize().x - fileText.getGlobalBounds().width) / 2, textWindow.getPosition().y + 60);
	
	// textBox
	fileInput.setFont (minecrafter);
	fileInput.setPosition (Vector2f (textWindow.getPosition().x + 20, textWindow.getPosition().y + 140));
	fileInput.setLimit (25);
	
	errorText[0].setFillColor (Color (230, 230, 230));
	errorText[0].setCharacterSize (30);
	errorText[0].setFont (minecrafter);
	errorText[0].setString ("ERROR");
	errorText[0].setPosition (textWindow.getPosition().x + (textWindow.getSize().x - errorText[0].getGlobalBounds().width) / 2, textWindow.getPosition().y + 60);
	
	errorText[1].setFillColor (Color (230, 230, 230));
	errorText[1].setCharacterSize (20);
	errorText[1].setFont (minecrafter);
	errorText[1].setString ("Blad we wczytywaniu pliku.");
	errorText[1].setPosition (textWindow.getPosition().x + (textWindow.getSize().x - errorText[1].getGlobalBounds().width) / 2, textWindow.getPosition().y + 120);
}


void postprocessing () {
	ofstream save ("properties.txt");
	save << saveName;
	save.close();
}


void drawAll () {
	
	// if we need to change the colors
	if (changeFrame) {
		changeFrame = false;
		
		for (int i = 0; i < 20; i++) {
			hexagon[i].setFillColor (colors[settings[settingFrame].hex[i] - 1]);
		}
	}
	
	// handling frames
	frame++;
	if (frame >= frameTime * 60) {
		frame = 0;
		settingFrame++;
		changeFrame = true;
		
		if (settingFrame == framesAmount) settingFrame = 0;
	}
	
	
	// hexagon drawin'
	for (int i = 0; i < 20; i++) okno.draw (hexagon[i]);
	okno.draw (button);
	for (int i = 0; i < 2; i++) okno.draw (buttonText[i]);
	
	// ekran nowego pliku
	if (newFile) {
		okno.draw (dark);
		okno.draw (textWindow);
		okno.draw (fileText);
		fileInput.drawTo (okno);
	}
	
	// ekran erroru
	if (fileError) {
		okno.draw (dark);
		okno.draw (textWindow);
		okno.draw (errorText[0]);
		okno.draw (errorText[1]);
	}
	
	// rysowanie intra
	if (intro.started) intro.drawFrame (okno);
}


bool fileReading (string fName) {
	
	fName = "../saves/" + fName;
	
	int n, fAm;
	float x;
	string g;
	
	// first we need to check whether the file is written propperly
	ifstream check (fName);
	
	if (!(check >> n)) return false;
	if (n < 1) return false;
	for (int i = 0; i < n; i++) {
		int a;
		
		for (int j = 0; j < 4; j++) {
			if (!(check >> a)) return false;
			if (a < 0 || 255 < a) return false;
		}
	}
	if (!(check >> fAm)) return false;
	if (!(check >> x)) return false;
	if (fAm < 1 || x <= 0) return false;
	for (int i = 0; i < fAm; i++) {
		for (int j = 0; j < 20; j++) {
			int a;
			if (!(check >> a)) return false;
			if (a < 1 || a > n) return false;
		}
	}
	if (check >> g) return false;
	
	check.close();
	
	
	// the actual file reading
	ifstream save (fName);
	
	save >> n;
	for (int i = 0; i < n; i++) {
		int r, g, b, a;
		save >> r >> g >> b >> a;
		
		colors.emplace_back (0, 0, 0, 0);
		colors[i].r = r;
		colors[i].g = g;
		colors[i].b = b;
		colors[i].a = a;
	}
	
	save >> framesAmount >> frameTime;
	
	for (int i = 0; i < framesAmount; i++) {
		settings.emplace_back ();
		
		for (int j = 0; j < 20; j++) {
			save >> settings[i].hex[j];
		}
	}
	
	save.close();
	
	frame = 0;
	settingFrame = 0;
	
	return true;
}


void reacting () {
	if (intro.started) return;
	
	if (newFile) {
    	fileInput.setPosition (Vector2f (textWindow.getPosition().x + (textWindow.getSize().x - fileInput.getGlobalBounds().width) / 2, textWindow.getPosition().y + 120));
    	
    	if (KBumped (Keyboard::Escape)) newFile = false;
    	
		if (!(textWindow.getGlobalBounds().contains (MPos(okno).x, MPos(okno).y))) {
			if (MBumped (Mouse::Left)) newFile = false;
		}
		
		if (KBumped (Keyboard::Return)) {
			newFile = false;
			tempSaveName = fileInput.getText ();
			
			if (!fileReading (tempSaveName)) {
				fileError = true;
			}
			else saveName = tempSaveName;
		}
	}
	
	else if (fileError) {
		if (KBumped (Keyboard::Escape) || KBumped (Keyboard::Return)) fileError = false;
		
		if (!(textWindow.getGlobalBounds().contains (MPos(okno).x, MPos(okno).y))) {
			if (MBumped (Mouse::Left)) fileError = false;
		}
	}
	
	else {
		if (button.getGlobalBounds().contains (MPos(okno).x, MPos(okno).y)) {
			button.setFillColor (Color (40, 40, 40));
			
			if (MBumped (Mouse::Left)) {
				button.setFillColor (Color (0, 0, 0));
				newFile = true;
				fileInput.setSelected (true);
			}
		}
		else button.setFillColor (Color (0, 0, 0));
	}
}




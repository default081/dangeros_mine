#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "menu.h"
#include <unistd.h>

using namespace std;
using namespace sf;

int menu(void){
	SoundBuffer buffer;

	RenderWindow window(VideoMode(1376, 768), "wit");
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/menu/111.png");
	menuTexture2.loadFromFile("images/menu/222.png");
	menuTexture3.loadFromFile("images/menu/333.png");
	aboutTexture.loadFromFile("images/menu/about.png");
	menuBackground.loadFromFile("images/menu/Penguins.jpg");

	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);

	Event event;
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(345, 0);

	if(!buffer.loadFromFile("sounds/GUI_Sound_Effects_by_Lokif/click.wav")){

	}
		Sound sound;
	sound.setBuffer(buffer);

	while(isMenu){
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;

		window.clear(Color(129, 181, 221));

		while(window.pollEvent(event)){
			if(event.type == Event::Closed){//для выхода через нажатие крестика
				window.close();
				exit(-1);
			}
		}

		if(IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))){
			menu1.setColor(Color::Blue);
			menuNum = 1;
			sound.play();
			// sleep(1);
			sound.pause();
			// sound.setPlayingOffset(sf::seconds(2));
		}

		if(IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))){
			menu2.setColor(Color::Blue);
			menuNum = 2;
		}
		if(IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))){
			menu3.setColor(Color::Blue);
			menuNum = 3;
		}

		if(Mouse::isButtonPressed(Mouse::Left)){//если нажато "начать" то выходим
			switch(menuNum){
				case 1: isMenu = false; break;
				case 2: window.draw(about); window.display(); while(!Keyboard::isKeyPressed(Keyboard::Escape)); break;
				case 3: isMenu = false; break;
			}
		}

		window.draw(menuBg);// рисуем компаненты
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}
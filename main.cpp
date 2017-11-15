#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "level.h"
#include "TinyXML/tinyxml.h"
#include "menu.h"

using namespace std;
using namespace sf;

class Entity{
public:
	vector<Object> obj;
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(){}
	virtual void update(float time) = 0;
	FloatRect getRect(){
		return FloatRect(w,y,w,h);
	}
};

class Player: public Entity{
public:
};

class Enemy: public Entity{
public:
};

int main(void){
	View view;
	menu(); //вызов метода с меню
	// Level lvl;
	// lvl.LoadFromFile("map/map.tmx");
	RenderWindow window(VideoMode(800, 600), "title");

	// view.reset(FloatRect(0, 0, 640, 480));
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}
			// menu();

		}

		window.setView(view);
		window.clear(Color(77,83,140));

		// lvl.Draw(window);
		window.display();
	}
}
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
	Entity(Image &image, String Name, float X, float Y, int W, int H){
		x = X; y = Y; w = W; h = H; name = Name;moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = true; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w/2, h/2);
	}
	virtual void update(float time) = 0;
	FloatRect getRect(){
		return FloatRect(w,y,w,h);
	}
};

class Player: public Entity{
public:
	int playerScore;
	enum{left, right, up, down, stay} state; //позиции нажатия клавиши
	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H):Entity(image, Name, X, Y, W, H){
		playerScore = 0; state = stay;
		obj = lev.GetAllObjects();
		if(name == "Palyer1"){
			sprite.setTextureRect(IntRect(4, 19, 2, h));
		}
	}
	void control(){
		if(Keyboard::isKeyPressed){
			if(Keyboard::isKeyPressed(Keyboard::Left)){
				state = left; speed = 0.1;
			}
			if(Keyboard::isKeyPressed(Keyboard::Right)){
				state = right; speed = 0.1;
			}
			if(Keyboard::isKeyPressed(Keyboard::up) && (onGround)){
				state = jump; dy = -0.6; onGround = false;
			}
			if(Keyboard::isKeyPressed(Keyboard::Down)){
				state = down;
			}
		}
	}
	void checkCollisionWithMap(float Dx, float Dy){

	}
};

class Enemy: public Entity{
public:
};

int main(void){
	View view;
	// menu(); //вызов метода с меню
	Level lvl;
	lvl.LoadFromFile("map.tmx");
	RenderWindow window(VideoMode(800, 600), "title");

	// view.reset(FloatRect(0, 0, 640, 480));
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}

		}

		window.setView(view);
		window.clear(Color(77,83,140));

		lvl.Draw(window);
		window.display();
	}
}
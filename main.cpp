#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "level.h"
#include "TinyXML/tinyxml.h"
#include "menu.h"
#include "view.h"

using namespace std;
using namespace sf;

class Entity{
public:
	std::vector<Object> obj;
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
		sprite.setOrigin(w/2, h/2);//смещаем центр персонажа в середину картинки
	}
	virtual void update(float time) = 0;
	FloatRect getRect(){//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return FloatRect(x,y,w,h);//эта ф-ция нужна для проверки столкновений 
	}
};

class Player: public Entity{
public:
	int playerScore;
	enum{left, right, up, down, jump, stay} state; //позиции нажатия клавиши
	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H):Entity(image, Name, X, Y, W, H){//конструктор который наследует конструктор класса Entity
		playerScore = 0; state = stay;
		obj = lev.GetAllObjects();//вектор obj содержит все обьекты на карте
		if(name == "Player1"){//если имя персонажа равно Player1
			sprite.setTextureRect(IntRect(4, 19, w, h));//то загружаем спрайт персонажа
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
			if(Keyboard::isKeyPressed(Keyboard::Up) && (onGround)){
				state = jump; dy = -0.6; onGround = false;
			}
			if(Keyboard::isKeyPressed(Keyboard::Down)){
				state = down;
			}
		}
	}
	void checkCollisionWithMap(float Dx, float Dy){
		for(int i = 0; i < obj.size(); i++){
			if(getRect().intersects(obj[i].rect)){
				if(obj[i].name == "solid"){
					if(Dy>0){
						y = obj[i].rect.top - h; dy = 0; onGround = true;
					}
					if(Dy<0){
						y = obj[i].rect.top + obj[i].rect.height; dy = 0;
					}
					if(Dx>0){
						x = obj[i]. rect.left - w;
					}
					if(Dx<0){
						x = obj[i].rect.left + obj[i].rect.width;
					}
				}
			}
		}
	}
	void update(float time){
		control();
		switch(state){
			case right: dx = speed; break;
			case left: dx= -speed; break;
			case up:break;
			case down:dx = 0; break;
			case stay: break;
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//проверяем столкновение по иксу
		y += dy*time;
		checkCollisionWithMap(0, dy);//проверяем столкновение по игрику
		sprite.setPosition(x+w/2, y+h/2);//даём позицию спрайту игрока
		if(health <= 0){//проверка на жищнь
			life = false;
		}
		if(!isMove){//если не двигаемся то скорость ровна 0
			speed = 0;
		}
		setPlayerCoordinateForView(x, y);
		if(life){//если мы живы то сосредотачиваем камеру на персонаже
			setPlayerCoordinateForView(x, y);
		}
		dy = dy + 0.0015*time;// ХЗ!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
};

class Enemy: public Entity{
public:
	Enemy(Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
		obj = lvl.GetObjects("solid");
		if(name == "EasyEnemy"){
			sprite.setTextureRect(IntRect(0,0,w,h));
			dx = 0.1;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{

		for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
				if (Dy>0)	{ y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0)	{ x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
				if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
		}
	}
	void update(float time){
		if(name == "EasyEnemy"){
			checkCollisionWithMap(dx,0);
			x += dx*time;
			sprite.setPosition(x+w/2, y+h/2);
			if (health <= 0){
				life = false;
			}
		}
	}
};

int main(void){

	RenderWindow window(VideoMode(800, 600), "title");
	view.reset(FloatRect(0, 0, 640, 480));

	// menu(); //вызов метода с меню
	Level lvl;
	lvl.LoadFromFile("map.tmx");

	// View view;



	Image heroImage;
	heroImage.loadFromFile("images/npc/player.png");
	Object player=lvl.GetObject("Player1");
	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 40, 30);
	
	Clock clock;

	while(window.isOpen()){
		Event event;
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}

		}
		p.update(time);
		window.setView(view);
		window.clear(Color(77,83,140));

		lvl.Draw(window);
		window.draw(p.sprite);//рисуем персонажа
		window.display();
	}
}






// использование сундуков и битвы:
	// 	if(getRect().intersects(obj[i].rect)){
	// 		if(Keyboard::isKeyPressed(Keyboard::Escape)){
	// 		if(obj[i].name == "ded"){
	// 			cout << ";;" << endl;
	// 		}
	// 	}			
	// }
	// }

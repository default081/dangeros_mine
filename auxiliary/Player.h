#ifndef PLAYER_H 
#define PLAYER_H

class Enemy{
public:
	Enemy();
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);

}

#endif
#include <SFML/Graphics.hpp>
#include <iostream>
<<<<<<< HEAD

=======
>>>>>>> 413a61f39e1112e2c8163968b192b9574d937368
using namespace std;
using namespace sf;

View view;

void setPlayerCoordinateForView(float x, float y){
	float tempX = x;
	float tempY = y;

	if(y > 624){
		tempY=624;
	}
	view.setCenter(tempX, tempY);
<<<<<<< HEAD
}
=======
}
>>>>>>> 413a61f39e1112e2c8163968b192b9574d937368

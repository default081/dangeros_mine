#include <iostream>
#include <stdlib.h>
int main(void){
/*лень было писать makefile:-)*/
system("g++ main.cpp -o main menu.cpp menu.h view.h -lsfml-graphics -lsfml-window -lsfml-system -ltinyxml -lsfml-audio");
}

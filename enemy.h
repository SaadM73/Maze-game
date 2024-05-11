#pragma once


//22i0822 Muhammad Shayan Ahmed :D
//22i0805 Shaheer Zaman :C
#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<string.h>
#include<cstdlib>
#include<ctime>

using namespace std;
using namespace sf;
class Enemy {
public:

	Texture tex;
	Sprite sprite;

	int x, y;


	virtual void draw() = 0;

};


class zombie :public Enemy {
public:

	void draw() {
		tex.loadFromFile("img/zombie.png");
		sprite.setTexture(tex);
		sprite.setScale(0.06, 0.06);
	}
};


class witch :public Enemy {
public:

	void draw() {
		tex.loadFromFile("img/witch.png");
		sprite.setTexture(tex);
		sprite.setScale(0.06, 0.06);
	}
};


class wolf :public Enemy {
public:

	void draw() {
		tex.loadFromFile("img/wolf.png");
		sprite.setTexture(tex);
		sprite.setScale(0.06, 0.06);
	}
};


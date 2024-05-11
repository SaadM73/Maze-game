#pragma once


#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
using namespace std;
using namespace sf;

class reward {

public:

	static int x;
	int ID;
	string name;


	Texture tex1;

	Sprite sp1;

	//	virtual void draw(RenderTarget& window,int x,int y) = 0;
	virtual void draw() = 0;



};


int reward::x = 0;

class sword : public reward {

public:



	void draw() {
		ID = x++;
		name = "SWORD";
		tex1.loadFromFile("img/sword.png");
		sp1.setTexture(tex1);
		sp1.setScale(0.03, 0.03);
	}

};


class shield : public reward {
public:


	void draw() {
		ID = x++;
		name = "SHIELD";
		tex1.loadFromFile("img/shield.png");
		sp1.setTexture(tex1);
		sp1.setScale(0.04, 0.04);
	}
};


class arrow : public reward {
public:
	void draw() {
		ID = x++;
		name = "ARROW";
		tex1.loadFromFile("img/arrow.png");
		sp1.setTexture(tex1);
		sp1.setScale(0.02, 0.02);
	}
};

class axe : public reward {
public:
	void draw() {
		ID = x++;
		name = "AXE";
		tex1.loadFromFile("img/axe.png");
		sp1.setTexture(tex1);
		sp1.setScale(0.015, 0.015);
	}
};


class treasure : public reward {
public:
	void draw() {
		ID = x++;
		name = "Treasure";
		tex1.loadFromFile("img/treasure.png");
		sp1.setTexture(tex1);
		sp1.setScale(0.05, 0.05);
	}
};

class SP : public reward {
public:
	void draw() {
		ID = x++;
		name = "shortest";
		tex1.loadFromFile("img/sp.png");
		sp1.setTexture(tex1);
		sp1.setScale(0.015, 0.015);
	}
};



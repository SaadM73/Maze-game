#pragma once
#include"game.h"

#include <SFML/Graphics.hpp>
#include<string.h>

using namespace sf;
class Player {
public:


	Texture tex;
	Sprite sprite;
	float speed = 1;
	int x, y;

	int health;

	int cellx, celly;




	int cellSize = 40;
	int gridHeight = 800;
	int gridWidth = 800;



	Player()
	{
		health = 5;


		tex.loadFromFile("img/GREENC.png");
		sprite.setTexture(tex);
		x = 10; y = 10;
		sprite.setPosition(x, y);
		sprite.setScale(0.25, 0.25);

		cellx = 0;
		celly = 0;
	}


	void moveDown() {
		if (celly < gridHeight - 1) {  // Ensure the player doesn't move out of grid bounds
			celly++;
			y += cellSize;
			sprite.setPosition(x, y);
		}
	}

	void moveUp() {
		if (celly > 0) {  // Ensure the player doesn't move out of grid bounds
			celly--;
			y -= cellSize;
			sprite.setPosition(x, y);
		}
	}

	void moveLeft() {
		if (cellx > 0) {  // Ensure the player doesn't move out of grid bounds
			cellx--;
			x -= cellSize;
			sprite.setPosition(x, y);
		}
	}

	void moveRight() {
		if (cellx < gridWidth - 1) {  // Ensure the player doesn't move out of grid bounds
			cellx++;
			x += cellSize;
			sprite.setPosition(x, y);
		}
	}


	//void move(int dx, int dy) {
	//	// Update the player's position
	//	x += dx * speed;
	//	y += dy * speed;

	//	// Update the sprite's position to match the player's new position
	//	sprite.setPosition(x, y);
	//}


};
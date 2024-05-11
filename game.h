// Game->h
#ifndef GAME_H
#define GAME_H

#include <time.h>

#include <iostream>
#include <fstream>

using namespace std;

const char title[] = "DS-Project, Spring-2024";
//using namespace sf;

#include <SFML/Audio.hpp>

#include <SFML/Graphics.hpp>
#include <stack>
#include <cstdlib>
#include <ctime>
#include"player.h"
#include"reward.h"
#include"enemy.h"
#include"AVL.h"
#include"ProgressBar.h"
#include"shortestpath.h"



RectangleShape createRectangle(float width, float height) {
    RectangleShape rectangle;
    rectangle.setSize({ width, height });
    return rectangle;
}

void resizeWindow(sf::RenderWindow& window, unsigned int width, unsigned int height) {
    window.setSize(sf::Vector2u(width, height));

}


class Game {
public:

    float checkCooldown = 0.0f;
    float pressCooldown = 0.0f;

    Font style;
    Text livesText;

    Player* p1;
    reward* r1;
    reward* r2;
    reward* r3;
    reward* r4;
    reward* r5;
    reward* r6;
    reward* r7;
    reward* r8;
    reward* r9;
    reward* r10;
    reward* r11;
    reward* r12;

    int shieldcount = 0;
    int swordcount = 0;
    int arrowcount = 0;
    int axecount = 0;

    Enemy* e1;
    Enemy* e2;
    Enemy* e3;
    Enemy* e4;
    Enemy* e5;
    Enemy* e6;


    reward* dispSword;
    reward* dispShield;
    reward* dispArrow;
    reward* dispAxe;
    reward* Treasure;
    reward* sp;


    AVLTree avlReward;


    sf::Music death;


    Text inventory;

    bool checkSword = false;
    bool checkArrow = false;
    bool checkShield = false;
    bool checkAxe = false;



    Sprite gameBG;
    Texture GBG;


    //Sprite treasure;
    //Texture treasuret;

    Text levelText; // Text to display the level
    Text highScoreText;//Text to display highscore
    // Text livesText; //Text to display available lives
    Text scoreText; // Text to display the current score
    Text Addt; // Text to indicate the new addons which are being dropped 

    //texts for the pause window
    Text mains;//displaying the main pause in the center
    Text rg;//displaying resume game
    Text guides;//dipslaying guides
    Text ViewAVL;
    Text theend;//displaying the end
    Text hst;

    Sprite Gameover;//sprite for the gameover screen
    Texture Gameot;//texture for the gameover screen

    Sprite winner;//sprite for the winner screen
    Texture wint;//texture for the winner screen


    //int pas;
    Sprite pb; // Pause background sprite
    Texture pt;
    Font font;

    sf::Clock pathTimer;
    bool showPath;
    std::vector<PathNode*> path; // Assuming this is filled somewhere else in your code
    float pathDisplayDuration; // seconds

    int pma;
    int highScore;
    bool paused;
    int c_score;

    const int width;
    const int height;
    const int cellSize = 40;
    int gridWidth; // Number of cells horizontally
    int gridHeight; // Number of cells vertically
    bool** occupied;

    struct Cell {
        int x, y;
        bool visited = false;
        bool walls[4] = { true, true, true, true };
        bool present = false;
    };

    Cell grid[20][20]; // Example grid size, adjust as needed


    Game(int width, int height) : width(width), height(height), cellSize(40), gridWidth(width / cellSize), gridHeight(height / cellSize) {

        srand(time(0));



        style.loadFromFile("img/Raleway-Black.ttf");

        p1 = new Player;
        r1 = new sword; // sword
        r2 = new sword;
        r3 = new sword;
        r4 = new shield;
        r5 = new shield;
        r6 = new shield;
        r7 = new arrow;
        r8 = new arrow;
        r9 = new arrow;
        r10 = new axe;
        r11 = new axe;
        r12 = new axe;

        e1 = new zombie;
        e2 = new zombie;
        e3 = new zombie;
        e4 = new wolf;
        e5 = new wolf;
        e6 = new witch;

        dispSword = new sword;
        dispShield = new shield;
        dispArrow = new arrow;
        dispAxe = new axe;
        Treasure = new treasure;

        pathDisplayDuration = 5.0f;
        showPath = false;

        ifstream highScoreFile("i220822_highestcore.txt");
        if (highScoreFile.is_open())
        {
            highScoreFile >> highScore;
            highScoreFile.close();
        }
        highScoreText.setString("High Score: " + std::to_string(highScore));


        GBG.loadFromFile("img/gameBG.jpg");
        gameBG.setTexture(GBG);
        gameBG.setScale(2, 2);





        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(10, 640);




        highScoreText.setFont(font);
        highScoreText.setCharacterSize(24);
        highScoreText.setFillColor(Color::White);
        highScoreText.setPosition(10, 670);	// Position below the total_Score text

        Addt.setFont(font);
        Addt.setCharacterSize(24);
        Addt.setFillColor(Color::White);
        Addt.setPosition(10, 730);	// Position below the lives text

        mains.setFont(font);
        mains.setString("Game Paused");
        mains.setCharacterSize(65);
        mains.setFillColor(Color::White);
        mains.setPosition(200, 200);

        rg.setFont(font);
        rg.setString("   Resume Game");
        rg.setCharacterSize(28);
        rg.setFillColor(Color::White);
        rg.setPosition(300, 350);

        ViewAVL.setFont(font);
        ViewAVL.setString("   View InOrder AVL");
        ViewAVL.setCharacterSize(28);
        ViewAVL.setFillColor(Color::White);
        ViewAVL.setPosition(270, 650);

        guides.setFont(font);
        guides.setString("   Guide");
        guides.setCharacterSize(28);
        guides.setFillColor(Color::White);
        guides.setPosition(350, 450);

        hst.setFont(font);
        hst.setString("   High Score");
        hst.setCharacterSize(28);
        hst.setFillColor(Color::White);
        hst.setPosition(325, 550);

        theend.setFont(font);
        theend.setString("   End Game");
        theend.setCharacterSize(28);
        theend.setFillColor(Color::White);
        theend.setPosition(325, 550);


        wint.loadFromFile("img/win.jpg");
        winner.setTexture(wint);
        winner.setScale(1.25, 1);



        pt.loadFromFile("img/background1.jpg");
        font.loadFromFile("img/Raleway-Black.ttf");
        pb.setTexture(pt);
        pb.setScale(2, 1.5);


        srand(time(nullptr));
        for (int y = 0; y < gridHeight; y++) {
            for (int x = 0; x < gridWidth; x++) {
                grid[y][x].x = x;
                grid[y][x].y = y;
            }
        }

        gridWidth = width / cellSize; // Number of cells horizontally
        gridHeight = height / cellSize; // Number of cells vertically

        // Dynamically allocate the 2D array
        occupied = new bool* [gridHeight];
        for (int i = 0; i < gridHeight; i++) {
            occupied[i] = new bool[gridWidth];
            std::fill(occupied[i], occupied[i] + gridWidth, false);
        }

        int x = rand() % 18 + 1;
        int y = rand() % 18 + 1;
        x *= 40;
        y *= 40;

        r1->draw();

        r1->sp1.setPosition(x, y);
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;
        x += 10;
        y += 10;



        r2->draw();

        r2->sp1.setPosition(x, y);
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;
        x += 10;
        y += 10;


        r3->draw();

        r3->sp1.setPosition(x, y);
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;
        x += 10;
        y += 10;

        r4->draw();
        r4->sp1.setPosition(x, y);
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;

        r5->draw();
        r5->sp1.setPosition(x, y);
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;




        r6->draw();

        r6->sp1.setPosition(x, y);
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;




        r7->draw();

        r7->sp1.setPosition(x, y);
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;

        r8->draw();

        r8->sp1.setPosition(x, y);
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;


        r9->draw();

        r9->sp1.setPosition(x, y);
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;





        r10->draw();
        //       r9->sp1.setScale(0.5, 0.5);
        r10->sp1.setPosition(x, y);
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;
        y += 10;

        r11->draw();

        r11->sp1.setPosition(x, y);
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;
        y += 10;

        r12->draw();

        r12->sp1.setPosition(x, y);


        dispSword->draw();
        dispSword->sp1.setPosition(990, 290);

        dispShield->draw();
        dispShield->sp1.setPosition(1030, 280);

        dispArrow->draw();
        dispArrow->sp1.setPosition(1090, 280);

        dispAxe->draw();
        dispAxe->sp1.setPosition(1140, 290);

        Treasure->draw();
        Treasure->sp1.setPosition(820, 700);


        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;
        e1->draw();
        e1->sprite.setPosition(x, y);


        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;
        e2->draw();
        e2->sprite.setPosition(x, y);


        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;
        e3->draw();
        e3->sprite.setPosition(x, y);


        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;
        y += 10;
        e4->draw();
        e4->sprite.setPosition(x, y);


        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
        x *= 40;
        y *= 40;
        y += 10;
        e5->draw();
        e5->sprite.setPosition(x, y);


        e6->draw();
        e6->sprite.setPosition(730, 760);



    }

    bool checkCollision(Sprite a, Sprite b)
    {
        return a.getGlobalBounds().intersects(b.getGlobalBounds());
    }


    void collision() {
        if (checkCollision(p1->sprite, r1->sp1)) {
            p1->health += 2;
            r1->sp1.setPosition(-30, -30);
            checkSword = true;
            swordcount++;
            avlReward.insert(r1);



        }

        if (checkCollision(p1->sprite, r2->sp1)) {
            p1->health += 2;
            r2->sp1.setPosition(-30, -30);
            checkSword = true;
            swordcount++;
            avlReward.insert(r2);

        }

        if (checkCollision(p1->sprite, r3->sp1)) {
            p1->health += 2;
            r3->sp1.setPosition(-30, -30);
            checkSword = true;
            swordcount++;
            avlReward.insert(r3);

        }

        if (checkCollision(p1->sprite, r4->sp1)) {
            p1->health += 1;
            r4->sp1.setPosition(-30, -30);
            checkShield = true;
            shieldcount++;
            avlReward.insert(r4);

        }

        if (checkCollision(p1->sprite, r5->sp1)) {
            p1->health += 1;
            r5->sp1.setPosition(-30, -30);
            checkShield = true;
            shieldcount++;
            avlReward.insert(r5);

        }

        if (checkCollision(p1->sprite, r6->sp1)) {
            p1->health += 1;
            r6->sp1.setPosition(-30, -30);
            checkShield = true;
            shieldcount++;
            avlReward.insert(r6);

        }

        if (checkCollision(p1->sprite, r7->sp1)) {
            p1->health += 3;
            r7->sp1.setPosition(-30, -30);
            checkArrow = true;
            arrowcount++;
            avlReward.insert(r7);

        }

        if (checkCollision(p1->sprite, r8->sp1)) {
            p1->health += 3;
            r8->sp1.setPosition(-30, -30);
            checkArrow = true;
            arrowcount++;
            avlReward.insert(r8);

        }

        if (checkCollision(p1->sprite, r9->sp1)) {
            p1->health += 3;
            r9->sp1.setPosition(-30, -30);
            checkArrow = true;
            arrowcount++;
            avlReward.insert(r9);

        }

        if (checkCollision(p1->sprite, r10->sp1)) {
            p1->health += 5;
            r10->sp1.setPosition(-30, -30);
            checkAxe = true;
            axecount++;
            avlReward.insert(r10);

        }

        if (checkCollision(p1->sprite, r11->sp1)) {
            p1->health += 5;
            r11->sp1.setPosition(-30, -30);
            checkAxe = true;
            axecount++;
            avlReward.insert(r11);

        }

        if (checkCollision(p1->sprite, r12->sp1)) {
            p1->health += 5;
            r12->sp1.setPosition(-30, -30);
            checkAxe = true;
            axecount++;
            avlReward.insert(r12);

        }



        //zombies
        if (checkCollision(p1->sprite, e1->sprite)) {


            death.openFromFile("death.ogg");
            death.setPosition(0, 0, 0);
            death.setVolume(100);
            death.setLoop(0);
            death.play();

            if (checkAxe || checkArrow || checkSword || checkShield)
            {
                p1->health += 5;
                e1->sprite.setPosition(-30, -30);
                // Remove an item based on priority: Axe > Sword > Arrow > Shield
                if (checkAxe && axecount > 0) {
                    avlReward.remove(r10->ID); // Assuming r10 is an Axe
                    axecount--;
                    checkAxe = (axecount > 0);
                }
                else if (checkSword && swordcount > 0) {
                    avlReward.remove(r1->ID); // Assuming r1 is a Sword
                    swordcount--;
                    checkSword = (swordcount > 0);
                }
                else if (checkArrow && arrowcount > 0) {
                    avlReward.remove(r7->ID); // Assuming r7 is an Arrow
                    arrowcount--;
                    checkArrow = (arrowcount > 0);
                }
                else if (checkShield && shieldcount > 0) {
                    avlReward.remove(r4->ID); // Assuming r4 is a Shield
                    shieldcount--;
                    checkShield = (shieldcount > 0);
                }
            }

            else
            {
                p1->health -= 10;

            }
        }


        if (checkCollision(p1->sprite, e2->sprite)) {


            death.openFromFile("death.ogg");
            death.setPosition(0, 0, 0);
            death.setVolume(100);
            death.setLoop(0);
            death.play();
            if (checkAxe || checkArrow || checkSword || checkShield)
            {
                p1->health += 5;
                e2->sprite.setPosition(-30, -30);
                // Remove an item based on priority: Axe > Sword > Arrow > Shield
                if (checkAxe && axecount > 0) {
                    avlReward.remove(r10->ID); // Assuming r10 is an Axe
                    axecount--;
                    checkAxe = (axecount > 0);
                }
                else if (checkSword && swordcount > 0) {
                    avlReward.remove(r1->ID); // Assuming r1 is a Sword
                    swordcount--;
                    checkSword = (swordcount > 0);
                }
                else if (checkArrow && arrowcount > 0) {
                    avlReward.remove(r7->ID); // Assuming r7 is an Arrow
                    arrowcount--;
                    checkArrow = (arrowcount > 0);
                }
                else if (checkShield && shieldcount > 0) {
                    avlReward.remove(r4->ID); // Assuming r4 is a Shield
                    shieldcount--;
                    checkShield = (shieldcount > 0);
                }
            }
            else
            {
                p1->health -= 10;

            }
        }


        if (checkCollision(p1->sprite, e3->sprite)) {


            death.openFromFile("death.ogg");
            death.setPosition(0, 0, 0);
            death.setVolume(100);
            death.setLoop(0);
            death.play();
            if (checkAxe || checkArrow || checkSword || checkShield)
            {
                p1->health += 5;
                e3->sprite.setPosition(-30, -30);
                // Remove an item based on priority: Axe > Sword > Arrow > Shield
                if (checkAxe && axecount > 0) {
                    avlReward.remove(r10->ID); // Assuming r10 is an Axe
                    axecount--;
                    checkAxe = (axecount > 0);
                }
                else if (checkSword && swordcount > 0) {
                    avlReward.remove(r1->ID); // Assuming r1 is a Sword
                    swordcount--;
                    checkSword = (swordcount > 0);
                }
                else if (checkArrow && arrowcount > 0) {
                    avlReward.remove(r7->ID); // Assuming r7 is an Arrow
                    arrowcount--;
                    checkArrow = (arrowcount > 0);
                }
                else if (checkShield && shieldcount > 0) {
                    avlReward.remove(r4->ID); // Assuming r4 is a Shield
                    shieldcount--;
                    checkShield = (shieldcount > 0);
                }
            }
            else
            {
                p1->health -= 10;

            }
        }

        //wolfs
        if (checkCollision(p1->sprite, e4->sprite)) {


            death.openFromFile("death.ogg");
            death.setPosition(0, 0, 0);
            death.setVolume(100);
            death.setLoop(0);
            death.play();
            if (checkAxe || checkArrow || checkSword || checkShield)
            {
                p1->health += 10;
                e4->sprite.setPosition(-30, -30);
                // Remove an item based on priority: Axe > Sword > Arrow > Shield
                if (checkAxe && axecount > 0) {
                    avlReward.remove(r10->ID); // Assuming r10 is an Axe
                    axecount--;
                    checkAxe = (axecount > 0);
                }
                else if (checkSword && swordcount > 0) {
                    avlReward.remove(r1->ID); // Assuming r1 is a Sword
                    swordcount--;
                    checkSword = (swordcount > 0);
                }
                else if (checkArrow && arrowcount > 0) {
                    avlReward.remove(r7->ID); // Assuming r7 is an Arrow
                    arrowcount--;
                    checkArrow = (arrowcount > 0);
                }
                else if (checkShield && shieldcount > 0) {
                    avlReward.remove(r4->ID); // Assuming r4 is a Shield
                    shieldcount--;
                    checkShield = (shieldcount > 0);
                }
            }
            else
            {
                p1->health -= 20;

            }
        }


        if (checkCollision(p1->sprite, e5->sprite)) {


            death.openFromFile("death.ogg");
            death.setPosition(0, 0, 0);
            death.setVolume(100);
            death.setLoop(0);
            death.play();
            if (checkAxe || checkArrow || checkSword || checkShield)
            {
                p1->health += 10;
                e5->sprite.setPosition(-30, -30);
                // Remove an item based on priority: Axe > Sword > Arrow > Shield
                if (checkAxe && axecount > 0) {
                    avlReward.remove(r10->ID); // Assuming r10 is an Axe
                    axecount--;
                    checkAxe = (axecount > 0);
                }
                else if (checkSword && swordcount > 0) {
                    avlReward.remove(r1->ID); // Assuming r1 is a Sword
                    swordcount--;
                    checkSword = (swordcount > 0);
                }
                else if (checkArrow && arrowcount > 0) {
                    avlReward.remove(r7->ID); // Assuming r7 is an Arrow
                    arrowcount--;
                    checkArrow = (arrowcount > 0);
                }
                else if (checkShield && shieldcount > 0) {
                    avlReward.remove(r4->ID); // Assuming r4 is a Shield
                    shieldcount--;
                    checkShield = (shieldcount > 0);
                }
            }
            else
            {
                p1->health -= 20;

            }
        }


        //witch
        if (checkCollision(p1->sprite, e6->sprite)) {


            death.openFromFile("death.ogg");
            death.setPosition(0, 0, 0);
            death.setVolume(100);
            death.setLoop(0);
            death.play();
            if (checkAxe && checkArrow && checkSword && checkShield)
            {
                p1->health += 55;
                e6->sprite.setPosition(-30, -30);
                // Remove an item based on priority: Axe > Sword > Arrow > Shield
                if (checkAxe && axecount > 0) {
                    avlReward.remove(r10->ID); // Assuming r10 is an Axe
                    axecount--;
                    checkAxe = (axecount > 0);
                }
                else if (checkSword && swordcount > 0) {
                    avlReward.remove(r1->ID); // Assuming r1 is a Sword
                    swordcount--;
                    checkSword = (swordcount > 0);
                }
                else if (checkArrow && arrowcount > 0) {
                    avlReward.remove(r7->ID); // Assuming r7 is an Arrow
                    arrowcount--;
                    checkArrow = (arrowcount > 0);
                }
                else if (checkShield && shieldcount > 0) {
                    avlReward.remove(r4->ID); // Assuming r4 is a Shield
                    shieldcount--;
                    checkShield = (shieldcount > 0);
                }
            }
            else
            {
                p1->health -= 1000;
            }
        }

    }


    void start() {
        RenderWindow window(sf::VideoMode(width + 400, height), "Random Maze Generator"); // Width + 200 for UI
        generateMaze();
        srand(time(0));
        Clock clock;
        float timer = 0;

        // Create two views
        sf::View gameView(sf::FloatRect(0, 0, width, height));
        sf::View uiView(sf::FloatRect(0, 0, width + 200, height));

        // Set the viewport for the game view (occupying the left part of the window)
        gameView.setViewport(sf::FloatRect(0.f, 0.f, float(width) / (width + 200), 1.f));

        // Set the viewport for the UI view (occupying the right part of the window)
        uiView.setViewport(sf::FloatRect(float(width) / (width + 200), 0.f, 200.f / (width + 200), 1.f));


        ProgressBar progressBar(850, 50, 300, 30, 100);


        while (window.isOpen()) {

            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            window.draw(gameBG);
            progressBar.setProgress(p1->health);
            progressBar.draw(window);

            updateHS();

            if (p1->health <= 0) // loose 
            {

                // Game Over logic goes here
                Text gameOverText;


                Gameot.loadFromFile("img/death.jpg");
                Gameover.setTexture(Gameot);
                Gameover.setScale(1.35, 0.75);
                gameOverText.setFont(font);
                gameOverText.setCharacterSize(80);
                gameOverText.setFillColor(Color::White);
                gameOverText.setPosition(450, 400);	// Position the game over text in the middle of the screen
                gameOverText.setString("You die :) ");

                while (window.isOpen())
                {
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == Event::Closed)
                        {
                            window.close();
                        }
                    }
                    resizeWindow(window, 790, 800);
                    window.clear();
                    window.draw(Gameover);
                    window.draw(gameOverText);
                    window.display();

                }
            }


            if (p1->health > 0 && p1->sprite.getPosition().x > 800)//win
            {


                while (window.isOpen())
                {
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == Event::Closed)
                        {
                            window.close();
                        }
                    }

                    window.clear();
                    window.draw(winner);
                    resizeWindow(window, 966, 800);
                    window.display();
                }
            }

            Text scoretxt("Health : ", style, 40);      // SHOWING score
            scoretxt.setPosition(820, 180);
            scoretxt.setString("Score : " + std::to_string(p1->health));
            scoretxt.setFillColor(Color::Black);


            Text inventorytxt("Inventory : ", style, 30);      // SHOWING inve
            inventorytxt.setPosition(820, 280);
            inventorytxt.setFillColor(Color::Black);



            window.draw(p1->sprite);

            window.draw(scoretxt);
            window.draw(inventorytxt);

            ////shortest path implementation
            //if (checkCollision(p1->sprite, sp->sp1)) {
            //    std::vector<std::vector<bool>> walkable(gridHeight, std::vector<bool>(gridWidth, true));  // Assuming all cells are initially walkable
            //    // Define walkable areas based on your game's logic
            //    for (int i = 0; i < gridHeight; i++) {
            //        for (int j = 0; j < gridWidth; j++) {
            //            walkable[i][j] = !grid[i][j].walls[0]; // Example: adjust based on actual wall positions
            //        }
            //    }
            //    PathNode start(p1->cellx, p1->celly);
            //    PathNode end(800, 800);  // Define target based on your game
            //    std::vector<PathNode*> path = findShortestPath(&start, &end, walkable);

            //    // Now handle the path visualization or usage
            //    if (!path.empty()) {
            //        visualizePath(window, path, 40); // Assuming cellSize is 40
            //    }
            //}
            //if (showPath && pathTimer.getElapsedTime().asSeconds() < pathDisplayDuration) {
            //    visualizePath(window, path, 40); // Assuming cellSize is 40
            //}
            //else {
            //    showPath = false; // Stop showing the path after the duration expires
            //}

            window.draw(r1->sp1);
            window.draw(r2->sp1);
            window.draw(r3->sp1);
            window.draw(r4->sp1);
            window.draw(r5->sp1);
            window.draw(r6->sp1);
            window.draw(r7->sp1);
            window.draw(r8->sp1);
            window.draw(r9->sp1);
            window.draw(r10->sp1);
            window.draw(r11->sp1);
            window.draw(r12->sp1);
            window.draw(Treasure->sp1);
            //window.draw(sp->sp1);
            window.draw(e1->sprite);
            window.draw(e2->sprite);
            window.draw(e3->sprite);
            window.draw(e4->sprite);
            window.draw(e5->sprite);
            window.draw(e6->sprite);

            if (checkSword && swordcount > 0) {
                window.draw(dispSword->sp1);
            }


            if (checkShield && shieldcount > 0) {
                window.draw(dispShield->sp1);
            }


            if (checkArrow && arrowcount > 0) {
                window.draw(dispArrow->sp1);
            }


            if (checkAxe && axecount > 0) {
                window.draw(dispAxe->sp1);
            }

            collision();


            pressCooldown -= time;
            int tempCordX = p1->cellx;
            int tempCordY = p1->celly;
            int direction = 0;

            //pause
            if (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::P))	// Pause/unpause the game if P is pressed
            {
                pause_game(window);
            }

            if (Keyboard::isKeyPressed(sf::Keyboard::Down) && pressCooldown <= 0.0f) {
                if (!grid[p1->celly][p1->cellx].walls[2]) {  // Check if there's no bottom wall
                    p1->moveDown();
                    pressCooldown = 0.2f;
                }
            }

            if (Keyboard::isKeyPressed(sf::Keyboard::Right) && pressCooldown <= 0.0f) {
                if (!grid[p1->celly][p1->cellx].walls[1]) {  // Check if there's no right wall
                    p1->moveRight();
                    pressCooldown = 0.2f;
                }
            }

            if (Keyboard::isKeyPressed(sf::Keyboard::Left) && pressCooldown <= 0.0f) {
                if (p1->cellx > 0 && !grid[p1->celly][p1->cellx].walls[3]) {  // Check if there's no left wall
                    p1->moveLeft();
                    pressCooldown = 0.2f;
                }
            }

            if (Keyboard::isKeyPressed(sf::Keyboard::Up) && pressCooldown <= 0.0f) {
                if (p1->celly > 0 && !grid[p1->celly][p1->cellx].walls[0]) {  // Check if there's no top wall
                    p1->moveUp();
                    pressCooldown = 0.2f;
                }
            }







            float wallThickness = 1.0f; // Thickness of the walls
            RectangleShape verticalWall = createRectangle(wallThickness, cellSize); // Vertical wall
            RectangleShape horizontalWall = createRectangle(cellSize, wallThickness);


            verticalWall.setFillColor(sf::Color::Black);
            horizontalWall.setFillColor(sf::Color::Black);

            for (int y = 0; y < gridHeight; y++) {
                for (int x = 0; x < gridWidth; x++) {
                    Cell& cell = grid[y][x];

                    // Position calculations
                    float posX = x * cellSize;
                    float posY = y * cellSize;

                    // Draw top wall
                    if (cell.walls[0]) {
                        horizontalWall.setPosition(posX, posY);
                        window.draw(horizontalWall);
                    }

                    // Draw right wall
                    if (cell.walls[1]) {
                        verticalWall.setPosition(posX + cellSize - wallThickness, posY);
                        window.draw(verticalWall);
                    }

                    // Draw bottom wall
                    if (cell.walls[2]) {
                        horizontalWall.setPosition(posX, posY + cellSize - wallThickness);
                        window.draw(horizontalWall);
                    }

                    // Draw left wall
                    if (cell.walls[3]) {
                        verticalWall.setPosition(posX, posY);
                        window.draw(verticalWall);
                    }
                }
            }
            window.display();
        }
    }


    void generateMaze() {
        std::stack<Cell*> stack;
        stack.push(&grid[0][0]);
        grid[0][0].visited = true;
        srand(time(0));

        while (!stack.empty()) {
            Cell* current = stack.top();
            int count;
            Cell** neighbors = getUnvisitedNeighbors(*current, count);

            if (count > 0) {
                int index = rand() % count;
                Cell* next = neighbors[index];
                removeWall(*current, *next);
                next->visited = true;
                stack.push(next);
            }
            else {
                stack.pop();
            }
        }
        // STARTING CELL
        grid[0][0].walls[0] = true;
        grid[0][0].walls[3] = true;


        grid[19][19].walls[0] = false;
        grid[19][19].walls[1] = false;
        grid[19][19].walls[2] = true;
        grid[19][19].walls[3] = false;


        // ENDING CELL
    }


    void removeWall(Cell& current, Cell& next) {
        int x = current.x - next.x;
        int y = current.y - next.y;
        if (x == 1) {
            current.walls[3] = false;
            next.walls[1] = false;
        }
        else if (x == -1) {
            current.walls[1] = false;
            next.walls[3] = false;
        }
        if (y == 1) {
            current.walls[0] = false;
            next.walls[2] = false;
        }
        else if (y == -1) {
            current.walls[2] = false;
            next.walls[0] = false;
        }
    }


    Cell** getUnvisitedNeighbors(Cell& cell, int& count) {
        static Cell* neighbors[4]; // Holds up to 4 neighbors
        count = 0;

        int x = cell.x;
        int y = cell.y;

        // Check all four possible neighbor positions and ensure they have not been visited
        if (x > 0 && !grid[y][x - 1].visited)
            neighbors[count++] = &grid[y][x - 1];
        if (x < gridWidth - 1 && !grid[y][x + 1].visited)
            neighbors[count++] = &grid[y][x + 1];
        if (y > 0 && !grid[y - 1][x].visited)
            neighbors[count++] = &grid[y - 1][x];
        if (y < gridHeight - 1 && !grid[y + 1][x].visited)
            neighbors[count++] = &grid[y + 1][x];

        return neighbors;
    }


    void di()
    {
        Text instructions;
        instructions.setFont(font);
        instructions.setCharacterSize(24);
        instructions.setFillColor(Color::White);
        instructions.setPosition(50, 50);
        instructions.setString("\t\t\t\t\t\t\tRules\n\n\n\n"
            "1.Use the arrow keys to navigate through the maze.\n\n\n"
            "2.Locate and collect the weapon before attempting to \n  engage any enemies.\n\n\n"
            "3.Press 'P' to pause the game at any time\n\n\n"
            "4.Once armed, approach an enemy to attack and defeat them."
            "5.Press 'Esc' to return to the main menu.");
        RenderWindow window(VideoMode(780, 780), "How to operate?", Style::Close);
        while (window.isOpen())
        {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::Num4))
            {
                return;
            }

            window.clear();
            window.draw(pb);
            window.draw(instructions);
            window.display();
        }
    }


    void ds()
    {

        ifstream file("i220822_highestcore.txt");
        if (!file.is_open())
        {
            cout << "Highscore file couldn't be openened :(" << endl;
        }
        RenderWindow window(VideoMode(780, 780), "Highest Score Even Made?", Style::Close);
        Text  hst;
        Text note;
        hst.setFont(font);
        // hst.setString("Press esc to end");
        hst.setCharacterSize(24);
        hst.setFillColor(Color::White);
        hst.setPosition(150, 280);
        note.setFont(font);
        note.setCharacterSize(24);
        note.setFillColor(Color::Red);
        note.setPosition(100, 730);
        note.setString("Note: Press Esc to return to the main menu.");

        string line;
        string  hs;
        hs = "The highest score ever made is: ";
        while (getline(file, line)) {
            hs += line + "\n";
        }

        hst.setString(hs);


        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                return;
            }

            window.clear(Color::Black);
            window.draw(pb);
            window.draw(hst);
            window.draw(note);
            window.display();
        }
    }


    void pause_game(RenderWindow& window)
    {
        Game g(800, 800);
        paused = !paused;
        if (paused)
        {
            RenderWindow pauseWindow(VideoMode(780, 780), "Time is Stopped, you are safe for the mean time", Style::Close);
            int pma = 0;  // Initialize the selection index

            while (pauseWindow.isOpen())
            {
                Event e;
                while (pauseWindow.pollEvent(e))
                {
                    if (e.type == Event::Closed)
                        window.close();

                    if (e.type == Event::KeyPressed)
                    {
                        if (e.key.code == Keyboard::Down)
                        {
                            pma = (pma + 1) % 4;  // Update to include 4 options
                        }
                        else if (e.key.code == Keyboard::Up)
                        {
                            pma = (pma + 3) % 4;  // Update to cycle back correctly
                        }
                        else if (e.key.code == Keyboard::Enter)
                        {
                            switch (pma) {
                            case 0:
                                pauseWindow.close();
                                paused = !paused;
                                break;
                            case 1:
                                di();  // Display instructions
                                break;
                            case 2:
                                pauseWindow.close();
                                window.close();
                                break;
                            case 3:
                                avlReward.display();  // Function to handle the AVL viewing
                                avlReward.checkBalanceRoot();
                                break;
                            }
                        }

                        // Update colors based on the selected item
                        rg.setFillColor(pma == 0 ? sf::Color::Yellow : sf::Color::White);
                        guides.setFillColor(pma == 1 ? sf::Color::Yellow : sf::Color::White);
                        theend.setFillColor(pma == 2 ? sf::Color::Yellow : sf::Color::White);
                        ViewAVL.setFillColor(pma == 3 ? sf::Color::Yellow : sf::Color::White);
                    }

                    pauseWindow.clear();
                    pauseWindow.draw(pb);
                    pauseWindow.draw(mains);
                    pauseWindow.draw(rg);
                    pauseWindow.draw(guides);
                    pauseWindow.draw(theend);
                    pauseWindow.draw(ViewAVL);  // Make sure to draw the new option
                    pauseWindow.display();
                }
            }
        }
    }


    void updateHS()
    {
        if (p1->health > highScore)
        {
            highScore = p1->health;
            ofstream highScoreFile("i220822_highestcore.txt");
            if (highScoreFile.is_open())
            {
                highScoreFile << highScore;
                highScoreFile.close();
            }

            highScoreText.setString("High Score: " + std::to_string(highScore));
        }
    }

};

#endif-


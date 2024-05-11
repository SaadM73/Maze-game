
#include<fstream>
#include "game.h"
#include <SFML/Graphics/Text.hpp>

#include <SFML/Audio.hpp>
class Menu {
    RenderWindow window;
    //fonts
    Font font;
    //texts
    Text menu;//text being used to display "Menu" on the menu screen
    Text start;//text being used to display "Start" on the menu screen
    Text instructions;//text being used to display "Instructions" on the menu screen
    Text scores;//text being used to display "Scores" on the menu screen
    Text exit;//text being used to display "Exit" on the menu screen
    Text note;//text being used to display note on the end of the menu screen
    int men;
    //sprite and its texture of the menu screen
    Sprite menus;
    Texture menback;
    //music object causing the music to be played
    Music music;
    Music click;

public:

    //add menu attributes here
    Menu()
    {
        men = 0;
        window.create(VideoMode(800, 800), "Game Menu");
        window.setFramerateLimit(60);

        font.loadFromFile("i220822_Typewriter.ttf");

        music.openFromFile("i220822_m.ogg");
        music.setPosition(0, 1, 10);
        music.setVolume(30);
        music.setLoop(true);
        music.play();

        menback.loadFromFile("img/gameBG2.jpg");
        menus.setTexture(menback);
        menus.setScale(2, 2);

        menu.setFont(font);
        menu.setString("Enchanted Labyrinth");
        menu.setCharacterSize(60);
        menu.setFillColor(Color::Black);
        menu.setPosition(90, 65);
        menu.setOutlineThickness(2);

        start.setFont(font);
        start.setString("Start Game");
        start.setCharacterSize(30);
        start.setFillColor(Color::Black);
        start.setPosition(300, 240);
        start.setCharacterSize(40);
        start.setOutlineThickness(2);



        instructions.setFont(font);
        instructions.setString("Rules");
        instructions.setCharacterSize(30);
        instructions.setFillColor(Color::Black);
        instructions.setPosition(300, 340);
        instructions.setCharacterSize(40);
        instructions.setOutlineThickness(2);


        scores.setFont(font);
        scores.setString("Scores ");
        scores.setCharacterSize(30);
        scores.setFillColor(Color::Black);
        scores.setPosition(300, 440);
        scores.setCharacterSize(40);
        scores.setOutlineThickness(2);



        exit.setFont(font);
        exit.setString("Exit");
        exit.setCharacterSize(30);
        exit.setFillColor(Color::Black);
        exit.setPosition(300, 540);
        exit.setCharacterSize(40);
        exit.setOutlineThickness(2);



        note.setFont(font);
        note.setString("              Enjoy the game :)\n              Saad Mursaleen       22I-0835\n              Shayan Ahmed          22I-0822\n              Bilal Raza                       22I-1325");
        note.setCharacterSize(15);
        note.setFillColor(Color::Black);
        note.setPosition(250, 700);


    }

    void ds()
    {

        ifstream file("i220822_highestcore.txt");
        if (!file.is_open())
        {
            cout << "Highscore file couldn't be openened :(" << endl;
        }

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
            window.draw(menus);
            window.draw(hst);
            window.draw(note);
            window.display();
        }
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
            window.draw(menus);
            window.draw(instructions);
            window.display();
        }
    }


    void display_menu()

    {

        Game g(800, 800);

        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e)) {

                if (e.type == Event::Closed)        // If cross/close is clicked/pressed
                    window.close();                 // close the game
                if (e.key.code == (Keyboard::Down)) // If left key is pressed
                {

                    men++;

                    if (men == 1 || men == 2)
                    {
                        instructions.setFillColor(sf::Color::White);
                        start.setFillColor(sf::Color::Black);
                        scores.setFillColor(sf::Color::Black);
                        exit.setFillColor(sf::Color::Black);


                        click.openFromFile("click.ogg");
                        click.setPosition(0, 0, 0);
                        click.setVolume(100);
                        click.setLoop(0);
                        click.play();


                    }
                    else if (men == 3 || men == 4)
                    {
                        start.setFillColor(sf::Color::Black);
                        instructions.setFillColor(sf::Color::Black);
                        scores.setFillColor(sf::Color::White);
                        exit.setFillColor(sf::Color::Black);



                        click.openFromFile("click.ogg");
                        click.setPosition(0, 0, 0);
                        click.setVolume(100);
                        click.setLoop(0);
                        click.play();

                    }
                    else if (men <= 6)
                    {
                        start.setFillColor(sf::Color::Black);
                        instructions.setFillColor(sf::Color::Black);
                        scores.setFillColor(sf::Color::Black);
                        exit.setFillColor(sf::Color::White);



                        click.openFromFile("click.ogg");
                        click.setPosition(0, 0, 0);
                        click.setVolume(100);
                        click.setLoop(0);
                        click.play();

                    }



                }
                else if (e.key.code == (Keyboard::Up)) // If left key is pressed
                {



                    men--;

                    if (men <= 0)
                    {
                        instructions.setFillColor(sf::Color::Black);
                        start.setFillColor(sf::Color::White);
                        scores.setFillColor(sf::Color::Black);
                        exit.setFillColor(sf::Color::Black);
                        click.openFromFile("click.ogg");
                        click.setPosition(0, 1, 10);
                        click.setVolume(100);
                        click.setLoop(0);
                        click.play();
                    }
                    else if (men == 1 || men == 2)
                    {
                        start.setFillColor(sf::Color::Black);
                        instructions.setFillColor(sf::Color::White);
                        scores.setFillColor(sf::Color::Black);
                        exit.setFillColor(sf::Color::Black);
                        click.openFromFile("click.ogg");
                        click.setPosition(0, 1, 10);
                        click.setVolume(100);
                        click.setLoop(0);
                        click.play();
                    }
                    else if (men >= 3)
                    {
                        start.setFillColor(sf::Color::Black);
                        instructions.setFillColor(sf::Color::Black);
                        scores.setFillColor(sf::Color::White);
                        exit.setFillColor(sf::Color::Black);
                        click.openFromFile("click.ogg");
                        click.setPosition(0, 1, 10);
                        click.setVolume(100);
                        click.setLoop(0);
                        click.play();
                    }
                }
                if (e.key.code == (Keyboard::Enter)) // If left key is pressed
                {



                    Color a, b, c, d;
                    a = start.getFillColor();
                    b = instructions.getFillColor();
                    c = scores.getFillColor();
                    d = exit.getFillColor();
                    if (a == Color::White)
                    {
                        window.close();
                        g.start();
                    }
                    else if (b == Color::White)
                    {
                        // Display instructions
                        di();
                    }
                    else if (c == Color::White)
                    {
                        //    // Display instructions
                        ds();
                    }
                    else if (d == Color::White)
                    {
                        //Exit
                        window.close();
                    }
                }
            }


            window.clear(Color::Green);
            window.draw(menus);
            window.draw(menu);
            window.draw(start);
            window.draw(scores);
            window.draw(instructions);
            window.draw(exit);
            window.draw(note);

            window.display();
        }


    }


};

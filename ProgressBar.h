#pragma once


#include <SFML/Graphics.hpp>
class ProgressBar {
private:
    sf::RectangleShape background;
    sf::RectangleShape fill;
    int maxValue;
    int currentValue;
    float width;
    float height;

public:
    ProgressBar(float x, float y, float width, float height, int maxVal)
        : maxValue(maxVal), currentValue(0), width(width), height(height)
    {
        background.setPosition(x, y);
        background.setSize(sf::Vector2f(width, height));
        background.setFillColor(sf::Color(50, 50, 50));  // Dark grey
        background.setOutlineColor(sf::Color::White);
        background.setOutlineThickness(2);

        fill.setPosition(x, y);
        fill.setSize(sf::Vector2f(0, height));  // Initial size is 0
        fill.setFillColor(sf::Color(100, 250, 50));  // Green
    }

    void setProgress(int value) {
        currentValue = value;
        float newWidth = (static_cast<float>(currentValue) / maxValue) * width;
        fill.setSize(sf::Vector2f(newWidth, height));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(fill);
    }
};
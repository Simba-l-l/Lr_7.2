#include <iostream>
#include <SFML/Graphics.hpp>
#include "figures.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace sf;
using namespace std;

int main(int argc, char *argv[]) {
    double R;
    const int n = 20;
    cout << "Введите R: ";
    cin >> R;
    Field field(R, n);
    srand(clock());
    ofstream file("Output.txt");
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(1000, 800), "SFML OpenGL");
    double rotate = 0;
    field.generate_main_field();
    field.generate_shapes();
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(field.main_field);

        for(int i = 0; i < field.rectangles; i++){
            if(field.rect[i].shape.getGlobalBounds().intersects(field.up_field.getGlobalBounds()) || field.rect[i].shape.getGlobalBounds().intersects(field.down_field.getGlobalBounds())){
                field.rect[i].movement[1] *= -1;
                field.rect[i].movement[2] *= -1;
                field.rect[i].shape.setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
            }
            else if(field.rect[i].shape.getGlobalBounds().intersects(field.left_field.getGlobalBounds()) || field.rect[i].shape.getGlobalBounds().intersects(field.right_field.getGlobalBounds())){
                field.rect[i].movement[0] *= -1;
                field.rect[i].movement[2] *= -1;
                field.rect[i].shape.setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
            }
            field.rect[i].move();
            field.rect[i].rotate();
            window.draw(field.rect[i].shape);
        }
        for(int i = 0; i < field.circles; i++){
            if(field.circ[i].shape.getGlobalBounds().intersects(field.up_field.getGlobalBounds()) || field.circ[i].shape.getGlobalBounds().intersects(field.down_field.getGlobalBounds())){
                field.circ[i].movement[1] *= -1;
               field.circ[i].shape.setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
            }
            else if(field.circ[i].shape.getGlobalBounds().intersects(field.left_field.getGlobalBounds()) || field.circ[i].shape.getGlobalBounds().intersects(field.right_field.getGlobalBounds())){
                field.circ[i].movement[0] *= -1;
                field.circ[i].shape.setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
            }
            field.circ[i].move();
            window.draw(field.circ[i].shape);
        }
        window.display();
    }
    return 0;
}
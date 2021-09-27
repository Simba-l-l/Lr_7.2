#ifndef LR7_FIGURES_H
#define LR7_FIGURES_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#define geometry_rectangle 4
#define geometry_circle 3
#define move_arg 3
#define probability 0.5

class Figure{
public:
    double* geometry;
    double* movement;
    virtual void move(){};
    virtual void rotate(){};

    virtual ~Figure(){
//        delete[] geometry;
//        delete[] movement;
    }
};

class Rectangle: public Figure{
public:
    sf::RectangleShape shape;
    Rectangle(double R){
        srand(clock());
        geometry = new double [geometry_rectangle];
        movement = new double [move_arg];
        geometry[0] = double (rand() % (int(R) - 6) + 4); //x
        geometry[1] = double (rand() % (int(R) - 6) + 4); //y
        double minimal = std::min(R-geometry[0], R-geometry[1]);
        double diag = double (rand() % (int(minimal-1)) + 2);
        geometry[2] = double (1+rand() % int(diag - 1)); //a
        geometry[3] = sqrt(diag * diag - geometry[2] * geometry[2]);
        shape.setSize(sf::Vector2f(geometry[2], geometry[3]));
        shape.setOutlineColor(sf::Color::Magenta);
        shape.setFillColor(sf::Color(10, 10, 10, 1));
        shape.setOutlineThickness(3);
        shape.setPosition(geometry[0], geometry[1]);
        movement[0] = (double (2. + rand()%int(R))-R/2)/(R*8) ; //dx
        std::cout << " " << movement[0] << std::endl;
        movement[1] = (double (2. + rand()%int(R))-R/2)/(R*8) ; //dy
        movement[2] = (double (rand()%100)-50)/500; //rotation
    }
    void move(){
        shape.move(movement[0], movement[1]);
    }

    void rotate(){
        shape.rotate(movement[2]);
        }

};

std::ostream& operator << (std::ostream &out, const Rectangle &point){
    return out << "[Rectangle] x=" << point.geometry[0] << "; у=" << point.geometry[1]
    << "; a=" << point.geometry[2] << "; b=" << point.geometry[3] << ";" << std::endl;
}


class Circle : public Figure{
public:
    sf::CircleShape shape;
    double R_field;
    Circle(double R){
        srand(clock());
        R_field = R;
        geometry = new double [geometry_circle];
        movement = new double [move_arg];
        geometry[0] = double (rand() % (int(R) - 6) + 4); //x
        geometry[1] = double (rand() % (int(R) - 6) + 4); //y
        double minimal = std::min(R-geometry[0], R-geometry[1]);
        geometry[2] = double (1 + rand() % int(minimal/2.2));
        shape.setRadius(geometry[2]);
        shape.setPosition(geometry[0], geometry[1]);
        shape.setFillColor(sf::Color(10, 10, 10, 0));
        shape.setOutlineColor(sf::Color::Green);
        shape.setOutlineThickness(3);
        movement[0] = (double (2. + rand() % int(R)) - R / 2) / ( R * 8); //dx
        movement[1] = (double (2. + rand() % int(R)) - R / 2) / (R * 8); //dy
        movement[2] = (double (rand()%100)-50)/500; //rotation
    }
    void move(){
        shape.move(movement[0], movement[1]);
    }

    void rotate(){
        shape.rotate(movement[3]);
    }
};

std::ostream& operator << (std::ostream &out, const Circle &point){
    return out << "[Circle] x=" << point.geometry[0] << "; у=" << point.geometry[1]
    << "; r=" << point.geometry[2]<< ";" << std::endl;
}

class Field{
public:
    float size;
    int n;
    int rectangles = 0;
    int circles = 0;
    sf::RectangleShape main_field;
    Figure* figures;
    std::string* types;
    std::vector <Circle> circ;
    std::vector <Rectangle> rect;
    sf::RectangleShape left_field;
    sf::RectangleShape right_field;
    sf::RectangleShape down_field;
    sf::RectangleShape up_field;

    Field(double R, int N){
        n = N;
        size = R * 100;
    }
    void generate_main_field(){
        left_field.setSize(sf::Vector2(1.f + 2, float(size + 2)));
        left_field.setFillColor(sf::Color::Blue);
        right_field.setSize(sf::Vector2(1.f + 2, float(size + 2)));
        right_field.setFillColor(sf::Color::Red);
        up_field.setSize(sf::Vector2(float(size + 2), 1.f + 2.f));
        up_field.setFillColor(sf::Color::Green);
        down_field.setSize(sf::Vector2(float(size + 2), 1.f + 2.f));
        down_field.setFillColor(sf::Color::Red);
        left_field.setPosition(-1,-1);
        right_field.setPosition(size + 3, 0);
        up_field.setPosition(0,0);
        down_field.setPosition(0, size + 3);
        main_field.setSize(sf::Vector2(size, size));
        main_field.setFillColor(sf::Color::Black);
        main_field.setOutlineThickness(2);
        main_field.setOutlineColor(sf::Color::Red);
        main_field.move(2,2);
    }
    void generate_shapes(){
        for (int i = 0; i < n; i++) {
            if (rand()%(int (1/probability))) {
                Rectangle *r = new Rectangle(size);
                rect.push_back(*r);
                rectangles++;
            } else {
                Circle *c = new Circle(size);
                circ.push_back(*c);
            }
        }
        circles = n - rectangles;
    }

    ~Field(){
//        delete[] figures;
//        delete[] types;
    }
};
#endif //LR7_FIGURES_H

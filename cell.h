#include <iostream>
#include <SDL2/SDL.h>
#pragma once

#define RANDCOLOR rand()%255

class Cell {
public:
    int aliveness = 0;
    SDL_Color color;
    int age = 0;
    int red = 0;
    int green = 0;
    int blue = 0;

    Cell() {
        aliveness = 0;
        age = 0;
    }

    Cell(int aliveness) {
        this->aliveness = aliveness;
        age = 0;
    }

    Cell(int aliveness, int age) {
        this->aliveness = aliveness;
        this->age = age;
    }

    Cell(int aliveness, int age, SDL_Color color) {
        this->aliveness = aliveness;
        this->color = color;
        this->age = age;
    }

    void upAge() {
        if (aliveness > 0) {
            this->age = this->age + 1;
        } else {
            this->age = 0;
        }
    }

    int getAge() {
        return age;
    }

    SDL_Color getColor() {
        return color;
    }

    void updateColor() {
        red = age;
        blue = 255;
        green = 100;
        this->color = SDL_Color{Uint8(red), Uint8(this->getAge()), 255};
    }
};

//
// Created by cotsm on 03/09/2021.
//

#ifndef STREAMPP_EXAMPLE_ANIMAL_H
#define STREAMPP_EXAMPLE_ANIMAL_H


#include <string>
#include <ostream>

class Animal {

public:
    enum GENDER {
        MALE = 0, FEMALE
    };

    Animal(const std::string &name, int age, GENDER gender);

    const std::string &getName() const;

    int getAge() const;

    friend std::ostream &operator<<(std::ostream &os, const Animal &animal);

    GENDER getGender() const;

private:
    std::string _name;
    int _age;
    GENDER _gender;
};


#endif //STREAMPP_EXAMPLE_ANIMAL_H

//
// Created by cotsm on 03/09/2021.
//

#include <streampp.h>
#include <iostream>
#include "Animal.h"

void line() {
    std::cout << "------------------------------------------------------" << std::endl;
}

void displayAnimal(Animal &a) {
    std::cout << a << std::endl;
}

int main() {

    std::vector<Animal> animals;
    std::vector<std::string> names{"Logan", "Matou", "Tim", "Valerie", "Cacao", "Soho"};
    std::vector<int> ages{12, 23, 121, 14, 17, 18};
    std::vector<Animal::GENDER> genders{
            Animal::GENDER::MALE, Animal::GENDER::FEMALE,
            Animal::GENDER::MALE, Animal::GENDER::FEMALE,
            Animal::GENDER::MALE, Animal::GENDER::FEMALE
    };

    for (int i = 0; i < names.size(); ++i) {
        animals.emplace_back(names.at(i), ages.at(i), genders.at(i));
    }

    auto animal_stream = streampp::StreamBuilder<Animal>::make(animals);
    line();

    std::cout << "COUNT :" << std::endl;
    std::cout << animal_stream->count() << " animal(s)" << std::endl;

    line();
    std::cout << "FOR EACH :" << std::endl;
    animal_stream = streampp::StreamBuilder<Animal>::make(animals);
    animal_stream->forEach(displayAnimal);

    line();
}
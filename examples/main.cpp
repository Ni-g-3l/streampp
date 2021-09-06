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

streampp::Stream<Animal, std::vector> *getAnimalStream() {
    line();
    auto *animals = new std::vector<Animal>();
    auto *names = new std::vector<std::string>({"Logan", "Matou", "Tim", "Valerie", "Cacao", "Soho", "Logan"});
    auto *ages = new std::vector<int>({12, 23, 121, 14, 17, 18, 12});
    auto *genders = new std::vector<Animal::GENDER>({
                                                            Animal::GENDER::MALE, Animal::GENDER::FEMALE,
                                                            Animal::GENDER::MALE, Animal::GENDER::FEMALE,
                                                            Animal::GENDER::MALE, Animal::GENDER::FEMALE,
                                                            Animal::GENDER::MALE
                                                    });

    for (int i = 0; i < names->size(); ++i) {
        animals->emplace_back(names->at(i), ages->at(i), genders->at(i));
    }

    ages->clear();
    names->clear();
    genders->clear();

    delete ages;
    delete names;
    delete genders;

    return streampp::StreamBuilder<Animal>::make(*animals);
}

int main() {

    auto animal_stream = getAnimalStream();
    std::cout << "COUNT :" << std::endl;
    std::cout << animal_stream->count() << " animal(s)" << std::endl;

    animal_stream = getAnimalStream();
    std::cout << "FOR EACH :" << std::endl;
    animal_stream->forEach(displayAnimal);

    animal_stream = getAnimalStream();
    std::cout << "ALL MATCH (is Male) : " << animal_stream->allMatch(&Animal::isMale) << std::endl;

    animal_stream = getAnimalStream();
    std::cout << "ANY MATCH (is Male) : " << animal_stream->anyMatch(&Animal::isMale) << std::endl;

    animal_stream = getAnimalStream();
    std::cout << "NONE MATCH (Age < 0) : " << animal_stream->noneMatch(
            [](Animal &a) { return a.getAge() < 0; }
    ) << std::endl;

    animal_stream = getAnimalStream();
    std::cout << "NONE MATCH (Age > 0) : " << animal_stream->noneMatch(
            [](Animal &a) { return a.getAge() > 0; }
    ) << std::endl;

    animal_stream = getAnimalStream();
    std::cout << "COUNT (Male) : " << animal_stream->filter(&Animal::isMale)->count() << std::endl;

    animal_stream = getAnimalStream();
    std::cout << "COUNT (Female) : " << animal_stream->filter(&Animal::isMale)->count() << std::endl;

    animal_stream = getAnimalStream();
    std::cout << "MIN : " << *animal_stream->min() << std::endl;

    animal_stream = getAnimalStream();
    std::cout << "MAX : " << *animal_stream->max() << std::endl;

    animal_stream = getAnimalStream();
    std::cout << "DISTINCT : " << std::endl;
    animal_stream->distinct()->forEach(displayAnimal);

}
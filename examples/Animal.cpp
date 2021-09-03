#include "Animal.h"

Animal::Animal(const std::string &name, int age, Animal::GENDER gender) : _name(name), _age(age), _gender(gender) {}

const std::string &Animal::getName() const {
    return _name;
}

int Animal::getAge() const {
    return _age;
}

Animal::GENDER Animal::getGender() const {
    return _gender;
}

std::ostream &operator<<(std::ostream &os, const Animal &animal) {
    os << "<Name: " << animal._name << " - Age: " << animal._age << " - Gender: " << animal._gender << ">";
    return os;
}

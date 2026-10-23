#include <iostream>
#include <string>
#include <vector>

#include "cat.hpp"
#include "dog.hpp"
#include "pet.hpp"

int main() {
    std::vector<Pet *> pet_shop = {new Dog("Bob", 65), new Dog("Stan", 37),
                                   new Cat("Tom", 12)};

    float total_fee = 0.0;
    for (size_t i = 0; i < pet_shop.size(); i++) {
        std::cout << pet_shop[i]->get_name() << ' '
                  << pet_shop[i]->calculate_fee() << "\n";
        total_fee = total_fee + pet_shop[i]->calculate_fee();
    }
    std::cout << "total licensing fee = " << total_fee << "\n";

    for (Pet *pet : pet_shop) {
        delete pet;
    }

    // clear all the varaibles in the vector to prevent dangling pointers
    pet_shop.clear();

    return 0;
}

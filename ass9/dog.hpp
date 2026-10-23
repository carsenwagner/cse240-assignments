#pragma once
#include <string>

#include "pet.hpp"

class Dog : public Pet {
  public:
    Dog(const std::string &name, int weight) : Pet(name, weight) {}

    // calculates the fee for the instance of the dog
    float calculate_fee() const override { return rate * weight; }

  private:
    constexpr static float rate = 2.0f;
};

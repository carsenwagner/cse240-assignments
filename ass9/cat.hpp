#pragma once
#include <string>

#include "pet.hpp"

class Cat : public Pet {
  public:
    Cat(const std::string &name, int weight) : Pet(name, weight) {}

    // calculates the fee for the instance of the cat
    float calculate_fee() const override { return rate * weight; }

  private:
    constexpr static float rate = 1.5f;
};

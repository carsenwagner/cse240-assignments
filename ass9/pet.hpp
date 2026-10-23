#pragma once
#include <string>

class Pet {
  protected:
    std::string name;
    int weight;

  public:
    Pet(const std::string &n, int w) : name(n), weight(w) {}

    // returns a const string reference to the instance pet's name
    const std::string &get_name() const { return this->name; }

    // virtual method that requires child classes to override to calculate the
    // fee
    virtual float calculate_fee() const = 0;

    virtual ~Pet() = default;
};

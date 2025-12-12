//
// Created by sebastian on 12/12/25.
//

#pragma once
#include <random>

class Random
{
public:
  static int getRandomInt(const int min, const int max)
  {
    // Creates the variables ones per thread to reuse later.
    thread_local std::random_device rd;
    thread_local std::mt19937 gen(rd());

    // Set the upper and lower limit, and return the random value.
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
  }
};
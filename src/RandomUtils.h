#pragma once
#include <random>
static std::random_device rd;
static std::mt19937 gen(rd());
float GetRandomNumber(float min, float max, bool isInteger) {


    if (isInteger) {
        // Properly cast to int and ensure correct bounds
        int imin = static_cast<int>(std::ceil(min));
        int imax = static_cast<int>(std::floor(max));
        std::uniform_int_distribution<> dis(imin, imax);
        return static_cast<float>(dis(gen));
    }
    else {
        std::uniform_real_distribution<float> dis(min, max);
        return dis(gen);
    }
}
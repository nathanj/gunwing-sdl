#pragma once

#include <iostream>
#include <chrono>
#include <stdio.h>
#include "vector.h"

template <typename T>
T clamp(T value, T min, T max)
{
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

void createMedals(const Vector<float>& position, float factor = 1);
int p(int percent);
int rand_between(int a, int b);
double gaussrand();
int rand_normal(int mean, int stddev);

#if 1
#define LOG(...) std::cout << __PRETTY_FUNCTION__ << ":" << __LINE__ << " " << __VA_ARGS__ << std::endl;
#define TRACE(x) std::cout << __PRETTY_FUNCTION__ << ":" << __LINE__ << " " << #x << " = " << x << std::endl;
#else
#define LOG(...)
#define TRACE(...)
#endif

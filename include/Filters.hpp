#ifndef FILTERS_HPP
#define FILTERS_HPP

#include "Image.hpp"
#include <vector>
#include <iostream>

// Transform Filters
int convertToGrayscale(Image &image);
Image applyBoxBlur(Image &image, int r);

#endif // FILTERS_HPP
#ifndef FILTERS_HPP
#define FILTERS_HPP

#include "Image.hpp"
#include <vector>
#include <iostream>

// Transform Filters
int convertToGrayscale(Image &image);
Image applyBoxBlur(Image image, int r);
std::vector<int> computeSummedAreaTable(Image image);
int getLinearIndex(int row, int column, int width, int no_of_channels);
int getColorChannelCount(int number_of_channels);
#endif // FILTERS_HPP
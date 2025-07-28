#include "../include/FileIO.hpp"
#include "../include/Image.hpp"
#include "../include/Filters.hpp"

int main()
{
    std::cout << "Mini Image Processing Library!" << std::endl;
    FileIO file_io;

    Image image = file_io.loadImage("../assets/car.ppm");
    Image grayscale_image = convertToGrayscale(image);

    file_io.saveImage(grayscale_image, "sample_out");
    return 0;
}
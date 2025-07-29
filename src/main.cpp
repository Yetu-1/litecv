#include "../include/FileIO.hpp"
#include "../include/Image.hpp"
#include "../include/Filters.hpp"

int main()
{
    std::cout << "Mini Image Processing Library!" << std::endl;
    FileIO file_io;

    Image image = file_io.loadImage("../assets/image.png");
    Image grayscale_image = convertToGrayscale(image);

    file_io.saveImage(grayscale_image, "../assets/image_out.png");
    return 0;
}
#include "../include/FileIO.hpp"
#include "../include/Image.hpp"
#include "../include/Filters.hpp"

int main()
{
    std::cout << "Mini Image Processing Library!" << std::endl;
    FileIO file_io;

    Image image = file_io.loadImage("../assets/image.png");

    // int flag = convertToGrayscale(image);
    int flag = applyBoxBlur(image, 1);

    file_io.saveImage(image, "../assets/image_out.png");
    return 0;
}
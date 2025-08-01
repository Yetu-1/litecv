#include "../include/FileIO.hpp"
#include "../include/Image.hpp"
#include "../include/Filters.hpp"

int main()
{
    std::cout << "Mini Image Processing Library!" << std::endl;
    FileIO file_io;

    Image image = file_io.loadImage("../assets/image.png");

    // int flag = convertToGrayscale(image);
    Image blurred_image = applyBoxBlur(image, 5);

    file_io.saveImage(blurred_image, "../assets/image_out.png");
    return 0;
}
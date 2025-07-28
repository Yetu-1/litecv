#include "../include/FileIO.hpp"
#include "../include/Image.hpp"

int main()
{
    std::cout << "Mini Image Processing Library!" << std::endl;
    FileIO file_io;

    file_io.loadImage("../assets/tree_1.ppm");

    return 0;
}
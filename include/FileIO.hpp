#ifndef FILEIO_HPP
#define FILEIO_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "Image.hpp"

class FileIO
{
public:
    Image loadImage(std::string image_src);
    int saveImage(const Image &image, std::string filename);
    FileIO()
    {
    }
    ~FileIO()
    {
    }

private:
    Image loadPPM(std::ifstream &file);
};

#endif // FILEIO_HPP
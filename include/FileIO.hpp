#ifndef FILEIO_HPP
#define FILEIO_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "Image.hpp"

class FileIO
{
public:
    int loadImage(std::string image_src);

    FileIO()
    {
    }
    ~FileIO()
    {
    }

private:
    Image loadPPM(std::ifstream &file);
    int savePPM(const Image &image);
};

#endif // FILEIO_HPP
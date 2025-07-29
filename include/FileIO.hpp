#ifndef FILEIO_HPP
#define FILEIO_HPP

#include <fstream>
#include <iostream>
#include "Image.hpp"

class FileIO
{
public:
    Image loadImage(const char *image_src);
    int saveImage(const Image &image, const char *filename);
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
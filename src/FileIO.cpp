#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "../include/stb_image.h"
#include "../include/stb_image_write.h"

#include "../include/FileIO.hpp"

Image FileIO::loadImage(const char *image_src)
{
    Image image;

    unsigned char *data = stbi_load(image_src, &image.width, &image.height, &image.no_of_chnls, 0);

    if (!data)
    {
        std::cerr << "Failed to open image file!" << std::endl;
        return image;
    }

    image.pixels.resize(image.width * image.height * image.no_of_chnls);
    image.pixels.assign(data, data + image.width * image.height * image.no_of_chnls);
    stbi_image_free(data);

    return image;
}

// Image FileIO::loadPPM(std::ifstream &file)
// {
//     std::cout << "Loading Image File!" << std::endl;
//     std::string line;
//     int width, height, maxval;

//     file.get(); // read newline char

//     std::getline(file, line);
//     // Parse line if it's not a comment
//     if (line[0] == '#')
//     {
//         file >> width >> height;
//     }
//     else
//     {
//         width = std::stoi(line.substr(0, 3));
//         height = std::stoi(line.substr(4, 3));
//     }
//     file >> maxval;
//     file.get();
//     int total_bytes = width * height * PPM_CHANNEL_SIZE;

//     Image image(width, height, PPM_CHANNEL_SIZE, maxval);

//     file.read(reinterpret_cast<char *>(image.pixels.data()), total_bytes);

//     return image;
// }

int FileIO::saveImage(const Image &image, const char *filepath)
{
    std::cout << "Saving Image File!" << std::endl;

    int flag = stbi_write_png(filepath, image.width, image.height, image.no_of_chnls, image.pixels.data(), image.width * image.no_of_chnls);

    std::cout << "Image File Saved!" << std::endl;

    return flag;
}
#include "../include/FileIO.hpp"

Image FileIO::loadImage(std::string image_src)
{
    Image image;
    std::ifstream file(image_src, std::ios::binary); // open file in binary mode
    if (!file.is_open())
    {
        std::cerr << "Failed to open image file!" << std::endl;
        return -1;
    }

    // read magic number to determine file format
    std::string magic_num;
    file >> magic_num;

    if (magic_num == "P6" || magic_num == "P3")
    {
        image = loadPPM(file);
        saveImage(image, "color_img");
    }

    file.close();

    return image;
}

Image FileIO::loadPPM(std::ifstream &file)
{
    std::cout << "Loading Image File!" << std::endl;
    std::string line;
    int width, height, maxval;

    file.get(); // read newline char

    std::getline(file, line);
    // Parse line if it's not a comment
    if (line[0] == '#')
    {
        file >> width >> height;
    }
    else
    {
        width = std::stoi(line.substr(0, 3));
        height = std::stoi(line.substr(4, 3));
    }
    file >> maxval;
    file.get();
    int total_bytes = width * height * PPM_CHANNEL_SIZE;

    Image image(width, height, PPM_CHANNEL_SIZE, maxval);

    file.read(reinterpret_cast<char *>(image.pixels.data()), total_bytes);

    return image;
}

int FileIO::saveImage(const Image &image, std::string filename)
{
    std::cout << "Saving Image File!" << std::endl;
    std::ofstream image_file("../assets/" + filename + ".ppm");

    if (!image_file.is_open())
    {
        std::cout << "Failed to open image file!" << std::endl;
        return -1;
    }
    int total_bytes = image.width * image.height * PPM_CHANNEL_SIZE;
    // Save image as binary PPM (P6): header + raw pixel data
    image_file << "P6" << "\n";
    image_file << image.width << " " << image.height << "\n";
    image_file << image.max_val << "\n";
    image_file.write(reinterpret_cast<const char *>(image.pixels.data()), total_bytes);
    image_file.close();

    std::cout << "Image File Saved!" << std::endl;

    return image_file ? 0 : -1;
}
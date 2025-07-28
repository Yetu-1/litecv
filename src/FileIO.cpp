#include "../include/FileIO.hpp"

int FileIO::loadImage(std::string image_src)
{
    std::ifstream file(image_src, std::ios::binary); // open file in binary mode

    if (!file.is_open())
    {
        std::cerr << "Failed to open image file!" << std::endl;
        return 1;
    }

    std::string magic_num;
    file >> magic_num;

    if (magic_num == "P6" || magic_num == "P3")
    {
        Image image = loadPPM(file);
        std::cout << "Buffer size: " << image.buffer.size() << std::endl;
        savePPM(image);
    }

    return 0;
}

Image FileIO::loadPPM(std::ifstream &file)
{
    std::cout << "Loading Image File!" << std::endl;

    int width, height, maxval;
    file >> width >> height >> maxval;
    file.get();
    int total_bytes = width * height * PPM_CHANNEL_SIZE;

    Image image(width, height, PPM_CHANNEL_SIZE, maxval);

    file.read(reinterpret_cast<char *>(image.buffer.data()), total_bytes);

    return image;
}

int FileIO::savePPM(Image &image)
{
    std::cout << "Saving Image File!" << std::endl;
    std::ofstream image_file("../assets/sample_out.ppm");
    int total_bytes = image.width * image.height * PPM_CHANNEL_SIZE;
    image_file << "P6" << "\n";
    image_file << image.width << " " << image.height << "\n";
    image_file << image.max_val << "\n";
    image_file.write(reinterpret_cast<char *>(image.buffer.data()), total_bytes);
    image_file.close();

    return 0;
}
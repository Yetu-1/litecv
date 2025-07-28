#include "../include/Filters.hpp"

// Convert image int rgb to grayscale using luminosity method
Image convertToGrayscale(Image &image)
{

    int totalBytes = image.width * image.height * PPM_CHANNEL_SIZE;
    std::vector<unsigned char> grayscale_pixels;
    int counter = 0;
    for (int i = 0; i < image.pixels.size(); i++)
    {
        uint8_t red = image.pixels[i];
        uint8_t green = image.pixels[++i];
        uint8_t blue = image.pixels[++i];

        // Equation for converstion to grayscale
        float pixel_value = 0.3 * red + 0.59 * green + 0.11 * blue;
        grayscale_pixels.push_back(pixel_value);
        grayscale_pixels.push_back(pixel_value);
        grayscale_pixels.push_back(pixel_value);
    }

    if (!(totalBytes == grayscale_pixels.size()))
    {
        std::cout << "Error converting Image!" << std::endl;
        return 0;
    }

    // Create grayscale image
    Image grayscale_image(image.width, image.height, PPM_CHANNEL_SIZE, image.max_val);
    grayscale_image.pixels = grayscale_pixels;

    return grayscale_image;
}
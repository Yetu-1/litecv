#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "../include/Filters.hpp"
#include "../include/stb_image_resize2.h"

// Convert image int rgb to grayscale using luminosity method
Image convertToGrayscale(Image &image)
{
    int output_img_size = image.width * image.height;
    int no_of_channels = 1;
    if (image.no_of_chnls <= 2) // Already in grayscale
    {
        return image;
    }
    else if (image.no_of_chnls == 4)
    {
        output_img_size *= 2; // Expand output image size (in bytes) to include alpha channel (2 channels total)
        ++no_of_channels;
    }
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

        if (image.no_of_chnls == 4) // If there are 4 channels, add the Alpha channel
        {
            grayscale_pixels.push_back(image.pixels[++i]);
        }
    }
    if (!(output_img_size == grayscale_pixels.size()))
    {
        std::cout << "Error converting Image!" << std::endl;
        return Image();
    }

    // Create grayscale image object
    Image grayscale_image(image.width, image.height, no_of_channels, image.max_val);
    grayscale_image.pixels = grayscale_pixels;

    return grayscale_image;
}

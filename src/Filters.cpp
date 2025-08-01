#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "../include/Filters.hpp"
#include "../include/stb_image_resize2.h"
#include <array>
#include <math.h>

// Convert image int rgb to grayscale using luminosity method
int convertToGrayscale(Image &image)
{
    int output_img_size = image.width * image.height;
    int no_of_channels = 1;
    if (image.no_of_chnls <= 2) // Already in grayscale
    {
        return 2; // 2 = code for "already in grayscale"
    }
    else if (image.no_of_chnls == 4)
    {
        output_img_size *= 2; // Expand output image size (in bytes) to include alpha channel (2 channels total)
        ++no_of_channels;
    }

    std::vector<unsigned char> grayscale_pixels;
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
        return -1;
    }

    image.no_of_chnls = no_of_channels;
    image.pixels = grayscale_pixels;

    return 0;
}

Image applyBoxBlur(Image &image, int r)
{
    int width = image.width;
    int height = image.height;
    Image new_image = image;
    int blurred_pixel_count = 0;

    int area = std::pow((2 * r + 1), 2);
    for (int y = r; y < height - r; y++)
    {
        for (int x = r; x < width - r; x++)
        {
            std::array<float, 3> rgb_sum = {0, 0, 0};
            for (int i = y - r; i <= y + r; i++) // loop rows
            {
                for (int j = x - r; j <= x + r; j++) // loop columns
                {
                    int pixel_idx = ((i * width) + j) * image.no_of_chnls; // Get the index of the pixel in the 1D array (pixel of the first element(red))

                    rgb_sum[0] += image.pixels[pixel_idx];
                    rgb_sum[1] += image.pixels[pixel_idx + 1];
                    rgb_sum[2] += image.pixels[pixel_idx + 2];
                }
            }

            for (auto &val : rgb_sum)
                val /= area;
            int idx = ((y * width) + x) * image.no_of_chnls; // Get the index of the pixel in the 1D array (pixel of the first element(red))
            new_image.pixels[idx] = rgb_sum[0];
            new_image.pixels[idx + 1] = rgb_sum[1];
            new_image.pixels[idx + 2] = rgb_sum[2];
            blurred_pixel_count++;
        }
    }
    int expected_image_size = (width - r * 2) * (height - r * 2);
    std::cout << "Expected: " << expected_image_size << std::endl;
    std::cout << "Actual: " << blurred_pixel_count << std::endl;
    if (blurred_pixel_count != expected_image_size)
    {
        std::cout << "Error Blurring Image" << std::endl;
        return image;
    }
    return new_image;
}
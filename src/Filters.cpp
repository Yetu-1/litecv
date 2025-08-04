#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "../include/Filters.hpp"
#include "../include/stb_image_resize2.h"
#include <array>
#include <math.h>

// Returns the 1D array index of a pixel in a row-major 2D image with multiple channels.
int getLinearIndex(int row, int column, int width, int no_of_channels)
{
    return ((row * width) + column) * no_of_channels;
}

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

Image applyBoxBlur(Image image, int r)
{
    int width = image.width;
    int height = image.height;
    Image new_image = image;
    int area = std::pow((2 * r + 1), 2);
    std::vector<int> table = computeSummedAreaTable(image);
    int num_color_channels = getColorChannelCount(image.no_of_chnls);
    int blurred_pixel_count = 0;
    for (int y = r + 1; y < height - r - 1; y++)
    {
        for (int x = r + 1; x < width - r - 1; x++)
        {
            int top_left_index = getLinearIndex(y - r - 1, x - r - 1, width, image.no_of_chnls);
            int top_right_index = getLinearIndex(y - r - 1, x + r, width, image.no_of_chnls);
            int bottom_left_index = getLinearIndex(y + r, x - r - 1, width, image.no_of_chnls);
            int bottom_right_index = getLinearIndex(y + r, x + r, width, image.no_of_chnls);
            int idx = getLinearIndex(y, x, width, image.no_of_chnls);

            // Loop over color channels excluding alpha
            for (int c = 0; c < num_color_channels; c++)
            {
                new_image.pixels[idx + c] = (table[bottom_right_index + c] - table[bottom_left_index + c] - table[top_right_index + c] + table[top_left_index + c]) / area;
            }
            blurred_pixel_count++;
        }
    }
    int expected_image_size = (width - (r + 1) * 2) * (height - (r + 1) * 2);
    if (blurred_pixel_count != expected_image_size)
    {
        std::cout << "Error Blurring Image" << std::endl;
        return image;
    }
    return new_image;
}

int getColorChannelCount(int number_of_channels)
{
    // If the number of channels is even, assume the last channel is alpha
    // (e.g., RGBA or Grayscale+Alpha), and exclude it from processing.
    // Otherwise, process all channels (e.g., RGB or Grayscale).
    return (number_of_channels % 2) ? number_of_channels : number_of_channels - 1;
}

std::vector<int> computeSummedAreaTable(Image image)
{
    int width = image.width;
    int height = image.height;
    int num_chnls = image.no_of_chnls;
    std::vector<int> table(width * height * num_chnls);
    table[0] = image.pixels[0];
    int num_color_channels = getColorChannelCount(image.no_of_chnls);
    // Calculate the values for the first element of each column
    for (int x = 1; x < width; x++)
    {
        int linear_index = getLinearIndex(0, x, width, num_chnls);
        int prev_lin_index = getLinearIndex(0, x - 1, width, num_chnls);
        // Loop over color channels excluding alpha
        for (int c = 0; c < num_color_channels; c++)
        {
            table[linear_index + c] = image.pixels[linear_index + c] + table[prev_lin_index + c];
        }
    }
    // Calculate the values for the first element of each row
    for (int y = 1; y < height; y++)
    {
        int linear_index = getLinearIndex(y, 0, width, num_chnls);
        int prev_lin_index = getLinearIndex(y - 1, 0, width, num_chnls);
        // Loop over color channels excluding alpha
        for (int c = 0; c < num_color_channels; c++)
        {
            table[linear_index + c] = image.pixels[linear_index + c] + table[prev_lin_index + c];
        }
    }

    // Calculate the values for the rest of the elements
    for (int i = 1; i < height; i++)
    { // loop rows
        for (int j = 1; j < width; j++)
        { // loop columns
            int index = getLinearIndex(i, j, width, num_chnls);
            int left_pixel_index = getLinearIndex(i - 1, j, width, num_chnls);
            int top_pixel_index = getLinearIndex(i, j - 1, width, num_chnls);
            int diagonal_pixel_index = getLinearIndex(i - 1, j - 1, width, num_chnls);

            // Loop over color channels excluding alpha
            for (int c = 0; c < num_color_channels; c++)
            {
                table[index + c] = image.pixels[index + c] + table[left_pixel_index + c] + table[top_pixel_index + c] - table[diagonal_pixel_index + c];
            }
        }
    }
    return table;
}

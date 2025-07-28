#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#define PPM_CHANNEL_SIZE 3
class Image
{
public:
    int width;
    int height;
    int channels;
    int max_val;
    std::vector<unsigned char> pixels;

    Image(int w = 0, int h = 0, int c = 0, int mv = 0)
        : width(w), height(h), channels(c), pixels(w * h * c), max_val(mv)
    {
    }
    ~Image()
    {
    }
};

#endif // IMAGE_HPP
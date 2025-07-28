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
    std::vector<unsigned char> buffer;

    Image(int w, int h, int c, int mv)
        : width(w), height(h), channels(c), buffer(w * h * c), max_val(mv)
    {
    }
    ~Image()
    {
    }
};

#endif // IMAGE_HPP
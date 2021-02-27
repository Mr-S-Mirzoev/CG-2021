/*! \file Image.h
    \brief Image and Pixel representation
*/

#ifndef MAIN_IMAGE_H
#define MAIN_IMAGE_H

#include <string>

constexpr int tileSize = 16;

/**
 * @brief Pixel in RGBA representation
 */
struct Pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

constexpr Pixel backgroundColor{0, 0, 0, 0};

/**
 * @brief Class representation of Image abstraction
 * 
 */
struct Image
{
    /**
     * @brief Construct a new Image object from image in path
     * 
     * @param a_path - path to an image we'd like to load
     */
    explicit Image(const std::string &a_path);
    /**
     * @brief Construct a blank Image object
     * 
     * @param a_width - width of generated image
     * @param a_height - height of generated image
     * @param a_channels - number of channels in a new image
     */
    Image(int a_width, int a_height, int a_channels);

    /**
     * @brief Save an image to path
     * 
     * If path ends with *.jpg the Image object will be saved in JPG format \n
     * If path ends with *.png the Image object will be saved in PNG format
     * 
     * @param a_path - path where to save an Image
     * @return int - 0 on success; 1 on error
     */
    int Save(const std::string &a_path);

    /* Getters */

    int Width()    const { return width; }
    int Height()   const { return height; }
    int Channels() const { return channels; }
    size_t Size()  const { return size; }
    Pixel* Data()        { return  data; }

    Pixel GetPixel(int x, int y) { return data[height * y + x];}

    /* Setter */

    void  PutPixel(int x, int y, const Pixel &pix) { data[height * y + x] = pix; }

    ~Image();

protected:
    int width = -1;
    int height = -1;
private:
    int channels = 3;
    size_t size = 0;
    Pixel *data = nullptr;
    bool self_allocated = false;
};

#endif //MAIN_IMAGE_H

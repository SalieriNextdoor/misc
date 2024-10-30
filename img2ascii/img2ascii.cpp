#include "stb_image.h"
#include <iostream>
#include <string>
#include <vector>

const char ASCII_CHARS[] = {'@', '%', '#', '$', '*', '+',
                            '=', '-', ':', '.', ' '};

char grayscaleToAscii(int grayscale) {
  int index = grayscale * (sizeof(ASCII_CHARS) - 1) / 255;
  return ASCII_CHARS[index];
}

int main(int argc, char *argv[]) {
  int newWidth = 80;
  if (argc < 2) {
    std::cerr << "Usage: img2ascii FILE [WIDTH]" << std::endl;
    return 1;
  }
  if (argc >= 3)
    newWidth = atoi(argv[2]);

  int width, height, nchannels;
  unsigned char *img = stbi_load(argv[1], &width, &height, &nchannels, 0);
  if (!img) {
    std::cerr << "Failed to load image at " << argv[1] << std::endl;
    return 1;
  }

  int newHeight = (int)((float)height * newWidth / width / 1.8f);

  std::vector<std::string> asciiArt(newHeight, std::string(newWidth, ' '));

  for (int y = 0; y < newHeight; ++y) {
    for (int x = 0; x < newWidth; ++x) {

      int origX = x * width / newWidth;
      int origY = y * height / newHeight;

      int pixelIndex = (origY * width + origX) * nchannels;
      int r = img[pixelIndex];
      int g = img[pixelIndex + 1];
      int b = img[pixelIndex + 2];
      int grayscale = (r + g + b) / 3;

      asciiArt[y][x] = grayscaleToAscii(grayscale);
    }
  }

  // Find left and right boundaries for non-space characters
  int left = newWidth - 1;
  int right = 0;
  for (const auto &row : asciiArt) {
    for (int x = 0; x < newWidth; ++x) {
      if (row[x] != ' ') {
        if (x < left)
          left = x;
        if (x > right)
          right = x;
      }
    }
  }

  for (const auto &row : asciiArt)
    std::cout << row.substr(left, right - left + 1) << std::endl;

  stbi_image_free(img);
  return 0;
}

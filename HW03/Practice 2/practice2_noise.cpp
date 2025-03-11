// Impulse noise
#include <iostream>
#include <algorithm>
#include <random>

# include "ImgProc.hpp"

// Gray Level
int a = 0;
int b = 255;

// Impulse noise
int A = 5;      // Salt noise
int B = 10;     // Pepper noise


int main() {
    Matrix img = RGBImage::fromFile("photo.bmp").toGray().toMatrix();

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 100);

    for(int row=0; row < img.height; row++) {
        for(int col=0; col < img.width; col++) {
            if(distribution(generator) < A) {
                img[row][col] = a;
            }
            else if (distribution(generator) < B) {
                img[row][col] = b;
            }
            // else {
            //     img[row][col] = img[row][col];
            // }
        }
    }

    GrayImage noise = GrayImage::fromMatrix(img);
    RGBImage::fromGrays(noise, noise, noise).toFile("result/noise.bmp");

    std::cout << "Done!" << std::endl;
}
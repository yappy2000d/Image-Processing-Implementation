// Impulse noise
#include <iostream>
#include <algorithm>
#include <random>

# include "ImgProc.hpp"

int a = 0;      // Salt noise
int b = 255;    // Pepper noise

int A = 5;      // Salt noise
int B = 5;      // Pepper noise

std::default_random_engine generator;
std::uniform_int_distribution<int> normalDistribution(0, 100);

Matrix& makeNoise(Matrix& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            if(normalDistribution(generator) < A) {
                img[j][i] = a;
            }
            else if (normalDistribution(generator) < B) {
                img[j][i] = b;
            }
        }
    }
    return img;
}

int main() {
    Matrix img = RGBImage::fromFile("photo.bmp").toGray().toMatrix();
    
    img = makeNoise(img);

    GrayImage noise = GrayImage::fromMatrix(img);
    RGBImage::fromGrays(noise, noise, noise).toFile("result/noise(impulse).bmp");

    std::cout << "Done!" << std::endl;
}
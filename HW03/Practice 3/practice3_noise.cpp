#include <iostream>
#include <algorithm>
#include <random>

# include "ImgProc.hpp"

// Gray Level
int a = 0;
int b = 255;

// Impulse noise
int A = 5;      // Salt noise
int B = 5;      // Pepper noise

// Gussian noise
double sigma = 20.0;
double mu = 0.0;

std::default_random_engine generator;
std::normal_distribution<double> gussianDistribution(mu, sigma);

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
            else {
                double x = gussianDistribution(generator);
                img[j][i] += x;
                img[j][i] = std::clamp(img[j][i], 0.0, 255.0);  // C++17
            }
        }
    }
    return img;
}

int main() {
    Matrix img = RGBImage::fromFile("photo.bmp").toGray().toMatrix();
    
    img = makeNoise(img);

    GrayImage noise = GrayImage::fromMatrix(img);
    RGBImage::fromGrays(noise, noise, noise).toFile("result/noise.bmp");

    std::cout << "Done!" << std::endl;
}
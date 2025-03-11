// Gussian noise
#include <iostream>
#include <algorithm>
#include <random>

# include "ImgProc.hpp"

// Gussian noise
double sigma = 20.0;
double mu = 0.0;

std::default_random_engine generator;
std::normal_distribution<double> gussianDistribution(mu, sigma);

Matrix& makeNoise(Matrix& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            double x = gussianDistribution(generator);
            img[j][i] += x;
            img[j][i] = std::clamp(img[j][i], 0.0, 255.0);  // C++17
        }
    }
    return img;
}

int main() {
    Matrix img = RGBImage::fromFile("photo.bmp").toGray().toMatrix();
    
    img = makeNoise(img);

    GrayImage noise = GrayImage::fromMatrix(img);
    RGBImage::fromGrays(noise, noise, noise).toFile("result/noise(gussian).bmp");

    std::cout << "Done!" << std::endl;
}
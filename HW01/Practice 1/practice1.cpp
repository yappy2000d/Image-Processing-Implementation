#include <iostream>
#include <sstream>
#include <iomanip>
#include "imgProcess.hpp"

int main() {
    GrayImage imageA = RGBImage::fromFile("1.bmp").toGray();
    GrayImage imageB = RGBImage::fromFile("2.bmp").toGray();

    imageA.toFile("result/1_gray.bmp");
    imageB.toFile("result/2_gray.bmp");
    
    for(double m=0.1; m<=0.9; m+=0.1) {
        Matrix result = m * imageA.toMatrix() + (1 - m) * imageB.toMatrix();

        std::stringstream ss;
        ss << std::setprecision(1) << m;

        GrayImage::fromMatrix(result).toFile("result/" + ss.str() + ".bmp");
    }
    
    std::cout << "Done!" << std::endl;
    return 0;
}
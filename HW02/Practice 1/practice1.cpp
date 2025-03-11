#include <iostream>
#include <vector>

#include "ImgProc.hpp"

int main() {
    GrayImage gray = RGBImage::fromFile("../img/photo.bmp").toGray();

    gray.toFile("photo_gray.bmp");

    Matrix img = gray.toMatrix();
    std::vector<int> histogram(256, 0);

    for(auto &row: img) {
        for(auto &pixel: row) {
            histogram[int(pixel)]++;
        }
    }
    
    int n = img.height * img.width;
    int smax = 255;

    std::vector<double> s(256, 0);

    // Step 1
    s[0] = histogram[0] * smax / n;

    for(int i=1; i<=255; i++) {
        s[i] = s[i-1] + histogram[i] * smax / double(n);
    }

    // Step 3
    for(auto &row: img) {
        for(auto &pixel: row) {
            pixel = static_cast<int>(s[pixel]);
        }
    }

    GrayImage::fromMatrix(img).toFile("result/result1.bmp");

    std::cout << "Done!" << std::endl;

    return 0;
}
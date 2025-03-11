#include <iostream>
#include <vector>

#include "ImgProc.hpp"

int k = 25;


std::vector<int> histogram(256, 0);
std::vector<double> s(256, 0);

double equalize(const Matrix& img) {

    // Reset histogram and s
    std::fill(histogram.begin(), histogram.end(), 0);
    std::fill(s.begin(), s.end(), 0.0);

    for(auto &row: img) {
        for(auto &pixel: row) {
            histogram[int(pixel)]++;
        }
    }
    
    int n = img.height * img.width;
    int smax = 255;


    // Step 1
    s[0] = histogram[0] * smax / n;

    for(int i=1; i<=255; i++) {
        s[i] = s[i-1] + histogram[i] * smax / double(n);
    }

    return static_cast<int>(s[img[img.height/2][img.width/2]]);
}

/* Local Enhancement */
int main() {
    Matrix img = RGBImage::fromFile("../img/Cameraman_gray.bmp").toGray().toMatrix();

    Matrix result(img.height, img.width);

    // Slicing window
    for(int i=0; i<img.height-k; i++) {
        for(int j=0; j<img.width-k; j++) {
            Matrix sub = img.submatrix(i, j, k, k);
            result[i + k/2][j + k/2] = equalize(sub);
        }
    }

    GrayImage::fromMatrix(result).toFile("result/25x25.bmp");
    
    std::cout << "Done!" << std::endl;

    return 0;
}
#include <iostream>
#include <algorithm>

#include "ImgProc.hpp"

int main() {

    GrayImage grayImg = RGBImage::fromFile("../img/elephant.bmp").toGray();
    grayImg.toFile("result/gray.bmp");

    Matrix img = grayImg.toMatrix();

    int k = 3;
    Matrix filter = { {-2,-2, 0},
                      {-2, 0, 2},
                      { 0, 2, 2} };

    Matrix result(img.height - k, img.width - k);
    for(int i=0; i < img.height - k; i++) {
        for(int j=0; j < img.width - k; j++) {
            Matrix subMat = img.submatrix(i, j, k, k);
            result[i][j] = std::clamp(static_cast<int>(subMat.dot(filter)), 0, 255);
        }
    }

    GrayImage::fromMatrix(result).toFile("result/result.bmp");

    std::cout << "Done!" << std::endl;

    return 0;
}
#include <iostream>
#include <algorithm>

#include "ImgProc.hpp"

int main() {

    GrayImage grayImg = RGBImage::fromFile("../img/photo.bmp").toGray();
    grayImg.toFile("result/gray.bmp");

    Matrix img = grayImg.toMatrix();

    int k = 3;
    Matrix filter = { { 0, 1, 1},
                      {-1, 0, 1},
                      {-1,-1, 0} };

    Matrix result(img.height - k, img.width - k);
    for(int i=0; i < img.height - k; i++) {
        for(int j=0; j < img.width - k; j++) {
            Matrix subMat = img.submatrix(i, j, k, k);
            // result[i][j] = std::clamp(static_cast<int>(subMat.dot(filter)), 0, 255);
            result[i][j] = subMat.dot(filter);
        }
    }

    // GrayImage::fromMatrix(result).toFile("result/horizontal.bmp");

    Matrix filterB = { {-1,-1, 0},
                       {-1, 0, 1},
                       { 0, 1, 1} };
    Matrix resultB(img.height - k, img.width - k);
    for(int i=0; i < img.height - k; i++) {
        for(int j=0; j < img.width - k; j++) {
            Matrix subMat = img.submatrix(i, j, k, k);
            // resultB[i][j] = std::clamp(static_cast<int>(subMat.dot(filterB)), 0, 255);
            resultB[i][j] = subMat.dot(filterB);
        }
    }

    // GrayImage::fromMatrix(resultB).toFile("result/vertical.bmp");

    result += resultB;

    for(auto &row: result)
        for(auto &element: row)
            element = std::clamp(static_cast<int>(element), 0, 255);

    GrayImage::fromMatrix(result).toFile("result/result.bmp");

    std::cout << "Done!" << std::endl;

    return 0;
}
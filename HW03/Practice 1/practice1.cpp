#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

#include "ImgProc.hpp"

int main() {

    GrayImage grayImg = RGBImage::fromFile("photo.bmp").toGray();
    grayImg.toFile("result/gray.bmp");

    Matrix img = grayImg.toMatrix();

    // int k = 3;
    int k = 3;
    // Matrix filter = { {1, 1, 1},
    //                   {1, 1, 1},
    //                   {1, 1, 1} };
    Matrix filter(k, k, 1);
    filter.height = filter.width = k;
    
    Matrix result(img.height-k, img.width-k);

    for(int i=0; i < img.height - k; i++) {
        for(int j=0; j < img.width - k; j++) {
            Matrix subMat = img.submatrix(i, j, k, k);
            // result[i][j] = subMat.dot(filter) / 9;
            result[i][j] = subMat.dot(filter) / k / k;
        }
    }

    // GrayImage::fromMatrix(result).toFile("result/lowpass3.bmp");
    std::stringstream fileName;
    fileName << "result/lowpass"  << k << ".bmp";
    GrayImage::fromMatrix(result).toFile(fileName.str());

    std::cout << "Done!" << std::endl;

    return 0;
}
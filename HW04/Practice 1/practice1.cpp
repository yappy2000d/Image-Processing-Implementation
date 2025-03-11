#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

#include "ImgProc.hpp"

int main() {

    GrayImage grayImg = RGBImage::fromFile("photo.bmp").toGray();
    grayImg.toFile("result/gray.bmp");

    Matrix img = grayImg.toMatrix();

    int k = 3;
    // Matrix filter = { {-1,-1,-1},
    //                   {-1, 8,-1},
    //                   {-1,-1,-1} };
    Matrix filter(k, k, -1);
    filter[k/2][k/2] = k * k - 1;
    
    Matrix result(img.height - k, img.width - k);

    for(int i=0; i < img.height - k; i++) {
        for(int j=0; j < img.width - k; j++) {
            Matrix subMat = img.submatrix(i, j, k, k);
            result[i][j] = std::clamp(static_cast<int>(subMat.dot(filter) / k / k), 0, 255);
        }
    }

    std::stringstream fileName;
    fileName << "result/hipass"  << k << ".bmp";
    GrayImage::fromMatrix(result).toFile(fileName.str());

    std::cout << "Done!" << std::endl;

    return 0;
}
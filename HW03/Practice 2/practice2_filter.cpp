#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

#include "ImgProc.hpp"

int k = 5;

// 使用簡化版 median of median
double filter(Matrix& mat) {

    std::vector<double> median(mat.height);

    for(int i=0; i<mat.height; i++) {
        std::nth_element(mat[i].begin(), mat[i].begin() + k / 2, mat[i].end());
        median[i] = mat[i][k / 2];
    }

    std::nth_element(median.begin(), median.begin() + k / 2, median.end());

    return median[k/2];
}

int main() {
    Matrix img = RGBImage::fromFile("result/noise.bmp").toGray().toMatrix();


    Matrix result(img.height-k, img.width-k);

    for(int i=0; i < img.height - k; i++) {
        for(int j=0; j < img.width - k; j++) {
            Matrix subMat = img.submatrix(i, j, k, k);
            // result[i][j] = subMat.dot(filter) / 9;
            result[i][j] = filter(subMat);
        }
    }

    std::stringstream fileName;
    fileName << "result/mediam"  << k << ".bmp";
    GrayImage::fromMatrix(result).toFile(fileName.str());

    std::cout << "Done!" << std::endl;
    return 0;
}

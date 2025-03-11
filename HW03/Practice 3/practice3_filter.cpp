#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

#include "ImgProc.hpp"

const int k = 3;
const int t = 4;

// alpha-trimmed mean filter
uint8_t filter(const Matrix& mat) {

    std::vector<double> list;
    list.reserve(mat.height * mat.width);

    for(auto& row: mat) {
        for(auto& element: row) {
            list.emplace_back(element);
        }
    }

    std::sort(list.begin(), list.end());
    
    unsigned int mean = 0;
    for(int i=t; i < mat.height * mat.width - t; i++) {
        mean += list[i] / (k * k - 2 * t);
    }

    return mean;
}

int main() {
    Matrix img = RGBImage::fromFile("result/noise.bmp").toGray().toMatrix();

    Matrix result(img.height-k, img.width-k);

    for(int i=0; i < img.height - k; i++) {
        for(int j=0; j < img.width - k; j++) {
            Matrix subMat = img.submatrix(i, j, k, k);
            result[i][j] = filter(subMat);
        }
    }

    std::stringstream fileName;
    fileName << "result/alphatrimmedmean"  << t << ".bmp";
    GrayImage::fromMatrix(result).toFile(fileName.str());

    std::cout << "Done!" << std::endl;
    return 0;
}

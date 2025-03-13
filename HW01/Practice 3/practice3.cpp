#include <iostream>
#include "imgProcess.hpp"

double maxPooling(const Matrix &image, int y, int x, int k) {
    double max = 0;
    for(int i=0; i<k; i++) {
        for(int j=0; j<k; j++) {
            max = std::max(max, image[y+i][x+j]);
        }
    }
    return max;
}

int main() {
    RGBImage image = RGBImage::fromFile("photo.bmp");
    GrayImage imageGray = image.toGray();

    int posY = 80, posX = 150, height = 300, width = 420;

    OutlineRenderer renderer(image);
    renderer.setShape(ShapeType::RECTANGLE)
            .setDimensions(height, width)
            .setPos(posY, posX)
            .setColor({0, 0, 255})
            .setThickness(1)
            .render()
            .toFile("result/rect.bmp");
            
    renderer.setImage(imageGray)
            .render()
            .toFile("result/rectGray.bmp");

    // 選擇範圍
    Matrix imageA = imageGray.toMatrix();
    imageA = imageA.submatrix(posY, posX, height, width);
    
    // 縮小 k 倍
    int k = 2;

    Matrix imageB(imageA.height / k, imageA.width / k);

    for(int y=0; y <= imageA.height - k; y+=k) {
        for(int x=0; x <= imageA.width - k; x+=k) {
            imageB[y/k][x/k] = maxPooling(imageA, y, x, k);
        }
    }

    GrayImage::fromMatrix(imageB).toFile("result/maxpooling.bmp");

    std::cout << "Done!" << std::endl;
    return 0;
}
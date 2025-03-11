#include <iostream>
#include "imgProcess.hpp"

int main() {
    RGBImage image = RGBImage::fromFile("photo.bmp");
    GrayImage imageGray = image.toGray();

    int posY = 230, posX = 300, height = 50, width = 60;

    OutlineRenderer renderer(image);
    renderer.setShape(ShapeType::RECTANGLE)
            .setDimensions(height, width)
            .setPos(posY, posX)
            .setColor({0, 0, 255})
            .render()
            .toFile("result/rect.bmp");
            
    renderer.setImage(imageGray)
            .render()
            .toFile("result/rectGray.bmp");

    // 選擇範圍
    Matrix imageA = imageGray.toMatrix();
    imageA = imageA.submatrix(posY, posX, height, width);
    
    // 放大 k 倍
    int k = 8;

    // Linear Interpolation
    Matrix imageB(imageA.height * k, imageA.width * k);

    for (int y = 0; y < imageB.height; y+=k) {
        for (int x = 0; x < imageB.width; x++) {
            int xA = x / k;
            int yA = y / k;
            int xA1 = std::min(xA + 1, imageA.width - 1);
            
            float xRatio = (float)(x % k) / k;

            for(int i = 0; i < k; i++) {
                imageB[y + i][x] = imageA[yA][xA] * (1 - xRatio) + imageA[yA][xA1] * xRatio;
            }   
        }
    }

    GrayImage::fromMatrix(imageB).toFile("result/linear.bmp");

    // Bilinear Interpolation
    Matrix imageC(imageA.height * k, imageA.width * k);

    for (int y = 0; y < imageC.height; y++) {
        for (int x = 0; x < imageC.width; x++) {
            int xA = x / k;
            int yA = y / k;
            int xA1 = std::min(xA + 1, imageA.width - 1);
            int yA1 = std::min(yA + 1, imageA.height - 1);
            
            float xRatio = (float)(x % k) / k;
            float yRatio = (float)(y % k) / k;

            imageC[y][x] = (imageA[yA][xA] * (1 - xRatio) * (1 - yRatio) +
                            imageA[yA][xA1] * xRatio * (1 - yRatio) +
                            imageA[yA1][xA] * (1 - xRatio) * yRatio +
                            imageA[yA1][xA1] * xRatio * yRatio);
        }
    }

    GrayImage::fromMatrix(imageC).toFile("result/bilinear.bmp");

    std::cout << "Done!" << std::endl;
    return 0;
}
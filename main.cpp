#define cimg_use_jpeg

#include <iostream>
#include <string>
#include "../CImg-master/CImg.h"
#include "node.h"

using namespace std;
using namespace cimg_library;

//para instalar c++: sudo apt-get install g++

void grayScale3(string name, string outputName);
void grayScale1(string name, string outputName);
void binScale1(string name, string outputName, int threshold);

int* foo() {
    static int test[2];
    test[0] = 1;
    test[1] = 1;
    return test;
}

int main() {

    //int *arr = foo();
    
    //cout << arr[0] << endl;


    CImg<unsigned char> sample("sample.jpg");
    CImg<unsigned char> sample_output(sample.width(), sample.height(), 1, 3); 

    Compresor c = Compresor();
    c.src = sample;
    c.minSize = 10;
    c.out = sample_output;

    c.compressImage("ads", "asdads");

    //grayScale3("kunka.jpg", "kunkaGray3.jpg");
    //grayScale1("kunka.jpg", "kunkaGray1.jpg");
    //binScale1("kunka.jpg", "kunkaBin1.jpg", 100);

    // CImg<unsigned char> src("kunka.jpg");
 

    // int width = src.width();
    // int height = src.height();

    // CImg<unsigned char> img(width, height, 1, 3); 

    // cout << width << "x" << height << endl;
    // for (int y = 0; y < height; y++)
    //     for (int x = 0; x < width; x++) {
    //         unsigned char color[] = {(int)src(x,y,0,0) ,(int)src(x,y,0,1) ,(int)src(x,y,0,2)};
    //         img.draw_point(x, y, color);
    //     }
    //         //cout << "(" << r << "," << c << ") ="
    //         //     << " R" << (int)src(c,r,0,0)
    //         //     << " G" << (int)src(c,r,0,1)
    //         //     << " B" << (int)src(c,r,0,2) << endl;
    // //img.normalize(0, 255);
    // img.save("file.jpg");


    return 0;
}



void grayScale3(string name, string outputName) {
    CImg<unsigned char> src(name.c_str());

    int width = src.width();
    int height = src.height();

    CImg<unsigned char> outputImg(width, height, 1, 3); 

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++) {

            int grayColor = ((int)src(x, y, 0, 0) + (int)src(x, y, 0, 1) + (int)src(x, y, 0, 2)) / 3;

            unsigned char color[] = {grayColor ,grayColor ,grayColor};

            outputImg.draw_point(x, y, color);
        }
    }
     
    outputImg.save(outputName.c_str());
    
}

void grayScale1(string name, string outputName) {
    CImg<unsigned char> src(name.c_str());

    int width = src.width();
    int height = src.height();

    CImg<unsigned char> outputImg(width, height, 1, 1); 

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++) {

            int grayColor = ((int)src(x, y, 0, 0) + (int)src(x, y, 0, 1) + (int)src(x, y, 0, 2)) / 3;

            unsigned char color[] = {grayColor};

            outputImg.draw_point(x, y, color);
        }
    }
     
    outputImg.save(outputName.c_str());
    
}

void binScale1(string name, string outputName, int threshold) {
    CImg<unsigned char> src(name.c_str());

    int width = src.width();
    int height = src.height();

    CImg<unsigned char> outputImg(width, height, 1, 1); 

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++) {

            int grayColor = ((int)src(x, y, 0, 0) + (int)src(x, y, 0, 1) + (int)src(x, y, 0, 2)) / 3;

            if (grayColor>threshold)
                grayColor = 255;
            else
                grayColor = 0;

            unsigned char color[] = {grayColor};

            outputImg.draw_point(x, y, color);
        }
    }
     
    outputImg.save(outputName.c_str());
    
}




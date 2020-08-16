#ifndef NODE_H
#define NODE_H
#define cimg_use_jpeg

#include <iostream>
#include <string>
#include "../CImg-master/CImg.h"

using namespace std;
using namespace cimg_library;

class Point {
    public:
        int x;
        int y;

    double show() {
        cout << x << " " << y << endl;
    }
};

class Node {
    public:
        Point p1;
        Point p2;
        int RGB[3];
        Node *nodes[4];
        Bool isLeaf;
};


class Compresor {
    public:
        CImg<unsigned char> src;
        CImg<unsigned char> out;
        Node *root;
        int minSize;

    int *averageColor(Point p1, Point p2) {
        static int RGB[3];

        int R = 0;
        int G = 0;
        int B = 0;
        int n = (p2.y - p1.y) * (p2.x - p1.x);

        for (int y = p1.y; y < p2.y; y++)
        {
            for (int x = p1.x; x < p2.x; x++)
            {
                R = R + (int)src(x, y, 0, 0);
                G = G + (int)src(x, y, 0, 1);
                B = B + (int)src(x, y, 0, 2);
            }
        }

        R = R / n;
        G = G / n;
        B = B / n;

        RGB[0] = R;
        RGB[1] = G;
        RGB[2] = B;

        return RGB;
    }

    bool shouldStop(Point p1, Point p2) {
        int* RGB = averageColor(p1, p2);
        int t = 30;
        for (int y = p1.y; y < p2.y; y++){
            for (int x = p1.x; x < p2.x; x++){
                int R = (int)src(x, y, 0, 0);
                int G = (int)src(x, y, 0, 1);
                int B = (int)src(x, y, 0, 2);

                if ( R > RGB[0] + t || R < RGB[0] - t )
                    return false;
                if ( G > RGB[1] + t || G < RGB[1] - t )
                    return false;
                if ( B > RGB[2] + t || B < RGB[2] - t )
                    return false;
            }
        }

        return true;
    }

    Point* calculateNodes(Point p1, Point p2) {
        int x0 = p1.x;
        int y0 = p1.y;

        int x1 = p2.x;
        int y1 = p2.y;

        static Point points[8];

        Point p1_ini = Point();Point p1_fin = Point();
        Point p2_ini = Point();Point p2_fin = Point();
        Point p3_ini = Point();Point p3_fin = Point();
        Point p4_ini = Point();Point p4_fin = Point();

        //p1
        p1_ini.x = x0;
        p1_ini.y = y0;

        p1_fin.x = (x1+x0)/2;
        p1_fin.y = (y1+y0)/2;

        //p2
        p2_ini.x = (x1+x0)/2;
        p2_ini.y = y0;

        p2_fin.x = x1;
        p2_fin.y = (y1+y0)/2;

        //p3
        p3_ini.x = x0;
        p3_ini.y = (y1+y0)/2;

        p3_fin.x = (x1+x0)/2;
        p3_fin.y = y1;

        //p4
        p4_ini.x = (x1+x0)/2;
        p4_ini.y = (y1+y0)/2;

        p4_fin.x = x1;
        p4_fin.y = y1;

        points[0] = p1_ini;
        points[1] = p1_fin;
        points[2] = p2_ini;
        points[3] = p2_fin;
        points[4] = p3_ini;
        points[5] = p3_fin;
        points[6] = p4_ini;
        points[7] = p4_fin;

        //cout <<"(" <<points[0].x << "," <<points[0].y << ") : (" << points[1].x << "," << points[1].y <<")"<< endl;
        //cout <<"(" <<points[2].x << "," <<points[2].y << ") : (" << points[3].x << "," << points[3].y <<")"<< endl;
        //cout <<"(" <<points[4].x << "," <<points[4].y << ") : (" << points[5].x << "," << points[5].y <<")"<< endl;
        //cout <<"(" <<points[6].x << "," <<points[6].y << ") : (" << points[7].x << "," << points[7].y <<")"<< endl;

        return points;
    } 

    void dividir(Node* currentNode, Point p1, Point p2, int tam) {
        //for (int i = 0; i < tam; i++)
            //cout << "\t";
        //cout <<tam<< " dividir con (" << p1.x << "," << p1.y << ") : (" << p2.x << "," << p2.y << ")" << endl;
        //base case

        if (shouldStop(p1, p2) || p2.x - p1.x <= minSize || p2.y - p1.y <= minSize) {
            //cout << "IS LEAF" << endl;
            int* avgRGB = averageColor(p1, p2);
            currentNode->p1 = p1;
            currentNode->p2 = p2;
            currentNode->RGB[0] = avgRGB[0];
            currentNode->RGB[1] = avgRGB[1];
            currentNode->RGB[2] = avgRGB[2];
            currentNode->isLeaf = true;
            cout << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << " " << avgRGB[0] << " " << avgRGB[1] << " " << avgRGB[2] << endl;

            for (int y = p1.y; y < p2.y; y++) {
                for (int x = p1.x; x < p2.x; x++) {
                    unsigned char color[] = {avgRGB[0], avgRGB[1], avgRGB[2]};
                    out.draw_point(x, y, color);       
                }
            }
            
            return;
        } else {
            //cout << "DIVIDIR AGAIN" << endl;
            Point *newPoints = calculateNodes(p1, p2);

            Node *s1 = new Node();
            s1->isLeaf = false;
            s1->p1 = newPoints[0];
            s1->p2 = newPoints[1];
            currentNode->nodes[0] = s1;
            //cout << "\tS1" << endl;
                     
            Node *s2 = new Node();
            s2->isLeaf = false;
            s2->p1 = newPoints[2];
            s2->p2 = newPoints[3];
            currentNode->nodes[1] = s2;
            //cout << "\tS2" << endl;

            Node *s3 = new Node();
            s3->isLeaf = false;
            s3->p1 = newPoints[4];
            s3->p2 = newPoints[5];
            currentNode->nodes[2] = s3;
            //cout << "\tS3" << endl;
            

            Node *s4 = new Node();
            s4->isLeaf = false;
            s4->p1 = newPoints[6];
            s4->p2 = newPoints[7];
            currentNode->nodes[3] = s4;
            //cout << "\tS4" << endl;

            dividir(s1, s1->p1, s1->p2, tam+1);
            dividir(s2, s2->p1, s2->p2, tam+1);
            dividir(s3, s3->p1, s3->p2, tam+1);
            dividir(s4, s4->p1, s4->p2, tam+1);
        }

    }

    //compress an image
    void compressImage(string input, string output) {
        //cout << "START - compressImage " << endl;
        root = new Node();

        int width = src.width();
        int height = src.height();

        Point p1 = Point();
        Point p2 = Point();

        p1.x = 0;
        p1.y = 0;

        p2.x = width;
        p2.y = height;

        root->p1 = p1;
        root->p2 = p2;
        root->isLeaf = false;

        dividir(root, root->p1, root->p2, 0);
        //cout << "END - compressImage " << endl;
        out.save("salida.jpg");
    }

    //uncompress an image
    void uncompressImage(string input, string output) {

    }

};

#endif
//
//  main.cpp
//  Qube-it_Eye
//
//  Created by Stephen on 5/21/16.
//  Copyright © 2016 Stephen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;



Scalar scalBluLO = Scalar(100,0,0);
Scalar scalBluHI = Scalar(255,150,150);
Scalar scalGrnLO = Scalar(0,80,0);
Scalar scalGrnHI = Scalar(80,255,80);
Scalar scalRedLO = Scalar(0,0,100);
Scalar scalRedHI = Scalar(100,100,255);

int main(int argc, const char * argv[]) {
    
    //VideoCapture capture(0);
    Mat imgOrig, imgRed, imgBlu, imgGrn;
    
    //cout << argv[1];
    
    string filename = "/Users/Stephen/Desktop/Stephengine/Apple Tutorials/Qube-it_Eye/build/Debug/BGR.jpg";
    cout << filename;
    
    //namedWindow("test0", WINDOW_AUTOSIZE);
    
    //Mat test0(200, 200, CV_8UC1, Scalar(100,100,100));
    //imshow("test0", test0);
    //imshow("test", imread("BGR.jpg"));

    imgOrig = imread(filename, CV_LOAD_IMAGE_COLOR);   // Read the file
    if(imgOrig.empty()){cout << "you suck"; return -1;}
    
        /*capture >> imgOrig;
        flip(imgOrig, imgFlip, 1);*/
        
    namedWindow("orig", WINDOW_NORMAL);
    fprintf(stderr, "data is %p\n", imgOrig.data);
    
    imshow("orig", imgOrig);

    
    cin.ignore();
    
    return 0;
}

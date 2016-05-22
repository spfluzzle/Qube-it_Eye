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



Scalar scalBlkLO = Scalar(0,0,0);
Scalar scalBlkHI = Scalar(30,30,30);


int main(int argc, const char * argv[]) {
    
    VideoCapture capture(0);
    Mat imgOrig, imgFlip, imgEdit0, imgEdit1, black;
    
    while(true) {
        
    vector<vector<Point> > contours;
    vector<Rect> rects;
    
    
    capture >> imgOrig;
    flip(imgOrig, imgFlip, 1);
    
    inRange(imgFlip, scalBlkLO, scalBlkHI, black);
    
    Mat can, con;
    
    erode(black, imgEdit0, 0);
    dilate(imgEdit0, imgEdit1, 0);
    dilate(imgEdit1, imgEdit0, 0);
        
    Canny(imgEdit0, can, 50, 200);
        
    findContours(can, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    
    Point br;
    for(int i = 0; i < contours.size(); i++) {
        rects.push_back(boundingRect(contours.at(i)));
        br = Point(rects.at(i).x + rects.at(i).width, rects.at(i).y + rects.at(i).height);
        rectangle(imgFlip, rects.at(i).tl(), br, Scalar(155,155,155));
    }
    
    if(rects.size() > 0) {
        int largeRect = 0;
        double compare = 0;
        compare = rects.at(0).size().area();
        for(int i = 1; i < rects.size(); i++) {
            if(rects.at(i).size().area() > compare) {
                    compare = rects.at(i).size().area();
                    largeRect = i;
                }
            }
            cout << (rects.at(largeRect).x + rects.at(largeRect).width/2) << endl;
        }
    
        imshow("orig", imgFlip);
    }
    return 0;
}



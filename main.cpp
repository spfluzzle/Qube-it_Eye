//
//  main.cpp
//  Qube-it_Eye
//
//  Created by Stephen on 5/21/16.
//  Copyright © 2016 Stephen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <curl/curl.h>
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
    
    CURL *curl;
  
    curl_global_init(CURL_GLOBAL_ALL);
 
    curl = curl_easy_init();
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    int version = 0;

    while(true) {
        
    vector<vector<Point> > contours;
    vector<Rect> rects;
    
    
    capture >> imgOrig;
    flip(imgOrig, imgFlip, 1);
    int maxPosition = imgOrig.rows;
    
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
    
    int position = -1;
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
	position = (rects.at(largeRect).x + rects.at(largeRect).width/2);
            cout << position << endl;

	    
    }

    if (position > maxPosition) {
      position = maxPosition;
    }

    if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, "http://concelo.io:8080/");
//       curl_easy_setopt(curl, CURLOPT_VERBOSE, 1l);

      std::stringstream json;

      json << "{ \"value\": " << (((double) position) / ((double) maxPosition)) << ", \"version\": " << version << " }"; 

      ++ version;

      std::string s = json.str();
      const char* c = s.c_str();
       
      fprintf(stderr, "%d/%d json is %s\n", position, maxPosition, c);

      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, c);
      curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, s.length());
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 

      CURLcode res = curl_easy_perform(curl);
      if(res != CURLE_OK)
	fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
 
    }
    
    imshow("orig", imgFlip);
    }
    return 0;
}



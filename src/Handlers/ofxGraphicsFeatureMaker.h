#pragma once

#include "ofMain.h"

class ofxGraphicsFeatureMaker {
public:
    ofxGraphicsFeatureMaker();
    vector<double>      createInstanceFromPointArray(vector<ofVec2f> &points);
    void                drawInstanceFromPointArray(vector<double> &instance,
                                                   int x=0, int y=0, int width=100, int height=100);
protected:
    ofFbo               fbo;
    ofPixels            fboPixels;
    float               hop;
    int                 n;
};
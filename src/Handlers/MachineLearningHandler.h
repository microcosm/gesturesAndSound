#pragma once

#include "ofMain.h"
#include "ofxLearn.h"
#include "ofxGraphicsFeatureMaker.h"

class MachineLearningHandler {
public:
    void setup();
    void draw();
    void drawMachineLearningUI();
    void keyPressed(int key);
    void mouseMoved(int x, int y);
protected:
    bool showMachineLearningUI;
    ofxLearn classifier;
    ofxGraphicsFeatureMaker maker;
    vector<double> instance;
    bool isCreatingInstance, lastInstanceIsTraining, isTrained;
    int lastLabel;
    vector<ofVec2f> points;
};
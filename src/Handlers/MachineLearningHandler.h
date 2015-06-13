#pragma once

#include "ofMain.h"
#include "AudioUnitHandler.h"
#include "ofxLearn.h"
#include "ofxGraphicsFeatureMaker.h"

class MachineLearningHandler {
public:
    void setup();
    void sendClassificationsTo(AudioUnitHandler* _classificationTarget);
    void draw();
    void keyPressed(int key);
    void mouseMoved(int x, int y);
    void drawMachineLearningUI();
protected:
    ofxLearn classifier;
    ofxGraphicsFeatureMaker maker;
    AudioUnitHandler* classificationTarget;

    vector<double> instance;

    bool isCreatingInstance, lastInstanceIsTraining, isTrained, showMachineLearningUI;
    int lastLabel;
    vector<ofVec2f> points;
};
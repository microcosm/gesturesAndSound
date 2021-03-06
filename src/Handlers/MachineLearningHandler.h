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
    void drawUI();
protected:
    void drawDebugBox(int x, int y, int width, int height, ofColor color=ofColor(255, 255, 255, 32));
    void toggleUI();

    ofxLearn classifier;
    ofxGraphicsFeatureMaker maker;
    AudioUnitHandler* classificationTarget;

    vector<double> instance;

    bool isCreatingInstance, lastInstanceIsTraining, isTrained, showUI;
    int lastLabel;
    vector<ofVec2f> points;
};
#pragma once

#include "ofMain.h"
#include "AudioUnitHandler.h"
#include "ofxLearn.h"
#include "ofxGraphicsFeatureMaker.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void setupAudioUnitChains();
    void update();
    void draw();
    void drawMachineLearningUI();
    void play();
    void togglePlaying();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    AudioUnitHandler audioUnitHandler;
    
    bool showMachineLearningUI;
    ofxLearn classifier;
    ofxGraphicsFeatureMaker maker;
    vector<double> instance;
    bool isCreatingInstance, lastInstanceIsTraining, isTrained;
    int lastLabel;
    vector<ofVec2f> points;
};
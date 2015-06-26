#pragma once

#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxAudioUnitManager.h"
#include "ofxBpm.h"
#include "TALNoiseMaker.h"
#include "LowPassFilter.h"
#include "Reverb.h"
#include "ofxAnimatableFloat.h"

class AudioUnitHandler {
public:
    void setup();
    void setupAudioUnitChains();
    void update();
    void interpret(int classification);
    void draw();
    void play();
    void togglePlaying();
    void exit();
    void keyPressed(int key);
protected:
    ofxAudioUnitManager audioUnitManager;
    AudioUnitChain chain1, chain2;
    TALNoiseMaker noiseMaker1, noiseMaker2;
    LowPassFilter filter1, filter2;
    Reverb reverb1, reverb2;
    
    ofxBpm bpm;
    bool playing;
    int note;
    
    ofxAnimatableFloat cutoff;
    float cutoffTarget;
};
#include "AudioUnitHandler.h"

void AudioUnitHandler::setup() {
    playing = false;
    note = 60;
    audioUnitManager.setup();
    setupAudioUnitChains();
    
    ofAddListener(bpm.beatEvent, this, &AudioUnitHandler::play);
    bpm.start();
}

void AudioUnitHandler::setupAudioUnitChains(){
    //Chain 1
    audioUnitManager.add(&chain1, "tal-one", ofColor::blue);
    
    chain1.link(&noiseMaker1)
    .to(&filter1)
    .to(&reverb1)
    .toMixer();
    
    audioUnitManager.loadPresets(&chain1);
    
    //Chain 2
    audioUnitManager.add(&chain2, "tal-two", ofColor::red);
    
    chain2.link(&noiseMaker2)
    .to(&filter2)
    .to(&reverb2)
    .toMixer();
    
    audioUnitManager.loadPresets(&chain2);
}

void AudioUnitHandler::play(void){
    if(playing) {
        chain1.midi()->sendNoteOn(1, note);
        chain2.midi()->sendNoteOn(1, note);
    }
}

void AudioUnitHandler::togglePlaying() {
    playing = !playing;
    if(!playing) {
        chain1.midi()->sendNoteOff(1, note);
        chain2.midi()->sendNoteOff(1, note);
    }
}

void AudioUnitHandler::update(){
    /*float cutoff = ofMap(sin(ofGetFrameNum() * 0.05), -1, 1, 0, 1);
     noiseMaker1.set(TALNoiseMaker_cutoff, cutoff);*/
}

void AudioUnitHandler::interpret(int classification){
    if(classification == 1) {
        chain1.presets()->increment();
    }
    if(classification == 2) {
        chain2.presets()->increment();
    }
}

void AudioUnitHandler::draw(){
    audioUnitManager.draw();
}

void AudioUnitHandler::exit() {
    audioUnitManager.exit();
}

void AudioUnitHandler::keyPressed(int key){
    if(key == ' ') {
        togglePlaying();
    } else if(key == '[') {
        togglePlaying();
        note--;
        togglePlaying();
    } else if(key == ']') {
        togglePlaying();
        note++;
        togglePlaying();
    } else {
        audioUnitManager.keyPressed(key);
    }
}
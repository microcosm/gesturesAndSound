#include "ofApp.h"

void ofApp::setup(){
    playing = false;
    note = 60;

    //Audio Unit Manager stuff
    manager.setup();
    manager.toggleDebugUI();

    //Chain 1
    manager.add(&chain1, "tal-one", ofColor::blue);

    chain1.link(&noiseMaker1)
          .to(&filter1)
          .to(&reverb1)
          .toMixer();

    manager.loadPresets(&chain1);
    
    //Chain 2
    manager.add(&chain2, "tal-two", ofColor::red);

    chain2.link(&noiseMaker2)
          .to(&filter2)
          .to(&reverb2)
          .toMixer();

    manager.loadPresets(&chain2);

    //ofxBpm
    ofAddListener(bpm.beatEvent, this, &ofApp::play);
    bpm.start();
}

void ofApp::play(void){
    if(playing) {
        chain1.midi()->sendNoteOn(1, note);
        chain2.midi()->sendNoteOn(1, note);
    }
}

void ofApp::togglePlaying() {
    playing = !playing;
    if(!playing) {
        chain1.midi()->sendNoteOff(1, note);
        chain2.midi()->sendNoteOff(1, note);
    }
}

void ofApp::update(){
    /*float cutoff = ofMap(sin(ofGetFrameNum() * 0.05), -1, 1, 0, 1);
    noiseMaker1.set(TALNoiseMaker_cutoff, cutoff);*/
}

void ofApp::draw(){
    manager.draw();
}

void ofApp::exit() {
    manager.exit();
}

void ofApp::keyPressed(int key){
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
        manager.keyPressed(key);
    }
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){

}
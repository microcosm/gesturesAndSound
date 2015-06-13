#include "ofApp.h"

void ofApp::setup(){
    audioUnitHandler.setup();
    machineLearningHandler.setup();
}

void ofApp::update(){
    audioUnitHandler.update();
}

void ofApp::draw(){
    audioUnitHandler.draw();
    machineLearningHandler.draw();
}

void ofApp::exit() {
    audioUnitHandler.exit();
}

void ofApp::keyPressed(int key){
    audioUnitHandler.keyPressed(key);
    machineLearningHandler.keyPressed(key);
}

void ofApp::mouseMoved(int x, int y ){
    machineLearningHandler.mouseMoved(mouseX, mouseY);
}

void ofApp::keyReleased(int key){

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
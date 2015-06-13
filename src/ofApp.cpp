#include "ofApp.h"

void ofApp::setup(){
    audioUnitHandler.setup();
    
    showMachineLearningUI = false;
    isCreatingInstance = false;
    lastInstanceIsTraining = true;
}

void ofApp::update(){
    audioUnitHandler.update();
}

void ofApp::draw(){
    audioUnitHandler.draw();
    if(showMachineLearningUI){
        drawMachineLearningUI();
    }
}

void ofApp::exit() {
    audioUnitHandler.exit();
}

void ofApp::keyPressed(int key){
    if(key == 'l') {
        showMachineLearningUI = !showMachineLearningUI;
    } else {
        audioUnitHandler.keyPressed(key);
    }
    
    //Machine Learning stuff
    //========================
    
    // add an instance to training set
    if (key > 48 && key < 58) {
        if (isCreatingInstance) {
            lastLabel = key - 48;        // training label is between 1 and 9
            instance = maker.createInstanceFromPointArray(points);
            classifier.addTrainingInstance(instance, lastLabel);
            points.clear();
            isCreatingInstance = false;
            lastInstanceIsTraining = true;
        }
    }
    // classify new instance
    else if (key=='c') {
        if (isCreatingInstance) {
            instance = maker.createInstanceFromPointArray(points);
            lastLabel = classifier.predict(instance);
            
            
            //lastLabel is the class of the classified gesture
            cout << lastLabel << endl;
            
            if(lastLabel == 1) {
                //chain1.presets()->increment();
            }
            if(lastLabel == 2) {
                //chain2.presets()->increment();
            }
            if(lastLabel == 3) {
                
            }
            
            
            points.clear();
            isCreatingInstance = false;
            lastInstanceIsTraining = false;
        }
    }
    // begin recording new instance
    else if (key=='i')
        isCreatingInstance = true;
    // train model
    else if (key=='t') {
        classifier.trainClassifier();
        isTrained = true;
    }
}

void ofApp::drawMachineLearningUI(){
    ofSetColor(0);
    
    ofDrawBitmapString("Training set currently contains " + ofToString(classifier.getNumberTrainingInstances()) + " examples", 55, 30);
    
    if (isTrained)
        ofDrawBitmapString("Model trained and ready to use", 55, 55);
    else
        ofDrawBitmapString("No model trained yet", 55, 55);
    
    if (isCreatingInstance) {
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofCircle(60, 75, 5);
        ofPopStyle();
        ofDrawBitmapString("Recording new instance...", 70, 80);
    }
    
    if (instance.size() > 0) {
        if (lastInstanceIsTraining)
            ofDrawBitmapString("Last instance added to training set, class " + ofToString(lastLabel), 555, 30);
        else
            ofDrawBitmapString("Prediction for this instance: class " + ofToString(lastLabel), 555, 30);
        maker.drawInstanceFromPointArray(instance, 550, 50, 300, 300);
    }
    
    // Instructions
    ofDrawBitmapString("INSTRUCTIONS:", 55, 400);
    ofDrawBitmapString("1) Click 'i' to begin recording your mouse motion.", 55, 420);
    ofDrawBitmapString("2) While recording, click any number key to assign that gesture to that class:", 55, 440);
    ofDrawBitmapString("3) Try to record at least 10 examples for each class", 55, 460);
    ofDrawBitmapString("4) Click 't' to train model (may take a minute)", 55, 480);
    ofDrawBitmapString("5) When model is trained, try applying model to new example by", 55, 500);
    ofDrawBitmapString("   by recording a new example and clicking 'c'", 55, 520);
}

void ofApp::mouseMoved(int x, int y ){
    if (isCreatingInstance) points.push_back(ofVec2f(mouseX,mouseY));
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
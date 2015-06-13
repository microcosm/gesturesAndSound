#include "MachineLearningHandler.h"

void MachineLearningHandler::setup() {
    showMachineLearningUI = false;
    isCreatingInstance = false;
    lastInstanceIsTraining = true;
}

void MachineLearningHandler::sendClassificationsTo(AudioUnitHandler* _classificationTarget) {
    classificationTarget = _classificationTarget;
}

void MachineLearningHandler::draw(){
    if(showMachineLearningUI){
        drawMachineLearningUI();
    }
}

void MachineLearningHandler::keyPressed(int key){
    if(key == 'l') {
        showMachineLearningUI = !showMachineLearningUI;
    }
    // add an instance to training set
    else if (key > 48 && key < 58) {
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
    else if (key == 'c') {
        if (isCreatingInstance) {
            instance = maker.createInstanceFromPointArray(points);
            lastLabel = classifier.predict(instance);

            classificationTarget->interpret(lastLabel);

            points.clear();
            isCreatingInstance = false;
            lastInstanceIsTraining = false;
        }
    }
    // begin recording new instance
    else if (key == 'i')
        isCreatingInstance = true;
    // train model
    else if (key == 't') {
        classifier.trainClassifier();
        isTrained = true;
    }
}

void MachineLearningHandler::mouseMoved(int x, int y){
    if(isCreatingInstance) {
        points.push_back(ofVec2f(x, y));
    }
}

void MachineLearningHandler::drawMachineLearningUI(){
    
    drawDebugBox(10, 445, 696, 314);
    ofFill();
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Training set currently contains " + ofToString(classifier.getNumberTrainingInstances()) + " examples", 330, 470);
    
    if (isTrained)
        ofDrawBitmapString("Model trained and ready to use", 330, 490);
    else
        ofDrawBitmapString("No model trained yet", 330, 490);
    
    if (isCreatingInstance) {
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofCircle(575, 541, 5);
        ofPopStyle();
        ofDrawBitmapString("Recording...", 591, 546);
    }
    
    drawDebugBox(330, 525, 220, 220);
    if (instance.size() > 0) {
        if (lastInstanceIsTraining)
            ofDrawBitmapString("Last instance added to training set, class " + ofToString(lastLabel), 330, 510);
        else
            ofDrawBitmapString("Prediction for this instance: class " + ofToString(lastLabel), 330, 510);
        
        maker.drawInstanceFromPointArray(instance, 340, 535, 200, 200);
    } else {
        drawDebugBox(340, 535, 200, 200, ofColor(ofColor::black, 150));
        ofDrawBitmapString("No instances recorded yet", 330, 510);
    }
    
    // Instructions
    ofDrawBitmapString("ofxLearn:", 20, 470);
    ofDrawBitmapString("1) i = record gesture", 20, 490);
    ofDrawBitmapString("2) 1-9 = assign gesture to class", 20, 510);
    ofDrawBitmapString("3) record 10 x gestures per class", 20, 530);
    ofDrawBitmapString("4) t = train model (wait)", 20, 550);
    ofDrawBitmapString("5) record new gesture, then", 20, 570);
    ofDrawBitmapString("6) c = interpret recorded gesture", 20, 590);
}

void MachineLearningHandler::drawDebugBox(int x, int y, int width, int height, ofColor color) {
    ofSetLineWidth(1);
    ofSetColor(color);
    ofFill();
    ofRect(x, y, width, height);
    ofSetColor(ofColor::white);
    ofNoFill();
    ofRect(x, y, width, height);
    ofFill();
}
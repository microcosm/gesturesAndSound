#include "ofApp.h"

ofxGraphicsFeatureMaker::ofxGraphicsFeatureMaker() {
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    fboPixels.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    hop = 0.25;
    n = 6;
}

vector<double> ofxGraphicsFeatureMaker::createInstanceFromPointArray(vector<ofVec2f> &points) {
    
    // get bounding box for point set
    float x_min = ofGetWidth();
    float x_max = 0;
    float y_min = ofGetHeight();
    float y_max = 0;
    
    for (int i = 0; i < points.size(); i++) {
        if (points[i].x > x_max)
            x_max = points[i].x;
        if (points[i].x < x_min)
            x_min = points[i].x;
        if (points[i].y > y_max)
            y_max = points[i].y;
        if (points[i].y < y_min)
            y_min = points[i].y;
    }
    
    // translate the points to the middle of the screen
    float transX = (ofGetWidth() - x_max - x_min) / 2;
    float transY = (ofGetHeight() - y_max - y_min) / 2;
    for (int i = 0; i < points.size(); i++)
        points[i].set(points[i].x + transX, points[i].y + transY);
    x_min += transX;
    x_max += transX;
    y_min += transY;
    y_max += transY;
    
    // add 10% extra to width and height
    x_min -= min((int) (0.1 * (x_max-x_min)), (int) x_min);
    x_max += min((int) (0.1 * (x_max-x_min)), ofGetWidth() - (int) x_max);
    y_min -= min((int) (0.1 * (y_max-y_min)), (int) y_min);
    y_max += min((int) (0.1 * (y_max-y_min)), ofGetHeight() - (int) y_max);
    
    // make the bounding box square
    if (x_max - x_min < y_max - y_min) {
        float diff = (y_max - y_min) - (x_max - x_min);
        float diff_left = min(diff / 2, x_min);
        float diff_right = min((float)(diff / 2 + (diff / 2 - diff_left)), (float)(ofGetWidth() - (int)x_max));
        x_min -= diff_left;
        x_max += diff_right;
    }
    else if (y_max - y_min < x_max - x_min) {
        float diff = (x_max - x_min) - (y_max - y_min);
        float diff_top = min(diff / 2, y_min);
        float diff_bottom = min((float)(diff / 2 + (diff / 2 - diff_top)), (float)(ofGetHeight() - (int)y_max));
        y_min -= diff_top;
        y_max += diff_bottom;
    }
    
    // draw the point set onto an FBO
    fbo.begin();
    ofPushStyle();
    ofClear(0,0,0);
    ofSetColor(0);
    
    ofStyle style;
    style.lineWidth = (x_max-x_min) / n;
    style.bFill = false;
    style.smoothing = true;
    ofSetStyle(style);
    
    // write trajectory to image
    ofBeginShape();
    for (int i = 0; i < points.size(); i++)
        ofCurveVertex(points[i].x, points[i].y);
    ofEndShape();
    ofPopStyle();
    fbo.end();
    fbo.readToPixels(fboPixels);
    
    // read image back from fbo and turn into feature vector
    double w = (x_max - x_min) / (n - n * hop + hop);
    double h = (y_max - y_min) / (n - n * hop + hop);
    unsigned char * p = fboPixels.getPixels();
    vector<double> instance;
    
    int r, g, b, left, right, top, bottom, index; float weight, totalweight;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            r = g = b = 0;
            left = x_min + i * w * (1-hop);
            right = left + w;
            top = y_min + j * h * (1-hop);
            bottom = top + h;
            totalweight = 0;
            for (int x = left; x < right; x++) {
                for (int y = top; y < bottom; y++) {
                    index = y * fboPixels.getWidth() * 3 + x * 3;
                    weight = 1 - ofDist(x, y, left + right/2, top + bottom/2) / ofDist(0, 0, x_max, y_max);
                    r += weight * p[index];
                    g += weight * p[index+1];
                    b += weight * p[index+2];
                    totalweight += weight;
                }
            }
            instance.push_back( (r+g+b) / (3 * totalweight) );
        }
    }
    return instance;
}

void ofxGraphicsFeatureMaker::drawInstanceFromPointArray(vector<double> &instance, int x, int y, int width, int height) {
    float widthcell = (float) width / n;
    float heightcell = (float) height / n;
    ofPushStyle();
    for (int j = 0; j < n * n; j++) {
        ofSetColor(instance[j] * 6);
        int yoff = (j % n) * widthcell;
        int xoff = (j / n) * heightcell;
        ofRect(x + xoff, y + yoff, widthcell - 2, heightcell - 2);
    }
    ofPopStyle();
}
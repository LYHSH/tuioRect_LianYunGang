#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	myBoxMgr.setup();

	gui.setup();

	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
	myBoxMgr.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	myBoxMgr.draw();

	gui.begin();
	myBoxMgr.showGui();
	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	myBoxMgr.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	myBoxMgr.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	myBoxMgr.mouseDragged(x, y,button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	myBoxMgr.mousePressed(x, y,button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	myBoxMgr.mouseReleased(x, y,button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

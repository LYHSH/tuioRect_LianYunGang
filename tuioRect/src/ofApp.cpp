#include "ofApp.h"
#include "ofxIdentificationMgr.h"
//--------------------------------------------------------------
void ofApp::setup(){
	{
		int nums = 5;
		ofxIdentificationMgr::setExtraInfo(ofToString(nums));
		ofxIdentificationMgr::setup();
	}
	


	myBoxMgr.setup();

	gui.setup();

	video.setup();

	bSetting = false;
	//Connect to Port
	myTuio.connect(3333);

	//Assign Global TUIO Callback Functions
	ofAddListener(ofEvents().touchDown, this, &ofApp::touchDown);
	ofAddListener(ofEvents().touchUp, this, &ofApp::touchUp);
	ofAddListener(ofEvents().touchMoved, this, &ofApp::touchMoved);

	lasttimer = 0.0f;

	ofSetWindowShape(screen_w, screen_h);
	ofSetFullscreen(true);
	ofHideCursor();
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
	myBoxMgr.update();

	video.update();

	myTuio.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	/*int activeIndex = video.getActiveIndex();

	if (video.isStoped())
	{
		video.draw(0, 0, screen_w,screen_h);
	}
	else
	{
		auto rect = myBoxMgr.getRect(activeIndex);
		video.draw(rect.getX(),rect.getY(),rect.getWidth(),rect.getHeight());
	}*/

	video.draw(0, 0, screen_w, screen_h);
	
	if (bSetting)
	{
		myBoxMgr.draw();

		gui.begin();
		myBoxMgr.showGui();
		gui.end();
	}

	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_RETURN)
	{
		bSetting = !bSetting;
		bSetting ? ofShowCursor() : ofHideCursor();
	}

	if (bSetting)
	{
		myBoxMgr.keyPressed(key);
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (bSetting)
	{
		myBoxMgr.mouseMoved(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (bSetting)
	{
		myBoxMgr.mouseDragged(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (bSetting)
	{
		myBoxMgr.mousePressed(x, y, button);
	}
	else
	{
		if (ofGetElapsedTimef() - lasttimer > 2.0f)
		{
			int id = myBoxMgr.touch(x, y);
			if (id != -1)
			{
				video.reloadVideo(id);
				lasttimer = ofGetElapsedTimef();
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (bSetting)
	{
		myBoxMgr.mouseReleased(x, y, button);
	}
	
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

void ofApp::exit()
{
	ofRemoveListener(ofEvents().touchDown, this, &ofApp::touchDown);
	ofRemoveListener(ofEvents().touchUp, this, &ofApp::touchUp);
	ofRemoveListener(ofEvents().touchMoved, this, &ofApp::touchMoved);
}

void ofApp::touchDown(ofTouchEventArgs & touch) {
	int x = touch.x * screen_w;
	int y = touch.y * screen_h;


	if (ofGetElapsedTimef() - lasttimer > 2.0f)
	{
		int id = myBoxMgr.touch(x, y);
		if (id != -1)
		{
			video.reloadVideo(id);
			lasttimer = ofGetElapsedTimef();
		}
	}
}

void ofApp::touchUp(ofTouchEventArgs & touch) {
	
}

void ofApp::touchMoved(ofTouchEventArgs & touch) {
	int x = touch.x * screen_w;
	int y = touch.y * screen_h;
	if (ofGetElapsedTimef() - lasttimer > 2.0f)
	{
		int id = myBoxMgr.touch(x, y);
		if (id != -1)
		{
			video.reloadVideo(id);
			lasttimer = ofGetElapsedTimef();
		}
	}
}

#pragma once

#include "ofMain.h"
#include "affineBox.h"
#include "ofxImGui.h"
#include "boxMgr.h"
#include "videoPlayer.h"
#include "ofxTuioClient.h"

static float const screen_w = 1920.0f;
static float const screen_h = 1080.0f;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();
		
		bool bSetting;
		ofxImGui::Gui gui;

		boxMgr myBoxMgr;

		videoPlayer video;


		ofxTuioClient myTuio;

		void touchDown(ofTouchEventArgs & touch);
		void touchUp(ofTouchEventArgs & touch);
		void touchMoved(ofTouchEventArgs & touch);

		float lasttimer;
};

#pragma once
#include "ofxImGui.h"
#include "affineBox.h"
#include "ofxXmlSettings.h"
class boxMgr
{
public:
	boxMgr();
	~boxMgr();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	void showGui();

	string getDir();
private:
	vector<affineBox *> boxs;
	int editorIndex;

	bool bShowGui;
};


#pragma once
/************************************************************************/
/* project name:雷达定位软件
/* fiel describe:捕获区域选框
/* author:hui
/* date:2019.01.04
/************************************************************************/
#include "ofMain.h"
#include "ofxXmlSettings.h"
class affineBox
{
public:
	affineBox();
	~affineBox();

	void setup();
	void setup(string _file);
	void draw(bool setting = false);

	ofRectangle getRect();

	void loadSetting(string _file);
	void saveSetting(string _file);
	void saveSetting();
	

	void mouseReleased(int x, int y);
	void mousePressed(int x, int y);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y);

	void keySetting(int key);
	void showDebugMessage();

	string getFile();
private:
	string defaultFile;
	struct DragPoint
	{
		bool bOver;
		bool bDrag;
		float radio;
		DragPoint()
		{
			bOver = false;
			bDrag = false;
			radio = 5.0f;
		}
	};

	static int const POINT_NUMS = 5;
	ofVec2f affinePts[POINT_NUMS];
	DragPoint* affineDragPts[POINT_NUMS];
	int setttingIndex;
};


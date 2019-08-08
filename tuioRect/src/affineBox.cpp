#include "affineBox.h"



affineBox::affineBox()
{
	defaultFile = "affine.xml";
	setttingIndex = -1;
}


affineBox::~affineBox()
{
}

void affineBox::setup()
{
	for (int i = 0; i < POINT_NUMS; i++)
	{
		affineDragPts[i] = new DragPoint();
 		affineDragPts[i]->bOver = false;
 		affineDragPts[i]->bDrag = false;
 		affineDragPts[i]->radio = 6.0f;
	}
// 
	affinePts[0].x = 5.0f;
	affinePts[0].y = 5.0f;

	affinePts[1].x = ofGetWidth() - 200.0f;
	affinePts[1].y = 5.0f;

	affinePts[2].x = 5.0f;
	affinePts[2].y = ofGetHeight() - 200.0f;

	affinePts[3].x = ofGetWidth() - 200.0f;
	affinePts[3].y = ofGetHeight() - 200.0f;

	affinePts[4].x = getRect().getCenter().x;
	affinePts[4].y = getRect().getCenter().y;

	cout << affinePts[4] << endl;

	loadSetting(defaultFile);
}

void affineBox::setup(string _file)
{
	defaultFile = _file;
	setup();
}

void affineBox::draw(bool setting /* = false */)
{
	ofPushStyle();
	ofSetColor(0, 255, 255);
	ofNoFill();
	ofDrawRectangle(affinePts[0].x, affinePts[0].y, affinePts[3].x - affinePts[0].x, affinePts[3].y - affinePts[0].y);
	if (setting)
	{
		ofPushStyle();
		ofSetColor(255, 0, 0, 128);
		ofFill();
		ofDrawRectangle(affinePts[0].x + 2, affinePts[0].y + 2, affinePts[3].x - affinePts[0].x - 4, affinePts[3].y - affinePts[0].y-4);
		ofPopStyle();
	}
	for (int i = 0; i < POINT_NUMS; i++)
	{
		if (affineDragPts[i]->bOver || setttingIndex == i)
		{
			ofFill();
		}
		else
		{
			ofNoFill();
		}
		ofCircle(affinePts[i].x, affinePts[i].y, 6);
	}
	ofPopStyle();

	if (-1 != setttingIndex)
	{
		showDebugMessage();
	}
}

ofRectangle affineBox::getRect()
{
	return ofRectangle(affinePts[0],affinePts[3]);
//	return ofRectangle(0,0,0,0);
}

void affineBox::loadSetting(string _file)
{
	ofxXmlSettings xml;
	if (!xml.load(_file))return;
	
	for (int i = 0; i < POINT_NUMS ;i++)
	{
		xml.pushTag("point", i);
		affinePts[i].x = xml.getValue("x", 0.0f);
		affinePts[i].y = xml.getValue("y", 0.0f);
		xml.popTag();
	}
}

void affineBox::saveSetting(string _file)
{
	ofxXmlSettings xml;

	for (int i = 0; i < POINT_NUMS; i++)
	{
		xml.addTag("point");
		xml.pushTag("point", i);
		xml.addValue("x", affinePts[i].x);
		xml.addValue("y", affinePts[i].y);
		xml.popTag();
	}

	xml.save(_file);
}

void affineBox::saveSetting()
{
	saveSetting(defaultFile);
}

void affineBox::mouseMoved(int x, int y)
{
	for (int i = 0; i < POINT_NUMS; i++)
	{
		if (ofDist(x, y, affinePts[i].x, affinePts[i].y) < affineDragPts[i]->radio)
		{
			affineDragPts[i]->bOver = true;
		}
		else
		{
			affineDragPts[i]->bOver = false;
		}
	}
}

void affineBox::mouseReleased(int x, int y)
{
	for (int i = 0; i < POINT_NUMS; i++)
	{
		affineDragPts[i]->bOver = false;
		affineDragPts[i]->bDrag = false;
	}
}

void affineBox::mousePressed(int x, int y)
{
	for (int i = 0; i < POINT_NUMS; i++)
	{
		if (affineDragPts[i]->bOver)
		{
			affineDragPts[i]->bDrag = true;
		}
	}
}


void affineBox::mouseDragged(int x, int y) {
	for (int i = 0; i < POINT_NUMS; i++)
	{
		if (affineDragPts[i]->bDrag)
		{
			affinePts[i] = ofVec2f(x, y);

			if (i == 0)
			{
				affinePts[2].x = x;
				affinePts[1].y = y;
			}
			else if (i == 1)
			{
				affinePts[0].y = y;
				affinePts[3].x = x;
			}
			else if (i == 2)
			{
				affinePts[0].x = x;
				affinePts[3].y = y;
			}
			else if (i == 3)
			{
				affinePts[1].x = x;
				affinePts[2].y = y;
			}
			else if (i == 4)
			{
				ofRectangle rect = getRect();
				rect.setFromCenter(affinePts[i], rect.getWidth(), rect.getHeight());

				affinePts[0] = rect.getTopLeft();
				affinePts[1] = rect.getTopRight();
				affinePts[2] = rect.getBottomLeft();
				affinePts[3] = rect.getBottomRight();
			}

			affinePts[4] = getRect().getCenter();
		}
	}

}

void affineBox::keySetting(int key)
{
	bool keyFlag = false;
	switch (key)
	{
	case 'd':
	case 'D':
		if (setttingIndex == -1)
		{
			setttingIndex = 0;
		}
		else
		{
			setttingIndex = -1;
		}
		break;
	case 'q':
	case 'Q':
		if (setttingIndex != -1)
		{
			setttingIndex = (++setttingIndex) % POINT_NUMS;
		}
		break;
	case 'w':
	case 'W':
		if (setttingIndex != -1)
		{
			setttingIndex = (--setttingIndex + POINT_NUMS) % POINT_NUMS;
		}
		break;
	case OF_KEY_LEFT:
		if (-1 != setttingIndex)
		{
			affinePts[setttingIndex].x--;
			keyFlag = true;
		}
		break;
	case OF_KEY_RIGHT:
		if (-1 != setttingIndex)
		{
			affinePts[setttingIndex].x++;
			keyFlag = true;
		}
		break;
	case OF_KEY_UP:
		if (-1 != setttingIndex)
		{
			affinePts[setttingIndex].y--;
			keyFlag = true;
		}
		break;
	case OF_KEY_DOWN:
		if (-1 != setttingIndex)
		{
			affinePts[setttingIndex].y++;
			keyFlag = true;
		}
		break;
	default:
		break;
	}

	if (keyFlag)
	{
		float x = affinePts[setttingIndex].x;
		float y = affinePts[setttingIndex].y;
		if (setttingIndex == 0)
		{
			affinePts[2].x = x;
			affinePts[1].y = y;
		}
		else if (setttingIndex == 1)
		{
			affinePts[0].y = y;
			affinePts[3].x = x;
		}
		else if (setttingIndex == 2)
		{
			affinePts[0].x = x;
			affinePts[3].y = y;
		}
		else if (setttingIndex == 3)
		{
			affinePts[1].x = x;
			affinePts[2].y = y;
		}
	}
}

void affineBox::showDebugMessage()
{
	stringstream sss;
	sss << "Press 'Q' or 'W' to choose point" << endl;
	sss << "Press 'KEY_LEFT' or 'KEY_RIGHT' to move x" << endl;
	sss << "Press 'KEY_UP' or 'KEY_DOWN' to move Y" << endl;

	ofPushStyle();
	ofSetColor(255, 0, 0);
	ofDrawBitmapString(sss.str(), affinePts[0].x + 10, affinePts[0].y + 10);
	ofPopStyle();
}

string affineBox::getFile()
{
	return defaultFile;
}

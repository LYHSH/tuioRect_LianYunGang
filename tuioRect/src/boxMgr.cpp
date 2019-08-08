#include "boxMgr.h"



boxMgr::boxMgr()
{
	ofFile file(getDir());
	if (!file.exists())
	{
		file.create();
	}
}


boxMgr::~boxMgr()
{
}

void boxMgr::setup() {
	bShowGui = true;

	ofxXmlSettings xml;
	xml.load(getDir() + "config.xml");

	int boxNums = xml.getNumTags("box");

	for (int i = 0;i < boxNums;i++)
	{
		xml.pushTag("box", i);
		string file = xml.getValue("file", "");
		affineBox * p = new affineBox();
		p->setup(file);
		boxs.push_back(p);
		xml.popTag();
	}

	editorIndex = -1;
}

void boxMgr::update()
{

}

void boxMgr::draw()
{
	for (int i = 0;i < boxs.size();i++)
	{
		boxs[i]->draw(editorIndex == i);
	}
}

void boxMgr::showGui()
{
	if (bShowGui)
	{
		ImGui::SetNextWindowPos(ImVec2(20, 20));
		ImGui::SetNextWindowSize(ImVec2(400, 480));

		ImGui::Begin("setting");
		for (int i = 0;i < boxs.size();i++)
		{
			if (!(i % 3))
			{
				ImGui::NewLine();
			}
			string name = "box" + ofToString(i);
			ImGui::RadioButton(name.c_str(), &editorIndex, i);
			ImGui::SameLine();
		}
		ImGui::NewLine();

		if (ImGui::Button("add"))
		{
			affineBox * p = new affineBox();
			string file = getDir() + ofToString(boxs.size()) + ".xml";
			p->setup(file);
			boxs.push_back(p);

			editorIndex = boxs.size() - 1;
		}
		if (ImGui::Button("remove"))
		{
			if (editorIndex >= 0 && editorIndex < boxs.size())
			{
				ofFile file(boxs[editorIndex]->getFile());
				file.remove();
				delete boxs[editorIndex];
				boxs.erase(boxs.begin() + editorIndex);

				editorIndex = -1;
			}
		}
		if (ImGui::Button("save"))
		{
			ofxXmlSettings xml;
			for (int i = 0;i < boxs.size();i++)
			{
				boxs[i]->saveSetting();
				xml.addTag("box");
				xml.pushTag("box", i);
				xml.addValue("file", boxs[i]->getFile());
				xml.popTag();
			}
			xml.save(getDir() + "config.xml");
		}
		ImGui::End();
	}
	
}

string boxMgr::getDir()
{
	return "box/";
}

//--------------------------------------------------------------
void boxMgr::keyPressed(int key) {
	for (int i = 0;i < boxs.size();i++)
	{
		if (editorIndex == i)
		{
			boxs[i]->keySetting(key);
		}
	}
}

//--------------------------------------------------------------
void boxMgr::keyReleased(int key) {

}

//--------------------------------------------------------------
void boxMgr::mouseMoved(int x, int y) {
	for (int i = 0; i < boxs.size(); i++)
	{
		if (editorIndex == i)
		{
			boxs[i]->mouseMoved(x, y);
		}
	}
}

//--------------------------------------------------------------
void boxMgr::mouseDragged(int x, int y, int button) {
	for (int i = 0; i < boxs.size(); i++)
	{
		if (editorIndex == i)
		{
			boxs[i]->mouseDragged(x, y);
		}
	}
}

//--------------------------------------------------------------
void boxMgr::mousePressed(int x, int y, int button) {
	for (int i = 0; i < boxs.size(); i++)
	{
		if (editorIndex == i)
		{
			boxs[i]->mousePressed(x, y);
		}
	}
}

//--------------------------------------------------------------
void boxMgr::mouseReleased(int x, int y, int button) {
	for (int i = 0; i < boxs.size(); i++)
	{
		if (editorIndex == i)
		{
			boxs[i]->mouseReleased(x, y);
		}
	}
}
#include "ofMain.h"
#include "ofApp.h"
//#include "../resource.h"
//========================================================================
int main( ){
	ofGLFWWindowSettings  wsettings;
	wsettings.setGLVersion(3, 2);    // <--- ofxShadertoy NEEDS the GL Programmable Renderer
	ofxXmlSettings s;
	ofDisableDataPath();
	s.loadFile("data/settings.xml");
	ofEnableDataPath();
	int w = s.getValue("settings:app:width", 640);
	int h = s.getValue("settings:app:height", 480);
	wsettings.setSize(w, h);
	if (w == 1920) wsettings.decorated = false;
	ofCreateWindow(wsettings);       // <-------- setup the GL context
	//
	//HWND hwnd = ofGetWin32Window();
	//HICON hMyIcon = LoadIconW(hInstance, MAKEINTRESOURCE(MAIN_ICON));
	//SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hMyIcon);
	//
	ofRunApp(new ofApp());

}

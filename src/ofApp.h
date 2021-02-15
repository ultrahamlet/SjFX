#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "..\..\SpoutSDK\SpoutSender.h"
#include <Windows.h>
#include "ofxNetwork.h"


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
		//
		ofVideoGrabber grabber;
		//
		char sendername[256];     // Sender name
		SpoutSender sender;    // Spout sender object
		unsigned int senderwidth;  // Dimensions of the sender can be independent
		unsigned int senderheight; // of the application window if using an fbo
		ofFbo  oFbo;
		ofFbo spFbo;           // For texture send example
		// udp FONT
		ofxUDPManager udpConnectionRx;
		ofxUDPManager udpConnectionTx;

		string rxMessage;
		string txMessage;
		string recvStr;
		string ostr;
		BOOL received;
		ofTrueTypeFont font;
		BOOL flipY;
		
};

#pragma once

#include "ofMain.h"
#include "Particle.h"

class ofApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();
	void resetParticles();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// Code Added
	int x;

	particleMode currentMode;
	string currentModeStr;
	
	vector<Particle> p;
	vector<glm::vec3> attractPoints;
	vector<glm::vec3> attractPointsWithMovement;

	ofRectangle rec = ofRectangle(0, 0, 0, 0);

	vector<string> string1;
	vector<string> string2;
	vector<string> string3;
	vector<string> string4;

	vector<int> keys = {};
	vector<int> timers = {};
	int counter = 0;
	bool replaying = false;
	bool recording = false;
	bool calledFromUpdate = false;
	ofImage recImage;
	ofImage repImage;
	int i = 0;

	bool information = false;
};

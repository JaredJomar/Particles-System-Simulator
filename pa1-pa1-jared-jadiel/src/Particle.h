#pragma once
#include "ofMain.h"

enum particleMode
{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE
};

class Particle
{

public:
	Particle();
	float particle_velocity;

	void setMode(particleMode newMode);
	void setAttractPoints(vector<glm::vec3> *attract);
	void attractToPoint(int, int);
	void repelFromPoint(int, int);
	void reset();
	void update();
	void draw();
	void increase_velocity();
	void decrease_velocity();

	bool getPause() { return pause; }
	void setPause(bool b) { pause = b; }
	bool pause = false;

	glm::vec3 posVec;
	glm::vec3 velVec;
	glm::vec3 frc;
	ofRectangle rec;

	float drag;
	float uniqueVal;
	float scale;
	float scaleSaved;

	particleMode mode;

	vector<glm::vec3> *attractPoints;

	// Code Added
	int counter = 0;
	bool multiColors = false;
	int i = 0;
	vector<ofColor> colors = {ofColor(255, 0, 0), ofColor(0, 255, 0), ofColor(0, 0, 255)};
};

#include "ofApp.h"
#include "Particle.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	//Code Added
	recImage.load("images/Rec.png");
	repImage.load("images/Rep.png");

	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";

	resetParticles();
	//Code Added
	string1.push_back("Fuerza: " + ofToString(glm::vec3(mouseX, mouseY, 0) - p[0].posVec) + "    normalize:" + ofToString(p[0].frc) + "    drag: " + ofToString(p[0].drag));
	string2.push_back("Posicion: " + ofToString(p[0].posVec) + "    posicion + velocidad: " + ofToString(p[0].posVec + p[0].velVec));
	string3.push_back("Velocidad: " + ofToString(p[0].velVec) + "    velocidad * drag: " + ofToString(p[0].velVec * p[0].drag));
	string4.push_back("X: " + ofToString(mouseX) + " Y: " + ofToString(mouseY) + "    velocidad + fuerza(normalizado) * .6: " + ofToString(p[0].velVec + p[0].frc * 0.6));
}

//--------------------------------------------------------------
void ofApp::resetParticles()
{

	// these are the attraction points used in the fourth demo
	attractPoints.clear();
	for (int i = 0; i < 4; i++)
	{
		attractPoints.push_back(glm::vec3(ofMap(i, 0, 4, 100, ofGetWidth() - 100), ofRandom(100, ofGetHeight() - 100), 0));
	}

	attractPointsWithMovement = attractPoints;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);
		p[i].reset();
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	//Code Added
	if (recording || replaying)
	{
		counter++;
	}
	else
	{
		counter = 0;
	}

	if (replaying && !keys.empty() && timers[i] == counter)
	{
		calledFromUpdate = true;
		keyPressed(keys[i]);
		i++;
		if (i >= keys.size())
		{
			replaying = false;
			i = 0;
			counter = 0;
		}
	}

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].update();
	}

	// lets add a bit of movement to the attract points
	for (unsigned int i = 0; i < attractPointsWithMovement.size(); i++)
	{
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}
	//Code Added
	if (string1.size() < 6)
	{
		string1.push_back("Fuerza: " + ofToString(glm::vec3(mouseX, mouseY, 0) - p[0].posVec) + "    normalize:" + ofToString(p[0].frc) + "    drag: " + ofToString(p[0].drag));
		string2.push_back("Posicion: " + ofToString(p[0].posVec) + "    posicion + velocidad: " + ofToString(p[0].posVec + p[0].velVec));
		string3.push_back("Velocidad: " + ofToString(p[0].velVec) + "    velocidad * drag: " + ofToString(p[0].velVec * p[0].drag));
		string4.push_back("X: " + ofToString(mouseX) + " Y: " + ofToString(mouseY) + "    velocidad + fuerza(normalizado) * .6: " + ofToString(p[0].velVec + p[0].frc * 0.6));
	}

	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (rec.inside(p[i].rec))
		{
			p[i].scale = p[i].scaleSaved * 3;
		}
		else
		{
			p[i].scale = p[i].scaleSaved;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].draw();
	}

	ofSetColor(190);
	if (currentMode == PARTICLE_MODE_NEAREST_POINTS)
	{
		for (unsigned int i = 0; i < attractPoints.size(); i++)
		{
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
	//Code Added
	if (information)
	{
		ofDrawBitmapString("Informacion de una particula en 6 iteraciones corridas", 10, 130);
		for (int i = 0; i < string1.size(); i++)
		{
			ofDrawBitmapString(string1[i], 10, 150 + i * 100);
			ofDrawBitmapString(string2[i], 10, 170 + i * 100);
			ofDrawBitmapString(string3[i], 10, 190 + i * 100);
			ofDrawBitmapString(string4[i], 10, 210 + i * 100);
		}
	}

	ofNoFill();
	ofDrawRectangle(rec.x, rec.y, rec.width, rec.height);

	if (recording)
		recImage.draw(ofGetWidth() - 100, 10, 90, 90);
	if (replaying)
		repImage.draw(ofGetWidth() - 100, 10, 90, 90);
	ofDrawBitmapString(ofToString(keys), 400, 10);
	ofDrawBitmapString(ofToString(timers), 400, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	//Code Added
	if (key == 'c')	// Cancel replay
	{
		replaying = false;
		i = 0;
		counter = 0;
	}

	if (!calledFromUpdate && replaying)
		return;
	calledFromUpdate = false;

	if (recording && key != 'r' && key != 'o')
	{
		keys.push_back(key);
		timers.push_back(counter);
	}

	if (key == '1')
	{
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
	}
	if (key == '2')
	{
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
	}
	if (key == '3')
	{
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:";
	}
	if (key == '4')
	{
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
	}

	if (key == ' ')
	{
		resetParticles();
	}

	if (key == 'i')
	{
		information = !information;
		string1.clear();
		string2.clear();
		string3.clear();
		string4.clear();
	}
	//Code Added
	if (key == 's')	// Pause
	{
		for (int i = 0; i < p.size(); i++)
		{
			p[i].setPause(!p[i].getPause());
		}
	}

	if (key == 'd')	// Increase speed
	{
		for (int i = 0; i < p.size(); i++)
		{
			p[i].increase_velocity();
		}
	}

	if (key == 'a')	// Decrease speed
	{
		for (int i = 0; i < p.size(); i++)
		{
			p[i].decrease_velocity();
		}
	}

	if (key == 't')	// Change colors
	{
		for (int i = 0; i < p.size(); i++)
		{
			p[i].multiColors = !p[i].multiColors;
		}
	}

	if (key == 'r')	// Record
	{
		if (recording == false)
		{
			keys.clear();
			timers.clear();
		}
		recording = !recording;
	}

	if (key == 'p')	// Replay
	{
		replaying = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	//Code Added
	if (button == 0)
	{
		rec.setWidth(x - rec.getX());
		rec.setHeight(y - rec.getY());
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	//Code Added
	if (button == 0)
	{
		rec.setX(x);
		rec.setY(y);
		rec.setWidth(0);
		rec.setHeight(0);
	}

	if (x >= rec.x && x <= rec.x + rec.width && y >= rec.y && y <= rec.y + rec.height && button == 2)
	{
		rec.setX(0);
		rec.setY(0);
		rec.setWidth(0);
		rec.setHeight(0);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

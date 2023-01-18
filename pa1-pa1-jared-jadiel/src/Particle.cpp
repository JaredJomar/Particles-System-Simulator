#include "Particle.h"

//------------------------------------------------------------------
Particle::Particle()
{
	attractPoints = NULL;
}

//------------------------------------------------------------------
void Particle::setMode(particleMode newMode)
{
	mode = newMode;
}

//------------------------------------------------------------------
void Particle::setAttractPoints(vector<glm::vec3> *attract)
{
	attractPoints = attract;
}

//------------------------------------------------------------------
void Particle::reset()
{
	// the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);

	posVec.x = ofRandomWidth();
	posVec.y = ofRandomHeight();
	posVec.z = 0;

	velVec.x = ofRandom(-3.9, 3.9);
	velVec.y = ofRandom(-3.9, 3.9);
	velVec.z = 0;

	frc = glm::vec3(0, 0, 0);

	scale = ofRandom(0.5, 1.0);
	scaleSaved = scale; // Code added

	if (mode == PARTICLE_MODE_NOISE)
	{
		drag = ofRandom(0.97, 0.99);
		velVec.y = fabs(velVec.y) * 3.0; // make the particles all be going down
	}
	else
	{
		drag = ofRandom(0.95, 0.998);
	}

	// Code Added
	particle_velocity = 1.0;
}

void Particle::attractToPoint(int x, int y)
{
	glm::vec3 attractPt(x, y, 0);
	frc = attractPt - posVec;  // we get the attraction force/vector by looking at the mouse pos relative to our pos
	frc = glm::normalize(frc); // by normalizing we disregard how close the particle is to the attraction point

	velVec *= drag;		 // apply drag
	velVec += frc * 0.6; // apply force
}

void Particle::repelFromPoint(int x, int y)
{
	glm::vec3 attractPt(x, y, 0);
	frc = attractPt - posVec;

	// let get the distance and only repel points close to the mouse
	float dist = glm::length(frc);
	frc = glm::normalize(frc);

	velVec *= drag;
	if (dist < 150)
	{
		velVec += -frc * 0.6; // notice the frc is negative
	}
	else
	{
		// if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
		frc.x = ofSignedNoise(uniqueVal, posVec.y * 0.01, ofGetElapsedTimef() * 0.2);
		frc.y = ofSignedNoise(uniqueVal, posVec.x * 0.01, ofGetElapsedTimef() * 0.2);
		velVec += frc * 0.04;
	}
}
//------------------------------------------------------------------
void Particle::update()
{
	// Code Added
	rec.setX(posVec.x);
	rec.setY(posVec.y);

	if (multiColors)
		counter++;
	if (counter == 60)
	{
		counter = 0;
		if (i < 2)
			i++;
		else
		{
			i = 0;
		}
	}
	// APPLY THE FORCES BASED ON WHICH MODE WE ARE IN

	if (mode == PARTICLE_MODE_ATTRACT)
	{
		attractToPoint(ofGetMouseX(), ofGetMouseY());
	}
	else if (mode == PARTICLE_MODE_REPEL)
	{
		repelFromPoint(ofGetMouseX(), ofGetMouseY());
	}
	else if (mode == PARTICLE_MODE_NOISE)
	{
		// lets simulate falling snow
		// the fake wind is meant to add a shift to the particles based on where in x they are
		// we add pos.y as an arg so to prevent obvious vertical banding around x values - try removing the pos.y * 0.006 to see the banding
		float fakeWindX = ofSignedNoise(posVec.x * 0.003, posVec.y * 0.006, ofGetElapsedTimef() * 0.6);

		frc.x = fakeWindX * 0.25 + ofSignedNoise(uniqueVal, posVec.y * 0.04) * 0.6;
		frc.y = ofSignedNoise(uniqueVal, posVec.x * 0.006, ofGetElapsedTimef() * 0.2) * 0.09 + 0.18;

		velVec *= drag;
		velVec += frc * 0.4;

		// we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
		if (posVec.y + velVec.y > ofGetHeight())
		{
			posVec.y -= ofGetHeight();
		}
	}
	else if (mode == PARTICLE_MODE_NEAREST_POINTS)
	{

		if (attractPoints)
		{

			// find closest attractPoint
			glm::vec3 closestPt;
			int closest = -1;
			float closestDist = 9999999;

			for (unsigned int i = 0; i < attractPoints->size(); i++)
			{
				float lenSq = glm::length2(attractPoints->at(i) - posVec);
				if (lenSq < closestDist)
				{
					closestDist = lenSq;
					closest = i;
				}
			}

			// if we have a closest point - lets calcuate the force towards it
			if (closest != -1)
			{
				closestPt = attractPoints->at(closest);
				float dist = sqrt(closestDist);

				// in this case we don't normalize as we want to have the force proportional to distance
				attractToPoint(closestPt.x, closestPt.y);

				// lets also limit our attraction to a certain distance and don't apply if 'f' key is pressed
				if (dist < 300 && dist > 40 && !ofGetKeyPressed('f'))
				{
					velVec += frc * 0.003;
				}
				else
				{
					// if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
					frc.x = ofSignedNoise(uniqueVal, posVec.y * 0.01, ofGetElapsedTimef() * 0.2);
					frc.y = ofSignedNoise(uniqueVal, posVec.x * 0.01, ofGetElapsedTimef() * 0.2);
					velVec += frc * 0.4;
				}
			}
		}
	}

	// UPDATE OUR POSITION

	if (!pause)
		posVec += velVec * particle_velocity;

	// LIMIT THE PARTICLES TO STAY ON SCREEN
	// we could also pass in bounds to check - or alternatively do this at the ofApp level
	if (posVec.x > ofGetWidth())
	{
		posVec.x = ofGetWidth();
		velVec.x *= -1.0;
	}
	else if (posVec.x < 0)
	{
		posVec.x = 0;
		velVec.x *= -1.0;
	}
	if (posVec.y > ofGetHeight())
	{
		posVec.y = ofGetHeight();
		velVec.y *= -1.0;
	}
	else if (posVec.y < 0)
	{
		posVec.y = 0;
		velVec.y *= -1.0;
	}
}

//------------------------------------------------------------------
void Particle::draw()
{
	// Code Added
	ofFill();
	if (multiColors)
	{
		ofSetColor(colors[i]);
	}
	else if (mode == PARTICLE_MODE_ATTRACT)
	{
		ofSetColor(255, 63, 180);
	}
	else if (mode == PARTICLE_MODE_REPEL)
	{
		ofSetColor(208, 255, 63);
	}
	else if (mode == PARTICLE_MODE_NOISE)
	{
		ofSetColor(99, 63, 255);
	}
	else if (mode == PARTICLE_MODE_NEAREST_POINTS)
	{
		ofSetColor(103, 160, 237);
	}

	ofDrawCircle(posVec.x, posVec.y, scale * 4.0);
}

//------------------------------------------------------------------
void Particle::increase_velocity()
{
	particle_velocity *= 2;
}
void Particle::decrease_velocity()
{
	particle_velocity /= 2;
}
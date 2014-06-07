//
//  Particle.cpp
//  mySketch0607
//
//  Created by 入江信之介 on 2014/06/07.
//
//

#include "Particle.h"

//----------------------------------------------------------------------------------
void Particle::setup(ofVec3f _position, ofVec3f _velocity){
    position = _position;
    velocity = _velocity;
    
}
//----------------------------------------------------------------------------------
void Particle::draw(){
    ofSetColor(0, 150, 200 + ofRandom(50), 250);
    ofCircle(position, radius);
}
//----------------------------------------------------------------------------------
void Particle::addForce(ofVec3f _force){
    force = _force;
    
}
//----------------------------------------------------------------------------------
void Particle::resetForce(){
    force.set(0, 0, 0);
}
//----------------------------------------------------------------------------------
void Particle::updateForce(){
    force -= velocity * friction;
}
//----------------------------------------------------------------------------------
void Particle::updatePos(){
    velocity += force;
    position += velocity;
}

//----------------------------------------------------------------------------------
void Particle::checkBounds(float xmin, float ymin, float xmax, float ymax){
    if (position.x < xmin || position.x > xmax ) {
        velocity.x *= -1;
    }
    if (position.y < ymin || position.y > ymax) {
        velocity.y *= -1;
    }
    
    if (position.x < xmin) {
        position.x = xmin + (xmin - position.x);
    }
    if (position.y < ymin) {
        position.y = ymin + (ymin - position.y);
    }
    if (position.x > xmax) {
        position.x = xmax - (xmax - position.x);
    }
    if (position.y < ymax) {
        position.y = ymax - (ymax - position.y);
    }
}
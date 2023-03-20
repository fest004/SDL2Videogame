#include "../include/MyContactListener.h"
#include <iostream>

void MyContactListener::BeginContact(b2Contact *contact) {
  // << " and body " << bodyB->GetUserData() << std::endl;
  std::cout << "Collison Started" << std::endl;
  // Get the two bodies that collided
  // b2Fixture *fixtureA = contact->GetFixtureA();
  // b2Fixture *fixtureB = contact->GetFixtureB();
  // b2Body *bodyA = fixtureA->GetBody();
  // b2Body *bodyB = fixtureB->GetBody();
  //
  // Print a message to indicate the collision
  // std::cout << "Collision started between body " << bodyA->GetUserData()
  // << " and body " << bodyB->GetUserData() << std::endl;
}

void MyContactListener::EndContact(b2Contact *contact) {
  // Get the two bodies that stopped colliding
  // b2Fixture *fixtureA = contact->GetFixtureA();
  // b2Fixture *fixtureB = contact->GetFixtureB();
  // b2Body *bodyA = fixtureA->GetBody();
  // b2Body *bodyB = fixtureB->GetBody();
  //
  // Print a message to indicate the end of the collision
  // std::cout << "Collision ended between body " << bodyA->GetUserData()
  // << "
  // and body " << bodyB->GetUserData() << std::endl;
  std::cout << "Collison Ended" << std::endl;
};

#ifndef MY_CONTACT_LISTENER_H
#define MY_CONTACT_LISTENER_H

#include "box2d/box2d.h"

class MyContactListener : public b2ContactListener {
public:
  virtual void BeginContact(b2Contact *contact) override;
  virtual void EndContact(b2Contact *contact) override;
};

#endif

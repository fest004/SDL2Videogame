#ifndef GLOBALS_H
#define GLOBALS_H

#include "MyContactListener.h"
#include "box2d/box2d.h"

extern b2World boxworld;
extern MyContactListener *contactListener;

void initBox();

#endif

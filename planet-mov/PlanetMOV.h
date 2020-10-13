#ifndef _PLANET_MOV_H
#define _PLANET_MOV_H

#include "cinder/Cinder.h"
#include "cinder/app/App.h"
#include "cinder/Camera.h"
#include "cinder/gl/Fbo.h"

#include <cstdio>
#include <chrono>

#include "TimeControl.h"
#include "CameraControl.h"
#include "PlanetSystem.h"


class PlanetMOV : public cinder::app::App
{
private:
    void setup() override;
    void cleanup() override;

    void keyDown(ci::app::KeyEvent event) override;
    void mouseDown(ci::app::MouseEvent event) override;
    void mouseDrag(ci::app::MouseEvent event) override;
    void mouseWheel(ci::app::MouseEvent event) override;

    void update() override;
    void draw() override;
    void drawUI();

public: // Gui
    void DrawGui();

    bool _toolsOpen = false;
};

#endif // _PLANET_MOV_H

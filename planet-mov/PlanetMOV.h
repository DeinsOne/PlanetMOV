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
#include "Error.h"

#include "cinder/CinderImGui.h"


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
    void setupGui();
    void drawGui();

    void drawTools();
    void drawButtons();
    void drawErrors();


    ImFont*     _fontDefault;
    ImFont*     _fontMain12;
    ImFont*     _fontMain14;
    ImFont*     _fontMainBold14;
    ImFont*     _fontSymbols;

    bool        _toolsWindowOpen = false;
    bool        _errorsWindowOpen = false;

    float       _toolsXSize = 275;
};

#endif // _PLANET_MOV_H

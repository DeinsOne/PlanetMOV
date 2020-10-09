#ifndef _PLANET_MOV_H
#define _PLANET_MOV_H

#include "cinder/Cinder.h"
#include "cinder/app/App.h"
#include "cinder/Camera.h"

#include <cstdio>
#include <chrono>


class PlanetMOV : public cinder::app::App {
    private :
        void setup() override;

        void keyDown(ci::app::KeyEvent event) override;
        void mouseDown(ci::app::MouseEvent event) override;
        void mouseDrag(ci::app::MouseEvent event) override;
        void mouseWheel(ci::app::MouseEvent event) override;

        void update() override;
        void draw() override;
        void drawUI();

    private :   // Hard logic
        glm::ivec2 _latMousePos;
        bool _setedPos = false;

        std::chrono::_V2::system_clock::time_point _nowTime = std::chrono::high_resolution_clock::now();


    public :    // Camera params
        glm::vec2 _cameraPos = {0, 0};
        ci::CameraOrtho _camera;
        float _zoom = 16;

    public :    // Time control
        bool _playTime = false;

        float _elapsedTime = 0.0;
        float _deltaTime = 0.0;



    public :    // Gui
        void DrawGui();

};




#endif // _PLANET_MOV_H

#include "PlanetMOV.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/CinderImGui.h"

#include <chrono>
#include <pthread.h>


void PlanetMOV::update() {
    _deltaTime = (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _nowTime ).count() / 1000.0; 
    _nowTime = std::chrono::system_clock::now();
    if (_playTime ) _elapsedTime += _deltaTime;


    _camera.setOrtho(getWindowWidth()/_zoom, 0, 0, getWindowHeight()/_zoom, 0.1, 500 );
    _camera.lookAt({_cameraPos.x,_cameraPos.y,0});
    _camera.setEyePoint({_cameraPos.x,_cameraPos.y,30});

}



void PlanetMOV::draw() {
    ci::gl::clear(ci::Color::hex(0x313131) );
    ci::gl::setMatrices(_camera );

    DrawGui();

}





// Keyboard
void PlanetMOV::keyDown(ci::app::KeyEvent event ) {
    if(event.getCode() == ci::app::KeyEvent::KEY_ESCAPE ) quit();
}

// Preparing for mouse movement
void PlanetMOV::mouseDown(ci::app::MouseEvent event ) {

}

// Movement
void PlanetMOV::mouseDrag(ci::app::MouseEvent event ) {

}

// Add zoom
void PlanetMOV::mouseWheel(ci::app::MouseEvent event ) {

}


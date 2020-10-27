#include "PlanetMOV.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/CinderImGui.h"

#include <chrono>
#include <pthread.h>


void PlanetMOV::update() {
    TimeControl::Get().updateTimeControl();

    CameraControl::Get().update();

    PlanetSystem::Get().update();

    if (TimeControl::Get()._play ) {
        PlanetSystem::Get().eventOnUpdate();
    }

}



void PlanetMOV::draw() {
    ci::gl::clear(ci::Color::hex(0x313131) );
    ci::gl::setMatrices(CameraControl::Get()._camera );

    DrawGui();


    PlanetSystem::Get().eventOnRender();
    PlanetSystem::Get().draw();

}





// Keyboard
void PlanetMOV::keyDown(ci::app::KeyEvent event ) {
    if(event.getCode() == ci::app::KeyEvent::KEY_ESCAPE ) quit();
}

void PlanetMOV::mouseDown(ci::app::MouseEvent event ) {
    CameraControl::Get().onMouseDown(event );

    PlanetSystem::Get().onMouseDown(event );
}

// Movement
void PlanetMOV::mouseDrag(ci::app::MouseEvent event ) {
    CameraControl::Get().onMouseDrag(event );
}

// Camera zoom
void PlanetMOV::mouseWheel(ci::app::MouseEvent event ) {
    CameraControl::Get().onMouseWheel(event );
}

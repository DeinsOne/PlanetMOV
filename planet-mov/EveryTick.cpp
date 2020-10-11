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


    _camera.setOrtho(getWindowWidth()/_zoom, -getWindowWidth()/_zoom, -getWindowHeight()/_zoom, getWindowHeight()/_zoom, 0.1, 500 ); // _camera.setOrtho(getWindowWidth()/_zoom, 0, 0, getWindowHeight()/_zoom, 0.1, 500 );
    _camera.lookAt({_cameraPos.x,_cameraPos.y,0});
    _camera.setEyePoint({_cameraPos.x,_cameraPos.y,30});

}



void PlanetMOV::draw() {
    ci::gl::clear(ci::Color::hex(0x313131) );
    ci::gl::setMatrices(_camera );

    DrawGui();

    for (auto planet : _planets ) {
        if (_selectedPlanet == planet.first ) {
            ci::gl::color(ci::Color::hex(_colorOfBorder ) );
            ci::gl::drawSolidCircle(planet.second->_pos, planet.second->_size + _radiusOfBorder, planet.second->_size*12 );
        }

        ci::gl::color(ci::Color::hex(0xeeeeee) );
        ci::gl::drawSolidCircle(planet.second->_pos, planet.second->_size, planet.second->_size*12 );
    }


}





// Keyboard
void PlanetMOV::keyDown(ci::app::KeyEvent event ) {
    if(event.getCode() == ci::app::KeyEvent::KEY_ESCAPE ) quit();
}

void PlanetMOV::mouseDown(ci::app::MouseEvent event ) {
    _setedPos = false;

    // FIXME: Update selected planet
    ci::Ray _ray = _camera.generateRay(event.getPos(), ci::app::getWindow()->getSize() );
    _ray.transform(
        glm::translate(glm::mat4(1.0), _camera.getEyePoint() )
    );


    glm::vec3 _rayOrigin = _ray.getOrigin();
    // printf("Origin  x : %f | y : %f\n", _rayOrigin.x, _rayOrigin.y );
    for (auto planet : _planets ) {
        if (glm::distance2(planet.second->_pos, glm::vec2(_rayOrigin.x, _rayOrigin.y) ) <= (2*planet.second->_size) ) {
            _selectedPlanet = planet.first;
            return;
        }
    }
    _selectedPlanet = "";


}

// Movement
void PlanetMOV::mouseDrag(ci::app::MouseEvent event ) {
    if (event.isLeftDown() ) return;

    static float sensitivity = ci::clamp((_zoom - _minZValue)/(_maxZValue - _minZValue), _minZAccelSpeed, 0.9f );
    if (_setedPos == false ) { _latMousePos = event.getPos(); _setedPos = true; }
    glm::vec2 delta = glm::vec2(((float)_latMousePos.x - (float)event.getPos().x)*sensitivity, ((float)_latMousePos.y - (float)event.getPos().y)*sensitivity );

    _cameraPos -= delta;
    _latMousePos = event.getPos();
}

// Camera zoom
void PlanetMOV::mouseWheel(ci::app::MouseEvent event ) {
    static float sensitivity = 0.6;
    _zoom -= event.getWheelIncrement()/sensitivity;

    _zoom = ci::clamp(_zoom, _minZValue, _maxZValue);
}

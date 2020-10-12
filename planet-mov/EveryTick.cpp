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


    _planetPicker.reset();
    _planetPicker = ci::gl::Fbo::create(ci::app::getWindow()->getSize().x, ci::app::getWindow()->getSize().y );
}



void PlanetMOV::draw() {
    ci::gl::clear(ci::Color::hex(0x313131) );
    ci::gl::setMatrices(_camera );

    DrawGui();

    for (auto planet : _planets ) {
        ci::gl::setModelMatrix(ci::translate(glm::vec3(planet.second->_pos, 0.0)) );

        if (_selectedPlanet == planet.first ) {
            ci::gl::getStockShader(ci::gl::ShaderDef().color() )->bind();
            ci::gl::color(ci::Color::hex(_colorOfBorder ) );
            ci::gl::drawSolidCircle({}, planet.second->_size + _radiusOfBorder, planet.second->_size*12 );
        }

        if (planet.second->_shader) planet.second->BindShader(_elapsedTime, _deltaTime );
        else ci::gl::color(ci::Color::hex(0xeeeeee) );
        ci::gl::drawSolidCircle({}, planet.second->_size, planet.second->_size*12 );
    }




    // Draw separeate fbo to give possibility planet picking 
    _planetPicker->bindFramebuffer();
        ci::gl::clear(ci::Color::hex(0x0000));
        ci::gl::setMatrices(_camera );

        auto planet = _planets.begin();
        for (int i = 0; i < _planets.size(); i++ ) {
            ci::gl::setModelMatrix(ci::translate(glm::vec3(planet->second->_pos, 0.0)) );

            ci::gl::getStockShader(ci::gl::ShaderDef().color() )->bind();
            ci::gl::color(0, ((float)(i+1))/((float)_planets.size()) ,0,1);
            ci::gl::drawSolidCircle({}, planet->second->_size, planet->second->_size*12 );
            planet++;
        }

    _planetPicker->unbindFramebuffer();

}





// Keyboard
void PlanetMOV::keyDown(ci::app::KeyEvent event ) {
    if(event.getCode() == ci::app::KeyEvent::KEY_ESCAPE ) quit();
}

void PlanetMOV::mouseDown(ci::app::MouseEvent event ) {
    _setedPos = false;


    if (event.isLeft() ) {
        ci::Surface32f pixel = _planetPicker->readPixels32f(ci::Area(0,0, _planetPicker->getSize().x, _planetPicker->getSize().y ), GL_COLOR_ATTACHMENT0 );
    
        if (pixel.getPixel(event.getPos() ).a != 0 ) {
            float _greenPx = pixel.getPixel(event.getPos() ).g;
    
            auto planet = _planets.begin();
            for (int i = 0; i < _planets.size(); i++ ) {
                float _objCl = ((float)(i+1))/((float)_planets.size());
    
                if (fabs(_objCl - _greenPx) <= 0.01 )
                    _selectedPlanet = planet->first;
    
                planet++;
            }
        }
        else _selectedPlanet = "";
    }

}

// Movement
void PlanetMOV::mouseDrag(ci::app::MouseEvent event ) {
    if (event.isLeftDown() ) return;

    static const float _as = 400; // Index of sensitivity
    static float sensitivity = (1.0f - ci::clamp((_zoom - _minZValue)/(_maxZValue - _minZValue), _minZAccelSpeed, 0.9f )) * _deltaTime * _as;
    if (_setedPos == false ) { _latMousePos = event.getPos(); _setedPos = true; }
    glm::vec2 delta = glm::vec2(((float)_latMousePos.x - (float)event.getPos().x)*sensitivity, ((float)_latMousePos.y - (float)event.getPos().y)*sensitivity );

    _cameraPos -= delta*_deltaTime;
    _latMousePos = event.getPos();
}

// Camera zoom
void PlanetMOV::mouseWheel(ci::app::MouseEvent event ) {
    static float sensitivity = 0.6;
    _zoom -= event.getWheelIncrement()/sensitivity;

    _zoom = ci::clamp(_zoom, _minZValue, _maxZValue);
}

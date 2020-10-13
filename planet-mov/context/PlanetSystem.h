#ifndef _PLANET_MOV_PLANET_SYSTEM_H
#define _PLANET_MOV_PLANET_SYSTEM_H

#include <string>
#include <cinder/gl/GlslProg.h>

#include <cinder/app/App.h>
#include <cinder/gl/Fbo.h>

class Planet {
    public :
        glm::vec2               _pos;
        float                   _size;

        Planet(glm::vec2 pos, float size);

        std::string             _pathToFragmentShader;
        std::string             _fragmentShaderText;
        ci::gl::GlslProgRef     _shader;

        void BindShader(float elapsedTime, float deltaTime );


};


class PlanetSystem {
    private :
        PlanetSystem() { }

        ci::gl::FboRef _planetPicker;

        int _colorOfBorder = 0xff463c;
        float _radiusOfBorder = 0.2;

    public :
        static PlanetSystem& Get() { static PlanetSystem pl; return pl; }

        void loadPlanetsConfig(std::string _file);

        void update();
        void draw();

        void onMouseDown(ci::app::MouseEvent event );

        void destroy();

        std::shared_ptr<Planet> getSelectedPlanet() {
            return _planets.at(_selectedPlanet);
        }

        std::map<std::string, std::shared_ptr<Planet> >  _planets;
        std::string _selectedPlanet;


};



#endif // _PLANET_MOV_PLANET_SYSTEM_H
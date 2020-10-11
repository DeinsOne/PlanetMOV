#include "PlanetSystem.h"
#include <cinder/gl/gl.h>
#include <cinder/gl/Batch.h>

Planet::Planet(glm::vec2 pos, float size) : _pos(pos), _size(size) {

}

void Planet::BindShader(float elapsedTime, float deltaTime ) {
    _shader->bind();

    _shader->uniform("elapsedTime", elapsedTime );
    _shader->uniform("deltaTime", deltaTime );

}
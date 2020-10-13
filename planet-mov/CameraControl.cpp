#include <cinder/app/App.h>
#include "CameraControl.h"

void CameraControl::update()
{
    _camera.setOrtho(ci::app::getWindowWidth() / _zoom, -ci::app::getWindowWidth() / _zoom, -ci::app::getWindowHeight() / _zoom, ci::app::getWindowHeight() / _zoom, 0.1, 500);
    _camera.lookAt({_cameraPos.x, _cameraPos.y, 0});
    _camera.setEyePoint({_cameraPos.x, _cameraPos.y, 30});
}

void CameraControl::onMouseDrag(ci::app::MouseEvent event)
{
    if (event.isLeftDown())
        return;

    static const float _as = 400; // Index of sensitivity
    static float sensitivity = (1.0f - ci::clamp((_zoom - _minZValue) / (_maxZValue - _minZValue), _minZAccelSpeed, 0.9f)) * TimeControl::Get().getDeltaTime() * _as;
    if (_setedPos == false)
    {
        _latMousePos = event.getPos();
        _setedPos = true;
    }
    glm::vec2 delta = glm::vec2(((float)_latMousePos.x - (float)event.getPos().x) * sensitivity, ((float)_latMousePos.y - (float)event.getPos().y) * sensitivity);

    _cameraPos -= delta * TimeControl::Get().getDeltaTime();
    _latMousePos = event.getPos();
}

void CameraControl::onMouseWheel(ci::app::MouseEvent event)
{
    static float sensitivity = 0.6;
    _zoom -= event.getWheelIncrement() / sensitivity;

    _zoom = ci::clamp(_zoom, _minZValue, _maxZValue);
}

void CameraControl::onMouseDown(ci::app::MouseEvent event)
{
    _setedPos = false;
}

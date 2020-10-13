#ifndef _PLANET_MOV_CAMERA_CONTROL_H
#define _PLANET_MOV_CAMERA_CONTROL_H


#include <cinder/Camera.h>

#include "TimeControl.h"


class CameraControl {
    private :
        float _zoom = 24.0; 

        const float _maxZValue = 64.0;
        const float _minZValue = 18.0;

        const float _minZAccelSpeed = 0.01;

        glm::ivec2 _latMousePos;
        bool _setedPos = false;

        CameraControl() {  }

    public :
        static CameraControl& Get() { static CameraControl c; return c; }

        void update();


        void onMouseDrag(ci::app::MouseEvent event );
        void onMouseWheel(ci::app::MouseEvent event );
        void onMouseDown(ci::app::MouseEvent event );

    public :
        glm::vec2 _cameraPos = {0, 0};
        ci::CameraOrtho _camera;


};

#endif // _PLANET_MOV_CAMERA_CONTROL_H

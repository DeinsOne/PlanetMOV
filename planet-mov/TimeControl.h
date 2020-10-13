#ifndef _PLANET_MOV_TIME_CONTROL_H
#define _PLANET_MOV_TIME_CONTROL_H

#include <chrono>

class TimeControl
{
private:
    TimeControl() {}

    float _deltaTime = 0.0;

public:
    bool _play = false;

    float _elapsedTime = 0.0;
    std::chrono::_V2::system_clock::time_point _time = std::chrono::high_resolution_clock::now();

public:
    static TimeControl &Get()
    {
        static TimeControl t;
        return t;
    }

    float getDeltaTime() { return _deltaTime; }
    void initTimeControl() {}

    void updateTimeControl()
    {
        _deltaTime = (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _time).count() / 1000.0;
        _time = std::chrono::system_clock::now();
        if (_play)
            _elapsedTime += _deltaTime;
    }
};

#endif // _PLANET_MOV_TIME_CONTROL_H

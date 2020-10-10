#ifndef _PLANET_MOV_PLANET_SYSTEM_H
#define _PLANET_MOV_PLANET_SYSTEM_H


class Planet {
    public :
        glm::vec2       _pos;
        float           _size;

        Planet(glm::vec2 pos, float size) { _pos = pos; _size = size; }
};



#endif // _PLANET_MOV_PLANET_SYSTEM_H
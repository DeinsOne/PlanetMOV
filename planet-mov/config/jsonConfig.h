#ifndef _PLANET_MOV_JSON_CONFIG_H
#define _PLANET_MOV_JSON_CONFIG_H

#include "json/json.h"
#include <typeinfo>

#include "cinder/gl/gl.h"

namespace Json {
    /* Conversion to simple values */

    // Boolean
    bool            getValueExtracted(Json::Value& source, bool defaultValue );            

    // Intager
    int             getValueExtracted(Json::Value& source, int defaultValue );

    // Float
    float           getValueExtracted(Json::Value& source, float defaultValue );

    // Double
    // double          getValueExtracted(Json::Value& source, double defaultValue );


    /* Conversion to array values */

    // CString
    const char*     getValueExtracted(Json::Value& source, const char* defaultValue );

    // String
    std::string     getValueExtracted(Json::Value& source, std::string defaultValue );


    /* Vectors */

    // glm::vec2
    glm::vec2       getValueExtracted(Json::Value& source, glm::vec2 defaultValue );

    // glm::vec3
    glm::vec3       getValueExtracted(Json::Value& source, glm::vec3 defaultValue );

    // glm::vec4
    glm::vec4       getValueExtracted(Json::Value& source, glm::vec4 defaultValue );




    

}





#endif // _PLANET_MOV_JSON_CONFIG_H



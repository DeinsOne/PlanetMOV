#ifndef _PLANET_MOV_JSON_CONFIG_H
#define _PLANET_MOV_JSON_CONFIG_H

#include "jsoncpp/json.h"
#include "labels.h"

#include "cinder/gl/gl.h"
#include <typeinfo>

namespace Json {
    /* Conversion to simple values */

    // Boolean
    bool            getValueExtracted(Json::Value& source, bool defaultValue = false );            

    // Intager
    int             getValueExtracted(Json::Value& source, int defaultValue = 0 );

    // Float
    float           getValueExtracted(Json::Value& source, float defaultValue = 0.0f );

    // Double
    double          getValueExtracted(Json::Value& source, double defaultValue = 0.0 );


    /* Conversion to array values */

    // CString
    const char*     getValueExtracted(Json::Value& source, const char* defaultValue = "" );

    // String
    std::string     getValueExtracted(Json::Value& source, std::string defaultValue = "" );


    /* Vectors */

    // glm::vec2
    glm::vec2       getValueExtracted(Json::Value& source, glm::vec2 defaultValue = {0,0} );

    // glm::vec3
    glm::vec3       getValueExtracted(Json::Value& source, glm::vec3 defaultValue = {0,0,0} );

    // glm::vec4
    glm::vec4       getValueExtracted(Json::Value& source, glm::vec4 defaultValue = {0,0,0,0} );






    /* Getting valuse by label */

    // Boolean
    bool            getValueByLabel(Json::Value& source, Labels_ label, bool defaultValue = false );            

    // Intager
    int             getValueByLabel(Json::Value& source, Labels_ label, int defaultValue = 0 );

    // Float
    float           getValueByLabel(Json::Value& source, Labels_ label, float defaultValue = 0.0f );

    // Double
    double          getValueByLabel(Json::Value& source, Labels_ label, double defaultValue = 0.0 );


    /* Conversion to array values */

    // CString
    const char*     getValueByLabel(Json::Value& source, Labels_ label, const char* defaultValue = "" );

    // String
    std::string     getValueByLabel(Json::Value& source, Labels_ label, std::string defaultValue = "" );


    /* Vectors */

    // glm::vec2
    glm::vec2       getValueByLabel(Json::Value& source, Labels_ label, glm::vec2 defaultValue = {0,0} );

    // glm::vec3
    glm::vec3       getValueByLabel(Json::Value& source, Labels_ label, glm::vec3 defaultValue = {0,0,0} );

    // glm::vec4
    glm::vec4       getValueByLabel(Json::Value& source, Labels_ label, glm::vec4 defaultValue = {0,0,0,0} );






    /* Getting valuse by str */

    // Boolean
    bool            getValueByStr(Json::Value& source, const char* label, bool defaultValue = false );            

    // Intager
    int             getValueByStr(Json::Value& source, const char* label, int defaultValue = 0 );

    // Float
    float           getValueByStr(Json::Value& source, const char* label, float defaultValue = 0.0f );

    // Double
    double          getValueByStr(Json::Value& source, const char* label, double defaultValue = 0.0 );


    /* Conversion to array values */

    // CString
    const char*     getValueByStr(Json::Value& source, const char* label, const char* defaultValue = "" );

    // String
    std::string     getValueByStr(Json::Value& source, const char* label, std::string defaultValue = "" );


    /* Vectors */

    // glm::vec2
    glm::vec2       getValueByStr(Json::Value& source, const char* label, glm::vec2 defaultValue = {0,0} );

    // glm::vec3
    glm::vec3       getValueByStr(Json::Value& source, const char* label, glm::vec3 defaultValue = {0,0,0} );

    // glm::vec4
    glm::vec4       getValueByStr(Json::Value& source, const char* label, glm::vec4 defaultValue = {0,0,0,0} );
}





#endif // _PLANET_MOV_JSON_CONFIG_H



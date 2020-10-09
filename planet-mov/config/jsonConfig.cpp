#include "jsonConfig.h"

    // Boolean
    bool Json::getValueExtracted(Json::Value& source, bool defaultValue )  {
        if (source.empty() || source.isArray() ) return defaultValue;

        try {
            bool returnValue = source.asBool();
            return returnValue;
        }
        catch (...) { }

        return defaultValue;
    }


    // Intager
    int Json::getValueExtracted(Json::Value& source, int defaultValue )  {
        if (source.empty() || source.isArray() ) return defaultValue;

        try {
            int returnValue = source.asInt();
            return returnValue;
        }
        catch (...) { }

        return defaultValue;
    }


    // Float
    float Json::getValueExtracted(Json::Value& source, float defaultValue )  {
        if (source.empty() || source.isArray() ) return defaultValue;

        try {
            float returnValue = source.asFloat();
            return returnValue;
        }
        catch (...) { }

        return defaultValue;
    }


    // Double
    // float Json::getValueExtracted(Json::Value& source, double defaultValue ) {
    //     if (source.empty() || source.isArray() ) return defaultValue;

    //     try {
    //         double returnValue = source.asDouble();
    //         return returnValue;
    //     }
    //     catch (...) { }

    //     return defaultValue;
    // }


    // CString
    const char* Json::getValueExtracted(Json::Value& source, const char* defaultValue )  {
        if (source.empty() || source.isArray() ) return defaultValue;

        try {
            const char* returnValue = source.asCString();
            return returnValue;
        }
        catch (...) { }

        return defaultValue;
    }


    // String
    std::string Json::getValueExtracted(Json::Value& source, std::string defaultValue )  {
        if (source.empty() || source.isArray() ) return defaultValue;

        try {
            std::string returnValue = source.asString();
            return returnValue;
        }
        catch (...) { }

        return defaultValue;
    }



    glm::vec2 Json::getValueExtracted(Json::Value& source, glm::vec2 defaultValue ) {
        if (source.empty() ) return defaultValue;
        if (source.size() < 2 ) return defaultValue;


        try {
            printf("reading\n");
            glm::vec2 returnValue = glm::vec2(source[0].asFloat(), source[1].asFloat() );
            return returnValue;
        }
        catch (...) { }

        return defaultValue;
    }


    glm::vec3 Json::getValueExtracted(Json::Value& source, glm::vec3 defaultValue )  {
        if (source.empty() ) return defaultValue;
        if (source.size() < 3 ) return defaultValue;

        try {
            glm::vec3 returnValue = glm::vec3(source[0].asFloat(), source[1].asFloat(), source[2].asFloat() );
            return returnValue;
        }
        catch (...) { }

        return defaultValue;
    }


    glm::vec4 Json::getValueExtracted(Json::Value& source, glm::vec4 defaultValue )  {
        if (source.empty() ) return defaultValue;
        if (source.size() < 4 ) return defaultValue;


        try {
            glm::vec4 returnValue = { source[0].asFloat(), source[1].asFloat(), source[2].asFloat(), source[3].asFloat() };
            return returnValue;
        }
        catch (...) { }

        return defaultValue;
    }
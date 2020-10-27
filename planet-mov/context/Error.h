#ifndef _PLANET_MOV_ERROR_H
#define _PLANET_MOV_ERROR_H

#include <string>
#include <vector>

enum ErrorType {
    Error_None = 0,

    Error_Config,

    Error_Script,

    Error_Shader
};

class Error {
    public :
        Error(ErrorType type, std::string title, std::string details ) : _type(type), _details(details), _title(title) { }

        std::string     _title;
        std::string     _details;

        ErrorType       _type;

};


class ErrorHandler {
    private :
        ErrorHandler() { }

    public :
        static ErrorHandler& Get() { static ErrorHandler eh; return eh; }

        std::vector<Error> _errors;

        void push(Error er ) { 
            if (er._type != ErrorType::Error_None )
                _errors.push_back(er); 
        }

        // TODO:
        void pop(uint idx) { }

};


#endif // _PLANET_MOV_ERROR_H

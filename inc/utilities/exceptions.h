/*! \file exceptions.h
    \brief Project-related exception
*/
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

namespace utilities
{
    class GameException: public std::runtime_error {
    public:
        GameException(const std::string &what): std::runtime_error(what) {};
    };

    class GLException: public GameException {
    public:
        GLException(const std::string &what): GameException(what) {}
    };

    class OuterSpaceException: public GameException {
    public:
        OuterSpaceException(const std::string &what): GameException(what) {}
    };

    class ParseException: public GameException {
    public:
        ParseException(const std::string &filename): GameException("Error parsing: " + filename) {}
    };

    class FileException: public GameException {
    public:
        FileException(const std::string &filename): GameException("Error openning: " + filename) {}
    };
} // namespace utilities

#endif //EXCEPTIONS_H
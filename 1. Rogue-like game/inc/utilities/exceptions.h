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

    class GraphicsException: public GameException {
    public:
        GraphicsException(const std::string &what): GameException(what) {}
    };

    class GLException: public GraphicsException {
    public:
        GLException(const std::string &what): GraphicsException(what) {}
    };

    class SizeMismatchException: public GraphicsException {
    public:
        SizeMismatchException(const std::string &what): GraphicsException(what) {}
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

    class DictError: public GameException {
    public:
        DictError(const std::string& key, const std::string& function): 
            GameException("Invalid key: " + key + " in the " + function + " function") {}
    };

    class InventoryException: public GameException {
    public:
        InventoryException(const std::string &what):
            GameException(what) {}
    };

    class InventoryHadItException: public InventoryException {
    public:
        InventoryHadItException(const std::string &item):
            InventoryException("Inventory already had " + item) {}
    };

    class InventoryDidntHaveItException: public InventoryException {
    public:
        InventoryDidntHaveItException(const std::string &item):
            InventoryException("Inventory didn't have " + item) {}
    };

} // namespace utilities

#endif //EXCEPTIONS_H
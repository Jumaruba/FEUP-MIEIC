#ifndef AEDA_PROJ1_ERRORS_H
#define AEDA_PROJ1_ERRORS_H

#include <string>

/**
 * @file Errors.h
 * @brief This is the implementation and declaration of error classes
 */
/**
 * @brief Class made to throw types of errors
 */
class Error{
protected:
    std::string info;                                       /**<string containing the cause of the error*/
public:
    /**
     * @brief Construct a new Error object
     * 
     * @param Info Information about the error
     */
    Error(std::string Info): info(Info) { };
    /**
     * @brief Get the Info parameter
     * 
     * @return std::string 
     */
    virtual std::string getInfo() const {return info;};
};
/**
 * @brief Error case the client doens't exist
 */
class NoClient: Error {
public:
    NoClient(const std::string & nif): Error(nif) {}
    std::string getInfo() const {return info;}
};

/**
 * @brief Error case the service doesn't exist
 */
class NoService: Error{
public:
    NoService(const std::string &id): Error(id){ }
    std::string getInfo() const {return info;}
};
/**
 * @brief Error case the client already exists
 */
class RepeatedClient: Error{
public:
    RepeatedClient(const std::string &id): Error(id){ }
    std::string getInfo() const {return info;}
};

/**
 * @brief Error for wrong inputs
 * 
 */
class WrongInput_option: Error{
public:
    WrongInput_option(const std::string &input): Error(input){ }
    std::string getInfo() const {return info;};
};

class NoWorker: Error{
public:
    NoWorker(): Error("No worker with the specified NIF!"){ }
    std::string getInfo() const {return info;};

};
class EmptyQueue : Error{
public:
    EmptyQueue();
    string getInfo() const {return "Empty Workshop queue!";};
};

#endif //AEDA_PROJ1_ERRORS_H
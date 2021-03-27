//
// Created by 666 on 2021/3/26.
//

#ifndef COMPUTERSCIENCEFOUNDATION_PUBLICEXCEPTION_H
#define COMPUTERSCIENCEFOUNDATION_PUBLICEXCEPTION_H
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::exception;

class illegalParameterValue : exception {

private:
    string message;
public:
    illegalParameterValue() : message("Illegal parameter value") {}
    explicit illegalParameterValue(const char* theMessage) {message = theMessage;}
    void outputMessage() {cout << message << endl;}

};


#endif //COMPUTERSCIENCEFOUNDATION_PUBLICEXCEPTION_H

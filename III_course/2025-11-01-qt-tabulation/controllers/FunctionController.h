//
// Created by tysser on 01.11.25.
//

// controllers/FunctionController.h
#ifndef FUNCTIONCONTROLLER_H
#define FUNCTIONCONTROLLER_H

#pragma once
#include <functional>
#include <QString>

class FunctionController {
public:
    static std::function<double(double)> getFunction(const QString &name);
};

#endif //FUNCTIONCONTROLLER_H

//
// Created by tysser on 19.04.26.
//

#pragma once
#include <vector>
#include <memory>
#include <iostream>

// Інтерфейс спостерігача
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

// Суб’єкт
class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;

public:
    void subscribe(const std::shared_ptr<Observer>& obs);
    void notify(const std::string& message);
};

// Конкретний спостерігач
class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override;
};

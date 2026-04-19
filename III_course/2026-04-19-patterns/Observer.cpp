//
// Created by tysser on 19.04.26.
//

#include "Observer.h"
#include <algorithm>

void Subject::subscribe(const std::shared_ptr<Observer>& obs) {
    observers.push_back(obs);
}

void Subject::notify(const std::string& message) {
    std::ranges::for_each(observers,
        [&message](auto& obs)
        {
            obs->update(message);
        });
}

void ConsoleObserver::update(const std::string& message) {
    std::cout << "Observer received: " << message << std::endl;
}
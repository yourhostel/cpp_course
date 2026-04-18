#include "Decorator.h"
#include <iostream>

void EmailNotifier::send(const std::string& message) {
    std::cout << "Email: " << message << std::endl;
}

NotifierDecorator::NotifierDecorator(std::shared_ptr<Notifier> notifier)
    : wrappee(std::move(notifier)) {}

void NotifierDecorator::send(const std::string& message) {
    wrappee->send(message);
}

SMSDecorator::SMSDecorator(std::shared_ptr<Notifier> notifier)
    : NotifierDecorator(std::move(notifier)) {}

void SMSDecorator::send(const std::string& message) {
    NotifierDecorator::send(message);
    std::cout << "SMS: " << message << std::endl;
}

SlackDecorator::SlackDecorator(std::shared_ptr<Notifier> notifier)
    : NotifierDecorator(std::move(notifier)) {}

void SlackDecorator::send(const std::string& message) {
    NotifierDecorator::send(message);
    std::cout << "Slack: " << message << std::endl;
}
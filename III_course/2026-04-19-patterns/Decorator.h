#pragma once

#include <memory>
#include <string>

// Базовий інтерфейс
class Notifier {
public:
    virtual void send(const std::string& message) = 0;
    virtual ~Notifier() = default;
};

// Конкретна реалізація
class EmailNotifier : public Notifier {
public:
    void send(const std::string& message) override;
};

// Базовий декоратор
class NotifierDecorator : public Notifier {
protected:
    std::shared_ptr<Notifier> wrappee;

public:
    explicit NotifierDecorator(std::shared_ptr<Notifier> notifier);
    void send(const std::string& message) override;
};

// Конкретний декоратор 1
class SMSDecorator : public NotifierDecorator {
public:
    explicit SMSDecorator(std::shared_ptr<Notifier> notifier);
    void send(const std::string& message) override;
};

// Конкретний декоратор 2
class SlackDecorator : public NotifierDecorator {
public:
    explicit SlackDecorator(std::shared_ptr<Notifier> notifier);
    void send(const std::string& message) override;
};
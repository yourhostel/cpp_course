#include <memory>

#include "Decorator.h"
#include "Observer.h"
#include "Visitor.h"

void visitor()
{
    const auto circle = std::make_shared<Circle>(5);
    const auto rectangle = std::make_shared<Rectangle>(4, 6);

    PrintVisitor visitor;

    circle->accept(visitor);
    rectangle->accept(visitor);
}

void observer()
{
    const auto subject = std::make_shared<Subject>();
    const auto obs1 = std::make_shared<ConsoleObserver>();
    const auto obs2 = std::make_shared<ConsoleObserver>();

    subject->subscribe(obs1);
    subject->subscribe(obs2);

    subject->notify("Сталася подія");
}

void decorator()
{
    std::shared_ptr<Notifier> notifier =
    std::make_shared<SlackDecorator>(
        std::make_shared<SMSDecorator>(
            std::make_shared<EmailNotifier>()
        )
    );

    notifier->send("Hello");
}

int main() {
    visitor();
    observer();
    decorator();

    return 0;
}

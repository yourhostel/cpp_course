#include <memory>

#include "Decorator.h"

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
    decorator();

    return 0;
}

#include <iostream>
#include <source_location>
void log(const std::string &message,
        const std::source_location location = std::source_location::current())
{
    std::cout << location.file_name() << ":" << location.line() << " "
            << location.function_name() << " - " << message << std::endl;
}
int main()
{
    log("Hello, World!");
    return 0;
}
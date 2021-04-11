//
// Created by Monkeys on 11.04.2021.
//


#ifndef MONKEYS_LOGGER_HPP
#define MONKEYS_LOGGER_HPP

#include <string>

Class Logger {
    public:
    void OpenLog();
    void CloseLog();
    void WriteLog(std::string text);
    int LogLevel;
    private:
    void LogError();
    void LogSuccessfulPass();
    void LogUserLogin();
    void LogUserLogout();
    void LogUnsuccesfulPass();

}


#endif //MONKEYS_LOGGER_HPP
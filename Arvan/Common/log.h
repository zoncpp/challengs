#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

void log(std::string s)
{
    auto t = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(t);

    struct tm*  tm_stc = localtime(&tt);
    char       buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", tm_stc);

    std::cout << "[" << buf << "]\t";
    std::cout << s.c_str() << std::endl;
}


#endif // LOG_H

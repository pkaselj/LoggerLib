#ifndef LOGGER_HPP
#define LOGGER_HPP

#include<iostream>
#include<fstream>
#include<cstdio>
#include<unistd.h>
#include<cstdlib>

/*
*
*
*   -----CHECK APPENDING
*
*
*/

class Logger
{
    private:
    std::ofstream output;
    time_t time;

    public:
    Logger(const char* path);
    ~Logger(void);

    template <class T>
    friend Logger& operator <<(Logger& logStream, T const& report);
};

Logger::Logger(const char* path)
{
    output.open(path, std::ios::out | std::ios::ate);

    if(output.is_open() == false)
        std::cout << "Could not open log file!" << std::endl;
}

Logger::~Logger(void)
{
    output.close();
}

template<class T>
Logger& operator <<(Logger& logStream, T const& report)
{
    if(logStream.output.is_open() == true)
    {
        time(&logStream.time);
        logStream.output << ctime(&logStream.time) << report << std::endl;
    }

    return logStream;
}

#endif
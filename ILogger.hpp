#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include<iostream>
#include<fstream>
#include<cstdio>
#include<unistd.h>
#include<cstdlib>
#include<sys/stat.h>
#include<sys/time.h>

class ILogger
{
    protected:
    virtual ILogger& logString (std::string const& report) = 0;

    public:
    //ILogger(void) = delete;
    virtual ~ILogger(void) {};
    virtual void Crash (void) = 0;
    friend ILogger& operator <<(ILogger& logStream, std::string const& report);
};

ILogger& operator <<(ILogger& logStream, std::string const& report)
{
    return logStream.logString(report);
}

#endif
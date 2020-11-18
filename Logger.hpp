#ifndef LOGGER_HPP
#define LOGGER_HPP

#include<iostream>
#include<fstream>
#include<cstdio>
#include<unistd.h>
#include<cstdlib>
#include<sys/stat.h>
#include<sys/time.h>


/*
*
*
*   -----CHECK APPENDING
*
*
*/

class Logger
{
    protected:
    std::string              filepath;
    std::ofstream            output;
    time_t                   time;

    void openIfExists(void);

    public:
         Logger (const std::string path);
        ~Logger (void);
    void Crash  (void);
    bool exists (void);
    void close  (void);
    void open   (void);

    template <class T>
    friend Logger& operator <<(Logger& logStream, T const& report);

};

Logger::Logger(const std::string path)
{
    filepath = path;
    open();
}

Logger::~Logger(void)
{
    close();
}

void Logger::Crash(void)
{
    *this << "Program crashed!";
    exit(-1);
}

bool Logger::exists(void)
{
    struct stat buf; // TODO Unnecessary buf?
    if(stat(filepath.c_str(), &buf) >= 0)
        return true;
    return false;
}

void Logger::close(void)
{
    output.close();
}

void Logger::open(void)
{
    output.open(filepath.c_str(), std::ios::out | std::ios::ate);
    if(output.is_open() == false)
        std::cout << "Could not open log file!" << std::endl;

    output << "Logger " + std::string(filepath) + " created!" << std::endl;
}

void Logger::openIfExists(void)
{
    if(exists() == false)
    {
        std::cout << "File doesn't exist!" << std::endl;
    }
    else if(output.is_open() == false)
    {
        open();
    }
}

template<class T>
Logger& operator <<(Logger& logStream, T const& report)
{
    logStream.openIfExists();

    if(logStream.output.is_open() == true)
    {
        struct timeval time;
        gettimeofday( &time, NULL );

        logStream.output << time.tv_sec << ":" << time.tv_usec << "--- " << report << std::endl;
    }

    return logStream;
}


#endif
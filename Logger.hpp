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


class NulLogger
{
    protected:
    virtual NulLogger& logString (std::string const& report);

    public:
    NulLogger(void) {};
    virtual ~NulLogger(void) {};
    void    Crash  (void);
    friend NulLogger& operator <<(NulLogger& logStream, std::string const& report);
};

NulLogger& NulLogger::logString (std::string const& report)
{
    return *this;
}

void NulLogger::Crash(void)
{
    *this << "Program crashed!";
    exit(-1);
}

NulLogger& operator <<(NulLogger& logStream, std::string const& report)
{
    return logStream.logString(report);
}

class Logger : public NulLogger
{
    private:
        bool exists (void);
        void close  (void);
        void open   (void);

    protected:
        std::string              filepath;
        std::ofstream            output;
        time_t                   time;

        void openIfExists(void);

        /* Called by operator<<, used for polymorphism (class NulLogger) */
        virtual Logger& logString (std::string const& report);
                        Logger    (void) {};
        /*_______________________________________________________________*/

    public:
            Logger (const std::string path);
    virtual ~Logger (void);

    /*  
    *   template <class T>
    *   friend Logger& operator <<(Logger& logStream, T const& report);
    *    
    *   Commented method allows for streaming objects to log,
    *   currently implemented one supports only strings.
    * 
    *   This was done because of child class NulLogger
    *   which is used when a class which uses Logger class
    *   doesn't want to log anything.
    * 
    *   TODO solution if possible?
    * 
    */

};


Logger::Logger(const std::string path)
{
    filepath = path;
    open();
}

Logger::~Logger(void)
{
    *this << "Closing logger";
    close();
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

Logger& Logger::logString (std::string const& report)
{
    openIfExists();

    if(output.is_open() == true)
    {
        struct timeval time;
        gettimeofday( &time, NULL );

        output << time.tv_sec << ":" << time.tv_usec << "--- " << report << std::endl;
    }

    return *this;
}





#endif
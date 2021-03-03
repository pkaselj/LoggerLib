#include"Logger.hpp"

#include "Time.hpp"

struct timespec Time::raw_time; //?
struct tm Time::refined_time; //?

Logger::Logger(const std::string& path)
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
    struct stat buf; // NECESSARRY - OTHERWISE SEG FAULT AT LINE BELOW
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
        exit(-1); // DO NOTHNIG --- TODO RAW WRITE TO FILE

    output << "Logger " + std::string(filepath) + " created!" << std::endl;
}

void Logger::openIfExists(void)
{
    if(exists() == false)
    {
        ; // DO NOTHNIG --- TODO RAW WRITE TO FILE
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
        std::lock_guard<std::mutex> lock(write_lock);
        output << Time::getTime() << "--- " << report << std::endl;
        //output.flush();
    }

    return *this;
}

std::string Logger::getName() const
{
    return filepath;
}

void Logger::flush()
{
    output.flush();
}

/*void Logger::Crash()
{
    *this << "Program crashed!";
    exit(-1);
}*/

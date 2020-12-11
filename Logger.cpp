#include"Logger.hpp"

#include"/home/pi/Shared/TimeLib/0.0.0/Time.hpp"

struct timespec Time::raw_time;
struct tm Time::refined_time;

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
        output << Time::getTime() << "--- " << report << std::endl;
    }

    return *this;
}

void Logger::Crash()
{
    *this << "Program crashed!";
    exit(-1);
}

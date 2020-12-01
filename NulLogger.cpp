#include"NulLogger.hpp"

NulLogger& NulLogger::logString (std::string const& report)
{
    return *this;
}

void NulLogger::Crash(void)
{
    *this << "Program crashed!";
    exit(-1);
}


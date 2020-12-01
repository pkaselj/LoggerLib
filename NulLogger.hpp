#ifndef NULLOGGER_HPP
#define NULLOGGER_HPP

#include"ILogger.hpp"

class NulLogger : public ILogger
{
    protected:
    virtual NulLogger& logString (std::string const& report);

    public:
    NulLogger(void) {};
    virtual ~NulLogger(void) {};
    virtual void Crash (void);
};

#endif
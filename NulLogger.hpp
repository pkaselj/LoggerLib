#ifndef NULLOGGER_HPP
#define NULLOGGER_HPP

#include"ILogger.hpp"

/**
 * @brief NulLogger class
 * 
 * Used as a default logger in other classes. \n
 * \n
 * Does nothing with the input. Used to implement logger as an optional parameter. \n
 */
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
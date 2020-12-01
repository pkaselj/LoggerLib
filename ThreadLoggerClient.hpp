#ifndef THREAD_LOGGER_CLIENT_HPP
#define THREAD_LOGGER_CLIENT_HPP

#include"Logger.hpp"
#include"/home/pi/Shared/IPCommunicationsLib/0.0.0/mailbox.hpp"

class ThreadLoggerClient : public ILogger
{
    private:
    Mailbox mailbox;
    MailboxReference loggerMailbox;

    public:
    ThreadLoggerClient(const std::string& mailboxId, const std::string& loggerMailboxId);
    virtual ~ThreadLoggerClient(void) {};
    virtual void Crash(void);
    virtual ThreadLoggerClient& logString(std::string const& report);

};

#endif
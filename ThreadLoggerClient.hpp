#ifndef THREAD_LOGGER_CLIENT_HPP
#define THREAD_LOGGER_CLIENT_HPP

#include<memory>

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

ThreadLoggerClient::ThreadLoggerClient(const std::string& mailboxId, const std::string& loggerMailboxId)
    :   mailbox(mailboxId), loggerMailbox(loggerMailboxId) {}

void ThreadLoggerClient::Crash(void)
{
    std::cout << "Program crashed!" << std::endl;
    exit(-1);
}

ThreadLoggerClient& ThreadLoggerClient::logString(std::string const& report)
{
    mailbox.send(loggerMailbox, report);
    return *this;
}

#endif
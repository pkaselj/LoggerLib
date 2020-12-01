#include"ThreadLoggerClient.hpp"
#include<memory>

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

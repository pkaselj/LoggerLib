#ifndef THREAD_LoggerHPP
#define THREAD_LoggerHPP

#include<memory>

#include"Logger.hpp"
#include"/home/pi/Shared/IPCommunicationsLib/0.0.0/mailbox.hpp"

class ThreadLogger : public Logger
{
    private:
    std::unique_ptr<Mailbox> mailbox = nullptr;

    public:
    ThreadLogger(const std::string& path, const std::string& mailboxId);
    void listenForMessages(void);

};

ThreadLogger::ThreadLogger(const std::string& path, const std::string& mailboxId)
    :   Logger(path)    
{
        /************** TODO *****************************
        *   Replace dynamic allocation with static?
        * ************************************************/

    mailbox = std::make_unique<Mailbox>(mailboxId, *this);
}

void ThreadLogger::listenForMessages(void)
{
    std::string rawMessage = mailbox->receive();

    if(rawMessage != "")
        

}

#endif
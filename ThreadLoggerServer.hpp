#ifndef THREAD_LOGGER_SERVER_HPP
#define THREAD_LOGGER_SERVER_HPP

#include"ThreadLoggerClient.hpp"
#include"NulLogger.hpp"
#include"/home/pi/Shared/IPCommunicationsLib/0.0.0/mailbox.hpp"


class ThreadLoggerServer
{
    private:
        Mailbox mailbox;
        ILogger* p_logger;
        bool available = false;

    public:

        ThreadLoggerServer(const std::string& mailboxId, ILogger* _logger);
        ~ThreadLoggerServer(void);
        void startLogging(void);
        void stopLogging(void) { available = false; };
        bool isAvailable(void) { return available; }; 

};
#endif
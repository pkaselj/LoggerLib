
#include"ThreadLoggerServer.hpp"

ThreadLoggerServer::ThreadLoggerServer(const std::string& mailboxId, ILogger* _logger)
    :   mailbox(mailboxId)
{
    if(_logger == nullptr)
        p_logger = new NulLogger();
    
    p_logger = _logger;

    available = true;
}


ThreadLoggerServer::~ThreadLoggerServer(void)
{
    /*if(p_logger != nullptr)
        delete p_logger;*/
}

void ThreadLoggerServer::startLogging(void)
{
    if(this->isAvailable() != true)
        return;

    mailbox_message message = mailbox.receiveWithoutAcknowledgement();

    if(p_logger != nullptr) // ? NEEDED ?
        *p_logger << "TL: " + message.sender + " : " + message.content;
}

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include"ILogger.hpp"

class Logger : public ILogger
{
    private:
        bool exists (void);
        void close  (void);
        void open   (void);

    protected:
        std::string              filepath;
        std::ofstream            output;
        time_t                   time;

        void openIfExists(void);

        /* Called by operator<<, used for polymorphism (class NulLogger) */
        virtual Logger& logString (std::string const& report);
                        Logger    (void) {};
        /*_______________________________________________________________*/

    public:
             Logger (const std::string path);
        void Crash  ();
    virtual ~Logger (void);

    /*  
    *   template <class T>
    *   friend Logger& operator <<(Logger& logStream, T const& report);
    *    
    *   Commented method allows for streaming objects to log,
    *   currently implemented one supports only strings.
    * 
    *   This was done because of child class NulLogger
    *   which is used when a class which uses Logger class
    *   doesn't want to log anything.
    * 
    *   TODO solution if possible?
    * 
    */

};
#endif
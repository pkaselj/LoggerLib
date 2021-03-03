#ifndef LOGGER_HPP
#define LOGGER_HPP

#include"ILogger.hpp"

#include<mutex>

/**
 * @brief Class used for logging messages to a file
 * 
 * Derives from ILogger interface
 */
class Logger : public ILogger
{
    private:
        /// returns TRUE if log file already exists
        bool exists (void);

        /// Close log file
        void close  (void);

        /// Open log file
        void open   (void);

    protected:

        /// Mutex to resolve concurrent writing to a file
        std::mutex write_lock; // Ignore error, not supported on Windows

        /// Path to log file
        std::string              filepath;

        /// Output stream object to write to `filepath`
        std::ofstream            output;

        /// Current time (to be replaced with Time class)
        time_t                   time;

        /// Open log file for writing ONLY if it exists
        void openIfExists(void);

        /// Called by operator<<, used for polymorphism (class NulLogger)
        virtual Logger& logString (std::string const& report);
                        /// Create default Logger object
                        Logger    (void) = default;

    public:
            /**
             * @brief Construct a new Logger object
             * 
             * @param path File path to a log file. Creates one if it doesn't exist
             */
             Logger (const std::string& path);

             /// Returns the name (path of the output log file) of the logger
             virtual std::string getName() const;

             void flush();

             /// Used to crash process in case of major error. (To be removed)
        //void Crash  ();
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
#include <Arduino.h>

enum LOG_LEVEL{
    debug = 0,
    info = 1,
    warn = 2,
    error = 3,
    fatal = 4
};
enum LOG_TYPE{
    serial
};

class Logger{
    private:
        static Logger* instance_;
        Logger(): log_type_(serial), write_level_(debug) {}
    
    public:
        static Logger* getInstance(){
            if(instance_ == 0) instance_ = new Logger();

            return instance_;
        }

    public:
        void setWriteLevel(LOG_LEVEL level){
            write_level_ = level;
        }
        void setLogType(LOG_TYPE type) {
            log_type_ = type;
        }

        //time level name - message
        //2200(millis) DEBUG(level) pid(name) - This is debug message(message)
        void writeLog(String class_name, LOG_LEVEL level, String message){
            if(write_level_ > level) return;
            String msg = "";

            msg += String(millis());

            switch(level){
                case LOG_LEVEL::debug:
                    msg += " DEBUG ";
                    break;
                case LOG_LEVEL::info:
                    msg += " INFO ";
                    break;
                case LOG_LEVEL::warn:
                    msg += " WARN ";
                    break;
                case LOG_LEVEL::error:
                    msg += " ERROR ";
                    break;
                case LOG_LEVEL::fatal:
                    msg += " FATAL ";
                    break;
            }

            msg += String(class_name + " - " + message);

            write(msg);
        }

    private:
        void write(String msg){
            switch(log_type_){
                case LOG_TYPE::serial:
                    Serial.println(msg);
            }
        }

    private:
        LOG_LEVEL write_level_;
        LOG_TYPE log_type_;
};

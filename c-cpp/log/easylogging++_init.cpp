// 不生成默认的logs\\easylog.txt文件
#define ELPP_NO_DEFAULT_LOG_FILE
// 线程安全设置
#define ELPP_THREAD_SAFE

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

void Easylogging_Setup() 
{
	// 加载easylogging配置文件
	el::Configurations conf("easylogging++_conf.txt");
	el::Loggers::reconfigureAllLoggers(conf);
	el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
	el::Loggers::addFlag(el::LoggingFlag::DisableApplicationAbortFatalLog);
}

// easylogging++_conf.txt
* GLOBAL:  
    ENABLED                 =   true  
    TO_FILE                 =   true
    TO_STANDARD_OUTPUT      =   true  
    FORMAT                  =   "[%level | %user | %datetime] |> %msg"  
    FILENAME                =   "log/log_%datetime{%Y-%M-%d}.log"  
    MILLISECONDS_WIDTH      =   3  
    PERFORMANCE_TRACKING    =   false  
    MAX_LOG_FILE_SIZE       =   1048576  
    LOG_FLUSH_THRESHOLD     =   0  
      
* TRACE:  
    FORMAT                  =   "[%level | %user | %datetime] <%loc> |> %msg"
    ##FILENAME                =   "log/trace_log_%datetime{%Y-%M-%d}.log"  
    FILENAME                =   "log/log_%datetime{%Y-%M-%d}.log"  
      
* DEBUG:  
    FORMAT                  =   "[%level | %user | %datetime] <%loc> |> %msg"
    ##FILENAME                =   "log/debug_log_%datetime{%Y-%M-%d}.log"  
    FILENAME                =   "log/log_%datetime{%Y-%M-%d}.log"  
      
* FATAL:  
    FORMAT                  =   "[%level | %user | %datetime] <%loc> |> %msg"
    ##FILENAME                =   "log/fatal_log_%datetime{%Y-%M-%d}.log"
    FILENAME                =   "log/log_%datetime{%Y-%M-%d}.log"  

* ERROR:  
    FORMAT                  =   "[%level | %user | %datetime] <%loc> |> %msg"
    ##FILENAME                =   "log/error_log_%datetime{%Y-%M-%d}.log"  
    FILENAME                =   "log/log_%datetime{%Y-%M-%d}.log"  
      
* WARNING:  
    FORMAT                  =   "[%level | %user | %datetime] <%loc> |> %msg"
    ##FILENAME                =   "log/warning_log_%datetime{%Y-%M-%d}.log"  
    FILENAME                =   "log/log_%datetime{%Y-%M-%d}.log"  
      
* INFO:  
    ##FILENAME                =   "log/info_log_%datetime{%Y-%M-%d}.log"  
    FILENAME                =   "log/log_%datetime{%Y-%M-%d}.log"  
      
* VERBOSE:  
    ENABLED                 =   false  

#if !defined(DE_SPDLOG_HELPER)
#define DE_SPDLOG_HELPER


//actually, I do not know if this is working as expected, I want to be something like a singleton but I am using
//static things for this, and this is used in many different places, like inside lambdas, and not sure about scopes, or anything
//please future me fix this, and other people please do not use

#ifndef SPDLOG_COMPILED_LIB
#define SPDLOG_COMPILED_LIB 
// this is here to be able to include this file in other project without needing to link spdlog.lib
// because for some reason is trying to link double, or use it as header only, so multiple definitions appears
#endif

#include <spdlog/spdlog.h>

#ifndef APP_NAME
#define APP_NAME "no_name_app"
#endif


//this need to be done better, to improve this attempt of singleton 
/**
 * @brief Get the Multi Sink Logger object reference. This logs to file and to console.
 * 
 * @return spdlog::logger& reference to singleton Multi Sink Logger
 */
spdlog::logger& getMultiSinkLogger();



#endif // DE_SPDLOG_HELPER

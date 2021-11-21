#pragma once

//actually, i do not know if this is working as expected, i want to be something like a singleton but i am using
//static things for this, and this is used in many diferent places, like inside lambdas, and not sure about scopes, or anything
//please future me fix this, and other people please do not use

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

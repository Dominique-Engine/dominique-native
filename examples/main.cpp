#ifndef APP_VERSION
# define APP_VERSION "0.0.0"
#endif
//#define SDL_MAIN_HANDLED//not needed in msvc,need to enable this from cmake, now is needed in msvc, wtf
//#define RC_INVOKED//this shouldn't be done

#ifndef APP_VERSION
# define APP_VERSION "0.0.0"
#endif


#include <iostream>
#include <iomanip>
#include <sstream>


#include "DEngine/spdlog_helper.h"
#include "DEngine/core.h"
#include "DEngine/sdl_helpers.h"


using namespace std;


int main(void)
{
    auto logger = getMultiSinkLogger();

    DEngine::DE App;
    App.rendererType = DEngine::RendererType::DirectX11;
    App.config.title = "DEngine App";
    App.config.width = 800;
    App.config.height = 600;

    DEngine::logSDL2renderersInfo();
    
    DEngine::Core::Init(App);
    DEngine::Core::Run(App);
    DEngine::Core::Clean(App);

    return 0;
}

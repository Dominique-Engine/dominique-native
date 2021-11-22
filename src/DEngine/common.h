#if !defined(DENGINE_COMMON)
#define DENGINE_COMMON



#ifdef _WIN32
#    ifdef DENGINE_EXPORTS
#        define DENGINE_API __declspec(dllexport)
#    else
#        define DENGINE_API __declspec(dllimport)
#    endif
#elif
#    define DENGINE_API
#endif

#endif // DENGINE_COMMON
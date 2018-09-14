#ifndef LIBRARY_HPP_INCLUDED
#define LIBRARY_HPP_INCLUDED

#ifdef _MSC_VER
#ifdef LIBRARY_BUILD_DLL
#define LIBAPI __declspec(dllexport)
#else
#define LIBAPI __declspec(dllimport)
#endif
#else
#ifdef LIBRARY_BUILD_DLL
#define LIBAPI __attribute__((visibility("default")))
#else
#define LIBAPI
#endif
#endif

LIBAPI int library_function();

#endif // LIBRARY_HPP_INCLUDED

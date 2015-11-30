/*!
 * \file GlobalDefines.h
 * \brief GlobalDefines
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_GLOBALDEFINES_H
#define ISKN_GLOBALDEFINES_H
#ifdef _ISKN_ANDROID_
#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "libclubic"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif

#ifdef _WIN32
//Build for Microsoft Visual Studio Compiler
#ifdef _MSC_BUILD
#ifdef ISKN_API_LIBRARY
    #define CLASS class __declspec(dllexport)
    #define STRUCT struct __declspec(dllexport)
#else
    #define CLASS class __declspec(dllimport)
    #define STRUCT struct __declspec(dllimport)
#endif
#endif /* _MSC_BUILD */

// Build for Qt
#ifdef QT_CORE_LIB
    #include <QtCore/qglobal.h>
#if defined(ISKN_API_LIBRARY)
    #define CLASS class Q_DECL_EXPORT
    #define STRUCT struct Q_DECL_EXPORT
#else
    #define CLASS class Q_DECL_IMPORT
    #define STRUCT struct Q_DECL_IMPORT
#endif
#endif /* QT_CORE_LIB */

#define END_CLASS
#define END_STRUCT

#endif /* _WIN32 */

#ifdef __MACH__
  #import "TargetConditionals.h"
  #if (!TARGET_OS_IPHONE)
    #define TARGET_OS_MACOSX 1
    #define _MACOS_
  #else
    #ifdef TARGET_OS_MACOSX
      #undef TARGET_OS_MACOSX
    #endif
  #endif
#endif /*__MACH__ */

#if TARGET_OS_IPHONE
#define _UNICODE
#define CLASS class
#define STRUCT struct
#define END_CLASS
#define END_STRUCT
#endif /* TARGET_OS_IPHONE */

#if TARGET_OS_MACOSX
typedef unsigned int DWORD ;
#define _UNICODE
#define CLASS _Pragma("GCC visibility push(default)") class
#define STRUCT _Pragma("GCC visibility push(default)") struct
#define END_CLASS _Pragma("GCC visibility pop")
#define END_STRUCT _Pragma("GCC visibility pop")
#define xCLASS class
#define xSTRUCT  struct
#define xEND_CLASS
#define xEND_STRUCT
#endif /* TARGET_OS_MACOSX */

#if defined(linux)
#define CLASS _Pragma("GCC visibility push(default)") class
#define STRUCT _Pragma("GCC visibility push(default)") struct
#define END_CLASS _Pragma("GCC visibility pop")
#define END_STRUCT _Pragma("GCC visibility pop")
#define xCLASS class
#define xSTRUCT  struct
#define xEND_CLASS
#define xEND_STRUCT
#endif


#ifdef _ISKN_ANDROID_
#define CLASS class
#define STRUCT struct
#define END_CLASS
#define END_STRUCT
#endif

// Include common classes
#include "isknDate.h"
#include "isknTime.h"

#include <string>
#include <vector>
#include <map>

#endif // ISKN_GLOBALDEFINES_H


/*
 * mptAssert.h
 * -----------
 * Purpose: assert and static_assert
 * Notes  : (currently none)
 * Authors: OpenMPT Devs
 * The OpenMPT source code is released under the BSD license. Read LICENSE for more details.
 */


#pragma once



#include "mptBaseMacros.h"



OPENMPT_NAMESPACE_BEGIN



// Static code checkers might need to get the knowledge of our assertions transferred to them.
#define MPT_CHECKER_ASSUME_ASSERTIONS 1
//#define MPT_CHECKER_ASSUME_ASSERTIONS 0

#ifdef MPT_BUILD_ANALYZED

#if MPT_COMPILER_MSVC

#if MPT_CHECKER_ASSUME_ASSERTIONS
#define MPT_CHECKER_ASSUME(x) __analysis_assume(!!(x))
#endif

#elif MPT_COMPILER_CLANG

#if MPT_CHECKER_ASSUME_ASSERTIONS
#ifdef NDEBUG
#error "Builds for static analyzers depend on assert() being enabled, but the current build has #define NDEBUG. This makes no sense."
#endif
OPENMPT_NAMESPACE_END
#include <cassert>
OPENMPT_NAMESPACE_BEGIN
#define MPT_CHECKER_ASSUME(x) assert(!!(x))
#endif

#endif // MPT_COMPILER

#endif // MPT_BUILD_ANALYZED

#ifndef MPT_CHECKER_ASSUME
#define MPT_CHECKER_ASSUME(x) MPT_DO { } MPT_WHILE_0
#endif



#if defined(_MFC_VER) && !defined(MPT_CPPCHECK_CUSTOM)

#if !defined(ASSERT)
#error "MFC is expected to #define ASSERT"
#endif // !defined(ASERRT)
#define MPT_FRAMEWORK_ASSERT_IS_DEFINED

#if defined(_DEBUG)
 #define MPT_FRAMEWORK_ASSERT_IS_ACTIVE 1
#else // !_DEBUG
 #define MPT_FRAMEWORK_ASSERT_IS_ACTIVE 0
#endif // _DEBUG

// let MFC handle our asserts
#define MPT_ASSERT_USE_FRAMEWORK 1

#else // !_MFC_VER

#if defined(ASSERT)
#define MPT_FRAMEWORK_ASSERT_IS_DEFINED
#if defined(_DEBUG)
 #define MPT_FRAMEWORK_ASSERT_IS_ACTIVE 1
#else // !_DEBUG
 #define MPT_FRAMEWORK_ASSERT_IS_ACTIVE 0
#endif // _DEBUG
#endif // !defined(ASERRT)

// handle assert in our own way without relying on some platform-/framework-specific assert implementation
#define MPT_ASSERT_USE_FRAMEWORK 0

#endif // _MFC_VER

#if defined(MPT_FRAMEWORK_ASSERT_IS_DEFINED) && (MPT_ASSERT_USE_FRAMEWORK == 1)

#define MPT_ASSERT_NOTREACHED()          ASSERT(0)
#define MPT_ASSERT(expr)                 ASSERT((expr))
#define MPT_ASSERT_MSG(expr, msg)        ASSERT((expr) && (msg))
#if (MPT_FRAMEWORK_ASSERT_IS_ACTIVE == 1)
#define MPT_ASSERT_ALWAYS(expr)          ASSERT((expr))
#define MPT_ASSERT_ALWAYS_MSG(expr, msg) ASSERT((expr) && (msg))
#else
#define MPT_ASSERT_ALWAYS(expr)          MPT_DO { if(!(expr)) { AssertHandler(__FILE__, __LINE__, __FUNCTION__, #expr); } MPT_CHECKER_ASSUME(expr); } MPT_WHILE_0
#define MPT_ASSERT_ALWAYS_MSG(expr, msg) MPT_DO { if(!(expr)) { AssertHandler(__FILE__, __LINE__, __FUNCTION__, #expr, msg); } MPT_CHECKER_ASSUME(expr); } MPT_WHILE_0
#ifndef MPT_ASSERT_HANDLER_NEEDED
#define MPT_ASSERT_HANDLER_NEEDED
#endif
#endif

#elif defined(NO_ASSERTS)

#define MPT_ASSERT_NOTREACHED()          MPT_CHECKER_ASSUME(0)
#define MPT_ASSERT(expr)                 MPT_CHECKER_ASSUME(expr)
#define MPT_ASSERT_MSG(expr, msg)        MPT_CHECKER_ASSUME(expr)
#define MPT_ASSERT_ALWAYS(expr)          MPT_DO { if(!(expr)) { AssertHandler(__FILE__, __LINE__, __FUNCTION__, #expr); } MPT_CHECKER_ASSUME(expr); } MPT_WHILE_0
#define MPT_ASSERT_ALWAYS_MSG(expr, msg) MPT_DO { if(!(expr)) { AssertHandler(__FILE__, __LINE__, __FUNCTION__, #expr, msg); } MPT_CHECKER_ASSUME(expr); } MPT_WHILE_0
#ifndef MPT_ASSERT_HANDLER_NEEDED
#define MPT_ASSERT_HANDLER_NEEDED
#endif

#else // !NO_ASSERTS

#define MPT_ASSERT_NOTREACHED()          MPT_DO { MPT_CONSTANT_IF(!(0)) { AssertHandler(__FILE__, __LINE__, __FUNCTION__, "0"); } MPT_CHECKER_ASSUME(0); } MPT_WHILE_0
#define MPT_ASSERT(expr)                 MPT_DO { if(!(expr)) { AssertHandler(__FILE__, __LINE__, __FUNCTION__, #expr); } MPT_CHECKER_ASSUME(expr); } MPT_WHILE_0
#define MPT_ASSERT_MSG(expr, msg)        MPT_DO { if(!(expr)) { AssertHandler(__FILE__, __LINE__, __FUNCTION__, #expr, msg); } MPT_CHECKER_ASSUME(expr); } MPT_WHILE_0
#define MPT_ASSERT_ALWAYS(expr)          MPT_DO { if(!(expr)) { AssertHandler(__FILE__, __LINE__, __FUNCTION__, #expr); } MPT_CHECKER_ASSUME(expr); } MPT_WHILE_0
#define MPT_ASSERT_ALWAYS_MSG(expr, msg) MPT_DO { if(!(expr)) { AssertHandler(__FILE__, __LINE__, __FUNCTION__, #expr, msg); } MPT_CHECKER_ASSUME(expr); } MPT_WHILE_0
#ifndef MPT_ASSERT_HANDLER_NEEDED
#define MPT_ASSERT_HANDLER_NEEDED
#endif

#endif // NO_ASSERTS


#if defined(MPT_ASSERT_HANDLER_NEEDED)
// custom assert handler needed
MPT_NOINLINE void AssertHandler(const char *file, int line, const char *function, const char *expr, const char *msg=nullptr);
#endif // MPT_ASSERT_HANDLER_NEEDED



// Compile time assert.
#if (MPT_CXX >= 17)
#define MPT_STATIC_ASSERT static_assert
#else
#define MPT_STATIC_ASSERT(expr) static_assert((expr), "compile time assertion failed: " #expr)
#endif



#define MPT_CONSTEXPR11_ASSERT MPT_STATIC_ASSERT
#if MPT_CXX_AT_LEAST(14) && !MPT_MSVC_BEFORE(2017,5)
#define MPT_CONSTEXPR14_ASSERT MPT_STATIC_ASSERT
#else
#define MPT_CONSTEXPR14_ASSERT MPT_ASSERT
#endif
#if MPT_CXX_AT_LEAST(17) && !MPT_MSVC_BEFORE(2017,5)
#define MPT_CONSTEXPR17_ASSERT MPT_STATIC_ASSERT
#else
#define MPT_CONSTEXPR17_ASSERT MPT_ASSERT
#endif



// legacy
#define STATIC_ASSERT(x) MPT_STATIC_ASSERT(x)



OPENMPT_NAMESPACE_END
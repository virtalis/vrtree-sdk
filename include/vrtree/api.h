/*
MIT License

Copyright (c) 2018 Virtalis Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// VRTree C API Wrangler.
/// Include this header to use the C API.

#ifndef VRAPI_H
#define VRAPI_H

#ifndef EXTERN_C
#define VRTREE_EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif
#endif

#ifndef VRTREE_C_API
#ifdef vrtree_API
#define VRTREE_C_API EXTERN_C vrtree_API
#else
#ifdef _MSC_VER
#define VRTREE_C_API EXTERN_C __declspec(dllimport)
#else
#define VRTREE_C_API EXTERN_C __attribute__ ((__visibility__("default")))
#endif
#endif
#endif

#ifndef VRTREE_APIENTRY
#ifdef _MSC_VER
#define VRTREE_APIENTRY __cdecl
#else
#define VRTREE_APIENTRY
#endif
#endif

#ifndef VRTREE_API_VERSIONS
#define VRTREE_API_VERSIONS
const int VRTREE_API_VERSION_MAJOR =  1; //incremented if backward compatibility is broken
const int VRTREE_API_VERSION_MINOR = 12; //incremented if new exports are added
#endif

#include <stdint.h>
#include <stddef.h>
#include "vrtree_api_types.h"

#ifdef VRAPI_INTERNAL
#ifdef VRAPI_INTERNAL_PFN
#define VR_INTERNAL_PFN(name) InternalPFN##name name = __vrexport_##name
#else
#define VR_INTERNAL_PFN(name) extern InternalPFN##name name
#endif

#define VR_API(returnType, name, params)                       \
  VRTREE_C_API returnType VRTREE_APIENTRY __vrexport_##name params;   \
  namespace vrtree_internal_pfn {                              \
    typedef returnType (VRTREE_APIENTRY *InternalPFN##name) params;   \
    VR_INTERNAL_PFN(name);                                     \
  }

#include "vrtree_api.h"

#undef VR_INTERNAL_PFN

#else
#ifndef VR_API

#ifdef __cplusplus
namespace vrtree_internal_pfn {}
extern "C" {
#endif

/// Dynamic VRTree API loader allowing plugin forward and backward compatibility.
/// Any missing functions are substituted with stubs.
int loadVrtree(void);

/// @copybrief loadVrtree(void)
/// @param useDefaultStubs when non-zero, missing vrtree functions are substituted by stub functions
/// @param libPath when non-zero, loads the specific library specified instead of just "vrtree.dll".
/// This uses search paths such that the dll and its dependencies can exist in a completely different directory.
/// that allow the caller to use the function pointer as if it exists, but the function will always fail.
int loadVrtreeEx(int useDefaultStubs, const char* libPath);

/// Definition of VR_API for clients dynamically loading vrtree.dll, also defines the version for clients linking directly to the api.
#define VR_API(returnType, name, params)                      \
  VRTREE_C_API returnType VRTREE_APIENTRY __vrexport_##name params;  \
  typedef returnType (VRTREE_APIENTRY *pfn##name) params;            \
  extern pfn##name name
 
#include "vrtree_api.h"
 
#ifdef __cplusplus
}
#endif //__cplusplus

#else // VR_API

#include "vrtree_api.h"

#endif // VR_API

#endif //VRAPI_INTERNAL

#ifdef VRTREE_EXTERN_C
#undef EXTERN_C
#endif

#endif //VRAPI_H

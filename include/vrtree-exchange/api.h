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

#ifndef VREXCHANGE_API
#define VREXCHANGE_API

#ifndef EXTERN_C
#define VRTREE_EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif
#endif

#ifndef VREXCHANGE_C_API
#ifdef vrtree_exchange_API
#define VREXCHANGE_C_API EXTERN_C vrtree_exchange_API
#else
#ifdef _MSC_VER
#define VREXCHANGE_C_API EXTERN_C __declspec(dllimport)
#else
#define VREXCHANGE_C_API EXTERN_C __attribute__ ((__visibility__("default")))
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

const int VREXCHANGE_API_VERSION_MAJOR = 1; //incremented if backward compatibility is broken
const int VREXCHANGE_API_VERSION_MINOR = 1; //incremented if new exports are added

#include <stdint.h>
#include <stddef.h>
#include "../api/vrtree/vrtree_api_types.h"

#define VRX_API(returnType, name, params) VREXCHANGE_C_API returnType VRTREE_APIENTRY __vrexport_##name params;

/// @defgroup api_exchange VR Exchange
/// VR Exchange API functions
///
/// This API is used to directly interact with other installed importer and exporter plugins. 
/// @{

/// Gets the VRExchange API Major version.
///
/// This version represents backward compatibility. It should be checked when loading
/// the library, against an expected value. If it is not what is expected, 
/// the API may not function according to the expectations of the program using it.
/// @return major version
VRX_API(int, VRXGetAPIVersionMajor, (void));

/// Gets the VRExchange API Minor version.
///
/// This version number represents additions to the API and does not affect backward compatibility.
/// @return minor version
VRX_API(int, VRXGetAPIVersionMinor, (void));

/// Imports the specified file onto the specified scenes and libraries nodes.
/// @param file The file to import
/// @param scenes The root node to create assemblies on (e.g. scenes root)
/// @param libs The root node to create library assets on (e.g. libraries root)
/// @param importerName Hint to specify the name of the importer plugin to use. If not specified (null), 
/// attempts to determine a suitable importer using the file parameter's file extension
/// @return 1 if the import is successful, otherwise 0
VRX_API(uint32_t, VRXImport, (const char* file, HNode scenes, HNode libs, const char* importerName));

/// Imports and merges the specified file onto the specified scenes and libraries nodes utilising the merge options to append the import data.
/// @param file The file to import
/// @param scenes The root node to create assemblies on (e.g. scenes root)
/// @param libs The root node to create library assets on (e.g. libraries root)
/// @param mergeOptions If this node is set then the import merges results to existing nodes. This node contains the merge settings. If not specified (null), then imports as normal
/// @param importerName Hint to specify the name of the importer plugin to use. If not specified (null), 
/// attempts to determine a suitable importer using the file parameter's file extension
/// @return 1 if the import is successful, otherwise 0
VRX_API(uint32_t, VRXImportAndMerge, (const char* file, HNode scenes, HNode libs, HNode mergeOptions, const char* importerName));


/// Saves the specified scenes and libraries nodes to the specified file
/// @param file The file to export to
/// @param scenes The root node containing assemblies (e.g. scenes root)
/// @param libs The root node containing library assets (e.g. libraries root)
/// @param exporterName Hint to specify the name of the exporter plugin to use. If not specified (null), 
/// attempts to determine a suitable exporter using the file parameter's file extension
/// @return 1 if the export is successful, otherwise 0
VRX_API(uint32_t, VRXExport, (const char* file, HNode scenes, HNode libs, const char* exporterName));

/// @}

#endif
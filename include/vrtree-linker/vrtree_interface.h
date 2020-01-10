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

/// @file

#ifndef _VRTREE_INTERFACE_H_
#define _VRTREE_INTERFACE_H_

#include "../vrtree/vrtree_api_types.h"
#include <stdint.h>

/// @defgroup api_plugins Plugins
/// @{

#ifdef __cplusplus
extern "C" {
#endif

/// (vrtree-linker based plugins) wrapper around plugin API yield function.
/// the helper macro `VRPLUGIN_API_YIELDIMPL` will
/// define the plugin registration function and implement it
/// to provide the function pointer to this helper.
void progress_yield(int min, int max, const char* msg);

#ifdef __cplusplus
} //extern "C"
#endif

#ifdef _MSC_VER
  #define PLUGIN_ENTRY_POINT extern "C" __declspec(dllexport)
#else
  #define PLUGIN_ENTRY_POINT extern "C" __attribute__ ((__visibility__("default"))) ///< Plugin function exports macro
#endif

#ifndef VRTREE_APIENTRY
#define VRTREE_APIENTRY ///< Plugin function calling convention
#endif

/// @defgroup api_plugin_interface Plugin Interface
/// Defines an interface for plugins to implement in order to be loadable by VRTree
/// @{

const int PLUGIN_API_VERSION_MAJOR = 1; ///< incremented if backward compatibility is broken
const int PLUGIN_API_VERSION_MINOR = 3; ///< incremented if new exports are added

/// Function prototype for the API version functions.
///
/// Plugins should implement both `VRPGetAPIVersionMajor` and `VRPGetAPIVersionMinor` with this function signature.
/// @return Value of ::PLUGIN_API_VERSION_MAJOR for `VRPGetAPIVersionMajor`, Value of ::PLUGIN_API_VERSION_MINOR for `VRPGetAPIVersionMinor`
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code
/// PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPGetAPIVersionMajor()
/// {
///   return 1;
/// }
///
/// PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPGetAPIVersionMinor()
/// {
///   return 2;
/// }
/// @endcode
/// @note `vrtree-linker` provides ::VRPLUGIN_API_STDIMPL to implement these automatically
typedef int (VRTREE_APIENTRY *VRPGetAPIVersionProc)(void);

/// Function prototype for the plugin init function.
///
/// This function is called by the loader, after checking the major version and performing any other registration requested by the plugin.
/// This means that `VRPInit` may check permissions or write to the log, or do whatever else was registered.
/// @return 0 for success, any positive integer to fail and abort the plugin init
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code
/// PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPInit()
/// {
///   return 0; //success
/// }
/// @endcode
typedef int (VRTREE_APIENTRY *VRPInitProc)(void);

/// Function prototype for the plugin cleanup function.
///
/// This function is called by the loader, before unloading the plugin.
///
/// The plugin should implement this to remove any state added to VRTree during any other plugin functions.
/// @return 0 for success (not currently used)
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code
/// PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPCleanup()
/// {
///   return 0; //success
/// }
/// @endcode
typedef int (VRTREE_APIENTRY *VRPCleanupProc)(void);

/// Function prototype for an import function.
///
/// This function is passed a path to a file, and is expected to do some work with it
/// The implementation should respect the callers requests to import onto nodes that are not the default scenes/libs nodes
/// @param file absolute path to the file to be imported
/// @param root the root of the tree
/// @param scenes the scenes root node to import assembly data into
/// @param libs the library root node to import assets into
/// @param flags any additional flags that should be applied to nodes
/// @param recipePath absolute path to a recipe file describing advanced configuration
/// @return 0 on success
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPImport(const char* file, HNode root, HNode scenes, HNode libs, uint64_t flags, const char* recipe)
/// {
///   // create some nodes in the tree...
///   return 0; //success
/// }
/// @endcode
typedef int (VRTREE_APIENTRY *VRPImportProc)(const char* file, HNode root, HNode scenes, HNode libs, uint64_t flags, const char* recipePath);

/// Function prototype for an export function.
///
/// This function is passed a path to a file and some nodes and is expected to write data from the nodes to the file.
/// The implementation should respect the callers requests to export the specified nodes rather than the whole tree.
/// @param outFile absolute path to the output file (this will be the root file name in the case of multi-file output)
/// @param fromRoot the root of the tree
/// @param fromScenes the node in the scenes tree to start export from
/// @param fromLibs the node in the libs tree to start export from
/// @param recipePath absolute path to a recipe file describing advanced configuration
/// @return 0 on success
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPExport(const char* outFile, HNode fromRoot, HNode fromScenes, HNode fromLibs, const char* recipe)
/// {
///   // write some nodes to outFile...
///   return 0; //success
/// }
/// @endcode
typedef int (VRTREE_APIENTRY *VRPExportProc)(const char* outFile, HNode fromRoot, HNode fromScenes, HNode fromLibs, const char* recipePath);

/// Function prototype for getting the plugin short name (-import shortcut)
typedef const char* (VRTREE_APIENTRY *VRPShortNameProc)(void);

/// Function prototype for getting the plugin full name
/// @return The name of the plugin. Must be a valid string.
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// PLUGIN_ENTRY_POINT const char* VRTREE_APIENTRY VRPName()
/// {
///   return "My Plugin";
/// }
/// @endcode
/// @note All plugins are required to implement this function.
typedef const char* (VRTREE_APIENTRY *VRPNameProc)(void);

/// Function prototype for getting the plugin dependencies.
///
/// This defines the order which plugins are loaded, ensuring that any plugins that this one depends on
/// are loaded first.
/// @return Comma separated list of plugin names (either names reported by plugins, or their filenames without extension)
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// PLUGIN_ENTRY_POINT const char* VRTREE_APIENTRY VRPDepends()
/// {
///   return "Another Plugin Name, anotherpluginfile"; // first by name, second by file
/// }
typedef const char* (VRTREE_APIENTRY *VRPDependsProc)(void);

/// Function prototype for getting the FFI namespace/module name to use for this plugin.
///
/// This specifies the namespace to use for registered FFI functions. For a plugin with ffi namespace
/// "MyPlugin" and a registered FFI function "foo", it will be accessible in lua as MyPlugin.foo()
/// If the specified namespace is already in use by another loaded plugin it will be ignored.
/// If this is blank, the namespace will be inferred from VRPName() or the module name.
/// @return Lua-safe ffi module name (letters, numbers and underscores, not beginning with a digit)
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// PLUGIN_ENTRY_POINT const char* VRTREE_APIENTRY VRPFFINamespace()
/// {
///   return "MyPlugin";
/// }
typedef const char* (VRTREE_APIENTRY *VRPFFINamespaceProc)(void);

/// Function prototype for getting the plugin signature (license)
/// @return The license text string provided by Virtalis
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// PLUGIN_ENTRY_POINT const char* VRTREE_APIENTRY VRPSignature()
/// {
///   return "<some signature signed xml>";
/// }
/// @endcode
/// @note Plugins that require access to the VRTree C API must implement this function.
typedef const char* (VRTREE_APIENTRY *VRPSignatureProc)(void);

/// Function prototype for getting the plugin version (human readable, not API version)
/// @return The version string (e.g. "1.0.5"). Must be a valid string.
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// PLUGIN_ENTRY_POINT const char* VRTREE_APIENTRY VRPVersion()
/// {
///   return "1.0.3a";
/// }
/// @endcode
/// @note All plugins are required to implement this function.
typedef const char* (VRTREE_APIENTRY *VRPVersionProc)(void);

/// Function prototype for getting the plugin lock condition
/// @return The lock condition.
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// PLUGIN_ENTRY_POINT const char* VRTREE_APIENTRY VRPLocked()
/// {
///   return true;
/// }
/// @endcode
typedef const char* (VRTREE_APIENTRY *VRPLockedProc)(void);

/// Function prototype for getting the XML description of formats accepted by ::VRPImportProc
/// @return XML document describing the accepted formats
/// @par Schema
/// @code{.xml}
/// <xs:schema attributeFormDefault="unqualified" elementFormDefault="qualified" xmlns:xs="http://www.w3.org/2001/XMLSchema">
///   <xs:element name="filetypes">
///     <xs:complexType>
///       <xs:sequence>
///         <xs:element name="type" maxOccurs="unbounded" minOccurs="1">
///           <xs:complexType>
///             <xs:simpleContent>
///               <xs:extension base="xs:string">
///                 <xs:attribute type="xs:string" name="ext" use="required"/>
///                 <xs:attribute type="xs:string" name="desc" use="required"/>
///               </xs:extension>
///             </xs:simpleContent>
///           </xs:complexType>
///         </xs:element>
///       </xs:sequence>
///     </xs:complexType>
///   </xs:element>
/// </xs:schema>
/// @endcode
/// @par Example
/// @pre groupedcode
/// C / C++{cpp}
/// @code{.cpp}
/// PLUGIN_ENTRY_POINT const char* VRTREE_APIENTRY VRPFormats()
/// {
///   return "<filetypes> \
///     <type ext=\"txt\" desc=\"Text File\" /> \
///   </filetypes>";
/// }
/// @endcode
/// XML{xml}
/// @code{.xml}
/// <filetypes>
///   <type ext="txt" desc="Text File" />
/// </filetypes>
/// @endcode
typedef const char* (VRTREE_APIENTRY *VRPFormatsProc)(void);

/// Function prototype for getting the XML description of the settings that should be 
/// presented in a user interface.
/// @return XML document describing the settings
/// @par Schema
/// @code{.xml}
/// <xs:schema attributeFormDefault="unqualified" elementFormDefault="qualified" xmlns:xs="http://www.w3.org/2001/XMLSchema">
///   <xs:element name="recipe">
///     <xs:complexType>
///       <xs:sequence>
///         <xs:element name="Page" maxOccurs="unbounded" minOccurs="0">
///           <xs:complexType mixed="true">
///             <xs:choice maxOccurs="unbounded" minOccurs="0">
///               <xs:element name="StringEdit">
///                 <xs:complexType>
///                   <xs:simpleContent>
///                     <xs:extension base="xs:string">
///                       <xs:attribute type="xs:string" name="label" use="optional"/>
///                       <xs:attribute type="xs:string" name="name" use="optional"/>
///                       <xs:attribute type="xs:string" name="value" use="optional"/>
///                       <xs:attribute type="xs:string" name="readonly" use="optional"/>
///                       <xs:attribute type="xs:string" name="desc" use="optional"/>
///                     </xs:extension>
///                   </xs:simpleContent>
///                 </xs:complexType>
///               </xs:element>
///               <xs:element name="IntBox">
///                 <xs:complexType>
///                   <xs:simpleContent>
///                     <xs:extension base="xs:string">
///                       <xs:attribute type="xs:string" name="label"/>
///                       <xs:attribute type="xs:string" name="name"/>
///                       <xs:attribute type="xs:byte" name="value"/>
///                       <xs:attribute type="xs:byte" name="min"/>
///                       <xs:attribute type="xs:byte" name="max"/>
///                       <xs:attribute type="xs:string" name="desc"/>
///                     </xs:extension>
///                   </xs:simpleContent>
///                 </xs:complexType>
///               </xs:element>
///               <xs:element name="Selection">
///                 <xs:complexType>
///                   <xs:simpleContent>
///                     <xs:extension base="xs:string">
///                       <xs:attribute type="xs:string" name="label" use="optional"/>
///                       <xs:attribute type="xs:string" name="name" use="optional"/>
///                       <xs:attribute type="xs:string" name="value" use="optional"/>
///                       <xs:attribute type="xs:string" name="options" use="optional"/>
///                       <xs:attribute type="xs:string" name="desc" use="optional"/>
///                     </xs:extension>
///                   </xs:simpleContent>
///                 </xs:complexType>
///               </xs:element>
///               <xs:element name="Check">
///                 <xs:complexType>
///                   <xs:simpleContent>
///                     <xs:extension base="xs:string">
///                       <xs:attribute type="xs:string" name="label" use="optional"/>
///                       <xs:attribute type="xs:string" name="name" use="optional"/>
///                       <xs:attribute type="xs:byte" name="value" use="optional"/>
///                       <xs:attribute type="xs:string" name="desc" use="optional"/>
///                     </xs:extension>
///                   </xs:simpleContent>
///                 </xs:complexType>
///               </xs:element>
///               <xs:element name="FloatBox">
///                 <xs:complexType>
///                   <xs:simpleContent>
///                     <xs:extension base="xs:string">
///                       <xs:attribute type="xs:string" name="label" use="optional"/>
///                       <xs:attribute type="xs:string" name="name" use="optional"/>
///                       <xs:attribute type="xs:float" name="value" use="optional"/>
///                       <xs:attribute type="xs:float" name="min" use="optional"/>
///                       <xs:attribute type="xs:float" name="max" use="optional"/>
///                       <xs:attribute type="xs:string" name="desc" use="optional"/>
///                     </xs:extension>
///                   </xs:simpleContent>
///                 </xs:complexType>
///               </xs:element>
///             </xs:choice>
///             <xs:attribute type="xs:string" name="name" use="optional"/>
///           </xs:complexType>
///         </xs:element>
///       </xs:sequence>
///     </xs:complexType>
///   </xs:element>
/// </xs:schema>
/// @endcode
/// @par Example
/// @pre groupedcode
/// C / C++{cpp}
/// @code{.cpp}
/// PLUGIN_ENTRY_POINT const char* VRTREE_APIENTRY VRPSettingsInterface()
/// {
///   return "<recipe> \
///     <Page name=\"Basic\"> \
///       <IntBox label=\"Log Level\" name=\"loglevel\" value=\"0\" min=\"0\" max=\"4\" desc=\"Set log level\"/> \
///       <Selection label=\"Unit\" name=\"vrUnit\" value=\"meters\" options=\"meters,milimeters,centimeters\" desc=\"Unit of values in the file\"/> \
///     </Page> \
///   </recipe>";
/// }
/// @endcode
/// XML{xml}
/// @code{.xml}
/// <recipe>
///   <Page name="Basic">
///     <IntBox label="Log Level" name="loglevel" value="0" min="0" max="4" desc="Set log level"/> 
///     <Selection label="Unit" name="vrUnit" value="meters" options="meters,milimeters,centimeters" desc="Unit of values in the file"/> 
///   </Page>
/// </recipe>
/// @endcode
typedef const char* (VRTREE_APIENTRY *VRPSettingsInterfaceProc)(void);

/// Function prototype for getting the name of the default recipe file used by the importer
/// @return A name of a recipe file to use as the default name (e.g. "myrecipe.vrcp")
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// PLUGIN_ENTRY_POINT const char* VRTREE_APIENTRY VRPDefaultRecipe()
/// {
///   return "myRecipe.vrcp";
/// }
/// PLUGIN_ENTRY_POINT const char* VRTREE_APIENTRY VRPExportDefaultRecipe()
/// {
///   return "myExportRecipe.vrcp";
/// }
/// @endcode
/// @note Any plugin implementing import or export functionality must provide this function as `VRPDefaultRecipe` for importers, and `VRPExportDefaultRecipe` for exporters
typedef const char* (VRTREE_APIENTRY *VRPDefaultRecipeProc)(void);

/// Function prototype for the log function.
///
/// Plugin will be passed a log function to use for logging, if it exports ::VRPRegisterLogProc.
/// @param type type of message:
///  - 0 = Info
///  - 1 = Warning
///  - 2 = Error
///  - 3 = Debug
/// @param message the text to write to the log
typedef void (VRTREE_APIENTRY *VRPLogProc)(int type, const char* message);

/// Function prototype for the log indent function.
///
/// Some log messages need to have more complex formatting, so plugins can use this function to indent all further log messages.
/// Plugin will be passed a log indent function to use for logging, if it exports ::VRPRegisterLogIndentProc.
/// @param indent boolean for increasing or decreasing indent. Pass 0 to decrease indent, any positive value to increase indent.
typedef void (VRTREE_APIENTRY *VRPLogIndentProc)(char indent);

/// Function prototype for being given a log function.
///
/// Plugin should implement this and store the pointer it is given, if it wishes to log to the application log.
/// To write a log message, the plugin should call the provided log function directly
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// static VRPLogProc s_logFunc = 0;
/// 
/// PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterLog(VRPLogProc proc) 
/// {
///   s_logFunc = proc;
/// }
/// 
/// PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPInit()
/// {
///   if(s_logFunc)
///     s_logFunc(2, "This is an error message\n");
/// }
/// @endcode
/// @note `vrtree-linker` provides ::VRPLUGIN_API_LOGIMPL to provide `s_logFunc` and `s_logIndentFunc`
typedef void (VRTREE_APIENTRY *VRPRegisterLogProc)(VRPLogProc);

/// Function prototype for being given a log indent function.
///
/// Plugin should implement this and store the pointer it is given, if it wishes to make use of the log indent functionality.
///
/// The indent levels should match (e.g. if you indent twice, you should unindent twice, too)
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// static VRPLogProc s_logFunc = 0;
/// static VRPLogIndentProc s_logIndentFunc = 0;
/// 
/// PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterLog(VRPLogProc proc) 
/// {
///   s_logFunc = proc;
/// }
///
/// PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterLogIndent(VRPLogIndentProc proc) 
/// {
///   s_logIndentFunc = proc;
/// }
/// 
/// PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPInit()
/// {
///   if(s_logFunc && s_logIndentFunc) {
///     s_logIndentFunc(1);
///     s_logFunc(2, "This is an INDENTED error message\n");
///     s_logIndentFunc(1);
///     s_logFunc(2, "This is a 2-deep indented error message\n");
///     s_logIndentFunc(0);
///     s_logIndentFunc(0);
///   }
/// }
/// @endcode
/// @note `vrtree-linker` provides ::VRPLUGIN_API_LOGIMPL to provide `s_logFunc` and `s_logIndentFunc`
typedef void (VRTREE_APIENTRY *VRPRegisterLogIndentProc)(VRPLogIndentProc);

/// Function prototype for triggering an application dialog containing a message to present directly to the user.
///
/// Plugin will be passed a message function to use if it exports ::VRPRegisterUserMessageProc
/// @param message the message to display to the user
/// @note Since this is a modal dialog, execution of the calling thread may be blocked until the box is dismissed. 
/// This does not happen when running on a cluster, so blocking behaviour should not be depended on. Plugins should avoid calling this during `VRPInit` and `VRPCleanup`.
typedef void (VRTREE_APIENTRY *VRPUserMessageProc)(const char* message);

/// Function prototype for triggering an application dialog containing a question to ask to the user. This also requires a registered ::VRPUserQuestionCallbackProc
///
/// Plugin will be passed a question function to use if it exports ::VRPRegisterUserQuestionProc
/// @param message the message to display to the user (phrased as a question)
/// @return 0 if question is submitted, 1 if there is no registered question callback to receive the user's answer
/// @note Since this is a modal dialog, execution of the calling thread may be blocked until the box is dismissed. 
/// This does not happen when running on a cluster, so blocking behaviour should not be depended on. Plugins should avoid calling this during `VRPInit` and `VRPCleanup`
typedef int (VRTREE_APIENTRY *VRPUserQuestionProc)(const char* message);

/// Function prototype for a callback to call when a user chooses an option presented by a UserQuestion.
/// @param result the index of the option selected
typedef void (VRTREE_APIENTRY *VRPUserQuestionCallbackProc)(int result, void* userData);

/// Function prototype for registering a ::VRPUserQuestionCallbackProc as the callback for UserQuestion dialogs.
///
/// Plugin will be passed a register function if it exports ::VRPRegisterUserQuestionCallbackProc
typedef void (VRTREE_APIENTRY *VRPUserQuestionCallbackRegisterProc)(VRPUserQuestionCallbackProc proc, void* userData);

/// Function prototype for registering a message function.
///
/// Plugin should implement this and store the pointer it is given, if it wishes to summon message boxes.
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// //This example registers a Lua function which, when called from Lua, summons a message box
/// static VRPUserMessageProc s_msgProc = 0;
/// 
/// PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterUserMessage(VRPUserMessageProc proc)
/// {
///   s_msgProc = proc;
/// }
///
/// static HFFIVar msg_func(int argc, HFFIVar* argv, void*) {
///   if(s_msgProc)
///     s_msgProc("Hello, this is a message box");
///   return 0;
/// }
///
/// PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPInit()
/// {
///   //...
///   // Registers msg_func as Lua function "helloMessage"
///   VRFFIRegister("helloMessage", &msg_func, 0, 0);
/// }
/// @endcode
typedef void (VRTREE_APIENTRY *VRPRegisterUserMessageProc)(VRPUserMessageProc);

/// Function prototype for registering a question callback function.
///
/// Plugin should implement this and use the pointer it is given to register a callback to be called by question boxes summoned by a ::VRPUserQuestionProc
///
/// This is not useful without also implementing ::VRPRegisterUserQuestionCallbackProc
typedef void (VRTREE_APIENTRY *VRPRegisterUserQuestionCallbackProc)(VRPUserQuestionCallbackRegisterProc);

/// Function prototype for registering a question function.
///
/// Plugin should implement this and store the pointer it is given, if it wishes to summon question boxes.
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// //This example registers a Lua function which, when called from Lua, summons a question box
/// static VRPUserQuestionProc s_qProc = 0;
/// static void question_callback(int result, void* userData) {
///    //result is the option the user chose
/// }
///
/// PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterUserQuestionCallback(VRPUserQuestionCallbackProc proc)
/// {
///   proc(&question_callback, 0); //register our callback proc.
///   // we could also store proc and register different functions for different questions
/// }
/// 
/// PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterUserQuestion(VRPUserQuestionProc proc)
/// {
///   s_qProc = proc;
/// }
///
/// static HFFIVar question_func(int argc, HFFIVar* argv, void*) {
///   if(s_qProc) {
///     s_qProc("Is this a dialog box?"); //user input on this dialog calls question_callback
///   }
///   return 0;
/// }
///
///
/// PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPInit()
/// {
///   //...
///   // Registers question_func as Lua function "askQuestion"
///   VRFFIRegister("askQuestion", &question_func, 0, 0);
/// }
/// @endcode
typedef void (VRTREE_APIENTRY *VRPRegisterUserQuestionProc)(VRPUserQuestionProc);

/// Function prototypes for a progress yield function.
///
/// Plugin will be passed a yield function to call during long operations,
/// if it exports the ::VRPRegisterProgressYieldProc function.
/// @param currentValue the current progress through the operation, if greater than zero will be represented by a progress bar
/// @param maxValue the maximum progress value, if greater than zero will be represented by the end of the progress bar
/// @param message the message to set on the progress display. If 0, the message does not change from whatever is already there.
/// @note The plugin execution will be blocked by calls to yield, until the application returns control to it.
typedef void(VRTREE_APIENTRY *VRPProgressYieldProc)(int currentValue, int maxValue, const char* message);

/// Function prototype for registering a progress yield function.
///
/// Plugin should implement this and store the pointer it is given, if it wishes to yield to the application during long operations.
/// @par Example
/// @pre groupedcode
/// C / C++
/// @code{.cpp}
/// static VRPProgressYieldProc s_progress = 0;
///
/// PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterProgressYield(VRPProgressYieldProc proc)
/// {
///   s_progress = proc;
/// }
///
/// PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPImport(const char* file, HNode root, HNode scenes, HNode libs, uint64_t flags, const char* recipe)
/// {
///   // create some nodes in the tree...
///   s_progress(0, nObjects, "Importing file...");
///   for(int i = 0; i < nObjects ++i) {
///     doLongImport(objects[i]);
///     s_progress(i, nObjects, 0);
///   }
///   return 0; //success
/// }
/// @endcode
/// @note `vrtree-linker` provides ::VRPLUGIN_API_YIELDIMPL to provide progress_yield
typedef void (VRTREE_APIENTRY *VRPRegisterProgressYieldProc)(VRPProgressYieldProc);

/// Function prototype for checking permission to do something.
/// Plugin will be passed a check function if it exports ::VRPRegisterHasPermissionProc.
///
/// This mainly corresponds to VRTree permissions - the plugin may check for
/// permissions (such as EditScript), and it may request permissions be obtained
/// from the licensing mechanism.
/// @param permissions comma-separated list of permission names to request. When specifying more than one, all are required for the check to pass.
/// @return 1 if the check is successful
typedef int (VRTREE_APIENTRY *VRPHasPermissionProc)(const char* permissions);

/// Function prototype for requesting permission to do something.
///
/// Plugin will be passed a request function if it exports ::VRPRegisterRequestPermissionProc
/// @param permissions comma-separated list of permission names to request. When specifying more than one, all are required for the check to pass.
/// @param cancelCaption optional caption to display on the cancel button of any license request dialog presented by the application to fulfil the request.
/// @return 1 if the request is successful
typedef int (VRTREE_APIENTRY *VRPRequestPermissionProc)(const char* permissions, const char* cancelCaption);

/// Function prototype for registering a permission check function.
///
/// Plugin should implement this and store the pointer it is given, if it wants to do license checks
/// @note `vrtree-linker` provides ::VRPLUGIN_API_PERMISSIONIMPL to provide ::VRPLUGIN_INIT_PERMISSION and ::VRPLUGIN_IMPORT_PERMISSION
typedef void (VRTREE_APIENTRY *VRPRegisterHasPermissionProc)(VRPHasPermissionProc);

/// Function prototype for registering a permission request function.
///
/// Plugin should implement this and store the pointer it is given, if it wants to do license requests
/// @note `vrtree-linker` provides ::VRPLUGIN_API_PERMISSIONIMPL to provide ::VRPLUGIN_INIT_PERMISSION and ::VRPLUGIN_IMPORT_PERMISSION
typedef void (VRTREE_APIENTRY *VRPRegisterRequestPermissionProc)(VRPRequestPermissionProc);

/// @}

/// @defgroup api_plugin_utils Plugin Utilities
/// Utilities to assist in plugin authoring, provided by the `vrtree-linker` library
/// @{

#define LOG_DEBUG 3 ///< Type passed to a ::VRPLogProc for debug messages
#define LOG_INFO 0 ///< Type passed to a ::VRPLogProc for info (standard) messages
#define LOG_WARN 1 ///< Type passed to a ::VRPLogProc for warning messages
#define LOG_ERROR 2 ///< Type passed to a ::VRPLogProc for error messages

#ifdef __cplusplus
extern "C" {
#endif
/// Internal implementation of @ref VRPProgressYieldProc "VRProgressYield" which stores the progress function and exposes it
/// via ::progress_yield
void registerYield(VRPProgressYieldProc proc);
#ifdef __cplusplus
}
#endif

/// Implements the major and minor version query functions
#define VRPLUGIN_API_STDIMPL                                            \
  PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPGetAPIVersionMajor() { return PLUGIN_API_VERSION_MAJOR; } \
  PLUGIN_ENTRY_POINT int VRTREE_APIENTRY VRPGetAPIVersionMinor() { return PLUGIN_API_VERSION_MINOR; }

/// Implements the log registration functions and provides static variables to store the registered log functions,
/// `s_logFunc` and `s_logIndentFunc`
#define VRPLUGIN_API_LOGIMPL                                            \
  static VRPLogProc s_logFunc = NULL;                                   \
  PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterLog(VRPLogProc proc) { s_logFunc = proc; } \
  static VRPLogIndentProc s_logIndentFunc = NULL;                       \
  PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterLogIndent(VRPLogIndentProc proc) { s_logIndentFunc = proc; }

/// Implements permission registration functions and provides static variables to store the registered permission functions,
/// `s_hasPermissionFunc` and `s_reqPermissionFunc`
#define VRPLUGIN_API_PERMISSIONIMPL                                     \
  static VRPHasPermissionProc s_hasPermissionFunc = NULL;               \
  PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterHasPermission(VRPHasPermissionProc proc) { s_hasPermissionFunc = proc; } \
  static VRPRequestPermissionProc s_reqPermissionFunc = NULL;           \
  PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterRequestPermission(VRPRequestPermissionProc proc) { s_reqPermissionFunc = proc; }

/// Helper macro that checks the existence of the registered ::VRPHasPermissionProc and calls it.
/// Inserts a `return 1` on failure, so should be used in a function that returns an int.
#define VRPLUGIN_INIT_PERMISSION(NAME)            \
  if(!s_hasPermissionFunc) return 1; \
  s_hasPermissionFunc(NAME)

/// Helper macro that checks and calls the registered ::VRPRequestPermissionProc to trigger an application
/// license check. Inserts a `return 1` on failure, so should be used in a function that returns an int.
#define VRPLUGIN_IMPORT_PERMISSION(NAME)                      \
  if(!s_reqPermissionFunc || s_reqPermissionFunc(NAME, "Cancel Import") == 0) \
    return 1

#ifdef VIRTALIS_FORCE_STATIC_LIBS
#define VRPLUGIN_INJECT_CORE_LOG                \
  vtCore::g_logPrintFunc = s_logFunc;           \
  vtCore::g_logIndentFunc = s_logIndentFunc
#define VRPLUGIN_INJECT_CORE_YIELD                     \
  vtCore::OpProgress().SigYield.connect(progress_yield);
#else //do not inject when linking dynamically!
#define VRPLUGIN_INJECT_CORE_LOG ///< Internal use for Virtalis plugins
#define VRPLUGIN_INJECT_CORE_YIELD ///< Internal use for Virtalis plugins
#endif

/// Implements progress yield registration function and wraps it in ::progress_yield
#define VRPLUGIN_API_YIELDIMPL                  \
  PLUGIN_ENTRY_POINT void VRTREE_APIENTRY VRPRegisterProgressYield(VRPProgressYieldProc proc) { registerYield(proc); }

/// Loads all the VRTree C API entry points
#define VRPLUGIN_LOADVRTREE {                   \
  int ret = loadVrtree();                       \
  if(ret != 0)                                  \
    return ret; }

/// Combines all helper impl macros
#define VRPLUGIN_API_IMPL    \
  VRPLUGIN_API_STDIMPL;      \
  VRPLUGIN_API_LOGIMPL;      \
  VRPLUGIN_API_YIELDIMPL;    \
  VRPLUGIN_API_PERMISSIONIMPL

/// @}

#endif

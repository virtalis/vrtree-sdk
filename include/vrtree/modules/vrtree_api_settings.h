/*
MIT License

Copyright (c) 2018 Virtalis Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
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

#ifndef VRAPI_H
#error api.h must be included before this file
#endif

/// @defgroup api_settings Settings
/// Functions for accessing settings
/// @{

/// Creates a boolean setting if it doesn't already exist
/// @param path the path from the root of the settings hierarchy
/// @param defaultValue the value to set if the setting didn't already exist
/// @return 0 if the setting was created or already existed, or 1 on failure
VR_API (int, VRCreateSettingBool, (const char* path, char defaultValue));

/// Creates an integer setting if it doesn't already exist
/// @param path the path from the root of the settings hierarchy
/// @param defaultValue the value to set if the setting didn't already exist
/// @return 0 if the setting was created or already existed, or 1 on failure
VR_API (int, VRCreateSettingInt, (const char* path, int defaultValue));

/// Creates an integer array setting if it doesn't already exist
/// @param path the path from the root of the settings hierarchy
/// @param count the number of elements in the array (may be 2, 3 or 4)
/// @param defaultValue the value to set if the setting didn't already exist
/// @return 0 if the setting was created or already existed, or 1 on failure
VR_API (int, VRCreateSettingArrayInt, (const char* path, size_t count, const int* defaultValues));

/// Creates a float setting if it doesn't already exist
/// @param path the path from the root of the settings hierarchy
/// @param defaultValue the value to set if the setting didn't already exist
/// @return 0 if the setting was created or already existed, or 1 on failure
VR_API (int, VRCreateSettingFloat, (const char* path, float defaultValue));

/// Creates a float array setting if it doesn't already exist
/// @param path the path from the root of the settings hierarchy
/// @param count the number of elements in the array (may be 2, 3, 4, 9 or 16)
/// @param defaultValue the value to set if the setting didn't already exist
/// @return 0 if the setting was created or already existed, or 1 on failure
VR_API (int, VRCreateSettingArrayFloat, (const char* path, size_t count, const float* defaultValues));

/// Creates a double setting if it doesn't already exist
/// @param path the path from the root of the settings hierarchy
/// @param defaultValue the value to set if the setting didn't already exist
/// @return 0 if the setting was created or already existed, or 1 on failure
VR_API (int, VRCreateSettingDouble, (const char* path, double defaultValue));

/// Creates a double array setting if it doesn't already exist
/// @param path the path from the root of the settings hierarchy
/// @param count the number of elements in the array (may be 2, 3, 4, 9 or 16)
/// @param defaultValue the value to set if the setting didn't already exist
/// @return 0 if the setting was created or already existed, or 1 on failure
VR_API (int, VRCreateSettingArrayDouble, (const char* path, size_t count, const double* defaultValues));

/// Creates a string setting if it doesn't already exist
/// @param path the path from the root of the settings hierarchy
/// @param defaultValue the value to set if the setting didn't already exist
/// @return 0 if the setting was created or already existed, or 1 on failure
VR_API (int, VRCreateSettingString, (const char* path, const char* defaultValue));

/// Creates a link setting if it doesn't already exist
/// @param path the path from the root of the settings hierarchy
/// @param defaultValue the value to set if the setting didn't already exist
/// @return 0 if the setting was created or already existed, or 1 on failure
VR_API (int, VRCreateSettingLink, (const char* path));

/// Assigns a custom caption to a setting, allowing the text displayed to in user interface to be different from the setting name
/// @param path the path from the root of the settings hierarchy
/// @param caption the caption to be displayed in the user interface
/// @return 0 on success, 1 on failure
VR_API (int, VRSetSettingCaption, (const char* path, const char* caption));

/// Assigns a range to a numeric setting
/// @param path the path from the root of the settings hierarchy
/// @param minValue the minimum allowable value
/// @param maxValue the maxumum allowable value
VR_API (int, VRSetSettingRange, (const char* path, double minValue, double maxValue));

/// Assigns a step size to a numeric setting
/// @param path the path from the root of the settings hierarchy
/// @param step the step size
VR_API (int, VRSetSettingStep, (const char* path, double step));

/// Assigns a type to a setting, which determines how the setting is presented in the user interface.
/// The types that can be assigned depend on the data type of the setting:
/// 
/// Data type                             | Valid type names
/// --------------------------------------|-------------------------------------------------------------------
/// string                                | image, file, filesave, stream, dir, font, password, singlelinetext
/// int/float/double                      | slider, logslider, log2slider, collisiongroupmask
/// float array (3 or 4 elements)         | colour
/// int/float/double array (4 elements)   | rect, sphere
/// int/float/double array (16 elements)  | matrix, 2dmatrix
/// 
/// @param path the path from the root of the settings hierarchy
/// @param type the type name
VR_API (int, VRSetSettingType, (const char* path, const char* type));

/// Assigns a filter to a setting. The meaning of the filter depends on the setting type:
///
/// Setting type                                      | Filter meaning
/// --------------------------------------------------| -----------------------------------------------------------------------------------------------------------------------------------------------
/// string with type "file", "filesave" or "stream"   | List of allowable file extensions specified as pairs of strings separated by \|, e.g. "Text files&#124;*.txt&#124;HTML files&#124;*.htm;*.html"
/// link                                              | List of allowable node types separated by commas, e.g. "StdMaterial,Texture"
/// 
/// @param path the path from the root of the settings hierarchy
/// @param type the filter to assign
VR_API (int, VRSetSettingFilter, (const char* path, const char* filter));

/// Returns the number of bytes required to store a setting's value. For string settings, this includes the terminating null character.
/// @param path the path from the root of the settings hierarchy
/// @return the size of the value in bytes, or 0 on failure
VR_API (size_t, VRGetSettingSize, (const char* path));

/// Reads a boolean setting
/// @param path the path from the root of the settings hierarchy
/// @return the setting value, or 0 on failure
VR_API (char, VRReadSettingBool, (const char* path));

/// Reads an int setting
/// @param path the path from the root of the settings hierarchy
/// @return the setting value, or 0 on failure
VR_API (int, VRReadSettingInt, (const char* path));

/// Reads an int array setting
/// @param path the path from the root of the settings hierarchy
/// @param values pointer to a buffer to receive the data
/// @param count the size of the buffer (number of int elements)
/// @return the number of values written to the buffer
VR_API (size_t, VRReadSettingArrayInt, (const char* path, int* values, size_t count));

/// Reads a float setting
/// @param path the path from the root of the settings hierarchy
/// @return the setting value, or 0 on failure
VR_API (float, VRReadSettingFloat, (const char* path));

/// Reads a float array setting
/// @param path the path from the root of the settings hierarchy
/// @param values pointer to a buffer to receive the data
/// @param count the size of the buffer (number of float elements)
/// @return the number of values written to the buffer
VR_API (size_t, VRReadSettingArrayFloat, (const char* path, float* values, size_t count));

/// Reads a double setting
/// @param path the path from the root of the settings hierarchy
/// @return the setting value, or 0 on failure
VR_API (double, VRReadSettingDouble, (const char* path));

/// Reads a double array setting
/// @param path the path from the root of the settings hierarchy
/// @param values pointer to a buffer to receive the data
/// @param count the size of the buffer (number of double elements)
/// @return the number of values written to the buffer
VR_API (size_t, VRReadSettingArrayDouble, (const char* path, double* values, size_t count));

/// Reads a string setting
/// @param path the path from the root of the settings hierarchy
/// @param buffer pointer to buffer to receive the string data
/// @param bufferSize the size of the buffer
/// @return the number of bytes written to the buffer
/// @note if buffer is null, the function returns the required size of the buffer
VR_API (size_t, VRReadSettingString, (const char* path, char* buffer, size_t bufferSize));

/// Reads a link setting
/// @param path the path from the root of the settings hierarchy
/// @return the setting value, or 0 on failure
VR_API (HNode, VRReadSettingLink, (const char* path));

/// Sets the value of a boolean setting
/// @param path the path from the root of the settings hierarchy
/// @param value the value to set
/// @return 0 on success, 1 on failure
VR_API (int, VRWriteSettingBool, (const char* path, char value));

/// Sets the value of an int setting
/// @param path the path from the root of the settings hierarchy
/// @param value the value to set
/// @return 0 on success, 1 on failure
VR_API (int, VRWriteSettingInt, (const char* path, int value));

/// Sets the value of an int array setting
/// @param path the path from the root of the settings hierarchy
/// @param values the values to set
/// @param count the number of values
/// @return 0 on success, 1 on failure
VR_API (int, VRWriteSettingArrayInt, (const char* path, const int* values, size_t count));

/// Sets the value of a float setting
/// @param path the path from the root of the settings hierarchy
/// @param value the value to set
/// @return 0 on success, 1 on failure
VR_API (int, VRWriteSettingFloat, (const char* path, float value));

/// Sets the value of a float array setting
/// @param path the path from the root of the settings hierarchy
/// @param values the values to set
/// @param count the number of values
/// @return 0 on success, 1 on failure
VR_API (int, VRWriteSettingArrayFloat, (const char* path, const float* values, size_t count));

/// Sets the value of a double setting
/// @param path the path from the root of the settings hierarchy
/// @param value the value to set
/// @return 0 on success, 1 on failure
VR_API (int, VRWriteSettingDouble, (const char* path, double value));

/// Sets the value of a double array setting
/// @param path the path from the root of the settings hierarchy
/// @param values the values to set
/// @param count the number of values
/// @return 0 on success, 1 on failure
VR_API (int, VRWriteSettingArrayDouble, (const char* path, const double* values, size_t count));

/// Sets the value of a string setting
/// @param path the path from the root of the settings hierarchy
/// @param  the value to set
/// @return 0 on success, 1 on failure
VR_API (int, VRWriteSettingString, (const char* path, const char* value));

/// Sets the value of a link setting
/// @param path the path from the root of the settings hierarchy
/// @param value the value to set
/// @return 0 on success, 1 on failure
VR_API (int, VRWriteSettingLink, (const char* path, HNode value));

/// Gets the VRTree node associated with a setting. If the setting has a scene override, the override node is returned; otherwise, the user setting node is returned.
/// @param path the path from the root of the settings hierarchy
/// @return the VRTree node currently associated with the setting
VR_API (HNode, VRGetSettingNode, (const char* path));

/// Gets the VRTree node associated with the root of the settings hierarchy
/// @return the VRTree node associated with the root of the settings hierarchy
VR_API (HNode, VRGetRootSettingNode, ());

/// Gets the VRTree node associated with the root of the scene overrides, if present
/// @return the VRTree node associated with the root of the scene overrides, or 0 if no overrides are present
VR_API (HNode, VRGetSceneRootSettingNode, ());

/// Adds a scene override of a setting (if it doesn't already exist) and copies the value from the user setting to the override
/// @param path the path from the root of the settings hierarchy
/// @return 0 if an override was added or already present, or 1 on failure
VR_API (int, VRAddSettingToScene, (const char* path));

/// Removes a scene override of a setting
/// @param path the path from the root of the settings hierarchy
/// @return 0 on success, 1 on failure
VR_API (int, VRRemoveSettingFromScene, (const char* path));

/// Registers a function to be called when a setting value changes
/// @param path the path from the root of the settings hierarchy
/// @param func the function to be called
/// @param userData an arbitrary value to be passed to the callback function
/// @return 0 on success, 1 on failure
VR_API (int, VRAddCallbackSettingChanged, (const char* path, SettingChangedFunc func, void* userData));

/// Removes a callback that was added with VRAddCallbackSettingChanged()
/// @param path the path from the root of the settings hierarchy
/// @param func the callback function
/// @return 0 on success, 1 on failure
VR_API (int, VRRemoveCallbackSettingChanged, (const char* path, SettingChangedFunc func));

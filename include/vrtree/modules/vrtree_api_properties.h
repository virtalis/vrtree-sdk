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

/// @defgroup api_properties Properties
/// Functions for accessing node @ref properties
/// @{

/// Gets a reusable property handle.
/// Even though this uses a node handle to get a property index, the property index
/// can still be used to interact with the property on any instance of the metanode.
/// (not just this single instance of node)
/// @see VRGetProperty(nodePropName)
/// @param node handle to node to use for its metanode
/// @param propName name of the property on this node
/// @return property index or PROPERTY_INVALID_INDEX
VR_API (uint32_t, VRGetProperty, (HNode node, const char* propName));

/// Gets a reusable property handle from a metanode name.
/// @param metaName name of the metanode
/// @param propName name of the property on the metaname
/// @return property index or PROPERTY_INVALID_INDEX
VR_API (uint32_t, VRGetPropertyEx, (const char* metaName, const char* propName));

/// (deprecated) Gets the size of a world float value.
///
/// In 32bit versions of VRTree, this is 4 bytes. On 64bit, it is 8 bytes.
///
/// Interaction with world float properties should be done using the native float or double APIs
/// based on the size reported by this function (e.g. if size == 8, use VRSetPropertyDouble to set
/// a world float property value, otherwise use VRSetPropertyFloat)
///
/// API functions that take data buffers perform widening or narrowing accordingly, if given 
/// the wrong data type. This may result in precision loss if giving doubles to a property expecting floats.
///
/// @note 32bit support is being phased out, so this function will become unnecessary.
VR_API (uint32_t, VRGetWorldFloatSize, (void));

/// Sets a property value on a node
/// @param node handle to the node to set value on
/// @param propName the name of the property to set
/// @param buffer of data to set as the property value
/// @param size of the buffer
/// @return 0 if property was set successfully
VR_API (int, VRSetPropertyValue, (HNode node, const char* propName, const void* valueData, size_t valueSize));

/// Sets a property value on a node
/// @param node handle to the node to set value on
/// @param prop the index of the property to set
/// @param buffer of data to set as the property value
/// @param size of the buffer
/// @param flags flags to use during property setting
/// @param userChange whether the property change is the result of user action
/// @return 0 on success
VR_API (int, VRSetPropertyValueEx, (HNode node, uint32_t prop, const void* valueData, size_t valueSize, uint32_t flags, int userChange));

/// Sets a CHAR or BOOL property on a node
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API (int, VRSetPropertyChar, (HNode node, const char* propName, char value));

/// Sets a CHAR or BOOL property on a node
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API (int, VRSetPropertyCharEx, (HNode node, uint32_t prop, char value, uint32_t flags, int userChange));

/// Sets an element in a CHAR or BOOL array property on a node
/// @param index element to set (0-based array index)
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API (int, VRSetPropertyCharElement, (HNode node, const char* propName, size_t index, char value));

/// Sets an element in a CHAR or BOOL array property on a node
/// @param index element to set (0-based array index)
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API (int, VRSetPropertyCharElementEx, (HNode node, uint32_t prop, size_t index, char value, uint32_t flags, int userChange));

/// Sets an INT property on a node
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API (int, VRSetPropertyInt, (HNode node, const char* propName, int value));

/// Sets an INT property on a node
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API (int, VRSetPropertyIntEx, (HNode node, uint32_t prop, int value, uint32_t flags, int userChange));

/// Sets an element in a INT array property on a node
/// @param index element to set (0-based array index)
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API (int, VRSetPropertyIntElement, (HNode node, const char* propName, size_t index, int value));

/// Sets an element in a INT array property on a node
/// @param index element to set (0-based array index)
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API (int, VRSetPropertyIntElementEx, (HNode node, uint32_t prop, size_t index, int value, uint32_t flags, int userChange));

/// Sets a FLOAT property on a node
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API (int, VRSetPropertyFloat, (HNode node, const char* propName, float value));

/// Sets a FLOAT property on a node
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API (int, VRSetPropertyFloatEx, (HNode node, uint32_t prop, float value, uint32_t flags, int userChange));

/// Sets an element in a FLOAT array property on a node
/// @param index element to set (0-based array index)
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API (int, VRSetPropertyFloatElement, (HNode node, const char* propName, size_t index, float value));

/// Sets an element in a FLOAT array property on a node
/// @param index element to set (0-based array index)
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API (int, VRSetPropertyFloatElementEx, (HNode node, uint32_t prop, size_t index, float value, uint32_t flags, int userChange));

/// Sets a DOUBLE property on a node
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API (int, VRSetPropertyDouble, (HNode node, const char* propName, double value));

/// Sets a DOUBLE property on a node
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API (int, VRSetPropertyDoubleEx, (HNode node, uint32_t prop, double value, uint32_t flags, int userChange));

/// Sets an element in a DOUBLE array property on a node
/// @param index element to set (0-based array index)
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API (int, VRSetPropertyDoubleElement, (HNode node, const char* propName, size_t index, double value));

/// Sets an element in a DOUBLE array property on a node
/// @param index element to set (0-based array index)
/// @param value value to set
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API (int, VRSetPropertyDoubleElementEx, (HNode node, uint32_t prop, size_t index, double value, uint32_t flags, int userChange));

/// Sets an INT property on a node using the value of a symbol
/// @param symbol name of the symbol to read the value from
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API (int, VRSetPropertyEnum, (HNode node, const char* propName, const char* symbol));

/// Sets an INT property on a node using the value of a symbol
/// @param symbol name of the symbol to read the value from
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API (int, VRSetPropertyEnumEx, (HNode node, uint32_t prop, const char* symbol, uint32_t flags, int userChange));

/// Sets a STRING property on a node
/// @param stringData value to set
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API (int, VRSetPropertyString, (HNode node, const char* propName, const char* stringData));

/// Sets a STRING property on a node
/// @param stringData value to set
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API (int, VRSetPropertyStringEx, (HNode node, uint32_t prop, const char* stringData, uint32_t flags, int userChange));

/// Sets an element in a STRING array property on a node
/// @param index element to set (0-based array index)
/// @param value value to set
/// @param valueSize the size of the size
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API(int, VRSetPropertyStringElement, (HNode node, const char* propName, size_t index, const char* value, size_t valueSize));

/// Sets an element in a STRING array property on a node
/// @param index element to set (0-based array index)
/// @param values values to set
/// @param arraySize the size of the values array
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API(int, VRSetPropertyStringElementEx, (HNode node, uint32_t prop, size_t index, const char* values, size_t arraySize, uint32_t flags, int userChange));

/// Sets a LINK property on a node
/// @param linkTarget value to set
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API (int, VRSetPropertyLink, (HNode node, const char* propName, HNode linkTarget));

/// Sets a LINK property on a node
/// @param linkTarget value to set
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API (int, VRSetPropertyLinkEx, (HNode node, uint32_t prop, HNode linkTarget, uint32_t flags, int userChange));

/// Sets an array of floats property on a node (useful to set matrices)
/// @param valueData single precision data to set
/// @param arraySize the size of the data buffer
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API(int, VRSetPropertyArrayFloat, (HNode node, const char* propName, float* valueData, size_t arraySize));

/// Sets an element in a float array property on a node
/// @param valueData data to set
/// @param arraySize size of the data buffer
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API(int, VRSetPropertyArrayFloatEx, (HNode node, uint32_t prop, float* valueData, size_t arraySize, uint32_t flags, int userChange));

/// Sets an array of doubles property on a node (useful to set matrices)
/// @param valueData double precision data to set
/// @param arraySize the size of the data buffer
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API(int, VRSetPropertyArrayDouble, (HNode node, const char* propName, double* valueData, size_t arraySize));

/// Sets an element in a double array property on a node
/// @param valueData data to set
/// @param arraySize size of the data buffer
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API(int, VRSetPropertyArrayDoubleEx, (HNode node, uint32_t prop, double* valueData, size_t arraySize, uint32_t flags, int userChange));

/// Sets an array of world float property on a node (useful to set matrices)
/// @param valueData data to set
/// @param arraySize the size of the data buffer
/// @return 0 on success
/// @see VRSetPropertyValue()
VR_API(int, VRSetPropertyArrayWorldFloat, (HNode node, const char* propName, void* valueData, size_t arraySize));

/// Sets an element in a world float array property on a node
/// @param valueData data to set
/// @param arraySize size of the data buffer
/// @return 0 on success
/// @see VRSetPropertyValueEx()
VR_API(int, VRSetPropertyArrayWorldFloatEx, (HNode node, uint32_t prop, void* valueData, size_t arraySize, uint32_t flags, int userChange));

/// Gets the required size of a buffer to pass to VRGetPropertyValue.
/// In the case of string properties, returns the length of the string including null terminator.
/// @param node node to read from
/// @param propName property to get the size of
/// @return number of bytes required to hold the property data
VR_API (size_t, VRGetPropertyValueSize, (HNode node, const char* propName));

/// Gets the required size of a buffer to pass to VRGetPropertyValue
/// In the case of string properties, returns the length of the string including null terminator.
/// @param node node to read from
/// @param prop property to get the size of
/// @return number of bytes required to hold the property data
VR_API (size_t, VRGetPropertyValueSizeEx, (HNode node, uint32_t prop));

/// Gets a property from a node
/// @param node node to read property from
/// @param propName name of the property to read
/// @param valueBuffer buffer to receive the data
/// @param bufferSize size of the buffer
/// @return number of bytes written to buffer on success
VR_API (size_t, VRGetPropertyValue, (HNode node, const char* propName, void* valueBuffer, size_t bufferSize));

/// Gets a property from a node
/// @param node node to read property from
/// @param prop the property to read
/// @param valueBuffer buffer to receive the data
/// @param bufferSize size of the buffer
/// @return number of bytes written to buffer on success
VR_API (size_t, VRGetPropertyValueEx, (HNode node, uint32_t prop, void* valueBuffer, size_t bufferSize));

/// Gets the value of an enum symbol in the context of the specified node type
VR_API (int, VRGetEnumValue, (HNode node, const char* symbol));

/// Gets the value of an enum symbol in the context of the specified node type
VR_API (int, VRGetEnumValueEx, (const char* metanode, const char* symbol));

/// Gets a CHAR or BOOL property from a node
/// @return the value
/// @see VRGetPropertyValue()
VR_API (char, VRGetPropertyChar, (HNode node, const char* propName));

/// Gets a CHAR or BOOL property from a node
/// @return the value
/// @see VRGetPropertyValueEx()
VR_API (char, VRGetPropertyCharEx, (HNode node, uint32_t prop));

/// Gets a CHAR or BOOL array element from a node property
/// @param index index of array to read
/// @return the value
/// @see VRGetPropertyValue()
VR_API (char, VRGetPropertyCharElement, (HNode node, const char* propName, size_t index));

/// Gets a CHAR or BOOL array element from a node property
/// @param index index of array to read
/// @return the value
/// @see VRGetPropertyValueEx()
VR_API (char, VRGetPropertyCharElementEx, (HNode node, uint32_t prop, size_t index));

/// Gets an INT property from a node
/// @return the value
/// @see VRGetPropertyValue()
VR_API (int, VRGetPropertyInt, (HNode node, const char* propName));

/// Gets an INT property from a node
/// @return the value
/// @see VRGetPropertyValueEx()
VR_API (int, VRGetPropertyIntEx, (HNode node, uint32_t prop));

/// Gets an INT array element from a node property
/// @param index index of array to read
/// @return the value
/// @see VRGetPropertyValue()
VR_API (int, VRGetPropertyIntElement, (HNode node, const char* propName, size_t index));

/// Gets an INT array element from a node property
/// @param index index of array to read
/// @return the value
/// @see VRGetPropertyValueEx()
VR_API (int, VRGetPropertyIntElementEx, (HNode node, uint32_t prop, size_t index));

/// Gets a FLOAT property from a node
/// @return the value
/// @see VRGetPropertyValue()
VR_API (float, VRGetPropertyFloat, (HNode node, const char* propName));

/// Gets a FLOAT property from a node
/// @return the value
/// @see VRGetPropertyValueEx()
VR_API (float, VRGetPropertyFloatEx, (HNode node, uint32_t prop));

/// Gets a FLOAT array element from a node property
/// @param index index of array to read
/// @return the value
/// @see VRGetPropertyValue()
VR_API (float, VRGetPropertyFloatElement, (HNode node, const char* propName, size_t index));

/// Gets a FLOAT array element from a node property
/// @param index index of array to read
/// @return the value
/// @see VRGetPropertyValueEx()
VR_API (float, VRGetPropertyFloatElementEx, (HNode node, uint32_t prop, size_t index));

/// Gets a DOUBLE property from a node
/// @return the value
/// @see VRGetPropertyValue()
VR_API (double, VRGetPropertyDouble, (HNode node, const char* propName));

/// Gets a DOUBLE property from a node
/// @return the value
/// @see VRGetPropertyValueEx()
VR_API (double, VRGetPropertyDoubleEx, (HNode node, uint32_t prop));

/// Gets a DOUBLE array element from a node property
/// @param index index of array to read
/// @return the value
/// @see VRGetPropertyValue()
VR_API (double, VRGetPropertyDoubleElement, (HNode node, const char* propName, size_t index));

/// Gets a DOUBLE array element from a node property
/// @param index index of array to read
/// @return the value
/// @see VRGetPropertyValueEx()
VR_API (double, VRGetPropertyDoubleElementEx, (HNode node, uint32_t prop, size_t index));

/// Gets the int value of symbol and checks if the specified INT property is currently set to that value
VR_API (int, VRIsPropertyEnumValue, (HNode node, const char* propName, const char* symbol));

/// Gets the int value of symbol and checks if the specified INT property is currently set to that value
VR_API (int, VRIsPropertyEnumValueEx, (HNode node, uint32_t prop, const char* symbol));

/// Gets a STRING property from a node
/// @param buffer buffer to receive the string data
/// @param bufferSize size of the buffer
/// @return the number of bytes written to the buffer
/// @note if buffer is null, function returns the required size of the buffer
/// @see VRGetPropertyValue()
VR_API (size_t, VRGetPropertyString, (HNode node, const char* propName, char* buffer, size_t bufferSize));

/// Gets a STRING property from a node
/// @param buffer buffer to receive the string data
/// @param bufferSize size of the buffer
/// @return the number of bytes written to the buffer
/// @note if buffer is null, function returns the required size of the buffer
/// @see VRGetPropertyValueEx()
VR_API (size_t, VRGetPropertyStringEx, (HNode node, uint32_t prop, char* buffer, size_t bufferSize));

/// Gets a STRING array element from a node property
/// @param index index of array to read
/// @return the value
/// @see VRGetPropertyValue()
VR_API(const char*, VRGetPropertyStringElement, (HNode node, const char* propName, size_t index));

/// Gets a STRING array element from a node property
/// @param index index of array to read
/// @return the value
/// @see VRGetPropertyValueEx()
VR_API(const char*, VRGetPropertyStringElementEx, (HNode node, uint32_t prop, size_t index));

/// Gets a LINK property from a node
/// @return handle to the link target node
/// @see VRGetPropertyValue()
VR_API (HNode, VRGetPropertyLink, (HNode node, const char* propName));

/// Gets a LINK property from a node
/// @return handle to the link target node
/// @see VRGetPropertyValueEx()
VR_API (HNode, VRGetPropertyLinkEx, (HNode node, uint32_t prop));

/// Gets a FLOAT array from a node property
/// @param buffer the buffer to store the data in
/// @param bufferSize size of the buffer
/// @return size of the buffer
/// @see VRGetPropertyValue()
VR_API(size_t, VRGetPropertyArrayFloat, (HNode node, const char* propName, float* buffer, size_t bufferSize));

/// Gets the FLOAT array from the property a node
/// @param buffer the buffer to store the data in
/// @param bufferSize size of the buffer
/// @return size of the buffer
/// @see VRGetPropertyValueEx()
VR_API(size_t, VRGetPropertyArrayFloatEx, (HNode node, uint32_t prop, float* buffer, size_t bufferSize));

/// Gets a DOUBLE array element from a node property
/// @param buffer the buffer to store the data in
/// @param bufferSize the size of the buffer to store the data in
/// @return the size of the data buffer
/// @see VRGetPropertyValue()
VR_API(size_t, VRGetPropertyArrayDouble, (HNode node, const char* propName, double* buffer, size_t bufferSize));

/// Gets the DOUBLE array from the property a node
/// @param buffer the buffer to store the data in
/// @param bufferSize size of the buffer
/// @return size of the buffer
/// @see VRGetPropertyValueEx()
VR_API(size_t, VRGetPropertyArrayDoubleEx, (HNode node, uint32_t prop, double* buffer, size_t bufferSize));

/// Gets a WORLD_FLOAT array element from a node property
/// @param buffer the buffer to store the data in
/// @param bufferSize the size of the buffer to store the data in
/// @return the size of the data buffer
/// @see VRGetPropertyValue()
VR_API(size_t, VRGetPropertyArrayWorldFloat, (HNode node, const char* propName, void* buffer, size_t bufferSize));

/// Gets the WORLD_FLOAT array from the property a node
/// @param buffer the buffer to store the data in
/// @param bufferSize size of the buffer
/// @return size of the buffer
/// @see VRGetPropertyValueEx()
VR_API(size_t, VRGetPropertyArrayWorldFloatEx, (HNode node, uint32_t prop, void* buffer, size_t bufferSize));

/// Gets the world transform of the specified node from the transform hierarchy.
/// Internally calls TransformHierarchy::getWorldTransformSafe unless a propName is specified
/// @param node the node to get the world transform of
/// @param propName optional name of the property containing the transform, for node types not managed by the transform hierarchy. In most cases can be NULL
/// @param valueBuffer buffer to populate with the world transform matrix
/// @param bufferSize size of the buffer
/// @return 0 on failure, number of bytes written to valueBuffer on success
VR_API (int, VRGetWorldTransform, (HNode node, const char* propName, void* valueBuffer, size_t bufferSize));

/// @}

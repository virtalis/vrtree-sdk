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

#ifndef VRAPI_H
#error api.h must be included before this file
#endif

/// @defgroup api_metanodes Metanodes
/// Functions for defining @ref metanodes
/// @{

/// @defgroup api_metanodes_general General
/// General functions such as creation and deletion
/// @{

/// Creates a metanode (a description of a node structure).
///
/// Metanodes start at version 0, and their version is incremented by VRAddMigration.
///
/// Once a metanode has been instantiated (by creating a Node of this type), no further modifications are allowed to its structure.
///
/// @param metaName the name of the new metanode
/// @return a handle to the metanode, for use with other metanode functions
VR_API (HMeta, VRCreateMetaNode, (const char* metaName));

/// Creates a metanode (a description of a node structure) with additional flags.
/// @param metaName the name of the new metanode
/// @param flags the flags to apply
/// @return a handle to the metanode, for use with other metanode functions
VR_API (HMeta, VRCreateMetaNodeEx, (const char* metaName, uint32_t flags));

/// Deletes a metanode.
/// Can only be done if there are no instances of the metanode and the metanode structure has not been passed to vrtree
/// @param metaNode handle to the metanode to delete
/// @return 0 on success. If successful, the handle is closed automatically
VR_API (int, VRDeleteMetaNode, (HMeta metaNode));

/// Finishes a metanode definition by passing it to VRTree.
///
/// At this point, modifications to the metanode can no longer be made because
/// the total number of migrations is used to set the metanode version.
/// @param metaNode handle to the metanode to finish. this handle is closed by this function
/// @return 0 on success
VR_API (int, VRFinishMetaNode, (HMeta metaNode));

/// Gets the length of a metanode's name, plus 1 for the trailing null terminator
/// @param metaNode handle to the metanode
VR_API(size_t, VRGetMetaNodeNameLength, (HMeta metaNode));

/// Gets the name of a metanode
/// @param metaNode handle to the metanode
/// @param buffer a buffer to receive the node name as a null terminated string
/// @param size size of the buffer
/// @return the number of characters written to the buffer (including trailing null)
VR_API(size_t, VRGetMetaNodeName, (HMeta metaNode, char* buffer, size_t bufferLength));

/// Finishes a metanode definition by passing it to VRTree.
///
/// At this point, modifications to the metanode can no longer be made because
/// the total number of migrations is used to set the metanode version.
/// @param metaNode handle to the metanode to finish. this handle is closed by this function
/// @return a new handle to the real metanode
VR_API (HMeta, VRFinishMetaNodeEx, (HMeta metaNode));

/// Gets the name of the current version of the specified metanode
/// @param metaName the name of the metanode (no version suffix)
/// @param buffer the variable to recieve the name of the current version of this metanode
/// @param bufferSize size of the output buffer
/// @return number of bytes written to outputBuffer
/// @note if buffer is null, function returns the required size of the buffer
VR_API (size_t, VRCurrentMetaNodeVersion, (const char* metaName, char* buffer, size_t bufferSize));

/// Copies a metanode internally in the API (that is, makes a new one with the same properties but doesn't give it to vrtree)
/// It does this so that a migration can then modify it before VRFinishMetaNode is called as usual to instantiate it properly.
/// @param other handle to the metanode to copy
/// @param versionIncrement automatically increments the version number by this much (negative for decrement)
/// @return new metanode
VR_API (HMeta, VRCopyMetaNode, (HMeta other, int versionIncrement));

/// Performs migrations of a metanode to create all known versions between start and end.
/// @param start handle to the metanode to use as the starting point for migrations
/// @param end handle to the metanode to migrate to (versions are created until this version, but does not create this version)
/// @return int the number of intermediate metanodes that exist between the requested versions, or -1 on failure
/// @note Uses the version of start to begin - if end is > start, up migrations are used, otherwise down migrations are used.
VR_API (int, VRCreateIntermediateMetaNodes, (HMeta start, HMeta end));

/// Checks if a metanode handle is valid (that is, pointing at a metanode and not closed)
/// @param metaNode handle to check
/// @return 0 if invalid, 1 if valid
VR_API (char, VRCheckMetaHandleValid, (HMeta metaNode));

/// Closes a handle to a metanode
VR_API (void, VRCloseMetaHandle, (HMeta metaNode));

/// @}

/// @defgroup api_metanodes_properties Properties
/// Functions for managing @ref properties on metanodes
/// @{

/// Gets the number of properties on a metanode
/// @param metaNode handle to the metanode to query
/// @return the number of properties on the metanode, or -1 on error (0 is a valid number of properties)
VR_API (int, VRGetPropertiesCount, (HMeta metaNode));

/// Adds a boolean property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes (truncated to 0 or 1)
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyBool, (HMeta metaNode, const char* propertyName, char defaultValue));

/// Adds a char property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyChar, (HMeta metaNode, const char* propertyName, char defaultValue));

/// Adds a char property to a metanode with min/max range hints.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes
/// @param minValue the minimum value hint
/// @param maxValue the maximum value hint
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyCharRange, (HMeta metaNode, const char* propertyName, char defaultValue, char minValue, char maxValue));

/// Adds an integer property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyInt, (HMeta metaNode, const char* propertyName, int defaultValue));

/// Adds an integer property to a metanode, with min/max range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes
/// @param minValue the minimum value hint
/// @param maxValue the maximum value hint
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyIntRange, (HMeta metaNode, const char* propertyName, int defaultValue, int minValue, int maxValue));

/// Adds an integer property to a metanode, with min/max range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes
/// @param type the Meta_PropSemantics::PropType to set
/// @return 0 if the property is added successfully
VR_API(int, VRAddPropertyIntType, (HMeta metaNode, const char* propertyName, int defaultValue, const char* type));

/// Adds a float property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyFloat, (HMeta metaNode, const char* propertyName, float defaultValue));

/// Adds a float property to a metanode, with min/max range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes
/// @param minValue the minimum value hint
/// @param maxValue the maximum value hint
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyFloatRange, (HMeta metaNode, const char* propertyName, float defaultValue, float minValue, float maxValue));

/// Adds a double property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyDouble, (HMeta metaNode, const char* propertyName, double defaultValue));

/// Adds a double property to a metanode, with min/max range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes
/// @param minValue the minimum value hint
/// @param maxValue the maximum value hint
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyDoubleRange, (HMeta metaNode, const char* propertyName, double defaultValue, double minValue, double maxValue));

/// Adds a world float property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes. Truncated according to world precision.
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyWorldFloat, (HMeta metaNode, const char* propertyName, double defaultValue));

/// Adds a world float property to a metanode, with min/max range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the default value on new nodes. Truncated according to world precision.
/// @param minValue the minimum value hint, truncated according to world precision
/// @param maxValue the maximum value hint, truncated according to world precision
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyWorldFloatRange, (HMeta metaNode, const char* propertyName, double defaultValue, double minValue, double maxValue));

/// Adds a link property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyLink, (HMeta metaNode, const char* propertyName));

/// Adds a link property to a metanode with a filter on allowed types.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param linkFilter comma separated list of metanodes or traits that are allowed to be linked to
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyLinkFilter, (HMeta metaNode, const char* propertyName, const char* linkFilter));

/// Adds a string property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyString, (HMeta metaNode, const char* propertyName));

/// Adds a string property to a metanode with a default string value
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param type the Meta_PropSemantics::PropType to set
/// @return 0 if the property is added successfully
VR_API(int, VRAddPropertyStringType, (HMeta metaNode, const char* propertyName, const char *type));

/// Adds a string property to a metanode with a default string value
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultValue the string to use as the default on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyStringEx, (HMeta metaNode, const char* propertyName, const char* defaultValue));

/// Adds a file property to a metanode with a file filter of allowed types.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param fileFilter adds a filter semantic to the property allowing file dialogs to filter files
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyFile, (HMeta metaNode, const char* propertyName, const char* fileFilter));

/// Adds a stream property to a metanode with a file filter of allowed types.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param fileFilter adds a filter semantic to the property allowing file dialogs to filter files
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyStream, (HMeta metaNode, const char* propertyName, const char* fileFilter));

/// Adds an integer vec2 property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec2i, (HMeta metaNode, const char* propertyName, int defaultX, int defaultY));

/// Adds an integer vec2 property to a metanode with range hints.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec2iRange, (HMeta metaNode, const char* propertyName, int defaultX, int defaultY, int minX, int minY, int maxX, int maxY));

/// Adds a float vec2 property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec2f, (HMeta metaNode, const char* propertyName, float defaultX, float defaultY));

/// Adds a float vec2 property to a metanode with range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec2fRange, (HMeta metaNode, const char* propertyName, float defaultX, float defaultY, float minX, float minY, float maxX, float maxY));

/// Adds a double vec2 property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec2d, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY));

/// Adds a double vec2 property to a metanode with range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec2dRange, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY, double minX, double minY, double maxX, double maxY));

/// Adds a world float vec2 property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec2w, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY));

/// Adds a world float vec2 property to a metanode with range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec2wRange, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY, double minX, double minY, double maxX, double maxY));

/// Adds an integer vec3 property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec3i, (HMeta metaNode, const char* propertyName, int defaultX, int defaultY, int defaultZ));

/// Adds an integer vec3 property to a metanode with range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param minZ the min value of the z element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @param maxZ the max value of the z element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec3iRange, (HMeta metaNode, const char* propertyName, int defaultX, int defaultY, int defaultZ, int minX, int minY, int minZ, int maxX, int maxY, int maxZ));

/// Adds a float vec3 property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec3f, (HMeta metaNode, const char* propertyName, float defaultX, float defaultY, float defaultZ));

/// Adds a float vec3 property to a metanode with range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param minZ the min value of the z element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @param maxZ the max value of the z element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec3fRange, (HMeta metaNode, const char* propertyName, float defaultX, float defaultY, float defaultZ, float minX, float minY, float minZ, float maxX, float maxY, float maxZ));

/// Adds a double vec3 property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec3d, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY, double defaultZ));

/// Adds a double vec3 property to a metanode with range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param minZ the min value of the z element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @param maxZ the max value of the z element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec3dRange, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY, double defaultZ, double minX, double minY, double minZ, double maxX, double maxY, double maxZ));

/// Adds a world float vec3 property to a metanode.
/// Defaults are specified as double and truncated to float if the world float type is single precision.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec3w, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY, double defaultZ));

/// Adds a world float vec3 property to a metanode with range hints
/// Defaults and range are specified as double and truncated to float if the world float type is single precision.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param minZ the min value of the z element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @param maxZ the max value of the z element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec3wRange, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY, double defaultZ, double minX, double minY, double minZ, double maxX, double maxY, double maxZ));

/// Adds an integer vec4 property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param defaultW the default value of the w element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec4i, (HMeta metaNode, const char* propertyName, int defaultX, int defaultY, int defaultZ, int defaultW));

/// Adds an integer vec4 property to a metanode with range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param defaultW the default value of the w element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param minZ the min value of the z element on new nodes
/// @param minW the min value of the w element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @param maxZ the max value of the z element on new nodes
/// @param maxW the max value of the w element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec4iRange, (HMeta metaNode, const char* propertyName, int defaultX, int defaultY, int defaultZ, int defaultW, int minX, int minY, int minZ, int minW, int maxX, int maxY, int maxZ, int maxW));

/// Adds a float vec4 property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param defaultW the default value of the w element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec4f, (HMeta metaNode, const char* propertyName, float defaultX, float defaultY, float defaultZ, float defaultW));

/// Adds a float vec4 property to a metanode with range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param defaultW the default value of the w element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param minZ the min value of the z element on new nodes
/// @param minW the min value of the w element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @param maxZ the max value of the z element on new nodes
/// @param maxW the max value of the w element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec4fRange, (HMeta metaNode, const char* propertyName, float defaultX, float defaultY, float defaultZ, float defaultW, float minX, float minY, float minZ, float minW, float maxX, float maxY, float maxZ, float maxW));

/// Adds a double vec4 property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param defaultW the default value of the w element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec4d, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY, double defaultZ, double defaultW));

/// Adds a double vec4 property to a metanode with range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param defaultW the default value of the w element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param minZ the min value of the z element on new nodes
/// @param minW the min value of the w element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @param maxZ the max value of the z element on new nodes
/// @param maxW the max value of the w element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec4dRange, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY, double defaultZ, double defaultW, double minX, double minY, double minZ, double minW, double maxX, double maxY, double maxZ, double maxW));

/// Adds a world float vec4 property to a metanode.
/// Defaults are specified as double and truncated to float if the world float type is single precision.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param defaultW the default value of the w element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec4w, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY, double defaultZ, double defaultW));

/// Adds a sphere property to a metanode.
/// Defaults are specified as double and truncated to float if the world float type is single precision.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the position element's x value on new nodes
/// @param defaultY the default value of the position element's y value on new nodes
/// @param defaultZ the default value of the position element's z value on new nodes
/// @param defaultR the default value of the radius element on new nodes
/// @return 0 if the property is added successfully
VR_API(int, VRAddPropertySphere, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY, double defaultZ, double defaultR));

/// Adds a world float vec4 property to a metanode with range hints
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultX the default value of the x element on new nodes
/// @param defaultY the default value of the y element on new nodes
/// @param defaultZ the default value of the z element on new nodes
/// @param defaultW the default value of the w element on new nodes
/// @param minX the min value of the x element on new nodes
/// @param minY the min value of the y element on new nodes
/// @param minZ the min value of the z element on new nodes
/// @param minW the min value of the w element on new nodes
/// @param maxX the max value of the x element on new nodes
/// @param maxY the max value of the y element on new nodes
/// @param maxZ the max value of the z element on new nodes
/// @param maxW the max value of the w element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVec4wRange, (HMeta metaNode, const char* propertyName, double defaultX, double defaultY, double defaultZ, double defaultW, double minX, double minY, double minZ, double minW, double maxX, double maxY, double maxZ, double maxW));

/// Adds an RGB colour property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultR the default value of the red element on new nodes
/// @param defaultG the default value of the green element on new nodes
/// @param defaultB the default value of the blue element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyRGB, (HMeta metaNode, const char* propertyName, float defaultR, float defaultG, float defaultB));

/// Adds an RGBA colour property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param defaultR the default value of the red element on new nodes
/// @param defaultG the default value of the green element on new nodes
/// @param defaultB the default value of the blue element on new nodes
/// @param defaultA the default value of the alpha element on new nodes
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyRGBA, (HMeta metaNode, const char* propertyName, float defaultR, float defaultG, float defaultB, float defaultA));

/// Adds a 3x3 float matrix property to a metanode.
/// Default value is an identity matrix.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyMat3f, (HMeta metaNode, const char* propertyName));

/// Adds a 3x3 double matrix property to a metanode.
/// Default value is an identity matrix.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyMat3d, (HMeta metaNode, const char* propertyName));

/// Adds a 3x3 world float matrix property to a metanode.
/// Default value is an identity matrix.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyMat3w, (HMeta metaNode, const char* propertyName));

/// Adds a 4x4 float matrix property to a metanode.
/// Default value is an identity matrix.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyMat4f, (HMeta metaNode, const char* propertyName));

/// Adds a 4x4 double matrix property to a metanode.
/// Default value is an identity matrix.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyMat4d, (HMeta metaNode, const char* propertyName));

/// Adds a 4x4 world float matrix property to a metanode.
/// Default value is an identity matrix.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyMat4w, (HMeta metaNode, const char* propertyName));

/// Adds a 4x4 world float matrix property to a metanode,
/// with a prop semantic specifying that a 2D matrix editing
/// control should be used for it (e.g. a texture map matrix).
/// Default value is an identity matrix.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyMat4w2D, (HMeta metaNode, const char* propertyName));

/// Adds an arbitrarily sized boolean array property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param num number of elements in the array
/// @param defaultValue default value to use in each element on new nodes
VR_API (int, VRAddPropertyArrayBool, (HMeta metaNode, const char* propertyName, int num, char defaultValue));

/// Adds an arbitrarily sized character array property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param num number of elements in the array
/// @param defaultValue default value to use in each element on new nodes
VR_API (int, VRAddPropertyArrayChar, (HMeta metaNode, const char* propertyName, int num, char defaultValue));

/// Adds an arbitrarily sized integer array property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param num number of elements in the array
/// @param defaultValue default value to use in each element on new nodes
VR_API (int, VRAddPropertyArrayInt, (HMeta metaNode, const char* propertyName, int num, int defaultValue));

/// Adds an arbitrarily sized float array property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param num number of elements in the array
/// @param defaultValue default value to use in each element on new nodes
VR_API (int, VRAddPropertyArrayFloat, (HMeta metaNode, const char* propertyName, int num, float defaultValue));

/// Adds an arbitrarily sized double array property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param num number of elements in the array
/// @param defaultValue default value to use in each element on new nodes
VR_API (int, VRAddPropertyArrayDouble, (HMeta metaNode, const char* propertyName, int num, double defaultValue));

/// Adds an arbitrarily sized world float array property to a metanode.
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @param num number of elements in the array
/// @param defaultValue default value to use in each element on new nodes
VR_API (int, VRAddPropertyArrayWorldFloat, (HMeta metaNode, const char* propertyName, int num, double defaultValue));

/// Adds a character vector property to a metanode (resizable container)
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVectorChar, (HMeta metaNode, const char* propertyName));

/// Adds a string vector property to a metanode (resizable container)
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API(int, VRAddPropertyVectorString, (HMeta metaNode, const char* propertyName));

/// Adds an integer vector property to a metanode (resizable container)
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVectorInt, (HMeta metaNode, const char* propertyName));

/// Adds a float vector property to a metanode (resizable container)
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVectorFloat, (HMeta metaNode, const char* propertyName));

/// Adds a world float vector property to a metanode (resizable container)
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to add
/// @return 0 if the property is added successfully
VR_API (int, VRAddPropertyVectorWorldFloat, (HMeta metaNode, const char* propertyName));

/// Sets a property as read-only (provides a hint to node property user interface to make the editor read only)
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to modify
/// @param readOnly any value greater than 0 makes the property read only
/// @return 0 if property is successfully changed
VR_API (int, VRSetPropertyReadOnly, (HMeta metaNode, const char* propertyName, char readOnly));

/// Sets a property as internal (provides a hint to node property user interface to not display the property editor)
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to modify
/// @param internal any value greater than 0 makes the property internal
/// @return 0 if property is successfully changed
VR_API (int, VRSetPropertyInternal, (HMeta metaNode, const char* propertyName, char internal));

/// Sets a property as cached (contents are replicated in the disk cache)
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to modify
/// @param cached any value greater than 0 makes the property cached
/// @return 0 if property is successfully changed
VR_API (int, VRSetPropertyCached, (HMeta metaNode, const char* propertyName, char cached));

/// Sets a property as purged (contents are ejected from memory and cached to disk)
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to modify
/// @param purged any value greater than 0 makes the property purged
/// @return 0 if property is successfully changed
VR_API (int, VRSetPropertyPurged, (HMeta metaNode, const char* propertyName, char purged));

/// Sets a property as saved (whether or not the value is saved to VRText/VRNative documents)
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to modify
/// @param saved any value greater than 0 makes the property saved
/// @return 0 if property is successfully changed
VR_API (int, VRSetPropertySaved, (HMeta metaNode, const char* propertyName, char saved));

/// Sets a property as cloned (whether the property value should be copied when cloning a node)
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to modify
/// @param saved any value greater than 0 makes the property saved
/// @return 0 if property is successfully changed
VR_API (int, VRSetPropertyCloned, (HMeta metaNode, const char* propertyName, char saved));

/// @}

/// @defgroup api_metanodes_semantics Semantics and Hints
/// Functions for adding @ref advanced_semantics "semantics and hints"
/// @{

/// Adds a symbol to the metanode.
/// Used to provide string representations of enum values for use with scripts and VRSetPropertyEnum etc
/// @param metaNode handle to the metanode to add the symbol to
/// @param symName name of the symbol to add
/// @param symValue value of the symbol
/// @return 0 on success
VR_API (int, VRAddSymbol, (HMeta metaNode, const char* symName, int symValue));

/// Adds a trait to a metanode (a description of its purpose).
/// @param metaNode handle to the metanode to modify
/// @param traitName name of the trait to add
/// @return 0 if trait was added successfully
VR_API (int, VRAddTrait, (HMeta metaNode, const char* traitName));

/// Adds a trait to a metanode (a description of its purpose).
/// @param metaNode handle to the metanode to modify
/// @param traitName name of the trait to add
/// @param primaryIdx index of the primary property that can be associated with the trait
/// @return 0 if trait was added successfully
VR_API(int, VRAddTraitEx, (HMeta metaNode, const char* traitName, int primaryIdx));

/// Adds a bool gui hint to the metanode.
/// Used to provide hints about how to display the property in a gui
/// @param metaNode      handle to the metanode to add the hint to
/// @param propertyName  name of the property to add the hint to
/// @param hintName      the name of the hint to add
/// @param value         the value
VR_API (int, VRAddGuiHintBool, (HMeta metaNode, const char* propertyName, const char* hintName, char value));

/// Adds an int gui hint to the metanode.
/// Used to provide hints about how to display the property in a gui
/// @param metaNode      handle to the metanode to add the hint to
/// @param propertyName  name of the property to add the hint to
/// @param hintName      the name of the hint to add
/// @param value         the value
VR_API (int, VRAddGuiHintInt, (HMeta metaNode, const char* propertyName, const char* hintName, int value));

/// Adds a double gui hint to the metanode.
/// Used to provide hints about how to display the property in a gui
/// @param metaNode      handle to the metanode to add the hint to
/// @param propertyName  name of the property to add the hint to
/// @param hintName      the name of the hint to add
/// @param value         the value
VR_API (int, VRAddGuiHintDouble, (HMeta metaNode, const char* propertyName, const char* hintName, double value));

/// Adds a string gui hint to the metanode.
/// Used to provide hints about how to display the property in a gui
/// @param metaNode      handle to the metanode to add the hint to
/// @param propertyName  name of the property to add the hint to
/// @param hintName      the name of the hint to add
/// @param value         the value
VR_API (int, VRAddGuiHintString, (HMeta metaNode, const char* propertyName, const char* hintName, const char* value));

/// @}

/// @}

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

/// @defgroup api_utils Utilities
/// Assorted utility functions
/// @{
#ifndef EXCLUDE_TEXINFO
/// Helper function for getting the OpenGL texture information out of a texture node
/// @param textureNode handle to the texture node
/// @return information reguarding texture paramaters, values will be 0 on faliure
VR_API(TextureInfo, VRGetTextureInfo, (HNode textureNode));
#endif
/// Helper function for getting the OpenGL texture format out of a texture node
/// @param textureNode handle to the texture node
/// @return 0 if node has no DDSData property, otherwise the GLenum value representing the texture format
VR_API (uint32_t, VRGetTextureFormat, (HNode textureNode));

/// Helper function for loading an image file from disk, converting it to DDS, and storing it in the specified 
/// char vector property.
/// @param node handle to the node to set the property on
/// @param propName name of the property
/// @param file path to the file to read, if not found, an error pattern is set instead
/// @param compress whether to compress the texture using DXT1
/// @return 0 if property is successfully populated with data from the file in DDS format
VR_API (int, VRFileToDDSProperty, (HNode node, const char* propName, const char* file, char compress));

/// Helper function for loading an image file from disk, converting it to DDS, and storing it in the specified 
/// char vector property.
/// @param node handle to the node to set the property on
/// @param propName name of the property
/// @param file path to the file to read, if not found, an error pattern is set instead
/// @param compress whether to compress the texture using DXT1
/// @return 0 if property is successfully populated with data from the file in DDS format
VR_API (int, VRFileToDDSPropertyEx, (HNode node, uint32_t prop, const char* file, char compress));

/// Helper function for converting it to DDS, and storing it in the specified 
/// char vector property.
/// @param node handle to the node to set the property on
/// @param propName name of the property
/// @param data buffer containing the image data to convert to DDS
/// @param glFormat the opengl format of the buffer data
/// @param glType the opengl type of the buffer data
/// @param width the pixel width of the buffer data
/// @param height the pixel height of the buffer data
/// @param compress whether to compress the texture using DXT1
/// @return 0 if property is successfully populated with DDS data
VR_API (int, VRBlobToDDSProperty, (HNode node, const char* propName, const void* data, uint32_t glFormat, uint32_t glType, uint32_t width, uint32_t height, char compress));

/// Helper function for converting it to DDS, and storing it in the specified 
/// char vector property.
/// @param node handle to the node to set the property on
/// @param propName name of the property
/// @param data buffer containing the image data to convert to DDS
/// @param glFormat the opengl format of the buffer data
/// @param glType the opengl type of the buffer data
/// @param width the pixel width of the buffer data
/// @param height the pixel height of the buffer data
/// @param compress whether to compress the texture using DXT1
/// @return 0 if property is successfully populated with DDS data
VR_API (int, VRBlobToDDSPropertyEx, (HNode node, uint32_t prop, const void* data, uint32_t glFormat, uint32_t glType, uint32_t width, uint32_t height, char compress));

/// Helper function for converting it to DDS, and storing it in the specified 
/// char vector property.
/// @param node handle to the node to set the property on
/// @param propName name of the property
/// @param data buffer containing the image data to convert to DDS
/// @param glFormat the opengl format of the buffer data
/// @param glType the opengl type of the buffer data
/// @param transparency (	0 = completely opaque, 1 = transarency mask, 2 = translucent )
/// @param width the pixel width of the buffer data
/// @param height the pixel height of the buffer data
/// @param compress whether to compress the texture using DXT1
/// @param number of mipMap levels
/// @return 0 if property is successfully populated with DDS data
VR_API (int, VRBlobToDDSPropertyV2, (HNode node, const char* propName, const void* data, uint32_t glFormat, uint32_t glType, uint32_t transparency, uint32_t width, uint32_t height, uint32_t depth, char compress, uint32_t mipLevels));


/// Helper function for converting it to DDS, and storing it in the specified 
/// char vector property.
/// @param node handle to the node to set the property on
/// @param propName name of the property
/// @param data buffer containing the image data to convert to DDS
/// @param glFormat the opengl format of the buffer data
/// @param glType the opengl type of the buffer data
/// @param transparency (	0 = completely opaque, 1 = transarency mask, 2 = translucent )
/// @param width the pixel width of the buffer data
/// @param height the pixel height of the buffer data
/// @param compress whether to compress the texture using DXT1
/// @param number of mipMap levels
/// @return 0 if property is successfully populated with DDS data
VR_API (int, VRBlobToDDSPropertyV2Ex, (HNode node, uint32_t prop, const void* data, uint32_t glFormat, uint32_t glType, uint32_t transparency, uint32_t width, uint32_t height, uint32_t depth, char compress, uint32_t mipLevels));

/// @}

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

/// @defgroup api_ffi Foreign Function Interface
/// Functions for interacting with the scripting engine inside VRTree
/// @{

/// Deletes the memory allocated for this FFI variable and closes the handle
VR_API (void, VRFFIFree, (HFFIVar var));

/// Identifies the type of variable.
/// @param var FFI variant handle
/// @return the type of the variable (direct enum conversion)
/// @note due to the return value being based on an enum, the representation may change between API versions.
/// Thus, it is recommended to only use this compare types against other variants.
VR_API (int, VRFFIGetType, (HFFIVar var));

/// Calls a named function in the scripting environment.
/// @param func The name of the method to call
/// @param args Array of HFFIVar handles representing the function parameters (pushed in array order).
/// The array may contain null entries, in which case a nil variant will be substituted for the call.
/// @param nArgs number of arguments in the args array
/// @return a new variant handle containing the return value from the function. This will need to be ::VRFFIFree'd after use.
/// @note this function, being C, is limited to returning only one value, so calling a FFI function that returns multiple values
/// will only return the first value returned by the FFI function. The rest of the return values are currently discarded.
VR_API (HFFIVar, VRFFIInvoke, (const char* func, HFFIVar* args, int nArgs));

/// Registers a function as a global Lua function in the main script environment.
/// This function becomes a first-class Lua function callable by any Lua code in events or other plugins.
/// @param funcName The name of the function as it should appear in the Lua state
/// @param func The function to call when invoked from the Lua state
/// @param minArgc minimuim number of arguments expected
/// @param userData Userdata which is passed back to func when it is invoked.
/// @return 0 if successful, non-zero if a function with this name already exists.
/// @note currently you can only register functions in the global scope, and only if they don't already exist.
VR_API (int, VRFFIRegister, (const char* funcName, FFIFunc func, int minArgc, void* userData));

/// Unregisters a previously registered FFIFunc
/// @return 0 if successful
VR_API (int, VRFFIUnregister, (const char* funcName, FFIFunc func));

/// Creates a boolean FFI variable and returns it.
/// @param value the value to wrap in the variant. any value other than zero results in a true boolean value.
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeBool, (char value));

/// Reads the boolean value contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Bool
/// @return 0 if false, 1 if true
VR_API (char, VRFFIGetBool, (HFFIVar var));

/// Creates a number FFI variable and returns it.
/// @param value the value to wrap in the variant.
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeInt, (int value));

/// Reads the integer value contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Int
/// @return integer value
VR_API (int, VRFFIGetInt, (HFFIVar var));

/// Creates a number FFI variable and returns it.
/// @param value the value to wrap in the variant.
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeDouble, (double value));

/// Reads the double value contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Double
/// @return double value
VR_API (double, VRFFIGetDouble, (HFFIVar var));

/// Creates a string FFI variable and returns it.
/// @param value the value to wrap in the variant.
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeString, (const char* value));

/// Reads the string value contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type String
/// @return null terminated string, may be UTF-8 encoded.
/// @warning the return value is only valid for the lifetime of the FFI variant. 
/// Using this string pointer after calling ::VRFFIFree on this var, without first copying it, will result in undefined behaviour.
VR_API (const char*, VRFFIGetString, (HFFIVar var));

/// Creates a vec2 (2 doubles in an array) 
/// @param values to wrap in the variant. expects an array of 2 doubles.
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeVec2, (const double* values));

/// Reads the vec2 contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Vec2
/// @return pointer to array of 2 doubles containing the values.
/// @warning the return value is only valid until the next call to ::VRFFIGetVec2 with ANY HFFIVar.
VR_API (const double*, VRFFIGetVec2, (HFFIVar var));

/// Creates a vec3 (3 doubles in an array) 
/// @param values to wrap in the variant. expects an array of 3 doubles.
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeVec3, (const double* values));

/// Reads the vec3 contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Vec3
/// @return pointer to array of 3 doubles containing the values.
/// @warning the return value is only valid until the next call to ::VRFFIGetVec3 with ANY HFFIVar.
VR_API (const double*, VRFFIGetVec3, (HFFIVar var));

/// Creates a vec4 (4 doubles in an array) 
/// @param values to wrap in the variant. expects an array of 4 doubles.
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeVec4, (const double* values));

/// Reads the vec4 contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Vec4
/// @return pointer to array of 4 doubles containing the values.
/// @warning the return value is only valid until the next call to ::VRFFIGetVec4 with ANY HFFIVar.
VR_API (const double*, VRFFIGetVec4, (HFFIVar var));

/// Creates a mat3 (9 doubles in an array)
/// @param values to wrap in the variant. expects an array of 9 doubles.
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeMat3, (const double* values));

/// Reads the mat3 contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Mat3
/// @return pointer to array of 9 doubles containing the values.
/// @warning the return value is only valid until the next call to ::VRFFIGetMat3 with ANY HFFIVar.
VR_API (const double*, VRFFIGetMat3, (HFFIVar var));

/// Creates a mat4 (16 doubles in an array)
/// @param values to wrap in the variant. expects an array of 16 doubles.
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeMat4, (const double* values));

/// Reads the mat4 contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Mat4
/// @return pointer to array of 16 doubles containing the values.
/// @warning the return value is only valid until the next call to ::VRFFIGetMat4 with ANY HFFIVar.
VR_API (const double*, VRFFIGetMat4, (HFFIVar var));

/// Creates a sphere (4 doubles in an array)
/// @param values to wrap in the variant. expects an array of 4 doubles (centre xyz, radius)
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeSphere, (const double* values));

/// Reads the sphere contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Sphere
/// @return pointer to array of 4 doubles containing the values (centre xyz, radius)
/// @warning the return value is only valid until the next call to ::VRFFIGetSphere with ANY HFFIVar.
VR_API (const double*, VRFFIGetSphere, (HFFIVar var));

/// Creates a quaternion (4 doubles in an array)
/// @param values to wrap in the variant. expects an array of 4 doubles (vector xyz, angle)
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeQuat, (const double* values));

/// Reads the quaternion contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Quat
/// @return pointer to array of 4 doubles containing the values (vector xyz, angle)
/// @warning the return value is only valid until the next call to ::VRFFIGetQuat with ANY HFFIVar.
VR_API (const double*, VRFFIGetQuat, (HFFIVar var));

/// Creates a plane (4 doubles in an array)
/// @param values to wrap in the variant. expects an array of 4 doubles (normal xyz, distance)
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakePlane, (const double* values));

/// Reads the plane contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Plane
/// @return pointer to array of 4 doubles containing the values (normal xyz, distance)
/// @warning the return value is only valid until the next call to ::VRFFIGetPlane with ANY HFFIVar.
VR_API (const double*, VRFFIGetPlane, (HFFIVar var));

/// Creates a ray (6 doubles in an array)
/// @param values to wrap in the variant. expects an array of 6 doubles (origin xyz, direction xyz)
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeRay, (const double* values));

/// Reads the ray contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type Ray
/// @return pointer to array of 6 doubles containing the values (origin xyz, direction xyz)
/// @warning the return value is only valid until the next call to ::VRFFIGetRay with ANY HFFIVar.
VR_API (const double*, VRFFIGetRay, (HFFIVar var));

/// Creates an AABB (6 doubles in an array)
/// @param values to wrap in the variant. expects an array of 6 doubles (min xyz, max xyz)
/// @return a new FFI variant handle representing the value
/// @see VRFFIFree(HFFIVar)
VR_API (HFFIVar, VRFFIMakeAABB, (const double* values));

/// Reads the AABB contained in the FFI variable and returns it
/// @param var FFI variant handle, must be of type AABB
/// @return pointer to array of 6 doubles containing the values (min xyz, max xyz)
/// @warning the return value is only valid until the next call to ::VRFFIGetAABB with ANY HFFIVar.
VR_API (const double*, VRFFIGetAABB, (HFFIVar var));

/// Wraps a node handle in an FFI variable
/// @param handle valid node handle
/// @return a new FFI variant handle representing the node
/// @see VRFFIFree(HFFIVar)
/// @note The node handle need not remain open in order for the returned var to remain valid.
VR_API (HFFIVar, VRFFIMakeNode, (HNode handle));

/// Reads the node contained in the FFI variable and returns a new handle to it
/// @param var FFI variant handle, must be of type Node
/// @return new node handle to the node contained in the var
/// @see VRCloseNodeHandle
/// @note the FFI var need not remain valid in order for the returned node handle to remain open.
VR_API (HNode, VRFFIGetNode, (HFFIVar var));

/// Registers a C function with a name which can then be used to call the function in direct response
/// to an Event (e.g. Create, Activate, Timestep, etc)
/// @param name The name with which to register the function.
/// @param func The function to register
/// @param userData arbitrary data to pass to the callback
/// @see VRUnregisterEventFunction(const char*)
VR_API (void, VRRegisterEventFunction, (const char* name, ScriptEventFunc func, void* userData));

/// Unregisters a previously registered event function
/// @param name the name of the function to unregister (as it was registered).
VR_API (void, VRUnregisterEventFunction, (const char* name));

/// Reads the value from an event register during a call to a registered event function.
/// These are the equivalent to the values provided to an event script such as __Self and __Other.
/// @param registerName the register to get the value from
/// @return a new FFI variant handle representing the value
VR_API (HFFIVar, VRFFIGetEventRegister, (const char* registerName));

/// @}

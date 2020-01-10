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

/// @defgroup api_core Core
/// Core API functions
/// @{

/// Sets the API error level, which controls which types of errors are reported and logged.
/// @param flags one or more @ref api_loggingmask which enable error reporting by type
VR_API (void, VRSetAPIErrorLevel, (uint32_t flags));

/// Specifies that errors tracked by ::VRSetAPIErrorLevel are also logged the the application log immediately
/// rather than only being stored for ::VRGetLastErrorString
/// @param enabled 1 or above to enable immediate error logging
VR_API (void, VRSetImmediateErrorLog, (char enabled));

/// Gets the last error code. 
///
/// This function does not clear the error.
/// @return @ref api_errors "The last error code"
VR_API (uint32_t, VRGetLastError, (void));

/// Gets the last error string. 
///
/// This function DOES clear the error using VRClearLastError.
/// The returned string is only valid until the next operation that sets a new error string.
/// @return the error string, or NULL if there is no error string to return.
VR_API (const char*, VRGetLastErrorString, (void));

/// Manually clear the last error code.
VR_API (void, VRClearLastError, (void));

/// Initialise VRTree
/// @param port the TCP port on which to listen for collaboration connection requests
/// @return 0 on success
/// @permission SC_INIT
VR_API (int, VRInit, (int port));

/// Connect to another instance of VRTree (e.g. Visionary Render) and synchronise trees
/// @param addr address of the remote instance
/// @param port TCP port that the remote instance is listening on
/// @return 1 on success
/// @permission SC_NETWORK
VR_API (int, VRConnect, (const char* addr, int port));

/// Specifies if there a large amount of data pending transfer between vrtree instances
/// @return 1 on success
/// @permission SC_NETWORK
VR_API(int, VRBulkData, (void));

/// Perform a full update, notifying observers and updating actors
/// @param deltaTime the time since the last frame (or any other value that will affect the step size of any actors)
/// @permission SC_OBSERVE
VR_API (void, VRUpdate, (double deltaTime));

/// Disconnect from the network and shut down
/// @permission SC_NETWORK
VR_API (void, VRShutdown, (void));

/// Diagnostic function
/// @return the number of open node handles
VR_API (size_t, VRCountOpenNodeHandles, (void));

/// Gets the VRTree API Major version.
///
/// This version represents backward compatibility. It should be checked when loading
/// the library, against an expected value. If it is not what is expected, 
/// the API may not function according to the expectations of the program using it.
VR_API (int, VRGetAPIVersionMajor, (void));

/// Gets the VRTree API Minor version.
///
/// This version number represents additions to the API and does not affect backward compatibility.
VR_API (int, VRGetAPIVersionMinor, (void));

/// Closes a node handle, clearing its connection to VRTree
/// @param node handle to close. Becomes unusable.
VR_API (void, VRCloseNodeHandle, (HNode node));

/// Creates a new node handle based off the old one
/// @param node handle stays open.
/// @return new node handle, VRCloseNodeHandle when you are done with it
VR_API(HNode, VRCopyNodeHandle, (HNode node));

/// Checks if a node handle is valid
/// @param node handle to check
/// @return 1 if the handle is valid, 0 if it is invalid (i.e. if it was closed already)
/// @permission SC_READ
VR_API (int, VRIsNodeHandleValid, (HNode node));

/// Gets the low 64-bits of a node's unique ID.
/// @return low 64-bits or 0 on error
/// @permission SC_READ
VR_API (uint64_t, VRGetUUIDLow, (HNode node));

/// Gets the high 64-bits of a node's unique ID.
/// @return high 64-bits or 0 on error
/// @permission SC_READ
VR_API (uint64_t, VRGetUUIDHigh, (HNode node));

/// Gets the node with the specified UUID
/// @param lo low 64-bits of the UUID
/// @param hi high 64-bits of the UUID
/// @return node handle, or 0 on error / non-existant
/// @permission SC_READ
VR_API (HNode, VRGetNodeFromUUID, (uint64_t lo, uint64_t hi));

/// Gets the metanode version of the specified node.
/// @param node node to query
/// @return version, or -1 on error / non-existant
/// @permission SC_READ
VR_API (int, VRGetNodeVersion, (HNode node));

/// Requests a unique userdata slot identifier.
///
/// The userdata slot system can be used by plugins to attach plugin-specific
/// data to a specific node and retrieve it again later. 
/// 
/// Generally a plugin should request one or more unique data slots on initialization 
/// and keep them open for the lifetime of the plugin. It does not need one per node - 
/// the userdata slot handle should be considered the unique slot identifier for plugin data
/// on ALL nodes. Using more than one is only necessary if the plugin needs to store more than one
/// piece of data on a single node, and even then only in the case where storing it in a struct
/// in the first slot is not appropriate.
///
/// This data is not managed by the application, so it is up to the plugin to make sure
/// it removes any userdata it adds before closing its user slot handle.
/// @return slot handle, or 0 on error
/// @permission SC_MODIFY
VR_API (HUserSlot, VRNewUserSlotHandle, (void));

/// Releases a unique userdata slot handle.
///
/// This does not remove userdata stored on nodes using this slot handle.
/// That data must be cleaned up before closing the slot handle to avoid data leaks.
/// @param slot an open slot handle
VR_API (void, VRCloseUserSlotHandle, (HUserSlot slot));

/// Requests a change in the API security context to grant access to API functions by
/// categories specified in the auth string.
///
/// Most plugins should let the plugin manager deal with this automatically by exporting their
/// signature string as a ::VRPSignatureProc. This API exists for programs that load vrtree.dll
/// independently of Visionary Render, in which case the auth string is likely to be required to specify
/// SC_INIT permissions in order to be able to do anything useful.
///
/// @param auth full contents of an API license (signed xml)
/// @param name the name of the application requesting the context
/// @return a new auth handle indicating successful context switch, or 0 on error / invalid auth
/// @note New contexts are pushed onto a stack, meaning that when the returned context is closed,
/// access controls revert to the level provided by the previous security context.
VR_API (HAuth, VRRequestSecurityContext, (const char* auth, const char* name));

/// Releases a previously requested security context.
VR_API (int, VRCloseSecurityContext, (HAuth context));

/// @}

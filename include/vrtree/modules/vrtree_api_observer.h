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

/// @defgroup api_observer Observers
/// Callback registration functions for @ref observers "observed node events"
/// @{

/// Registers a function to be called whenever a node is created
/// @param metaName the name of the metanode (type of node) to observe
/// @param callback the function to call on creation
/// @param userData arbitrary data to pass to the callback
VR_API (void, VRAddCallbackNodeCreation, (const char* metaName, NodeCreatedFunc callback, void* userData));

/// Registers a function to be called whenever a node is deleted
/// @param metaName the name of the metanode (type of node) to observe
/// @param callback the function to call on deletion
/// @param userData arbitrary data to pass to the callback
VR_API (void, VRAddCallbackNodeDestruction, (const char* metaName, NodeDestroyingFunc callback, void* userData));

/// Registers a function to be called whenever a node is modified
/// @param metaName the name of the metanode (type of node) to observe
/// @param callback the function to call on creation
/// @param userData arbitrary data to pass to the callback
VR_API (void, VRAddCallbackNodeValuesChanged, (const char* metaName, NodeValuesChangedFunc callback, void* userData));

/// Registers a function to be called whenever a node is renamed
/// @param metaName the name of the metanode (type of node) to observe
/// @param callback the function to call on creation
/// @param userData arbitrary data to pass to the callback
VR_API (void, VRAddCallbackNodeRenamed, (const char* metaName, NodeRenamedFunc callback, void* userData));

/// Registers a function to be called whenever a node has a child added to it
/// @param metaName the name of the metanode (type of node) to observe
/// @param callback the function to call on creation
/// @param userData arbitrary data to pass to the callback
VR_API (void, VRAddCallbackNodeChildAdded, (const char* metaName, NodeChildAddedFunc callback, void* userData));

/// Registers a function to be called whenever a node has a child removed from it
/// @param metaName the name of the metanode (type of node) to observe
/// @param callback the function to call on creation
/// @param userData arbitrary data to pass to the callback
VR_API (void, VRAddCallbackNodeChildRemoved, (const char* metaName, NodeChildRemovedFunc callback, void* userData));

/// Registers a function to be called whenever a node is moved to a new parent
/// @param metaName the name of the metanode (type of node) to observe
/// @param callback the function to call on creation
/// @param userData arbitrary data to pass to the callback
VR_API (void, VRAddCallbackNodeParentChanged, (const char* metaName, NodeParentChangedFunc callback, void* userData));

/// Registers a function to be called whenever VRTree updates (either by the host application or by a call to ::VRUpdate)
/// @param metaName the name of the metanode (type of node) to observe
/// @param callback the function to call on creation
/// @param userData arbitrary data to pass to the callback
VR_API (void, VRAddCallbackUpdate, (UpdateFunc callback, void* userData));

/// Unregisters a function called whenever a node is created
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackNodeCreation, (const char* metaName, NodeCreatedFunc callback));

/// Unregisters a function called whenever a node is destroyed
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackNodeDestruction, (const char* metaName, NodeDestroyingFunc callback));

/// Unregisters a function called whenever a node is modified
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackNodeValuesChanged, (const char* metaName, NodeValuesChangedFunc callback));

/// Unregisters a function called whenever a node is renamed
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackNodeRenamed, (const char* metaName, NodeRenamedFunc callback));

/// Unregisters a function called whenever a node has children added to it
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackNodeChildAdded, (const char* metaName, NodeChildAddedFunc callback));

/// Unregisters a function called whenever a node has children removed from it
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackNodeChildRemoved, (const char* metaName, NodeChildRemovedFunc callback));

/// Unregisters a function called whenever a node is moved somewhere else in the tree
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackNodeParentChanged, (const char* metaName, NodeParentChangedFunc callback));

/// Unregisters an update function
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackUpdate, (UpdateFunc callback));

/// Unregisters a function called whenever a node is created
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
/// @param userData arbitrary data to passed to the callback
VR_API (void, VRRemoveCallbackNodeCreationEx, (const char* metaName, NodeCreatedFunc callback, void* userData));

/// Unregisters a function called whenever a node is destroyed
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
/// @param userData arbitrary data to passed to the callback
VR_API (void, VRRemoveCallbackNodeDestructionEx, (const char* metaName, NodeDestroyingFunc callback, void* userData));

/// Unregisters a function called whenever a node is modified
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
/// @param userData arbitrary data to passed to the callback
VR_API (void, VRRemoveCallbackNodeValuesChangedEx, (const char* metaName, NodeValuesChangedFunc callback, void* userData));

/// Unregisters a function called whenever a node is renamed
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
/// @param userData arbitrary data to passed to the callback
VR_API (void, VRRemoveCallbackNodeRenamedEx, (const char* metaName, NodeRenamedFunc callback, void* userData));

/// Unregisters a function called whenever a node has children added to it
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
/// @param userData arbitrary data to passed to the callback
VR_API (void, VRRemoveCallbackNodeChildAddedEx, (const char* metaName, NodeChildAddedFunc callback, void* userData));

/// Unregisters a function called whenever a node has children removed from it
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
/// @param userData arbitrary data to passed to the callback
VR_API (void, VRRemoveCallbackNodeChildRemovedEx, (const char* metaName, NodeChildRemovedFunc callback, void* userData));

/// Unregisters a function called whenever a node is moved somewhere else in the tree
/// @param metaName the name of the metanode (type of node) to stop observing
/// @param callback the previously added function to remove
/// @param userData arbitrary data to passed to the callback
VR_API (void, VRRemoveCallbackNodeParentChangedEx, (const char* metaName, NodeParentChangedFunc callback, void* userData));

/// Unregisters an update function
/// @param callback the previously added function to remove
/// @param userData arbitrary data to passed to the callback
VR_API (void, VRRemoveCallbackUpdateEx, (UpdateFunc callback, void* userData));

/// @}

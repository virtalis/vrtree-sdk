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



/// Event callbacks. Some already exist :
/// VRAddCallbackUpdate for Event::TimeStep
/// VRAddCallbackNodeCreation for Event::Create
/// VRAddCallbackNodeDestruction for Event::Delete
/// VRAddCallbackNodeRenamed for Event::Rename
/// 
/// View select and View deselect are added despite they are missing in the Event list in vrscript.hpp, 57

/// Add callback for Activate event of a node and the other node deactivated
/// @param node node handle
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackActivate, (HNode node, EventTwoNodesUserFunc callback, void* userData, int flags));

/// Remove callback for Activate event of a node and the other node deactivated
/// @param node node handle
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackActivate, (HNode node, EventTwoNodesUserFunc callback));

/// Add Touch callback (assembly has collided)
/// @param node node handle
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackTouch, (HNode node, EventTwoNodesFunc callback, void* userData, int flags));

/// Remove Touch callback (assembly has collided)
/// @param node node handle
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackTouch, (HNode node, EventTwoNodesFunc callback));

/// Add Break callback (assembly has ceased colliding)
/// @param node node handle
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackBreak, (HNode node, EventTwoNodesFunc callback, void* userData, int flags));

/// Remove Break callback (assembly has ceased colliding)
/// @param node node handle
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackBreak, (HNode node, EventTwoNodesFunc callback));

/// Add Key press callback (key was pressed)
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackKeyPress, (EventKeyFunc callback, void* userData, int flags));

/// Remove Key press callback (key was pressed)
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackKeyPress, (EventKeyFunc callback));

/// Add Key release callback (key was released)
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackKeyRelease, (EventKeyFunc callback, void* userData, int flags));

/// Remove Key release callback (key was released)
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackKeyRelease, (EventKeyFunc callback));

/// Add Pose entered callback (a hand switched to a pose)
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackPoseEntered, (EventKeyFunc callback, void* userData, int flags));

/// Remove Pose entered callback (a hand switched to a pose)
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackPoseEntered, (EventKeyFunc callback));

/// Add Pose left callback (a hand left a pose)
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackPoseLeft, (EventKeyFunc callback, void* userData, int flags));

/// Remove Pose left callback (a hand left a pose)
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackPoseLeft, (EventKeyFunc callback));

/// Add Gesture callback (a hand activated a gesture)
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackGesture, (EventGestureFunc callback, void* userData, int flags));

/// Remove Gesture callback (a hand activated a gesture)
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackGesture, (EventGestureFunc callback));

/// Add Click callback (button or similar node clicked)
/// @param node node handle
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackClick, (HNode node, EventNodeFunc callback, void* userData, int flags));

/// Remove Click callback (button or similar node clicked)
/// @param node node handle
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackClick, (HNode node, EventNodeFunc callback));

/// Add Double click callback (button or similar node double-clicked)
/// @param node node handle
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackDoubleClick, (HNode node, EventNodeFunc callback, void* userData, int flags));

/// Remove Double click callback (button or similar node double-clicked)
/// @param node node handle
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackDoubleClick, (HNode node, EventNodeFunc callback));

/// Add Enter callback (a generic state was entered)
/// @param node node handle
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackEnter, (HNode node, EventNodeFunc callback, void* userData, int flags));

/// Remove Enter callback (a generic state was entered)
/// @param node node handle
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackEnter, (HNode node, EventNodeFunc callback));

/// Add Leave callback (a generic state was left)
/// @param node node handle
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackLeave, (HNode node, EventNodeFunc callback, void* userData, int flags));

/// Remove Leave callback (a generic state was left)
/// @param node node handle
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackLeave, (HNode node, EventNodeFunc callback));

/// Add Move callback. The ‘move’ event applies to sliders, scrollbars and markers in the GUI 
/// system in addition to assemblies. It’s not the same as observing the transform property 
/// because the move event is also triggered on all the descendant assemblies of the object 
/// that has moved.
/// @param node node handle
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackMove, (HNode node, EventNodeFunc callback, void* userData, int flags));

/// Remove Move callback (the transform property has changed)
/// @param node node handle
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackMove, (HNode node, EventNodeFunc callback));

/// Add Press callback (button or similar node pressed)
/// @param node node handle
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackPress, (HNode node, EventNodeFunc callback, void* userData, int flags));

/// Remove Press callback (button or similar node pressed)
/// @param node node handle
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackPress, (HNode node, EventNodeFunc callback));

/// Add Release callback (button or similar node released)
/// @param node node handle
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackRelease, (HNode node, EventNodeFunc callback, void* userData, int flags));

/// Remove Release callback (button or similar node released)
/// @param node node handle
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackRelease, (HNode node, EventNodeFunc callback));

/// Add Toggle callback (button or similar node toggled)
/// @param node node handle
/// @param callback the function to call
/// @param userData arbitrary data to pass to the callback
/// @param flags additional flags for future use (must be zero)
VR_API (void, VRAddCallbackToggle, (HNode node, EventNodeFunc callback, void* userData, int flags));

/// Remove Toggle callback (button or similar node toggled)
/// @param node node handle
/// @param callback the previously added function to remove
VR_API (void, VRRemoveCallbackToggle, (HNode node, EventNodeFunc callback));


/// @}

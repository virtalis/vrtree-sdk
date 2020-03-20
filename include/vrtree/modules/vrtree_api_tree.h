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

/// @defgroup api_tree Tree
/// Functions for operating on the @ref nodes "node" structure of the VR Tree
/// @{

/// Gets the VRTree root node.
VR_API (HNode, VRGetRootNode, (void));

/// Gets the VRTree scenes node.
VR_API (HNode, VRGetScenesNode, (void));

/// Gets the VRTree system library node.
VR_API (HNode, VRGetSystemLibraryNode, (void));

/// Gets the VRTree libraries node.
VR_API (HNode, VRGetLibrariesNode, (void));

/// Gets the VRTree users node.
VR_API (HNode, VRGetUsersNode, (void));

/// Gets the VRTree user node.
VR_API (HNode, VRGetThisUser, (void));

/// Loads a VRText or VRNative format file from disk.
/// @param targetNode the node to load the file onto (usually root)
/// @param fileName the full path to the file to load
/// @return The first new child of targetNode, or NULL if load failed
VR_API (HNode, VRLoadTree, (HNode targetNode, const char* fileName));

/// Loads a VRText or VRNative format file from disk.
/// @param targetNode the node to load the file onto (usually root)
/// @param fileName the full path to the file to load
/// @param ioFlags Input flags to apply while loading the tree
/// @param builderFlags flags which adjust the behaviour of the builder
/// @param builderMetaFlags additional MetaNode flags applied to nodes created by the tree builder
/// @return The first new child of targetNode, or NULL if load failed
VR_API(HNode, VRLoadTreeEx, (HNode targetNode, const char* fileName, uint64_t ioFlags, uint32_t builderFlags, uint32_t builderMetaFlags));

/// Saves the tree to a VRText or VRNative format file on disk.
/// @param rootNode the node to start saving from (usually root)
/// @param fileName the full path to the file to save to
/// @return 0 if the save was successful
VR_API (int, VRSaveTree, (HNode rootNode, const char* fileName));

/// Saves the tree to a VRText or VRNative format file on disk.
/// @param rootNode the node to start saving from (usually root).
/// @param fileName the full path to the file to save to.
/// @return 0 if the save was successful.
VR_API(int, VRSaveTreeEx, (HNode rootNode, const char* fileName, uint64_t ioFlags));

/// Compares all the properties on both nodes to make sure they are equal.
/// @param lhs first node to compare
/// @param rhs second node to compare
/// @param checkNameMatches whether to compare the node name as well as the properties (non-zero to enable)
/// @return 1 if the nodes are the same, 0 if they are not
VR_API (int, VRCompareNode, (HNode lhs, HNode rhs, int checkNameMatches));

/// Creates a node.
/// @param parentNode Handle to the parent of the new node
/// @param metaName type of node to create
/// @param nodeName name of the new node
/// @return node handle
VR_API (HNode, VRCreateNode, (HNode parentNode, const char* metaName, const char* nodeName));

/// Creates a node.
/// @param parentNode Handle to the parent of the new node
/// @param metaName type of node to create
/// @param nodeName name of the new node
/// @param flags creation flags (bits) to provide to the new node
/// @param idLO low 64bits of a unique id (or 0 for auto ID)
/// @param idHI high 64bits of a unique id (or 0 for auto ID)
/// @param userChange whether the change is a response to a user action
/// @note Flags larger than 16bits will be truncated.
/// @internal API compatibility; if we ever need more than 64 bits for flags, do not change the size
/// of this flags parameter. Add a new function to the API called VRCreateNodeEx
/// or something that takes a bigger flags parameter, or even a second uint32 as the high bits.
VR_API (HNode, VRCreateNodeEx, (HNode parentNode, const char* metaName, const char* nodeName, uint64_t flags, uint64_t idLO, uint64_t idHI, int userChange));

/// Gets or creates a node matching metanode and name.
/// @param parentNode Handle to the parent of the node
/// @param metaName type of node to create
/// @param nodeName name of the new node
/// @return node handle
VR_API (HNode, VRFindOrCreateChild, (HNode parentNode, const char* metaName, const char* nodeName));


/// Gets or creates a node matching metanode and name.
/// @param parentNode Handle to the parent of the node
/// @param metaName type of node to create
/// @param nodeName name of the new node
/// @return node handle
VR_API (HNode, VRFindOrCreateChildEx, (HNode parentNode, const char* metaName, const char* nodeName, uint64_t flags, uint64_t idLO, uint64_t idHI, int userChange));

/// Clones an existing node
/// @param parentNode Handle to the parent of the new node
/// @param nodeToClone the node to copy
/// @param recursive if not 0, also copies descendants
/// @return the copy of nodeToClone
VR_API (HNode, VRCloneNode, (HNode parentNode, HNode nodeToClone, int recursive));

/// Deletes a node and all its children
/// @param node the node to delete
/// @return 0 if deletion successful
VR_API (int, VRDeleteNode, (HNode node));

/// Gets the length of the type name of a node
VR_API (size_t, VRGetTypeLength, (HNode node));

/// Gets the type of a node.
/// @param node handle to the node
/// @param buffer a buffer to recieve the node type name as a null terminated string
/// @param size size of the buffer
/// @return the number of characters written to the buffer (including trailing null)
VR_API (size_t, VRGetType, (HNode node, char* buffer, size_t bufferLength));

/// Determines if a node is of a particular type.
/// @param node handle to the node
/// @param metaName name of the node type to match
/// @return 1 if node is of type metaName, 0 if it is not
VR_API (int, VRIsType, (HNode node, const char* metaName));

/// Determines if a node value has been changed/dirtied.
/// @param node handle to the node
/// @param propName name of the property on this node
/// @return 1 if node property is dirty, 0 if it is not
VR_API (int, VRIsDirty, (HNode node, const char* propName));

/// Determines if a node value has been changed/dirtied.
/// @param node handle to the node
/// @param prop the index of the property to set
/// @return 1 if node property is dirty, 0 if it is not
VR_API (int, VRIsDirtyEx, (HNode node, uint32_t prop));

/// Gets the length of a node's name, plus 1 for the trailing null terminator
/// @param node handle to the node
VR_API (size_t, VRGetNodeNameLength, (HNode node));

/// Gets the name of a node
/// @param node handle to the node
/// @param buffer a buffer to receive the node name as a null terminated string
/// @param size size of the buffer
/// @return the number of characters written to the buffer (including trailing null)
VR_API (size_t, VRGetNodeName, (HNode node, char* buffer, size_t bufferLength));

/// Checks if the name of the node is equal to parameter
/// @param node handle to the node
/// @param name to check against
/// @return 1 if name is equal -1 if node invalid 0 if not equal
VR_API (int, VRIsNodeName, (HNode node, const char* name));

/// Sets the name of a node
/// @param node handle to the node
/// @param name the new node name
/// @return 0 on success
VR_API (int, VRSetNodeName, (HNode node, const char* name));

/// Stores a pointer on the node
/// @param node handle to the node
/// @param data which you wish to store in slot, can be null to remove data
/// @return previously bound data, if any
VR_API (void*, VRSetNodeUserData, (HNode node, HUserSlot slot, void* data));

/// Stores a pointer on the node
/// @param node handle to the node
/// @return user data bound to slot
VR_API (void*, VRGetNodeUserData, (HNode node, HUserSlot slot));

/// Gets the length of a node's path
/// @param node handle to the node
VR_API (size_t, VRGetNodePathLength, (HNode node));

/// Gets the path of a node
/// @param node handle to the node
/// @param buffer a buffer to recieve the node path as a null terminated string
/// @param size size of the buffer
/// @return the number of characters written to the buffer (including trailing null)
/// @note if buffer is null, function returns the required size of the buffer
VR_API (size_t, VRGetNodePath, (HNode node, char* buffer, size_t bufferLength));

/// Checks if two node handles are pointing at the same node.
/// @param a first node
/// @param b second node
/// @return 1 if the nodes are the same
VR_API (int, VRIsSameNode, (HNode a, HNode b));

/// Checks if node a is an ancestor of node b
/// @param a first node
/// @param b second node
/// @return 1 if a is an ancestor of b
VR_API (int, VRIsAncestor, (HNode a, HNode b));

/// Finds a descendant of startNode using its path
/// @param startNode node to search from
/// @param path path from start node to requested node
/// @return handle to requested node or NULL if not found
VR_API (HNode, VRFind, (HNode startNode, const char* path));

/// Finds a direct child of startNode.
/// Index is used to specify n'th child if multiple children have the same name
/// @param startNode node to get the child from
/// @param childName name of the child
/// @param index index of child with non-unique name
/// @return handle to requested node or NULL if not found
VR_API (HNode, VRFindChild, (HNode startNode, const char* childName, uint32_t index));

/// Finds a direct child of startNode by specifying name and type
/// @param startNode node to get child from
/// @param metaNode type of child node to get
/// @param childName name of the child node to return
/// @return handle to found node or NULL if not found
VR_API (HNode, VRFindChildPooled, (HNode startNode, const char* metaNode, const char* childName));

/// Gets the first child of node
/// @return first child or NULL if no children
VR_API (HNode, VRGetChild, (HNode node));

/// Gets the first child of a specific type
/// @param childMetaNode the type of child to get
/// @return first child of requested type, or NULL if no children/no children of this type
VR_API (HNode, VRGetChildOfType, (HNode node, const char* childMetaNode));

/// Gets the next sibling of a node
/// @return sibling or NULL if no siblings
VR_API (HNode, VRGetNext, (HNode node));

/// Gets the next sibling of a specific type
/// @param nextMetaNode the type of sibling to get
/// @return next sibling of requested type, or NULL if no siblings/no siblings of this type
VR_API (HNode, VRGetNextOfType, (HNode node, const char* nextMetaNode));

/// Gets the previous sibling of a node
/// @return sibling or NULL if no siblings
VR_API(HNode, VRGetPrev, (HNode node));

/// Gets the previous sibling of a specific type
/// @param prevMetaNode the type of sibling to get
/// @return previous sibling of requested type, or NULL if no siblings/no siblings of this type
VR_API(HNode, VRGetPrevOfType, (HNode node, const char* prevMetaNode));

/// Gets the parent of a node
/// @return parent node or NULL if no parent (root node)
VR_API (HNode, VRGetParent, (HNode node));

/// Sets the parent of a node, adding it as the last child
/// @return 0 on success
VR_API (int, VRSetParent, (HNode node, HNode parent));

/// Sets the parent of a node, specifying a sibling to insert after
/// @param afterSibling the node after which to insert this node. If null, inserts as first child of parent
/// @return 0 on success
VR_API(int, VRSetParentEx, (HNode node, HNode parent, HNode afterSibling));

/// Gets the metanode of a node
/// @return metanode or NULL if no metanode
VR_API(HMeta, VRGetMetaNode, (HNode node));
/// @}

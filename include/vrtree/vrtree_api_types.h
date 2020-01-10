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

#ifndef _VRTREE_INTERFACE_TYPES_H_
#define _VRTREE_INTERFACE_TYPES_H_

/// @defgroup api_defs API Definitions
/// Collection of standard type definitions and constants.
/// @{

/// @defgroup api_types Types
/// Defines the data types used for object handle parameters to API functions.
/// @{

/// A handle to a VRTree node
typedef struct NodeHandle* HNode;

/// A handle to a VRTree metanode
typedef struct MetaHandle* HMeta;

/// A handle to a migration description
typedef struct MigrationHandle* HMigration;

/// A handle to a variable passed through the foreign function interface (FFI)
typedef struct FFIVarHandle* HFFIVar;

/// A handle to a userdata slot on a VRTree node
typedef struct UserDataHandle* HUserSlot;

/// A handle to a security context
typedef struct SecurityContextHandle* HAuth;

#ifndef EXCLUDE_TEXINFO
typedef struct _TextureInfo
{
  unsigned int target;
  unsigned int format;
  unsigned int width;
  unsigned int height;
  unsigned int depth;
  unsigned int mipLevels;
} TextureInfo;
#endif
/// @}

/// @defgroup api_proto Function Prototypes
/// Defines the function prototypes used for registering callbacks with the API.
/// @{

/// Signature of a function that receives a new migration handle and should use it to register other callbacks.
/// @param m handle to a migration
typedef void(*MigrationAddFunc)(HMigration m);

/// Signature of a function that should perform an upgrade on a metanode
/// @param m the migration that owns this upgrade function
/// @param meta the metanode that should be modified as part of the upgrade
/// @return should return zero on success
typedef int(*MigrationUpFunc)(HMigration m, HMeta meta);

/// Signature of a function that should perform a downgrade on a metanode
/// @param m the migration that owns this downgradfe function
/// @param meta the metanode that should be modified as part of the downgrade
/// @return should return zero on success
typedef int(*MigrationDownFunc)(HMigration m, HMeta meta);

/// Signature of a function that should perform an upgrade on a node instance, e.g. by modifying property values
/// @param m the migration that owns this upgrade function
/// @param node the node instance to upgrade
/// @return a node handle representing the new, upgraded node instance
typedef HNode(*MigrationUpgradeFunc)(HMigration m, HNode node);

/// Signature of a function that should perform a downgrade on a node instance
/// @param m the migration that owns this upgrade function
/// @param node the node instance to downgrade
/// @return a node handle representing the new, downgraded node instance
typedef HNode(*MigrationDowngradeFunc)(HMigration m, HNode node);

/// Signature of a function that is called at the end of a nodes migration calls
/// @param node the node that you are migrating
/// @param userData arbitrary user data that was provided when registering the callback
typedef void(*MigrationFunc)(HNode node, void* userData);

/// Signature of a function that is called in response to a registered script event
/// @param userData arbitrary user data that was provided when registering the callback
typedef void(*ScriptEventFunc)(void* userData);

/// Signature of a function that is called when a node is created
/// @param node the node that was created
/// @param userData arbitrary user data that was provided when registering the callback
typedef void(*NodeCreatedFunc)(HNode node, void* userData);

/// Signature of a function that is called when a node is about to be deleted
/// @param node the node that is about the be deleted
/// @param userData arbitrary user data that was provided when registering the callback
typedef void(*NodeDestroyingFunc)(HNode node, void* userData);

/// Signature of a function that is called when properties on a node are changed
/// @param node the node that was modified
/// @param userData arbitrary user data that was provided when registering the callback
typedef void(*NodeValuesChangedFunc)(HNode node, void* userData);

/// Signature of a function that is called when a node is renamed
/// @param node the node that was created
/// @param userData arbitrary user data that was provided when registering the callback
typedef void(*NodeRenamedFunc)(HNode node, void* userData);

/// Signature of a function that is called when a child is added to a node
/// @param parent the parent node
/// @param child the child that is being added to the parent
/// @param userData arbitrary user data that was provided when registering the callback
typedef void(*NodeChildAddedFunc)(HNode parent, HNode child, void* userData);

/// Signature of a function that is called when a child is removed from a node
/// @param parent the parent node
/// @param child the child that was removed from the parent
/// @param userData arbitrary user data that was provided when registering the callback
typedef void(*NodeChildRemovedFunc)(HNode parent, HNode child, void* userData);

/// Signature of a function that is called when a node is moved to a new parent
/// @param node the node that was moved
/// @param newParent the new parent of the node
/// @param oldParent the old parent that the node was moved from
/// @param userData arbitrary user data that was provided when registering the callback
typedef void(*NodeParentChangedFunc)(HNode node, HNode newParent, HNode oldParent, void* userData);

/// Signature of a function that is called every frame
/// @param deltaTime the time (in seconds) since the last frame
/// @param userData arbitrary user data that was provided when registering the callback
typedef void(*UpdateFunc)(double deltaTime, void* userData);

/// Signature of a function that is exposed to the Lua environment
typedef HFFIVar(*FFIFunc)(int argc, HFFIVar* argv, void* userData);

/// @}

/// @defgroup api_flags Flags
/// Flags that can be applied to some API operations
/// @{

#include <stdint.h>

/// Specifies that a metanode or specific node instance should not be copy-able by the application
const uint32_t METANODE_NO_CLONE = (1 << 0);

/// Specifies that a metanode or specific node instance should not be saved into a scene
const uint32_t METANODE_NO_SAVE = (1 << 1);

/// Specifies that a metanode or specific node instance should not be saved anywhere, including special system-save operations
const uint32_t METANODE_DEVELOPER_NO_SAVE = (1 << 2);

/// Specifies that a metanode or specific node instance should be treated as node-spy, which triggers its dirty flags when any of its descendants are modified
const uint32_t METANODE_NODE_SPY = (1 << 3);

/// Specifies that a metanode or specific node instance should not be inserted into the undo/redo history
const uint32_t METANODE_NO_HISTORY = (1 << 5);

/// Indicates that an application should not attempt to represent this node in whatever 2D drawing system it is using
const uint32_t METANODE_NO_GUI  = (1 << 10);

/// Specifies that a metanode or specific node instance should use a map for its children (performance optimization for nodes with large numbers of children)
const uint32_t METANODE_CHILD_MAP = (1 << 11);

/// Specifies that a metanode or specific node instance is protected from all user and script operations that would affect its position in the tree (deleting, parenting, etc)
const uint32_t METANODE_PROTECTED = (1 << 4);

/// Indicates that the metanode should only be represented in the 2D drawing system when in developer admin mode.
const uint32_t METANODE_ADMIN = (1 << 12);

/// Used for event MetaNodes and similar. Nodes of this MetaNode can be expected to be deleted shortly after their creation.
const uint32_t METANODE_TRANSIENT = (1 << 6);

/// Identifier of an invalid property index
const uint32_t PROPERTY_INVALID_INDEX = 0xFFFFFFFF;

/// Specifies that the value being set should not be applied to the node until the next frame update.
/// This is useful when trying to set properties in response to observer functions which would otherwise violate the observer pattern.
const uint32_t FLAG_VALUE_BY_POST = 1;

/// @}

/// @defgroup api_io_flags Save/Load Tree I/O Flags
/// Input and output operation flags that can be passed to the `ioFlags` parameter on ::VRLoadTreeEx and ::VRSaveTreeEx
/// @{

/// Signals the file IO to only output Libraries that are changed
const uint64_t FILEIO_CHANGED_ONLY = ((uint64_t)1 << 0);

/// Signals the file IO that this call to loadTree() is nested inside another
const uint64_t FILEIO_NESTED = ((uint64_t)1 << 1);

/// Signals the file IO that this call to loadTree() is merging files into the current scene, newly created
/// library nodes will always be flagged as dirty so they are saved with the existing data they have been merged with
const uint64_t FILEIO_MERGE = ((uint64_t)1 << 2);

/// Signals the file IO that we should override the NO_SAVE flag and save anyways
const uint64_t FILEIO_FORCE_SAVE = ((uint64_t)1 << 3);

/// Signals that the file IO should not preserve the Node UUID's
const uint64_t FILEIO_NEW_UUIDS = ((uint64_t)1 << 4);

/// Signals that the file IO should throw an exception if the file being loaded does not have UUID's
const uint64_t FILEIO_UUIDS_MUST_EXIST = ((uint64_t)1 << 5);

/// Signals that Library nodes' archive flag should be ignored
const uint64_t FILEIO_MONOLITHIC = ((uint64_t)1 << 6);

/// Signals that values of properties that aren't saved should be ignored when loading
const uint64_t FILEIO_IGNORE_UNSAVED_PROPERTIES = ((uint64_t)1 << 7);

/// Signals that the document should be saved as a system document.
const uint64_t FILEIO_SYSTEM_DOCUMENT = ((uint64_t)1 << 8);

/// Signals that the document should be saved as a system document.
const uint64_t FILEIO_OVERLAY_DOCUMENT = ((uint64_t)1 << 9);

/// Signals that the nodes siblings should be saved.
const uint64_t FILEIO_SAVE_SIBLINGS_TOO = ((uint64_t)1 << 32);

/// Signals that the files should be saved/loaded as a VRNative file. 
const uint64_t FILEIO_FILE_FORMAT_MACHINE = ((uint64_t)1 << 33);

/// Signals that the file should be saved/loaded as a VRText file.
const uint64_t FILEIO_FILE_FORMAT_HUMAN = ((uint64_t)1 << 34);

/// Signals that the save/load operation should determine the file format from the file extension. 
const uint64_t FILEIO_FILE_FORMAT_GUESS = ((uint64_t)1 << 35);

/// @}

/// @defgroup api_builder_flags Build Filter flags
/// Input and output operation flags that can be passed to the `builderFlags` parameter on ::VRLoadTreeEx
/// @{

/// Signals that the load operation should populate property values with defaults when the value does not exist in the file
const uint32_t BUILDFILTER_ALLOW_MISSING_ATTRIBS = (1 << 0);

/// Signals that the load operation should merge the standard root nodes 
/// (e.g. a file containing a Scenes node will load its contents into the existing Scenes tree)
const uint32_t BUILDFILTER_MERGE_ROOTS = (1 << 1);

/// Signals that the load operation should merge all nodes by UUID where possible
const uint32_t BUILDFILTER_MERGE_ALL = (1 << 2);

/// Signals that the loader should continue even if it encounters node types that it does not understand
const uint32_t BUILDFILTER_ALLOW_MISSING_METANODES = (1 << 3);

/// Signals that the loader should continue even if it encounters properties that it does not understand
const uint32_t BUILDFILTER_ALLOW_INVALID_ATTRIBS = (1 << 4);

/// @}

/// @defgroup api_loggingmask Logging masks
/// Flags that control the level of API error reporting. These can be combined.
/// @{

/// Do not set any internal error codes nor generate any messages
const uint32_t VRTREE_ERRORLEVEL_NONE = 0;

/// Record critial errors
const uint32_t VRTREE_ERRORLEVEL_ERRORS = (1 << 0);

/// Record warnings
const uint32_t VRTREE_ERRORLEVEL_WARNINGS = (1 << 1);

/// Record debug messages
const uint32_t VRTREE_ERRORLEVEL_DEBUG = (1 << 2);

/// Record info messages
const uint32_t VRTREE_ERRORLEVEL_INFO = (1 << 3);

/// @}

/// @defgroup api_errors Error codes
/// Error codes that might be set if an API function fails, assuming the log level is something other than VRTREE_ERRORLEVEL_NONE
/// @{

/// No error - operation succeeded
const uint32_t VRTREE_API_OK = 0;

/// API function expected a valid object handle
const uint32_t VRTREE_API_INVALID_HANDLE = 1;

/// API function expected a valid parameter (buffer, string, etc)
const uint32_t VRTREE_API_INVALID_PARAMETER = 2;

/// API function expected a valid property name/index
const uint32_t VRTREE_API_INVALID_PROPERTY = 3;

/// API function expected a valid metanode name/handle
const uint32_t VRTREE_API_INVALID_METANODE = 4;

/// API function attempted to perform migrations but some are missing
const uint32_t VRTREE_API_MISSING_MIGRATIONS = 5;

/// API function was called without adequate permissions
const uint32_t VRTREE_API_INVALID_SECURITYCONTEXT = 6;

/// API function attempted to do something inherently forbidden
const uint32_t VRTREE_API_NOT_ALLOWED = 7;

/// @}
/// @}
#endif

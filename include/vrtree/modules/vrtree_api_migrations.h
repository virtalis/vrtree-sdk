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

/// @defgroup api_migrations Migrations
/// Functions for defining metanode @ref advanced_metanode_versioning "migrations"
/// @{

/// Removes a property from a metanode
/// @param metaNode handle to the metanode to modify
/// @param propertyName name of the property to remove
/// @return 0 if property is removed
VR_API (int, VRRemoveProperty, (HMeta metaNode, const char* propertyName));

/// Changes the specified property to single element VR_BOOL type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyBool, (HMeta metaNode, const char* propName));

/// Changes the specified property to single element VR_CHAR type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyChar, (HMeta metaNode, const char* propName));

/// Changes the specified property to single element VR_INT type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyInt, (HMeta metaNode, const char* propName));

/// Changes the specified property to single element VR_FLOAT type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyFloat, (HMeta metaNode, const char* propName));

/// Changes the specified property to single element VR_DOUBLE type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyDouble, (HMeta metaNode, const char* propName));

/// Changes the specified property to single element VR_WORLD_FLOAT type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyWorldFloat, (HMeta metaNode, const char* propName));

/// Changes the specified property to single element VR_STRING type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyString, (HMeta metaNode, const char* propName));

/// Changes the specified property to single element VR_LINK type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyLink, (HMeta metaNode, const char* propName));

/// Changes the specified property to a VR_VEC_CHAR type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyVectorChar, (HMeta metaNode, const char* propName));

/// Changes the specified property to a VR_VEC_STRING type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API(int, VRChangePropertyVectorString, (HMeta metaNode, const char* propName));

/// Changes the specified property to a VR_VEC_INT type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyVectorInt, (HMeta metaNode, const char* propName));

/// Changes the specified property to a VR_VEC_FLOAT type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyVectorFloat, (HMeta metaNode, const char* propName));

/// Changes the specified property to a VR_VEC_WORLD_FLOAT type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @return 0 on success
VR_API (int, VRChangePropertyVectorWorldFloat, (HMeta metaNode, const char* propName));

/// Changes the specified property to a VR_BOOL array type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @param numElements number of elements in the new array property
/// @return 0 on success
VR_API (int, VRChangePropertyArrayBool, (HMeta metaNode, const char* propName, int numElements));

/// Changes the specified property to a VR_CHAR array type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @param numElements number of elements in the new array property
/// @return 0 on success
VR_API (int, VRChangePropertyArrayChar, (HMeta metaNode, const char* propName, int numElements));

/// Changes the specified property to a VR_INT array type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @param numElements number of elements in the new array property
/// @return 0 on success
VR_API (int, VRChangePropertyArrayInt, (HMeta metaNode, const char* propName, int numElements));

/// Changes the specified property to a VR_FLOAT array type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @param numElements number of elements in the new array property
/// @return 0 on success
VR_API (int, VRChangePropertyArrayFloat, (HMeta metaNode, const char* propName, int numElements));

/// Changes the specified property to a VR_DOUBLE array type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change 
/// @param numElements number of elements in the new array property
/// @return 0 on success
VR_API (int, VRChangePropertyArrayDouble, (HMeta metaNode, const char* propName, int numElements));

/// Changes the specified property to a VR_WORLD_FLOAT array type
/// @param metaNode handle to the metanode to change
/// @param propName name of the property to change
/// @param numElements number of elements in the new array property
/// @return 0 on success
VR_API (int, VRChangePropertyArrayWorldFloat, (HMeta metaNode, const char* propName, int numElements));

/// Renames a property
/// @param metaNode handle to the metanode to change
/// @param propName the name of the property to rename
/// @param newPropName the new name of the property
/// @return 0 on success
VR_API (int, VRChangePropertyName, (HMeta metaNode, const char* propName, const char* newPropName));

/// Closes a migration handle
/// @param migration the handle to close
VR_API (void, VRCloseMigrationHandle, (HMigration migration));

/// Adds a migration to the ordered list of migrations applied to the metanode.
///
/// The function provided is expected to be implemented to call VRSetMigration functions.
/// (::VRSetMigrationUp, ::VRSetMigrationDown, ::VRSetMigrationUpgradeNode, ::VRSetMigrationDowngradeNode)
///
/// The number of calls to this function during metanode creation defines the version number of the metanode.
///
/// Migrations can only be added to uninstantiated metanodes.
/// 
/// @param metaNode handle to the metanode to modify
/// @param func function to call to register the migration specifics. This function is called immediately.
/// @return 0 if the migration is added successfully.
VR_API (int, VRAddMigration, (HMeta metaNode, MigrationAddFunc func));

/// Adds an upgrade function to a migration
/// @param migration handle to migration to modify
/// @param func function implementing the upgrade. the implementation need not close the handle parameters.
/// @return 0 if the function is added successfully
VR_API (int, VRSetMigrationUp, (HMigration migration, MigrationUpFunc func));

/// Adds a downgrade function to a migration
/// @param migration handle to migration to modify
/// @param func function implementing the downgrade. the implementation need not close the handle parameters.
/// @return 0 if the function is added successfully
VR_API (int, VRSetMigrationDown, (HMigration migration, MigrationDownFunc func));

/// Adds a node upgrade function to a migration
/// @param migration handle to migration to modify
/// @param func function implementing the upgrade. the implementation need not close the handle parameters.
/// @return 0 if the function is added successfully
VR_API (int, VRSetMigrationUpgradeNode, (HMigration migration, MigrationUpgradeFunc func));

/// Adds a node downgrade function to a migration
/// @param migration handle to migration to modify
/// @param func function implementing the downgrade. the implementation need not close the handle parameters.
/// @return 0 if the function is added successfully
VR_API (int, VRSetMigrationDowngradeNode, (HMigration migration, MigrationDowngradeFunc func));

/// Gets the previous migration in the chain (the one for the version before this one)
/// @param migration handle to the migration
/// @return the previous migration or NULL if this is the oldest one
VR_API (HMigration, VRMigrationPrev, (HMigration migration));

/// Gets the next migration in the chain (the one for the version after this one)
/// @param migration handle to the migration
/// @return the next migration or NULL if this is the newest one
VR_API (HMigration, VRMigrationNext, (HMigration migration));

VR_API (int, VRAddInstanceMigration, (HNode node, MigrationFunc func, void* userData));

/// Calls the registered upgrade node function of the migration previous or next to this one
/// (depending on whether node is older or newer than migration).
/// This effectively brings node up to date, ready for this migration to perform its upgrade.
///
/// @param migration handle to the migration
/// @param node the node to transform to the version of this migration
/// @return handle to the node at the requested version.
VR_API (HNode, VRMigrationPrepareNode, (HMigration migration, HNode node));

/// Creates an instance of a node using the metanode version defined by this migration
VR_API (HNode, VRMigrationCreateCurrentNode, (HMigration migration, HNode node));

/// Copies values of all properties that exist on both new and old node versions of the nodes.
/// The nodes must be the same basic type, but may be different versions of that type.
/// Properties that do not match in name or type between the versions are left for the migration implementation to handle.
/// @param migration migration handle
/// @param old the old version of the node (source)
/// @param newNode the new node to copy into (dest)
/// @return 0 on success
VR_API (int, VRMigrationCopyKnownProperties, (HMigration migration, HNode old, HNode newNode));

/// Helper function for completing a migration step.
/// This function moves all children of old to newNode, deletes old, and closes its handle
/// @param migration the migration being completed
/// @param old the node to clear and delete
/// @param newNode the new parent of the children being moved
/// @return 0 on success
VR_API (int, VRMigrationFinish, (HMigration migration, HNode old, HNode newNode));

/// @}

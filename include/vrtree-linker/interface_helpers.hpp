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

#pragma once
#include "../vrtree/api.h"
#include <string>
#include <vector>

/// Namespace containing a collection of helper functions for simplifying reading of C++ objects out of the C API (e.g. strings, etc)
namespace vrtree_cpp {

/// Helper structure that provides a reference count that persists between refcounted handle copies
struct HRefCount {
  HRefCount() : rc(0) {}
  HRefCount(const HRefCount&) : rc(0) {}
  HRefCount& operator=(const HRefCount&) { return *this; }

  /// Increments the reference counter
  void inc() { ++rc; }

  /// Decrements the reference counter. If the reference counter hits zero, this instance is deleted.
  bool dec() { if(rc > 1) { --rc; return true; } else { delete this; return false; } }
  
  /// Reference counter
  unsigned int rc;
};

/// Helper struct to take any handle and close it appropriately
struct Handle {
  /// Closes a node handle
  static void close(HNode handle) { VRCloseNodeHandle(handle); }

  /// Closes a metanode handle
  static void close(HMeta handle) { VRCloseMetaHandle(handle); }

  /// Closes a migration handle
  static void close(HMigration handle) { VRCloseMigrationHandle(handle); }

  /// Close an FFI var handle
  static void close(HFFIVar handle) { VRFFIFree(handle); }
};

/// Reference counted wrapper around a handle. Automatically closes the handle when there are no references left.
template <typename T>
struct HTypeR {
  /// Reference counter. Automatically deletes itself when the refcount is zero
  HRefCount* ptr;

  /// The handle to wrap
  T m_handle;

  /// Construct a null handle
  HTypeR<T>() : ptr(0), m_handle(0) {}

  /// Decrements refcount, closing the node handle if this is the last reference
  ~HTypeR<T>() { dec(); }

  /// Copy an existing handle, incrementing its refcount
  HTypeR<T>(const HTypeR<T>& other) : ptr(other.ptr), m_handle(other.m_handle) { inc(); }

  /// Construct from a raw node handle and make it refcounted
  HTypeR<T>(T handle) : ptr(new HRefCount()), m_handle(handle) { inc(); }

  /// Assign an existing handle
  HTypeR<T>& operator=(const HTypeR<T>& other) { 
    if(ptr != other.ptr) { 
      dec(); ptr = other.ptr; m_handle = other.m_handle; inc(); 
    } 
    return *this; 
  }

  /// Assign a raw handle and make it refcounted
  HTypeR<T>& operator=(T handle) { 
    if(m_handle != handle) { 
      dec(); 
      ptr = new HRefCount(); 
      m_handle = handle; 
      inc();
    } 
    return *this; 
  }

  /// Access the raw node handle
  operator T() const { return m_handle; }

  /// Compare the raw node handle for storage in ordered containers
  bool operator < (T other) const { return other < m_handle; }

  /// Manually increment the refcount (effectively makes the handle permanent until manually closed)
  void inc() { if(ptr) ptr->inc(); }

  /// Manually decrement the refcount. If recount hits zero, handle is closed.
  void dec() { if(ptr) if(!ptr->dec() && m_handle) Handle::close(m_handle); }

  /// Converts an array of reference counted handles to an array of raw handles for passing
  /// to an api function that expects an array of handles.
  /// Return value is only valid until the next call to this function.
  static T* raw(const HTypeR<T> arr[]) {
    static std::vector<T> tempArray;
    size_t n = sizeof(arr);
    tempArray.resize(n);
    for(size_t i = 0; i < n; ++i) {
      tempArray[i] = arr[i];
    }
    return &tempArray[0];
  }
};

/// Reference counted node handle
typedef HTypeR<HNode> HNodeR;

/// Reference counted metanode handle
typedef HTypeR<HMeta> HMetaR;

/// Reference counted migration handle
typedef HTypeR<HMigration> HMigrationR;

/// Reference counted FFI handle
typedef HTypeR<HFFIVar> HFFIVarR;

/// Utility function for reading a string property.
///
/// Uses an internal buffer to provide to the C API, and copies it into 
/// the returned std::string object.
static std::string readStringProp(HNode node, const char* propName) 
{
  std::vector<char> vProp(1, 0);
  if(size_t len = VRGetPropertyValueSize(node, propName)) {
    vProp.resize(len);
    VRGetPropertyString(node, propName, &vProp[0], len);
  }
  return (const char*)&vProp[0];
}

/// Utility function for reading a string property.
///
/// Uses an internal buffer to provide to the C API, and copies it into 
/// the returned std::string object.
static std::string readStringProp(HNode node, uint32_t prop) 
{
  std::vector<char> vProp(1, 0);
  if(size_t len = VRGetPropertyValueSizeEx(node, prop)) {
    vProp.resize(len);
    VRGetPropertyStringEx(node, prop, &vProp[0], len);
  }
  return (const char*)&vProp[0];
}

/// Utility function for getting the name of a node
///
/// Uses an internal buffer to provide to the C API, and copies it into 
/// the returned std::string object.
static std::string getNodeName(HNode node)
{
  std::vector<char> vName(1, 0);
  if(size_t len = VRGetNodeNameLength(node)) {
    vName.resize(len);
    VRGetNodeName(node, &vName[0], len);
  }
  return (const char*)&vName[0];
}

/// Utility function for getting the path of a node
///
/// Uses an internal buffer to provide to the C API, and copies it into 
/// the returned std::string object.
static std::string getNodePath(HNode node)
{
  std::vector<char> vPath(1, 0);
  if(size_t len = VRGetNodePathLength(node)) {
    vPath.resize(len);
    VRGetNodePath(node, &vPath[0], len);
  }
  return (const char*)&vPath[0];
}

/// Wraps a class implementing static observer functions accepting refcounted handles
template<typename T>
struct ObserverWrapper
{ // Cast to HNodeR so C++ can safely access node handles, without having to call VRCloseNodeHandle
  static void NodeCreated(HNode vrNode, void*) { HNodeR managedNode = VRCopyNodeHandle(vrNode); T::NodeCreated(managedNode); }
  static void NodeDestroying(HNode vrNode, void*) { HNodeR managedNode = VRCopyNodeHandle(vrNode); T::NodeDestroying(managedNode); }
  static void NodeValuesChanged(HNode vrNode, void*) { HNodeR managedNode = VRCopyNodeHandle(vrNode); T::NodeValuesChanged(managedNode); }
  static void NodeRenamed(HNode vrNode, void*) { HNodeR managedNode = VRCopyNodeHandle(vrNode); T::NodeRenamed(managedNode); }
  static void NodeChildAdded(HNode vrParent, HNode vrChild, void*)
  {
    HNodeR managedParentNode = VRCopyNodeHandle(vrParent);
    HNodeR managedChildNode = VRCopyNodeHandle(vrChild);
    T::NodeChildAdded(managedParentNode, managedChildNode);
  }
  static void NodeChildRemoved(HNode vrParent, HNode vrChild, void*)
  {
    HNodeR managedParentNode = VRCopyNodeHandle(vrParent);
    HNodeR managedChildNode = VRCopyNodeHandle(vrChild);
    T::NodeChildRemoved(managedParentNode, managedChildNode);
  }
  static void NodeParentChanged(HNode vrNode, HNode vrNewParent, HNode vrOldParent, void*)
  {
    HNodeR managedNode = VRCopyNodeHandle(vrNode);
    HNodeR managedNewParentNode = VRCopyNodeHandle(vrNewParent);
    HNodeR managedOldParentNode = VRCopyNodeHandle(vrOldParent);
    T::NodeParentChanged(managedNode, managedNewParentNode, managedOldParentNode);
  }
};

/// Registers a class implementing static observer functions as an observer of the specified metanode
template<typename T>
void RegisterObserver(const char* metaName)
{
  VRAddCallbackNodeCreation(metaName, &ObserverWrapper<T>::NodeCreated, nullptr);
  VRAddCallbackNodeDestruction(metaName, &ObserverWrapper<T>::NodeDestroying, nullptr);
  VRAddCallbackNodeValuesChanged(metaName, &ObserverWrapper<T>::NodeValuesChanged, nullptr);
  VRAddCallbackNodeRenamed(metaName, &ObserverWrapper<T>::NodeRenamed, nullptr);
  VRAddCallbackNodeChildAdded(metaName, &ObserverWrapper<T>::NodeChildAdded, nullptr);
  VRAddCallbackNodeChildRemoved(metaName, &ObserverWrapper<T>::NodeChildRemoved, nullptr);
  VRAddCallbackNodeParentChanged(metaName, &ObserverWrapper<T>::NodeParentChanged, nullptr);
}

/// Unregisters a class implementing static observer functions as an observer of the specified metanode
template<typename T>
void UnRegisterObserver(const char* metaName)
{
  VRRemoveCallbackNodeCreation(metaName, &ObserverWrapper<T>::NodeCreated);
  VRRemoveCallbackNodeDestruction(metaName, &ObserverWrapper<T>::NodeDestroying);
  VRRemoveCallbackNodeValuesChanged(metaName, &ObserverWrapper<T>::NodeValuesChanged);
  VRRemoveCallbackNodeRenamed(metaName, &ObserverWrapper<T>::NodeRenamed);
  VRRemoveCallbackNodeChildAdded(metaName, &ObserverWrapper<T>::NodeChildAdded);
  VRRemoveCallbackNodeChildRemoved(metaName, &ObserverWrapper<T>::NodeChildRemoved);
  VRRemoveCallbackNodeParentChanged(metaName, &ObserverWrapper<T>::NodeParentChanged);
}

/// Utility class providing an interface for responding to changes to specified metanodes;
/// with an additional update function, which will be called every time a frame is drawn.
class NodeManager
{
public:
  virtual void update(double deltaTime) {}
  virtual void nodeCreated(HNodeR& vrNode) {}
  virtual void nodeDestroying(HNodeR& vrNode) {}
  virtual void nodeValuesChanged(HNodeR& vrNode) {}
  virtual void nodeRenamed(HNodeR& vrNode) {}
  virtual void nodeChildAdded(HNodeR& vrParent, HNodeR& vrChild) {}
  virtual void nodeChildRemoved(HNodeR& vrParent, HNodeR& vrChild) {}
  virtual void nodeParentChanged(HNodeR& vrNode, HNodeR& vrNewParent, HNodeR& vrOldParent) {}

  void registerUpdateable()
  {
    VRAddCallbackUpdate(&NodeManager::Update, this);
  }
  void unRegisterUpdateable()
  {
    VRRemoveCallbackUpdateEx(&NodeManager::Update, this);
  }

  /// Registers a class implementing static observer functions as an observer of the specified metanode
  void registerObserver(const char* metaName)
  {
    VRAddCallbackNodeCreation(metaName, &NodeManager::NodeCreated, this);
    VRAddCallbackNodeDestruction(metaName, &NodeManager::NodeDestroying, this);
    VRAddCallbackNodeValuesChanged(metaName, &NodeManager::NodeValuesChanged, this);
    VRAddCallbackNodeRenamed(metaName, &NodeManager::NodeRenamed, this);
    VRAddCallbackNodeChildAdded(metaName, &NodeManager::NodeChildAdded, this);
    VRAddCallbackNodeChildRemoved(metaName, &NodeManager::NodeChildRemoved, this);
    VRAddCallbackNodeParentChanged(metaName, &NodeManager::NodeParentChanged, this);
  }

  /// Unregisters a class implementing static observer functions as an observer of the specified metanode
  void unRegisterObserver(const char* metaName)
  {
    VRRemoveCallbackNodeCreationEx(metaName, &NodeManager::NodeCreated, this);
    VRRemoveCallbackNodeDestructionEx(metaName, &NodeManager::NodeDestroying, this);
    VRRemoveCallbackNodeValuesChangedEx(metaName, &NodeManager::NodeValuesChanged, this);
    VRRemoveCallbackNodeRenamedEx(metaName, &NodeManager::NodeRenamed, this);
    VRRemoveCallbackNodeChildAddedEx(metaName, &NodeManager::NodeChildAdded, this);
    VRRemoveCallbackNodeChildRemovedEx(metaName, &NodeManager::NodeChildRemoved, this);
    VRRemoveCallbackNodeParentChangedEx(metaName, &NodeManager::NodeParentChanged, this);
  }
private:
  static void Update(double deltaTime, void* userData)
  {
    ((NodeManager*)userData)->update(deltaTime);
  }
  static void NodeCreated(HNode vrNode, void* ud) { HNodeR managedNode = VRCopyNodeHandle(vrNode); ((NodeManager*)ud)->nodeCreated(managedNode); }
  static void NodeDestroying(HNode vrNode, void* ud) { HNodeR managedNode = VRCopyNodeHandle(vrNode); ((NodeManager*)ud)->nodeDestroying(managedNode); }
  static void NodeValuesChanged(HNode vrNode, void* ud) { HNodeR managedNode = VRCopyNodeHandle(vrNode); ((NodeManager*)ud)->nodeValuesChanged(managedNode); }
  static void NodeRenamed(HNode vrNode, void* ud) { HNodeR managedNode = VRCopyNodeHandle(vrNode); ((NodeManager*)ud)->nodeRenamed(managedNode); }
  static void NodeChildAdded(HNode vrParent, HNode vrChild, void* ud)
  {
    HNodeR managedParentNode = VRCopyNodeHandle(vrParent);
    HNodeR managedChildNode = VRCopyNodeHandle(vrChild);
    ((NodeManager*)ud)->nodeChildAdded(managedParentNode, managedChildNode);
  }
  static void NodeChildRemoved(HNode vrParent, HNode vrChild, void* ud)
  {
    HNodeR managedParentNode = VRCopyNodeHandle(vrParent);
    HNodeR managedChildNode = VRCopyNodeHandle(vrChild);
    ((NodeManager*)ud)->nodeChildRemoved(managedParentNode, managedChildNode);
  }
  static void NodeParentChanged(HNode vrNode, HNode vrNewParent, HNode vrOldParent, void* ud)
  {
    HNodeR managedNode = VRCopyNodeHandle(vrNode);
    HNodeR managedNewParentNode = VRCopyNodeHandle(vrNewParent);
    HNodeR managedOldParentNode = VRCopyNodeHandle(vrOldParent);
    ((NodeManager*)ud)->nodeParentChanged(managedNode, managedNewParentNode, managedOldParentNode);
  }
};



#ifdef _kHugeWorld_h_
static int setWorldFloat(HNode node, const char* propName, vtCore::floatw val)
{
  if(VRGetWorldFloatSize() == sizeof(float)) {
    return VRSetPropertyFloat(node, propName, (float)val);
  }
  else {
    return VRSetPropertyDouble(node, propName, val);
  }
}

static int setWorldFloat(HNode node, uint32_t prop, vtCore::floatw val)
{
  if(VRGetWorldFloatSize() == sizeof(float)) {
    return VRSetPropertyFloatEx(node, prop, (float)val, 0, 0);
  }
  else {
    return VRSetPropertyDoubleEx(node, prop, val, 0, 0);
  }
}

#endif

}
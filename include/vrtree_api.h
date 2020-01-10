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

//this file is not intended for inclusion within vrtree.dll, so it should undef any internals to avoid
//re-inclusion related errors when dynamic loading code is included after vrtree (metanode headers include api)
#ifdef VRAPI_INTERNAL
#undef VRAPI_INTERNAL
#endif
#ifdef VR_API
#undef VR_API
#endif
#ifdef VRAPI_H
#undef VRAPI_H
#endif

#include "vrtree/api.h"
#include "vrtree-linker/vrtree_interface.h"

#ifdef __cplusplus
#include "vrtree-linker/interface_helpers.hpp"
#endif

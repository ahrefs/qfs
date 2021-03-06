//---------------------------------------------------------- -*- Mode: C++ -*-
// $Id$
//
// Created 2007/09/20
// Author: Sriram Rao
//
// Copyright 2008,2016 Quantcast Corporation. All rights reserved.
// Copyright 2007-2008 Kosmix Corp.
//
// This file is part of Kosmos File System (KFS).
//
// Licensed under the Apache License, Version 2.0
// (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
// implied. See the License for the specific language governing
// permissions and limitations under the License.
//
// \brief Move all the blocks (chunks) from one file after the last block of
// another file.
//
//----------------------------------------------------------------------------

#include "kfsshell.h"
#include "libclient/KfsClient.h"

#include <errno.h>

#include <iostream>

namespace KFS {
namespace tools {

using std::cout;
using std::vector;
using std::string;

int
handleAppend(KfsClient* kfsClient, const vector<string>& args)
{
    if (args.size() != 2 || args[0] == "--help") {
        cout << "Usage: append src dst " << "\n";
        return -EINVAL;
    }
    chunkOff_t offset = -1;
    const int ret = kfsClient->CoalesceBlocks(
        args[0].c_str(), args[1].c_str(), &offset);
    cout << "append status: " << ErrorCodeToStr(ret) <<
        " offset: " << offset << "\n";
    return ret;
}

}
}

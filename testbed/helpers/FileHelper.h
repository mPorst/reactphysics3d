/********************************************************************************
* ReactPhysics3D physics library, http://www.reactphysics3d.com                 *
* Copyright (c) 2025 Moritz Porst                                               *
*********************************************************************************
*                                                                               *
* This software is provided 'as-is', without any express or implied warranty.   *
* In no event will the authors be held liable for any damages arising from the  *
* use of this software.                                                         *
*                                                                               *
* Permission is granted to anyone to use this software for any purpose,         *
* including commercial applications, and to alter it and redistribute it        *
* freely, subject to the following restrictions:                                *
*                                                                               *
* 1. The origin of this software must not be misrepresented; you must not claim *
*    that you wrote the original software. If you use this software in a        *
*    product, an acknowledgment in the product documentation would be           *
*    appreciated but is not required.                                           *
*                                                                               *
* 2. Altered source versions must be plainly marked as such, and must not be    *
*    misrepresented as being the original software.                             *
*                                                                               *
* 3. This notice may not be removed or altered from any source distribution.    *
*                                                                               *
********************************************************************************/
#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <string>
#include <filesystem>

namespace helpers
{

// search a folder with name foldername, traversing towards the root directory starting at startSearchPath
// returns empty path when no folder is found
static std::filesystem::path findFolderAbove(std::string_view foldername, std::filesystem::path startSearchPath){
  // search fails if a trailing slash is present, so remove it
  if(foldername.back() == '/'){
    foldername.remove_suffix(1);
  }
  std::filesystem::path& searchPath = startSearchPath;
  bool rootDirectoryReached = false;
  
  while(!rootDirectoryReached) {

    for(auto& dirEntry : std::filesystem::directory_iterator{searchPath}) {
      
      if(std::filesystem::is_directory(dirEntry.path()) && 
          dirEntry.path().filename() == foldername) {
        return dirEntry.path();
      }
    }
    rootDirectoryReached = (searchPath == searchPath.parent_path());
    searchPath = searchPath.parent_path();
  }
  return std::filesystem::path{};
}

// shorthand for finding a folder starting from current path
static std::filesystem::path findFolderAbove(std::string_view foldername)
{
  return findFolderAbove(foldername, std::filesystem::current_path());
}
  
}

#endif // FILE_HELPER_H
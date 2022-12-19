//
//  Metadata.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#include "Metadata.h"

std::string Metadata::getAppVersion()
{
    std::string version = "v";
    version += std::to_string(major);
    version += ".";
    version += std::to_string(minor);
    version += ".";
    version += std::to_string(patch);
    return version;
}

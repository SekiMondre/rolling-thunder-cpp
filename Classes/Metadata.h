//
//  Metadata.h
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#ifndef Metadata_h
#define Metadata_h

#include "axmol.h"

namespace Metadata
{
    const u_int8_t major = 1;
    const u_int8_t minor = 1;
    const u_int8_t patch = 2;
    
    std::string getAppVersion();
}

#endif /* Metadata_h */

#ifndef _WebsiteBuilder_h
#define _WebsiteBuilder_h

#include <string>
#include "MemoryMap.h"

class WebsiteBuilder{

    public:
        String generateConfigPage();
        static String generateLoginPage(const String& placeholder);
};
#endif
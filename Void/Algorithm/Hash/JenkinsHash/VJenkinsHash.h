#pragma once
#ifndef _V_JENKINSHASH_H_
#define _V_JENKINSHASH_H_

#include <stddef.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VJenkinsHash
    //----------------------------------------------------------------------------------------------------
    class VJenkinsHash
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static unsigned OneAtATimeHash(const char* _key, size_t _length);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        static void Mix(unsigned& _a, unsigned& _b, unsigned& _c);
        
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VJenkinsHashTest();
}

#endif

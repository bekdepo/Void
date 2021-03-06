#pragma once
#ifndef _V_INTERNETPROTOCOL_H_
#define _V_INTERNETPROTOCOL_H_


//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VInternetProtocolVersion
    // Internet Layer
    //----------------------------------------------------------------------------------------------------
    enum class VInternetProtocolVersion
    {
        Version4 = 4,
        Version6 = 6,
    };
        
    // Test
    //----------------------------------------------------------------------------------------------------
    void VInternetProtocolTest();
}

#endif

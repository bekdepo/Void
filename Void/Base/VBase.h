#pragma once
#ifndef _V_BASE_H_
#define _V_BASE_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VBase
	//----------------------------------------------------------------------------------------------------
	class VBase
	{
	public:
		VBase();
		VBase(const VBase& _base);
		virtual ~VBase();
	};
}

#endif
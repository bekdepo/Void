#include "VAudioWindowsHandler.h"
#ifdef _VOID_USE_WINMM_
#include "../../AudioFormat/VAudioFormat.h"
#include "../../../Utility/Logger/VLogger.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VAudioWindowsHandler
	//----------------------------------------------------------------------------------------------------
	VAudioWindowsHandler::VAudioWindowsHandler()
	{

	}

	//----------------------------------------------------------------------------------------------------
	VAudioWindowsHandler::VAudioWindowsHandler(const VAudioWindowsHandler& _handler)
	{

	}

	//----------------------------------------------------------------------------------------------------
	std::map<int, VAudioDevice> VAudioWindowsHandler::LoadDevice()
	{
		// Input
		WAVEINCAPS waveInCaps;
		int inputCount = waveInGetNumDevs();
		for (int i = 0; i < inputCount; ++i)
		{
			waveInGetDevCaps(i, &waveInCaps, sizeof(WAVEINCAPS));
		}

		// Output
		WAVEOUTCAPS waveOutCaps;
		int outputCount = waveOutGetNumDevs();
		for (int i = 0; i < outputCount; ++i)
		{
			waveOutGetDevCaps(i, &waveOutCaps, sizeof(WAVEINCAPS));
		}

		return std::map<int, VAudioDevice>();
	}

	//----------------------------------------------------------------------------------------------------
	int VAudioWindowsHandler::DefaultInputDeviceId()
	{

		return -1;
	}

	//----------------------------------------------------------------------------------------------------
	int VAudioWindowsHandler::DefaultOutputDeviceId()
	{

		return -1;
	}

	//----------------------------------------------------------------------------------------------------
	bool VAudioWindowsHandler::Open(VAudioStream& _stream)
	{

		return false;
	}

	//----------------------------------------------------------------------------------------------------
	bool VAudioWindowsHandler::Start(VAudioStream& _stream)
	{

		return false;
	}

	// Test
	//----------------------------------------------------------------------------------------------------
	void VAudioWindosHandlerTest()
	{

		return;
	}

}

#endif

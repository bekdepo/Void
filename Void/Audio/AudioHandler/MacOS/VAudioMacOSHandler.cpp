#include "VAudioMacOSHandler.h"
#ifdef _VOID_USE_COREAUDIO_
#include "../../../Utility/Logger/VLogger.h"
#include <CoreAudio/CoreAudio.h>
//#include <AudioToolbox/AudioToolbox.h>
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VAudioMacOSHandler
    //----------------------------------------------------------------------------------------------------
    VAudioMacOSHandler::VAudioMacOSHandler()
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VAudioMacOSHandler::VAudioMacOSHandler(const VAudioMacOSHandler& _handler)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    std::map<int, VAudioDevice> VAudioMacOSHandler::LoadDevice()
    {
        #ifdef __MAC_10_0
        std::map<int, VAudioDevice> result;
        AudioObjectPropertyAddress address = { kAudioHardwarePropertyDevices, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster };
        UInt32 size(0);
        if (AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &address, 0, nullptr, &size) != kAudioHardwareNoError) { return std::map<int, VAudioDevice>(); };
        int deviceCount = size / sizeof(AudioDeviceID);
        if (deviceCount)
        {
            // DeviceIds
            std::vector<AudioDeviceID> deviceIds(deviceCount);
            if (AudioObjectGetPropertyData(kAudioObjectSystemObject, &address, 0, nullptr, &size, deviceIds.data()) != kAudioHardwareNoError) { return std::map<int, VAudioDevice>(); };
            for (int i = 0; i < deviceCount; ++i)
            {
                VAudioDevice device;
                // Device id
                device.deviceId = deviceIds[i];
                // Device name
                address.mSelector = kAudioDevicePropertyDeviceName;
                if (AudioObjectGetPropertyDataSize(device.deviceId, &address, 0, nullptr, &size) == kAudioHardwareNoError)
                {
                    device.deviceName.resize(size);
                    AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, (void*)device.deviceName.data());
                }
                // Sample rate
                size = sizeof(Float64);
                address.mSelector = kAudioDevicePropertyNominalSampleRate;
                AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, &device.sampleRate);
                // Channels
                address = { kAudioDevicePropertyStreamConfiguration, kAudioDevicePropertyScopeInput };
                if (AudioObjectGetPropertyDataSize(device.deviceId, &address, 0, nullptr, &size) == kAudioHardwareNoError)
                {
                    std::vector<AudioBufferList> bufferList(size / sizeof(AudioBufferList) + 1);
                    if (AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, bufferList.data()) == kAudioHardwareNoError)
                    {
                        for (UInt32 i = 0; i < bufferList[0].mNumberBuffers; ++i)
                        {
                            device.maxInputChannels += bufferList[0].mBuffers[i].mNumberChannels;
                        }
                    }
                }
                address = { kAudioDevicePropertyStreamConfiguration, kAudioDevicePropertyScopeOutput };
                if (AudioObjectGetPropertyDataSize(device.deviceId, &address, 0, nullptr, &size) == kAudioHardwareNoError)
                {
                    std::vector<AudioBufferList> bufferList(size / sizeof(AudioBufferList) == 0 ? 1 : size / sizeof(AudioBufferList));
                    if (AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, bufferList.data()) == kAudioHardwareNoError)
                    {
                        for (UInt32 i = 0; i < bufferList[0].mNumberBuffers; ++i)
                        {
                            device.maxOutputChannels += bufferList[0].mBuffers[i].mNumberChannels;
                        }
                    }
                }
                // Frame latency
                size = sizeof(UInt32);
                address = { kAudioDevicePropertyLatency, kAudioDevicePropertyScopeInput };
                AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, &device.frameLatency);
                address = { kAudioDevicePropertyLatency, kAudioDevicePropertyScopeOutput };
                AudioObjectGetPropertyData(device.deviceId, &address, 0, nullptr, &size, &device.frameLatency);
                // Push
                result[device.deviceId] = device;
            }
        }
        return result;
        #else
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wdeprecated-declarations"
        std::map<int, VAudioDevice> result;
        UInt32 size(0);
        if (AudioHardwareGetPropertyInfo(kAudioHardwarePropertyDevices, &size, nullptr) != kAudioHardwareNoError) { return std::map<int, VAudioDevice>(); };
        int deviceCount = size / sizeof(AudioDeviceID);
        if (deviceCount)
        {
            // DeviceIds
            std::vector<AudioDeviceID> deviceIds(deviceCount);
            if (AudioHardwareGetProperty(kAudioHardwarePropertyDevices, &size, deviceIds.data()) != kAudioHardwareNoError) { return std::map<int, VAudioDevice>(); };
            for (int i = 0; i < deviceCount; ++i)
            {
                VAudioDevice device;
                // Device id
                device.deviceId = deviceIds[i];
                // Device name
                if (AudioDeviceGetPropertyInfo(device.deviceId, 0, 0, kAudioDevicePropertyDeviceName, &size, nullptr) == kAudioHardwareNoError)
                {
                    device.deviceName.resize(size);
                    AudioDeviceGetProperty(device.deviceId, 0, 0, kAudioDevicePropertyDeviceName, &size, (void*)device.deviceName.data());
                }
                // Sample rate
                size = sizeof(Float64);
                AudioDeviceGetProperty(device.deviceId, 0, 0, kAudioDevicePropertyNominalSampleRate, &size, &device.sampleRate);
                // Channels
                if (AudioDeviceGetPropertyInfo(device.deviceId, 0, 1, kAudioDevicePropertyStreamConfiguration, &size, nullptr) == kAudioHardwareNoError)
                {
                    std::vector<AudioBufferList> bufferList(size / sizeof(AudioBufferList) + 1);
                    if (AudioDeviceGetProperty(device.deviceId, 0, 1, kAudioDevicePropertyStreamConfiguration, &size, bufferList.data()) == kAudioHardwareNoError)
                    {
                        for (UInt32 i = 0; i < bufferList[0].mNumberBuffers; ++i)
                        {
                            device.maxInputChannels += bufferList[0].mBuffers[i].mNumberChannels;
                        }
                    }
                }
                if (AudioDeviceGetPropertyInfo(device.deviceId, 0, 0, kAudioDevicePropertyStreamConfiguration, &size, nullptr) == kAudioHardwareNoError)
                {
                    std::vector<AudioBufferList> bufferList(size / sizeof(AudioBufferList) == 0 ? 1 : size / sizeof(AudioBufferList));
                    if (AudioDeviceGetProperty(device.deviceId, 0, 0, kAudioDevicePropertyStreamConfiguration, &size, bufferList.data()) == kAudioHardwareNoError)
                    {
                        for (UInt32 i = 0; i < bufferList[0].mNumberBuffers; ++i)
                        {
                            device.maxOutputChannels += bufferList[0].mBuffers[i].mNumberChannels;
                        }
                    }
                }
                // Frame latency
                size = sizeof(UInt32);
                AudioDeviceGetProperty(device.deviceId, 0, 1, kAudioDevicePropertyLatency, &size, &device.frameLatency);
                AudioDeviceGetProperty(device.deviceId, 0, 0, kAudioDevicePropertyLatency, &size, &device.frameLatency);
                // Push
                result[device.deviceId] = device;
            }
        }
        return result;
        #pragma clang diagnostic pop
        #endif
        return std::map<int, VAudioDevice>();
    }
    
    //----------------------------------------------------------------------------------------------------
    int VAudioMacOSHandler::DefaultInputDeviceId()
    {
        #ifdef __MAC_10_0
        AudioObjectPropertyAddress address = { kAudioHardwarePropertyDefaultInputDevice, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster };
        UInt32 size = sizeof(AudioDeviceID);
        AudioDeviceID result;
        if (AudioObjectGetPropertyData(kAudioObjectSystemObject, &address, 0, nullptr, &size, &result) == kAudioHardwareNoError)
        {
            return result;
        }
        #else
        UInt32 size = sizeof(AudioDeviceID);
        AudioDeviceID result;
        if (AudioHardwareGetProperty(kAudioHardwarePropertyDefaultInputDevice, &size, &result) == kAudioHardwareNoError)
        {
            return result;
        }
        #endif
        return -1;
    }
    
    //----------------------------------------------------------------------------------------------------
    int VAudioMacOSHandler::DefaultOutputDeviceId()
    {
        #ifdef __MAC_10_0
        AudioObjectPropertyAddress address = { kAudioHardwarePropertyDefaultOutputDevice, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster };
        UInt32 size = sizeof(AudioDeviceID);
        AudioDeviceID result;
        if (AudioObjectGetPropertyData(kAudioObjectSystemObject, &address, 0, nullptr, &size, &result) == kAudioHardwareNoError)
        {
            return result;
        }
        #else
        UInt32 size = sizeof(AudioDeviceID);
        AudioDeviceID result;
        if (AudioHardwareGetProperty(kAudioHardwarePropertyDefaultOutputDevice, &size, &result) == kAudioHardwareNoError)
        {
            return result;
        }
        #endif
        return -1;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VAudioMacOSHandlerTest()
    {
        
        return;
    }
    
}

#endif

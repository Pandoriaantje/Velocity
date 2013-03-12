/* Most parts of this class were originally developed by Lander Griffith (https://github.com/landr0id/).
   Much of his code is used throughout this class or very slightly modified */

#ifndef DEVICEIO_H
#define DEVICEIO_H

#include "BaseIO.h"
#include "../FATX/fatxhelpers.h"
#include "XboxInternals_global.h"

#ifdef _WIN32
    #include <windows.h>
    #include <WinIoCtl.h>
#else
    #define _FILE_OFFSET_BITS 64
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/ioctl.h>
    #include <sys/disk.h>
    #include <unistd.h>
#endif

#ifndef _WIN32
    #include <sys/stat.h>
#endif


class XBOXINTERNALSSHARED_EXPORT DeviceIO : public BaseIO
{
public:
    DeviceIO(HANDLE deviceHandle);
    DeviceIO(std::string devicePath);
    DeviceIO(std::wstring devicePath);

    void ReadBytes(BYTE *outBuffer, DWORD len);

    void WriteBytes(BYTE *buffer, DWORD len);

    void SetPosition(UINT64 address, std::ios_base::seek_dir dir = std::ios_base::beg);

    UINT64 GetPosition();

    UINT64 DriveLength();

    void Close();

    void Flush();

private:
    void loadDevice(std::wstring devicePath);

    UINT64 realPosition();

    #ifdef _WIN32
        HANDLE deviceHandle;
        OVERLAPPED offset;
    #else
        int device;
        INT64 offset;
    #endif

    UINT64 pos;
    BYTE lastReadData[0x200];
    UINT64 lastReadOffset;
};

#endif // DEVICEIO_H

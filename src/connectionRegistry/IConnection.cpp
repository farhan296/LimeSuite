/**
    @file   IConnection.cpp
    @author Lime Microsystems (www.limemicro.com)
    @brief  Implementation of IConnection interface
*/

#include "IConnection.h"
#include <cstring> //memcpy

DeviceInfo::DeviceInfo(void):
    addrSi5351(-1),
    addrADF4002(-1)
{
    return;
}

StreamMetadata::StreamMetadata(void):
    timestamp(0),
    endOfBurst(false)
{
    return;
}

StreamConfig::StreamConfig(void):
    isTx(false),
    bufferLength(0),
    format(STREAM_12_BIT_IN_16),
    linkFormat(STREAM_12_BIT_IN_16)
{
    return;
}

IConnection::IConnection(void)
{
    callback_logData = nullptr;
    unsigned short test = 0x1234;
    unsigned char* bytes = (unsigned char*)&test;
    if(bytes[0] == 0x12 && bytes[1] == 0x34)
        mSystemBigEndian = true;
    else
        mSystemBigEndian = false;
}

IConnection::~IConnection(void)
{
    return;
}

const ConnectionHandle &IConnection::GetHandle(void) const
{
    return _handle;
}

bool IConnection::IsOpen(void)
{
    return false;
}

DeviceInfo IConnection::GetDeviceInfo(void)
{
    DeviceInfo info;
    info.addrsLMS7002M.push_back(0);
    return info;
}

OperationStatus IConnection::DeviceReset(void)
{
    return UNSUPPORTED;
}

OperationStatus IConnection::TransactSPI(const int addr, const uint32_t *writeData, uint32_t *readData, const size_t size)
{
    return UNSUPPORTED;
}

OperationStatus IConnection::WriteI2C(const int addr, const std::string &data)
{
    return UNSUPPORTED;
}

OperationStatus IConnection::ReadI2C(const int addr, const size_t numBytes, std::string &data)
{
    return UNSUPPORTED;
}

void IConnection::UpdateExternalBandSelect(const size_t channel, const int trfBand, const int rfePath)
{
    return;
}

void IConnection::UpdateExternalDataRate(const size_t channel, const double txRate, const double rxRate)
{
    return;
}

double IConnection::GetReferenceClockRate(void)
{
    //this is the populated TCXO on many boards
    return 61.44e6/2;
}

void IConnection::SetReferenceClockRate(const double rate)
{
    return;
}

double IConnection::GetTxReferenceClockRate(void)
{
    return this->GetReferenceClockRate();
}

void IConnection::SetTxReferenceClockRate(const double rate)
{
    return this->SetReferenceClockRate(rate);
}

std::string IConnection::SetupStream(size_t &streamID, const StreamConfig &config)
{
    streamID = ~0;
    return "SetupStream not implemented";
}

void IConnection::CloseStream(const size_t streamID)
{
    return;
}

size_t IConnection::GetStreamSize(const size_t streamID)
{
    //this should be overloaded, but if not,
    //pick a number that will probably work (power of 2)
    return 16*1024;
}

bool IConnection::ControlStream(const size_t streamID, const bool enable, const size_t burstSize, const StreamMetadata &metadata)
{
    return false;
}

int IConnection::ReadStream(const size_t streamID, void * const *buffs, const size_t length, const long timeout_ms, StreamMetadata &metadata)
{
    return -1;
}

int IConnection::WriteStream(const size_t streamID, const void * const *buffs, const size_t length, const long timeout_ms, const StreamMetadata &metadata)
{
    return -1;
}

/** @brief Sets callback function which gets called each time data is sent or received
*/
void IConnection::SetDataLogCallback(std::function<void(bool, const unsigned char*, const unsigned int)> callback)
{
    callback_logData = callback;
}

OperationStatus IConnection::ProgramWrite(const char *buffer, const size_t length, const int programmingMode, const int index, ProgrammingCallback callback)
{
    return UNSUPPORTED;
}

OperationStatus IConnection::ProgramRead(char *buffer, const size_t length, const int index, ProgrammingCallback callback)
{
    return UNSUPPORTED;
}

OperationStatus IConnection::GPIOWrite(const uint8_t *buffer, const size_t bufLength)
{
    return UNSUPPORTED;
}

OperationStatus IConnection::GPIORead(uint8_t *buffer, const size_t bufLength)
{
    return UNSUPPORTED;
}

OperationStatus IConnection::WriteRegisters(const uint32_t *addrs, const uint32_t *data, const size_t size)
{
    return UNSUPPORTED;
}

OperationStatus IConnection::ReadRegisters(const uint32_t *addrs, uint32_t *data, const size_t size)
{
    return UNSUPPORTED;
}

OperationStatus IConnection::WriteRegister(const uint32_t addr, const uint32_t data)
{
    return this->WriteRegisters(&addr, &data, 1);
}

OperationStatus IConnection::CustomParameterWrite(const uint8_t *ids, const double *values, const int count, const std::string* units)
{
    return UNSUPPORTED;
}

OperationStatus IConnection::CustomParameterRead(const uint8_t *ids, double *values, const int count, std::string* units)
{
    return UNSUPPORTED;
}

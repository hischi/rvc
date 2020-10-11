#pragma once

#include <cstdint>

namespace ara::com
{
    #pragma pack(push, 1)
    /**
     * SOME/IP message id.
     */
    struct SomeIpMsgId
    {
        uint16_t serviceId;
        uint16_t methodId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    /**
     * SOME/IP request id.
     */
    struct SomeIpReqId
    {
        uint16_t clientId;
        uint16_t sessionId;
    };
    #pragma pack(pop)

    /**
     * SOME/IP message types.
     */
    enum class SomeIpMsgType : uint8_t {
        Request         = 0x00,
        RequestNoRet    = 0x01,
        Notification    = 0x02,
        Response        = 0x80,
        Error           = 0x81,
        TpRequest       = 0x21,
        TpRequestNoRet  = 0x22,
        TpResponse      = 0x23,
        TpError         = 0x24
    };

    /**
     * SOME/IP return codes.
     * Not an enum-class since other uint8 values are reserved for application codes.
     */
    enum SomeIpRetCode : uint8_t {
        Ok              = 0x00,
        NotOk           = 0x01,
        UnknownService  = 0x02,
        UnknownMethod   = 0x03,
        NotReady        = 0x04,
        NotReachable    = 0x05,
        Timeout         = 0x06,
        WrongProtoVers  = 0x07,
        WrongIntfVers   = 0x08,
        MalformedMsg    = 0x09,
        WrongMsgType    = 0x0A             
    };

    #pragma pack(push, 1)
    /**
     * SOME/IP header.
     */
    struct SomeIpHdr
    {
        SomeIpMsgId msgId;
        uint32_t len;
        SomeIpReqId reqId;
        uint8_t protoVers;
        uint8_t intfVers;
        SomeIpMsgType msgType;
        SomeIpRetCode retCode;
    };
    #pragma pack(pop)

    void ntoh(SomeIpHdr* hdr);
    void hton(SomeIpHdr* hdr);
} // namespace ara::com

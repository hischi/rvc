#pragma once

#include "someip_types.h"

namespace ara::com
{
    /**
     * Returns true if the unerlying SOME/IP-message is a service-discovery msg.
     */
    bool IsSomeIpSd(const SomeIpHdr* hdr) {
        return (hdr->msgId.serviceId == 0xFFFFU) && (hdr->msgId.methodId == 0x8100);
    }

    // ------------------------------------------
    // SOME/IP-SD Header
    // ------------------------------------------
    #pragma pack(push, 1)
    /**
     * Part of the SOME/IP-SD header.
     * Missing are list of entries, options-len and list of options.
     */
    struct SomeIpSdHdr
    {
        uint8_t flags;
        uint8_t reserved0;
        uint16_t reserved1;
        uint32_t entriesLen;
    };
    #pragma pack(pop)

    void hton_SomeIpSdHdr(SomeIpSdHdr* hdr);
    void ntoh_SomeIpSdHdr(SomeIpSdHdr* hdr);


    // ------------------------------------------
    // SOME/IP-SD Entry
    // ------------------------------------------
    /**
     * Type of entry in SOME/IP-SD. 
     * Determines the meaning of data in Entry.
     */
    enum class SomeIpSdEntryType : uint8_t {
        FindService     = 0x00,
        OfferService    = 0x01,
        Subscribe       = 0x06,
        SubscribeAck    = 0x07
    };

    #pragma pack(push, 1)
    struct SomeIpSdEvtGrpEntry {
        uint8_t reserved;
        uint8_t flagsCounter;
        uint16_t evtGrpId;
    };

    union SomeIpSdEntryData
    {
        uint32_t raw;
        uint32_t minorVers; // only if entry-type is 0 or 1
        SomeIpSdEvtGrpEntry evtGrpEntry; // only if entry-type is 6 or 7
    };
    
    /**
     * Entry in the SOME/IP-SD header.
     */
    struct SomeIpSdEntry
    {
        SomeIpSdEntryType type;
        uint8_t idxFstOpt;
        uint8_t idxSndOpt;
        uint8_t numOpts; // lower nibble: numFstOpts, upper nibble: numSndOpts
        uint16_t serviceId;
        uint16_t instId;
        uint32_t majorVersTtl; // lower byte: majorVers, other bytes: ttl
        SomeIpSdEntryData data;
    };
    #pragma pack(pop)

    void hton_SomeIpSdEntry(SomeIpSdEntry* entry);
    void ntoh_SomeIpSdEntry(SomeIpSdEntry* entry);

    uint8_t NumFstOpts(const SomeIpSdEntry* entry) {
        return entry->numOpts & 0x0FU;
    }

    uint8_t NumSndOpts(const SomeIpSdEntry* entry) {
        return entry->numOpts >> 4U;
    }

    void SetNumFstOpts(SomeIpSdEntry* entry, uint8_t numFstOpts) {
        entry->numOpts = (entry->numOpts & 0xF0U) | (numFstOpts & 0x0FU);
    }
    
    void SetNumSndOpts(SomeIpSdEntry* entry, uint8_t numSndOpts) {
        entry->numOpts = (entry->numOpts & 0x0FU) | (numSndOpts << 4U);
    }

    uint8_t MajorVers(const SomeIpSdEntry* entry) {
        return entry->majorVersTtl & 0x000000FFU;
    }

    uint32_t Ttl(const SomeIpSdEntry* entry) {
        return entry->majorVersTtl >> 8U;
    }

    void SetMajorVers(SomeIpSdEntry* entry, uint8_t majorVers) {
        entry->majorVersTtl = (entry->majorVersTtl & 0xFFFFFF00U) | majorVers;
    }

    void SetTtl(SomeIpSdEntry* entry, uint32_t ttl) {
        entry->majorVersTtl = (entry->majorVersTtl & 0x000000FFU) | (ttl << 8U);
    }

    bool IsInitDataReqFlag(const SomeIpSdEvtGrpEntry* evtGrpEntry) {
        return (evtGrpEntry->flagsCounter & 0x01U);
    }

    void SetInitDataReqFlag(SomeIpSdEvtGrpEntry* evtGrpEntry, bool initDataReqFlag) {
        evtGrpEntry->flagsCounter = (evtGrpEntry->flagsCounter & 0xFEU) | (initDataReqFlag & 0x01U);
    }

    uint8_t Counter(const SomeIpSdEvtGrpEntry* evtGrpEntry) {
        return (evtGrpEntry->flagsCounter >> 4U);
    }

    void SetCounter(SomeIpSdEvtGrpEntry* evtGrpEntry, uint8_t counter) {
        evtGrpEntry->flagsCounter = (evtGrpEntry->flagsCounter & 0x0FU) | (counter << 4U);
    }

    // ------------------------------------------
    // SOME/IP-SD Options
    // ------------------------------------------
    #pragma pack(push, 1)
    struct SomeIpSdConfigOpt {
        char config; // zero terminated string's first char
    };

    struct SomeIpSdLoadBalanceOpt {
        uint16_t prio;
        uint16_t weight;
    };

    struct SomeIpSdIpv4EPOpt {
        uint32_t ipv4Addr;
        uint8_t reserved;
        uint8_t proto;
        uint16_t port;
    };

    struct SomeIpSdIpv6EPOpt {
        uint8_t ipv6Addr[16];
        uint8_t reserved;
        uint8_t proto;
        uint16_t port;
    };

    union SomeIpSdOptData {
        SomeIpSdConfigOpt config;   // only if type is 0x01
        SomeIpSdLoadBalanceOpt loadBalance; // only if type is 0x02
        SomeIpSdIpv4EPOpt ipv4EP;   // only if type is 0x04, 0x14, 0x24
        SomeIpSdIpv6EPOpt ipv6EP;   // only if type is 0x06, 0x16, 0x26
    };

    enum class SomeIpSdOptionType : uint8_t {
        Config          = 0x01,
        LoadBalance     = 0x02,
        Ipv4EP          = 0x04,
        Ipv6EP          = 0x06,
        Ipv4MultiCastEP = 0x14,
        Ipv6MultiCastEP = 0x16,
        Ipv4SdEP        = 0x24,
        Ipv6SdEP        = 0x26
    };

    struct SomeIpSdOption {
        uint16_t len;
        SomeIpSdOptionType type;
        uint8_t reserved; // already part of len
        SomeIpSdOptData data;
    };
    #pragma pack(pop)

    void hton_SomeIpSdOption(SomeIpSdOption* opt);
    void ntoh_SomeIpSdOption(SomeIpSdOption* opt);


    // ------------------------------------------
    // SOME/IP-SD Message
    // ------------------------------------------
    void hton_SomeIpSdMsg(uint8_t* msg);
    void ntoh_SomeIpSdMsg(uint8_t* msg);

    uint32_t SomeIpSdNumEntries(const uint8_t* msg) {
        return ((SomeIpSdHdr*) msg)->entriesLen / 16;
    }

    uint32_t* SomeIpSdOptLenPtr(const uint8_t* msg) {
        return (uint32_t*) &msg[8 + ((SomeIpSdHdr*) msg)->entriesLen];
    }

    uint32_t SomeIpSdOptsLen(const uint8_t* msg) {
        return *SomeIpSdOptLenPtr(msg);
    }

    void SetSomeIpSdOptsLen(uint8_t* msg, uint32_t optsLen) {
        *SomeIpSdOptLenPtr(msg) = optsLen;
    }

    SomeIpSdEntry* GetSomeIpSdEntry(uint8_t* msg, uint32_t idx) {
        SomeIpSdHdr* hdr = (SomeIpSdHdr*) msg;
        if(idx < hdr->entriesLen) {
            return (SomeIpSdEntry*) &msg[8 + 16 * idx];
        }
        else {
            return nullptr;
        }
    }

    SomeIpSdOption* GetSomeIpSdOpt(uint8_t* msg, uint32_t idx) {
        uint32_t offs = 12 + ((SomeIpSdHdr*) msg)->entriesLen;
        uint32_t optsLen = SomeIpSdOptsLen(msg);

        if(optsLen == 0) {
            return nullptr;
        }

        SomeIpSdOption* opt = (SomeIpSdOption*) &msg[offs];
        if(optsLen < opt->len) {
            return nullptr;
        }

        for(uint32_t i = 0; i < idx; i++) {
            optsLen = optsLen - opt->len;
            offs = offs + 3 + opt->len;
            opt = (SomeIpSdOption*) &msg[offs];
            if(optsLen < opt->len) {
                return nullptr;
            }
        }
        return opt;
    }

    uint32_t GetSomeIpSdNumOpts(const uint8_t* msg) {
        uint32_t offs = 12 + ((SomeIpSdHdr*) msg)->entriesLen;
        uint32_t optsLen = SomeIpSdOptsLen(msg);
        uint32_t numOpts = 0;

        if(optsLen == 0) {
            return numOpts;
        }

        SomeIpSdOption* opt = (SomeIpSdOption*) &msg[offs];
        while(optsLen > opt->len && optsLen > 0) {
            offs = offs + 3 + opt->len;
            optsLen -= opt->len;
            opt = (SomeIpSdOption*) &msg[offs];
            numOpts++;
        }

        return numOpts;
    }

} // namespace ara::com

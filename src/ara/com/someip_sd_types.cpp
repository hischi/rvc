#include "someip_sd_types.h"
#include <arpa/inet.h>

using namespace ara::com;

void ara::com::hton_SomeIpSdHdr(SomeIpSdHdr* hdr) {
    hdr->entriesLen = htonl(hdr->entriesLen);
}

void ara::com::ntoh_SomeIpSdHdr(SomeIpSdHdr* hdr) {
    hdr->entriesLen = ntohl(hdr->entriesLen);
}

void ara::com::hton_SomeIpSdEntry(SomeIpSdEntry* entry) {
    entry->serviceId = htons(entry->serviceId);
    entry->instId = htons(entry->instId);
    entry->majorVersTtl = htonl(entry->majorVersTtl);
    entry->data.raw = htonl(entry->data.raw);
}

void ara::com::ntoh_SomeIpSdEntry(SomeIpSdEntry* entry) {
    entry->serviceId = ntohs(entry->serviceId);
    entry->instId = ntohs(entry->instId);
    entry->majorVersTtl = ntohl(entry->majorVersTtl);
    entry->data.raw = ntohl(entry->data.raw);
}

void ara::com::hton_SomeIpSdOption(SomeIpSdOption* opt) {
    opt->len = htons(opt->len);
    switch (opt->type)
    {
    case SomeIpSdOptionType::LoadBalance:
        opt->data.loadBalance.prio = htons(opt->data.loadBalance.prio);
        opt->data.loadBalance.weight = htons(opt->data.loadBalance.weight);
        break;

    case SomeIpSdOptionType::Ipv4EP:
    case SomeIpSdOptionType::Ipv4MultiCastEP:
    case SomeIpSdOptionType::Ipv4SdEP:
        opt->data.ipv4EP.ipv4Addr = htons(opt->data.ipv4EP.ipv4Addr);
        opt->data.ipv4EP.port = htons(opt->data.ipv4EP.port);
        break;
    
    case SomeIpSdOptionType::Ipv6EP:
    case SomeIpSdOptionType::Ipv6MultiCastEP:
    case SomeIpSdOptionType::Ipv6SdEP:
        opt->data.ipv6EP.port = htons(opt->data.ipv6EP.port);
        break;

    default:
        break;
    }
}

void ara::com::ntoh_SomeIpSdOption(SomeIpSdOption* opt) {
    opt->len = ntohs(opt->len);
    switch (opt->type)
    {
    case SomeIpSdOptionType::LoadBalance:
        opt->data.loadBalance.prio = ntohs(opt->data.loadBalance.prio);
        opt->data.loadBalance.weight = ntohs(opt->data.loadBalance.weight);
        break;

    case SomeIpSdOptionType::Ipv4EP:
    case SomeIpSdOptionType::Ipv4MultiCastEP:
    case SomeIpSdOptionType::Ipv4SdEP:
        opt->data.ipv4EP.ipv4Addr = ntohs(opt->data.ipv4EP.ipv4Addr);
        opt->data.ipv4EP.port = ntohs(opt->data.ipv4EP.port);
        break;
    
    case SomeIpSdOptionType::Ipv6EP:
    case SomeIpSdOptionType::Ipv6MultiCastEP:
    case SomeIpSdOptionType::Ipv6SdEP:
        opt->data.ipv6EP.port = ntohs(opt->data.ipv6EP.port);
        break;

    default:
        break;
    }
}

void ara::com::hton_SomeIpSdMsg(uint8_t* msg) {
    ara::com::hton_SomeIpSdHdr((SomeIpSdHdr*) msg);         // switch hdr
    uint32_t num = SomeIpSdNumEntries(msg);
    for(uint32_t i = 0; i < num; i++) {                     // switch for all entries
        hton_SomeIpSdEntry(GetSomeIpSdEntry(msg, i));
    }
    SetSomeIpSdOptsLen(msg, htonl(SomeIpSdOptsLen(msg)));   // switch opts len

    uint32_t offs = 12 + ((SomeIpSdHdr*) msg)->entriesLen;
    int32_t optsLen = SomeIpSdOptsLen(msg);

    SomeIpSdOption* opt = (SomeIpSdOption*) &msg[offs];
    while(optsLen > 0) {
        hton_SomeIpSdOption(opt);

        offs = offs + 3 + opt->len;
        optsLen -= opt->len;
        opt = (SomeIpSdOption*) &msg[offs];
    }
}

void ara::com::ntoh_SomeIpSdMsg(uint8_t* msg) {
    ara::com::ntoh_SomeIpSdHdr((SomeIpSdHdr*) msg);         // switch hdr
    uint32_t num = SomeIpSdNumEntries(msg);
    for(uint32_t i = 0; i < num; i++) {                     // switch for all entries
        ntoh_SomeIpSdEntry(GetSomeIpSdEntry(msg, i));
    }
    SetSomeIpSdOptsLen(msg, ntohl(SomeIpSdOptsLen(msg)));   // switch opts len

    uint32_t offs = 12 + ((SomeIpSdHdr*) msg)->entriesLen;
    int32_t optsLen = SomeIpSdOptsLen(msg);

    SomeIpSdOption* opt = (SomeIpSdOption*) &msg[offs];
    while(optsLen > 0) {
        offs = offs + 3 + opt->len;
        optsLen -= opt->len;
        opt = (SomeIpSdOption*) &msg[offs];

        ntoh_SomeIpSdOption(opt);
    }
}
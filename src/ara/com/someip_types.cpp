#include <arpa/inet.h>
#include "someip_types.h"

using namespace ara::com;

void ntoh(SomeIpHdr* hdr) {
    hdr->msgId.serviceId = ntohs(hdr->msgId.serviceId);
    hdr->msgId.methodId = ntohs(hdr->msgId.methodId);
    hdr->len = ntohl(hdr->len);
    hdr->reqId.clientId = ntohs(hdr->reqId.clientId);
    hdr->reqId.sessionId = ntohs(hdr->reqId.sessionId);
}

void hton(SomeIpHdr* hdr) {
    hdr->msgId.serviceId = htons(hdr->msgId.serviceId);
    hdr->msgId.methodId = htons(hdr->msgId.methodId);
    hdr->len = htonl(hdr->len);
    hdr->reqId.clientId = htons(hdr->reqId.clientId);
    hdr->reqId.sessionId = htons(hdr->reqId.sessionId);
}
//
// Created by System Administrator on 1/17/18.
//

#include <algorithm>
#include "TcpInfo.h"
#include "../util/enc.h"

uint32_t TcpInfo::UpdateAck(uint32_t ack) {
    this->ack = ack;
    return this->ack;
}

uint32_t TcpInfo::UpdateSeq(uint32_t seq) {
    this->seq = seq;
    return this->seq;
}

char *TcpInfo::Encode(char *buf, int len) const {
    if (len < sizeof(*this)) {
        return nullptr;
    }

    char *p = ConnInfo::Encode(buf, len);
    if (nullptr == p) {
        return nullptr;
    }
    p = encode_uint32(seq, p);
    p = encode_uint32(ack, p);
    return p;
}

const char *TcpInfo::Decode(const char *buf, int len) {
    if (len < sizeof(*this)) {
        return nullptr;
    }
    auto p = ConnInfo::Decode(buf, len);
    if (!p) {
        return nullptr;
    }
    p = decode_uint32(&seq, p);
    p = decode_uint32(&ack, p);
    return p;
}

std::string TcpInfo::ToStr() const {
    auto s = ConnInfo::ToStr();
    s += ", seq:" + std::to_string(seq) + ", ack: " + std::to_string(ack);
    return s;
}

TcpInfo::TcpInfo(const ConnInfo &info) : ConnInfo(info) {
    udp = false;
    seq = 0;
    ack = 0;
}

void TcpInfo::Reverse() {
    ConnInfo::Reverse();
    std::swap<uint32_t>(seq, ack);
}

TcpInfo::TcpInfo() : ConnInfo() {
    udp = false;
}

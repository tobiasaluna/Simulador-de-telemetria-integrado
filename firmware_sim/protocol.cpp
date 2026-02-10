#include "protocol.hpp"
#include <cstdint>

static uint8_t checksum(const std::string& s) {
    uint8_t cs = 0;
    for (unsigned char c : s) {
        cs ^= c;
    }
    return cs;
}

// Frame format:
// [STX=0x02] PAYLOAD [ETX=0x03] [CHECKSUM_HEX_2CHARS] \n
std::string packFrame(const std::string& payload) {
    std::string frame;
    frame.push_back(0x02);
    frame += payload;
    frame.push_back(0x03);

    uint8_t cs = checksum(payload);

    const char hex[] = "0123456789ABCDEF";
    frame.push_back(hex[(cs >> 4) & 0xF]);
    frame.push_back(hex[cs & 0xF]);
    frame.push_back('\n');

    return frame;
}

bool verifyFrame(const std::string& frame) {
    if (frame.size() < 5) return false;
    if (frame.front() != 0x02) return false;

    auto etxPos = frame.find(0x03);
    if (etxPos == std::string::npos) return false;
    if (etxPos + 3 >= frame.size()) return false;

    std::string payload = frame.substr(1, etxPos - 1);

    uint8_t cs = checksum(payload);

    auto hexToNibble = [](char c) -> int {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
        return -1;
    };

    int hi = hexToNibble(frame[etxPos + 1]);
    int lo = hexToNibble(frame[etxPos + 2]);

    if (hi < 0 || lo < 0) return false;

    uint8_t received = (hi << 4) | lo;
    return received == cs;
}

std::string extractPayload(const std::string& frame) {
    auto etxPos = frame.find(0x03);
    if (etxPos == std::string::npos) return "";
    return frame.substr(1, etxPos - 1);
}

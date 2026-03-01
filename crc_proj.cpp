#include <iostream>
#include <vector>
#include <iomanip>

class CRC_checker {
public:
    uint16_t crc_x25(const std::vector<uint8_t>& data) {
        uint16_t crc = 0xFFFF;

        for (auto byte : data) {
            crc ^= byte;

            for (int i = 0; i < 8; i++) {
                if (crc & 0x0001) {
                    crc = (crc >> 1) ^ 0x8408;
                } else {
                    crc >>= 1;
                }
            }
        }

        crc ^= 0xFFFF;
        return crc;
    }
};

int main() {
    CRC_checker checker;

    std::vector<uint8_t> test = {
        '1','2','3','4','5','6','7','8','9'
    };

    uint16_t result = checker.crc_x25(test);

    std::cout << "CRC-16/X25: 0x"
              << std::hex << std::uppercase
              << std::setw(4) << std::setfill('0')
              << result << std::endl;

    std::vector<uint8_t> packet = {
        0x45, 0x00, 0x00, 0x54,
        0x12, 0x34, 0x00, 0x00
    };

    packet[2] ^= 0x04;  // flip bit 2 of byte index 2
    result = checker.crc_x25(packet); 

    std::cout << "CRC-16/X25: 0x"
            << std::hex << std::uppercase
            << std::setw(4) << std::setfill('0')
            << result << std::endl;
    
    return 0;
}

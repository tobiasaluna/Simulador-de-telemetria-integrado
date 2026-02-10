#include <iostream>
#include <thread>
#include <chrono>

#include "telemetry.hpp"
#include "protocol.hpp"

int main() {
    std::cout << "Embedded Telemetry Simulator Started\n";
    std::cout << "Sending telemetry frames...\n\n";

    while (true) {
        TelemetryData d = generateTelemetry();
        std::string json = toJson(d);
        std::string frame = packFrame(json);

        // Simulating UART output (stdout)
        std::cout << frame;
        std::cout.flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    return 0;
}

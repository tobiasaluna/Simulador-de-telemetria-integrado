#include "telemetry.hpp"
#include <random>
#include <sstream>

TelemetryData generateTelemetry() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> tempDist(20.0f, 90.0f);
    std::uniform_real_distribution<float> voltDist(3.0f, 4.2f);
    std::uniform_int_distribution<int> rpmDist(500, 5000);

    TelemetryData d;
    d.temperature = tempDist(gen);
    d.voltage = voltDist(gen);
    d.rpm = rpmDist(gen);
    d.system_ok = (d.temperature < 80.0f && d.voltage > 3.2f);

    return d;
}

std::string toJson(const TelemetryData& data) {
    std::ostringstream oss;
    oss << "{"
        << "\"temp\":" << data.temperature << ","
        << "\"volt\":" << data.voltage << ","
        << "\"rpm\":" << data.rpm << ","
        << "\"ok\":" << (data.system_ok ? "true" : "false")
        << "}";
    return oss.str();
}

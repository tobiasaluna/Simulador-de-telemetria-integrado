# Simulador de Telemetría Embebido (C++ + JS)

Este proyecto simula un dispositivo embebido que envía datos de telemetría a través de UART.

## Características
- Generador de telemetría tipo firmware en C++
- Protocolo serie simple con suma de comprobación
- Panel web mediante API Web Serial (Chrome/Edge)
- Visualización en tiempo real de temperatura, voltaje, RPM y estado

## Simulador de Compilación de Firmware
```bash
cd firmware_sim
mkdir build && cd build
cmake ..
cmake --build .
./telemetry_sim

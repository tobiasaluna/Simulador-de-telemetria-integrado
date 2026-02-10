# Simulador de Telemetría Embebido (C++ y JS)

La idea general es:

-✅ Un “firmware” escrito en C++ genera datos como si fueran sensores (temperatura, voltaje, rpm).
-✅ Esos datos se envían como si fueran por UART/Serial, usando un formato de trama (frame) con checksum.
-✅ Un dashboard en JavaScript se conecta a un puerto serial y muestra los datos en tiempo real.

# ¿Qué hace el programa en general?

El programa simula un dispositivo embebido que hace telemetría, como por ejemplo:

un sistema automotriz

un controlador industrial

un sensor IoT

un módulo de monitoreo de baterías

El flujo es:

Generar datos simulados (como sensores)

Convertir esos datos a JSON

Encapsularlos en un frame (protocolo simple)

Enviar el frame por “serial” (aquí es stdout)

El dashboard recibe esos frames

Extrae el JSON y lo parsea

Muestra los valores en pantalla
## Simulador de Compilación de Firmware
```bash
cd firmware_sim
mkdir build && cd build
cmake ..
cmake --build .
./telemetry_sim

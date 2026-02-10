# Simulador de Telemetría Embebido (C++ y JS)

La idea general es:

- Un “firmware” escrito en C++ genera datos como si fueran sensores (temperatura, voltaje, rpm)
- Esos datos se envían como si fueran por UART/Serial, usando un formato de trama (frame) con checksum
- Un dashboard en JavaScript se conecta a un puerto serial y muestra los datos en tiempo real.

# ¿Qué hace el programa en general?

El programa simula un dispositivo embebido que hace telemetría, como por ejemplo:
- Un sistema automotriz
- un controlador industrial
- un sensor IoT
- un módulo de monitoreo de baterías
  
El flujo es:
1. Generar datos simulados (como sensores)
2. Convertir esos datos a JSON
3. Encapsularlos en un frame (protocolo simple)
4. Enviar el frame por “serial” (aquí es stdout)
5. El dashboard recibe esos frames
6. Extrae el JSON y lo parsea
7. Muestra los valores en pantalla

## Simulador de Compilación de Firmware
```bash
g++ main.cpp telemetry.cpp protocol.cpp -o telemetry_sim.exe


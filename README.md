# TTK4155-Byggern-Lab

This repository is the documented software and hardware designed by Håken Sivesindtajet Lunn and Alexander Navasca Skinstad in TTK4155 - Embedded and Industrial Computer Systems Design "Byggern" lab at NTNU.

Node 1 (ATmega 162) firmware contains:

USART driver (printf).
Parallel bus driver for (SRAM, ADC and OLED controller).
Graphical user interface (GUI).
SPI driver.
CANbus driver. (external MCP2515 CANcontroller is used for this.)
Node 2 (ATSAM3X8E) firmware contains:

USART driver and printf (code provided by NTNU).
CANbus driver (code provided by NTNU).
PWM driver.
PI-controller.
please feel free to use and learn from our mistakes in this project.

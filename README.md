# CaIN: Low Power and Low Latency VHF Mesh Networking
A repository containing code, hardware design, and documentation for the paper "CaIN: Low Power and Low Latency VHF Mesh Networking"

## Table of Contents
1. [Abstract](#abstract)
2. [Project Structure](#Project-Structure)
5. [License](#license)

## Abstract
Low-power wireless mesh networks provide a solution for the seamless wireless coverage of complex physical environments due to their ability to route around physical obstructions and sources of interference. For example, networks such as SmartMesh-IP, WirelessHART and 6TiSCH deliver industry-grade reliability with low routing power consumption. However, conventional low power mesh networks suffer from high latency. The root of this problem is the need to reduce receiver power consumption by duty cycling the radio receiver using time-synchronized wake-ups or preamble sampling. We tackle this problem by introducing CaIN, a near field mesh network that transmits information using strong Capacitive and INductive effects that can be detected by a passive receiver front end, thereby side-stepping the need for intermittent receiver usage. Given that near field effects are limited to a few wavelengths, we implement our proof-of-principle transceiver in the VHF frequency band at 40 MHz, achieving a unique performance profile including: 20 kbps link layer throughput, sub-𝜇W receiver power consumption, sub-ms wireless wake-up and 17 m per-hop range. Building upon these properties, we realize a novel mesh network with a worst-case latency of under 40 ms for a 3 hop network. To promote replication and further work, we have made the hardware and software of our reference implementation open source.

## Project Structure
### Hardware
In the `Hardware` folder, you will find:
1. **Schematic Designs** – Includes the schematic for each iteration of the CaIN transceiver hardware.
2. **PCB Project Files** – The original project files used to design the PCB.
3. **Gerber Files** – Ready-to-submit files for PCB manufacturing.

#### Hardware Version
The hardware version used in the article is **CaIN v2.2**, featuring a pin header compatible with the Arduino Due.
#### Microcontroller & Evaluation Board
All software code was written using the Arduino IDE, and the evaluation board used for testing is the [Arduino Due](https://store.arduino.cc/products/arduino-due), based on the Atmel SAM3X8E ARM Cortex-M3 CPU. 

#### Main Components on CaIN transciver
| **CAIN Prototype Components** | **Part Number**  | **Purchase Link**                                              |
|------------------------------|-------------------|----------------------------------------------------------------|
| SMS7630-005LF                | SMS7630-005LF     | [Digi-Key](https://www.digikey.com/en/products/detail/???/???) |
| ADG918                       | ADG918            | [Mouser](https://www.mouser.com/ProductDetail/???/???)         |
| ADG902                       | ADG902            | [Mouser](https://www.mouser.com/ProductDetail/???/???)         |
| TLV7031                      | TLV7031           | [Mouser](https://www.mouser.com/ProductDetail/???/???)         |
| LTC6905                      | LTC6905           | [Digi-Key](https://www.digikey.com/en/products/detail/???/???) |
| TRF37D73                     | TRF37D73          | [Mouser](https://www.mouser.com/ProductDetail/???/???)         |
| SMA-EDGE-S                   | SMA-EDGE-S        | [Mouser](https://www.mouser.com/ProductDetail/???/???)         |

### Software
In the `Software` folder, you will find: 

# Boot_F745_SFU
Small, fast and simple STM32F7xx UART bootloader.
With very small footprint but without assembler code.

* **Target MCU**: STM32F745
* **clocks**: 147.5 MHz (for minimal BOD error)
* **uart**: 921600 BOD, 8bit, noParity, recive from IRQ to fifo buffer, direct send
* **Protocol**: Packets with H/W CRC32 and acknowledgment, lost and corrupt data protection
* **Can work from locked flash**
* **Firmware update ONLY**
* **fast write speed** 400kb firmware in 9 seconds
* **partital erase** and full erase
* **timeout for start main** 5 seconds

Project finished
#### Current footprint:
|text|data|bss|filename|
|----|----|----|--------------|
|**10389**|4|271112|Boot_F745_SFU.elf|
:orphan:

.. _zephyr_4.1:

Zephyr 4.1.0 (Working Draft)
############################

We are pleased to announce the release of Zephyr version 4.1.0.

Major enhancements with this release include:

An overview of the changes required or recommended when migrating your application from Zephyr
v4.0.0 to Zephyr v4.1.0 can be found in the separate :ref:`migration guide<migration_4.1>`.

The following sections provide detailed lists of changes by component.

Security Vulnerability Related
******************************
The following CVEs are addressed by this release:

More detailed information can be found in:
https://docs.zephyrproject.org/latest/security/vulnerabilities.html

API Changes
***********

Removed APIs in this release
============================

 * The deprecated Bluetooth HCI driver API has been removed. It has been replaced by a
   :c:group:`new API<bt_hci_api>` that follows the normal Zephyr driver model.

Deprecated in this release
==========================

Architectures
*************

* Common

  * Introduced :kconfig:option:`CONFIG_ARCH_HAS_CUSTOM_CURRENT_IMPL`, which can be selected when
    an architecture implemented and enabled its own :c:func:`arch_current_thread` and
    :c:func:`arch_current_thread_set` functions for faster retrieval of the current CPU's thread
    pointer. When enabled, ``_current`` variable will be routed to the
    :c:func:`arch_current_thread` (:github:`80716`).

* ARC

* ARM

* ARM64

* RISC-V

  * Implements :c:func:`arch_current_thread_set` & :c:func:`arch_current_thread`, which can be enabled
    by :kconfig:option:`CONFIG_RISCV_CURRENT_VIA_GP` (:github:`80716`).

* Xtensa

* native/POSIX

  * :kconfig:option:`CONFIG_NATIVE_APPLICATION` has been deprecated.
  * For the native_sim target :kconfig:option:`CONFIG_NATIVE_SIM_NATIVE_POSIX_COMPAT` has been
    switched to ``n`` by default, and this option has been deprecated.

Kernel
******

Bluetooth
*********

* Audio

* Host

* HCI Drivers

Boards & SoC Support
********************

* Added support for these SoC series:

* Made these changes in other SoC series:

* Added support for these boards:

* Made these board changes:

* Added support for the following shields:

Build system and Infrastructure
*******************************

Drivers and Sensors
*******************

* ADC

* Battery

* CAN

* Charger

* Clock control

* Counter

* DAC

* Disk

* Display

  * Added flag ``frame_incomplete`` to ``display_write`` that indicates whether a write is the last
    write of the frame, allowing display drivers to implement double buffering / tearing enable
    signal handling (:github:`81250`)
  * Added ``frame_incomplete`` handling to SDL display driver (:dtcompatible:`zephyr,sdl-dc`)
    (:github:`81250`)
  * Added transparency support to SDL display driver (:dtcompatible:`zephyr,sdl-dc`) (:github:`81184`)

* Ethernet

* Flash

* GNSS

* GPIO

* Hardware info

* I2C

* I2S

* I3C

* Input

* LED

  * Added a new set of devicetree based LED APIs, see :c:struct:`led_dt_spec`.

* LED Strip

* LoRa

* Mailbox

* MDIO

* MFD

* Modem

* MIPI-DBI

* MSPI

* Pin control

* PWM

* Regulators

* Reset

* RTC

* RTIO

* SDHC

* Sensors

* Serial

* SPI

* USB

* Video

* Watchdog

* Wi-Fi

Networking
**********

* ARP:

* CoAP:

* Connection manager:

* DHCPv4:

* DHCPv6:

* DNS/mDNS/LLMNR:

* gPTP/PTP:

* HTTP:

* IPSP:

* IPv4:

* IPv6:

* LwM2M:

* Misc:

* MQTT:

* Network Interface:

* OpenThread

* PPP

* Shell:

* Sockets:

* Syslog:

* TCP:

* Websocket:

* Wi-Fi:

* zperf:

USB
***

Devicetree
**********

Kconfig
*******

Libraries / Subsystems
**********************

* Debug

* Demand Paging

* Formatted output

* Management

* Logging

* Modem modules

* Power management

* Crypto

* CMSIS-NN

* FPGA

* Random

* SD

* State Machine Framework

* Storage

* Task Watchdog

* POSIX API

* LoRa/LoRaWAN

* ZBus

HALs
****

* Nordic

* STM32

* ADI

* Espressif

MCUboot
*******

OSDP
****

Trusted Firmware-M
******************

LVGL
****

* Added ``frame_incomplete`` support to indicate whether a write is the last
  write of the frame (:github:`81250`)

Tests and Samples
*****************

* Fixed incorrect alpha values in :zephyr_file:`samples/drivers/display`. (:github:`81184`)
* Added :zephyr_file:`samples/modules/lvgl/screen_transparency`. (:github:`81184`)

Issue Related Items
*******************

Known Issues
============

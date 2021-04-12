### Compatibility
The TLE94112ES DC Motor Control HAT in combination with this library is compatible with the following hardware platforms:

| Platform | Compatible |
| --- |:---:|
| Raspberry Pi 4 Mod. B | :heavy_check_mark: |
| Raspberry Pi 3 Mod. B+ | :heavy_check_mark: |
| Raspberry Pi 3 Mod. B | :heavy_check_mark: |
| Raspberry Pi 3 Mod. A+ | :heavy_check_mark: |
| Raspberry Pi Zero | :heavy_check_mark: |  |
| Raspberry Pi Zero W(H) | :heavy_check_mark: |
| Raspberry Pi 2 Mod. B v1.2 | :heavy_check_mark: |
| Raspberry Pi 2 Mod. B | :heavy_check_mark: |
| Raspberry Pi 1 Mod. B+ | :heavy_check_mark: |
| Raspberry Pi 1 Mod. B | :x: |
| Rapsberry Pi 1 Mod. A+ | :heavy_check_mark: |
| Raspberry Pi 1 Mod. A | :x: |

### Prerequisites
It is assumed that you have already set up a compatible Raspberry Pi with Raspberry Pi OS or similar and that the hardware setup is already done. If this is not the case, please refer to the [getting started page](RPi-Getting-Started).

### Required Software

* [Raspberry Pi OS](https://www.raspberrypi.org/downloads/raspberry-pi-os/) or similar
* git
* [bcm2835 library](https://www.airspayce.com/mikem/bcm2835/)
* build-essential
* Infineon multi-half-bridge library (this library)

### Library Installation

The library itself does not have to be installed. It is sufficient to clone it from GitHub to compile the example code. However, beforehand the required packets have to be installed:

##### Install required packages.
```
sudo apt-get install git build-essential
```

##### Clone this library from GitHub.
```
git clone https://github.com/Infineon/multi-half-bridge.git
```

##### Install BCM2835 library
```
cd multi-half-bridge/src/framework/raspberrypi
chmod +x ./install_requirements.sh
./install_requirements.sh
```

The BCM2835 library is needed to access the SPI peripheral of the Raspberry Pi.

**Ready To Go! Continue [here](RPi-Examples) to find out how the example code can be compiled and tested.**
# ESP-8266EX sniffer on WeMos D1 mini board

## Content

This software sketch is a port of the Espressif SDK sniffing functionality to the famous Arduino platform for the WeMos D1 mini (http://www.wemos.cc). 
With this code sketch, one is able to catch and analyse WiFi packages in the air and transmit them via USB-to-Serial to a PC in order to get information like the MAC addresses of participating receivers/senders.

For more information of the main sniffer functionality, see the Espressif SDK documentation:

http://espressif.com/file/384/download?token=6Xs47A-_

This instruction summarises the main points of the WeMos Tutorial (http://www.wemos.cc/Tutorial/get_started_in_arduino.html) and other tutorials about this topic on the Internet.

Note that the Git software is used to clone this repository, see https://git-scm.com for more information or download the whole package from the repository page. For executing the commands, the Git Bash console is recommended.

## How to get started? 

### First step

First of all, one needs to install the driver of the USB-to-Serial chip for recognising the WeMos D1 mini board which is called ch301g. Download it from the following webpage:

http://www.wemos.cc/downloads/

Install the driver and plug the WeMos D1 mini board to your computer per USB.

In addition, a key point is to install the Arduino IDE software on the local machine as the WeMos D1 mini board is supported by it directly. Download the official Arduino software from the Arduino webpage: 

http://www.arduino.cc

### Second step

Clone the Arduino support of the WeMos D1 mini board into the Arduino Sketchbook (see Arduino IDE: ``Files – Preferences`` for Sketchbook path):

```
cd hardware  
mkdir esp8266com
cd esp8266com
git clone https://github.com/esp8266/Arduino.git
```

If the hardware directory does not exist, create it.

As a next step, the ESP 8266 binary tools must be downloaded by executing:

```
cd esp8266/tools
python get.py
```

If the command ``python`` is unknown to your OS, please install the Python 2 package from the respective website (https://www.python.org/download/releases/2.7.2/) and configure it to work with your system. Especially, add the python executable file path to your Windows PATH variable or use the explicit ```python``` executable in its respective directory.

### Third step

Start the Arduino IDE and configure the software for programming the WeMos D1 mini board under ``Tools – Board - WeMos D1 R2 & mini``. 
There are two ways to upload the code to the ESP 8266 to the board: either by USB-to-Serial using the USB plug on the board or per OTA to upload directly per WiFi.
For first tries, one should rely on the USB variant as it is less complicated. To do so, set under ``Tools`` the following settings:

```
Upload Using “Serial”
CPU Frequency “80 MHz”
Flash Size “4M (3M SPIFFS)
Upload Speed “921600”
```

### Fourth (optional) step

There are several examples for this board from WeMos directly available. Just clone the examples directory to the Sketchbook directory by executing:

```
cd Sketchbook
git clone https://github.com/wemos/D1_mini_Examples.git
``` 

As examples are always a good way of introducing programming to oneself, it is strongly recommended for beginners to download them.

### Fifth step

Clone this repository to the Sketchbook directory as it contains the main code and the sniffer program itself

```
git clone https://github.com/IoTpower/esp8266-ard-sniff.git
```

### Fifth step

Restart the Arduino IDE if still executed in the background.

## Loading the actual sniffer program

### Compiling and flashing

Start the Arduino IDE and load the Sniffer file ```/Sniffer/Sniffer.ino``` via ``File – Open`` from the Sniffer directory. Compile it and upload it to the board.

### Start serial monitoring

Go to ``Tools – Serial Monitor`` and set Baudrate to 115200, enjoy!

### What do I see?

The first number is the channel of the monitored WiFi transmissions where the package has been captured. The second number is the length of the package and the following columns are the Addr1, Addr2, Addr3, and Addr4 of the MAC header of the captured WiFi package. The delay times and times of scanning a specific channel can be adjusted.

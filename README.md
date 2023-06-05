# Gro-Shine-F-AltFW
My work on a Growatt ShineWifi-F version firmware update. Tested against a SPF 3000T LVM-ES but not completely functional. Needs work still on getting the correct registers for data.

LOTS of respect to the guy that created this originally.. https://github.com/otti/Growatt_ShineWiFi-S (and of course, all the repos he used to create his work)

--UPDATE--
I use ESPHome on the ShineWIfi-F device and the growattinverter.yaml file for the config. Works well! But I left all this in case someone wants it..although it didn't work when I flashed it this time? But I can't devote time to debugging, since i only have one device and it's working with ESPHome.
--UPDATE--

## How I backed up and updated the device: ##
(Win11 based ShineWifi-F firmware dump and update)

* I downloaded 'esptool-v4.1-win64' and extracted it to a folder.
* Cut traces to R16, R11 and 3232EE chip.
* Connect USB-TTL interface to breakout pins (be sure to set voltage to 3.3V first!!)
    * Gnd to Gnd
    * 3.3v to 3.3v source (if youre just plugging it into a USB slot to power it skip this, you only need GND and TX/RX)
    * TX on the board to RX on your interface
    * RX on the board to TX on your interface
* Plug in the interface and power the board (if your interface isnt doing it).
* Open a cmd prompt to your extraced esptool folder, run the following command (I use windows terminal):

```
.\esptool.exe --port COM4 read_flash 0x00000 0x400000 image4M.bin

esptool.py v4.1
Serial port COM4
Connecting....
Detecting chip type... Unsupported detection protocol, switching and trying again...
Connecting...
Detecting chip type... ESP8266
Chip is ESP8266EX
Features: WiFi
Crystal is 26MHz
MAC: 30:83:98:xx:xx:xx
Uploading stub...
Running stub...
Stub running...
4194304 (100 %)
4194304 (100 %)
Read 4194304 bytes at 0x00000000 in 389.7 seconds (86.1 kbit/s)...
Hard resetting via RTS pin...
```

Move the image4M.bin file somewhere safe.
By the way, my file size is 4096KiB, the CRC for my file is CRC32: CRC32: D77C2455

## Working with the code: ##

I ended up creating a new PlatformIO arduino project, with the board ESP-07s.
Then copied the code from the main INO file into main.cpp, and copied the Growatt.cpp, Growatt.h and index.h into the src folder.
(Importing an arduino project in PlatformIO didn't work well for me)

* You could open the main.cpp file and update WIFI_SSID, WIFI_PASSWORD, and the other variables in the first part of the sketch, but I did it different below.
* Add the PubSubClient by Nick O'Leary library to the project if needed. (see github link if you hit packet size issues).
* Add the ModBusMaster library to the project as well.
* If you get errors about SendJsonSite or other subs not being defined, make sure you reorganize the main.cpp, 
 putting the main loop() section below all the other procedures (might need to move setup() just above loop() as well).
 This is common when migrating adruino to PlatformIO actually..
* Compile, fix errors if any are found.. 

I prefer to keep wifi secrets in a secrets.h file, and specifically exclude secrets.h in .gitignore so my creds never get published.
 (basically you cut that section out of main.cpp that sets the password/users, paste it into a secrets.h in the src folder, 
 replace the old code with a 'include "secrets.h"' in main.cpp, and add secrets.h to a line in .gitignore. Then you can update the
 secrets.h file with your WIFI_SSID, WIFI_PASSWORD, etc..)

* https://assets.maxlinear.com/web/documents/sipex/datasheets/sp3222e_sp3232e.pdf
* https://docs.ai-thinker.com/_media/esp8266/docs/esp-07s_product_specification_en.pdf
* https://github.com/knolleary/pubsubclient
* https://www.photovoltaicsolar.in/Growatt_Manual/MAX%20Series%20Modbus%20RTU%20Protocol.pdf

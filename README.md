# PicoNetBoot

This project has for goal to be able to start, power-off and reboot over 
Internet with a Raspberry Pi Pico W.

## Installation

1. Install the [Pico SDK](https://github.com/raspberrypi/pico-sdk).
2. Clone the repository.
    ```bash 
    git clone git@github.com:jujur10/PicoNetBoot.git
    ```
3. Modify parameters in order to use PicoNetBoot properly.
Into [CMakeList.txt](CMakeLists.txt) file.
   1. Set the [SSID](https://fr.wikipedia.org/wiki/Service_set_identifier) 
      of your network at **line 4**.
   2. Set the Password of your network at **line 5**.
   3. Set the path of your PICO SDK at **line 13**.
   4. _(Optional)_ Modify server port **line 11**.
4. Build the project (it is not micropython lol).
   1. Create a build directory.
       ```bash 
       mkdir build && cd build
       ```
   2. Build Makefile.
       ```bash
       cmake ..
       ```
   3. Build project.
       ```bash
       make
       ```
5. Copy "PicoNetBoot.uf2" into your Raspberry Pi Pico !

## Interact with the server

You can create a basic C client and write to PicoNetBoot server with these 
commands (free to you to create a little client 🙂):

- "START" : Start the computer.
- "POWER-OFF" : Power-off the computer.
- "REBOOT" : Power-off and re-start the computer.
- When communication terminated, close socket.

## Demonstration

Here's a short demonstration.

![Demonstration](https://lh3.googleusercontent.com/u/0/drive-viewer/AKGpiha3JVosFB985ZNpJSxaPhBcDAQXIgEQf_b5sc6rcutpgG9iwcs65bGuNJOVgAAKP_sN_ZutB57bZgUDitEYLrYjrGZm_YPCnc4=w3064-h1890)

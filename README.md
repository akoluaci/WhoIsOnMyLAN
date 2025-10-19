This file scans your network to reveal the information of the devices connected to your local network.It reveals,
- ip address of host device
- mac address of host device
- vendor name of host device
- ip address of each device in the network
- mac address of each device in the network
- vendor name of each device in the network
- the ports is being used of each device in the network

In order to use, you need to have CMake and MinGW. When you install them once, you need to execute:
> CMake -S . -B build -G "MinGW Makefiles" 

after successfull execution, execute:

> cmake --build build

Congratulations, you now can execute the program.

The code below executes the cli version:
> .\build\bin\netls_cli.exe

The code below executes the ui version:
> .\build\bin\netls_ui.exe

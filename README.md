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

after that,

> .\build\bin\netls.exe

The UI version of the program will be here soon.

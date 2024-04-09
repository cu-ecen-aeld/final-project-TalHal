
# Overview

The goals of this project is to create a basic tool for p2p network protocols testing.
A network protocol developer can use the tool by adding packet processing code.
The code is based on the following SW componenets:
- pusher
- rreceiver
- snull
- bridge br0 configure to include network interfaces: ethX and tap0.


   ![final_project](https://github.com/cu-ecen-aeld/final-project-TalHal/assets/67574645/67b24e26-0f7c-4142-ab7e-3852c8535e32)



# Target Build System
buildroot

# Hardware Platform
Rapberry PI (Specifically used version 4).
sdcard.img is burned to sdcard.
Laptop connected to Raspbery with ethernet PI via SSH for control.
Also another ethernet connection between Laptop and Raspberry used for data traffic.


![hw](https://github.com/cu-ecen-aeld/final-project-TalHal/assets/67574645/1fb4f603-0f04-4d7d-a07b-123c31ba1b99)


# Open Source Projects Used
Project would be based on Assignment 5 buildroot as a starting point that include buildroot.

# Previously Discussed Content

# New Content
How to create a tun/tap netdevice.
Setup a Network driver
Client/server with RAW sockets.

# Shared Material
Using assignment 5 buildroot as a starting point.

# Source Code Organization

All code will be hosted at https://github.com/cu-ecen-aeld/final-project-TalHal


## Team project members:

TalHal - Code Developer

# Schedule Page

https://github.com/users/TalHal/projects/1/views/1?groupedBy%5BcolumnId%5D=86905036


# Overview

The goals of this project is to learn about the following Linux kernel features:
 - Network tunnels - TUN.
 - Network drivers.
 - Client/Server applications.

The application would be composed of 2 threads: a receive thread to receive packets form the Tunnel.
The second thread would be a client the would send the packet to a dedicated network device.

The network device would be created by a dummy network driver. This Dummy network driver would hold 2 netdevices and implement a loopback between them.


   


             ############################################         #########################################     ####################################
             #                                          #  queue  #                                       #     #                                  #
             # Userspace Application 1 - Receive thread ########### Userspace Application 1 - Send thread #     # Userspace Application 2 - Server # 
             #                                          #         #                                       #     #                                  #
             ############################################         #########################################     #################################### 
                         #                                                    #                                       #
                         # Tunnel                                             # Socket                                # Socket
                         #                                                    #                                       #
                         #                                                    #                                       #
             #########################                                  ######################            #####################
             #                       #                                  #                    #  Loopback  #                   #
             # Kernel Network Stack  #                                  # Dummy Netdevice 0  ############## Dummy Netdevice 1 #
             #                       #                                  #                    #            #                   #
             #########################                                  ######################            ##################### 



# Target Build System
buildroot

# Hardware Platform
1 Rapberry PI 4.
Booted from sdcard burned with sdcard image created by buildroot build for Raspberry PI.


# Open Source Projects Used
Project would be based on Assignment 5 buildroot.

# Previously Discussed Content

# New Content
Creating a tun/tap netdevice
encryption/decryption
Network drivers


# Shared Material
Using assignment 5 buildroot as a starting point.

# Source Code Organization
TBD: Modify the content below:

Buildroot Repository will be hosted at https://github.com/cu-ecen-aeld/final-project-TalHal

Network driver code will be hosted in in a repository at https://github.com/cu-ecen-aeld/final-project-TalHal

Encrypt Application would be hosted in https://github.com/cu-ecen-aeld/final-project-TalHal

Decrypt Application would be hosted at https://github.com/cu-ecen-aeld/final-project-TalHal


## Team project members:

TalHal - Code Developer

# Schedule Page

https://github.com/users/TalHal/projects/1/views/1?groupedBy%5BcolumnId%5D=86905036

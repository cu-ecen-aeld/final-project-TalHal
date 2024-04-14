# Overview

This page provide's an overview of Tal's contribution to the AESD Final Project final-project-assignment-raspberry-tun-server-client

# Video Outline
See <TODO: insert link to video>

The video demonstrates:
* Project's SW and HW overview
* Initial network configuration
* Running Pusher application
* Running rrecv application
* Traffic generation from PC
* Packets sent to Pusher application through eth0->tap0->Pusher
* Packets sent to rrecv application  through Pusher->sn0->sn1->rrecv

## Challenges
My most difficult challenge when implementing this project were:
* Uderstanding tap operation.
* Implementing Raw socket sender and receiver.


## Lessons Learned
The most important topics I learned from this project were:
* How to create a tap and use it
* Linux Bridge operaion
* Raw sockets usage



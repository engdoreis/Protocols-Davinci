@mainpage Protocol Stack

# Sumary
The protocol is difived in two layers described below.
 - @subpage transportProtocol "Transport layer"
 - @subpage CommandProtocol "Enlace layer"
 

# Using the API
 The fasted solution to use the protocol is using the provided library which implentes all the layers a can be accessed by a simplified API.
 - @subpage API "Library API"

# Implementing the protocol
    In case you want to implement the protocol by youself this section will describe how it works.
    The lowest layer is called Transport Layer and is responsable for send and receive packets with integrity.
    Over the Tranporte Layer, there's the Enlace Layer whitch is responsable for elaborate the functions for each packet.
## Transport Layer
   @copydoc transportFrame
   @image html Protocols-TransportProtocol.jpg "Transport Flow"

## Enlace Layer
   @copydoc PacketFrame
   @copydoc PacketType
   @copydoc StatusCode
   @image html Protocols-EnlaceProtocol.jpg "Enlace Flow"

## Command/Response list   
   @copydoc Commands

## Event list
   @copydoc Events

#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import MFRC522
import signal
import socket

#hostIp = '127.0.0.1'     # Endereco IP do Servidor
hostIp = sys.argv[1] # Endereco IP do Servidor
hostPort = 4325 # hostPorta que o Servidor esta

# tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# dest = (hostIp, hostPort)
# tcp.connect(dest)
print 'Para sair use CTRL+X\n'
# msg = " Hello"

# while msg != '\x18':
#     tcp.send (msg)
#     msg = raw_input()
# tcp.close()




continue_reading = True
MIFAREReader = MFRC522.MFRC522()
MIFAREReader.GPIO_CLEEN()

# def end_read(signal, frame):
#   global continue_reading
#   continue_reading = False
#   print "Ctrl+C captured, ending read."
#   MIFAREReader.GPIO_CLEEN()

# signal.signal(signal.SIGINT, end_read)

while continue_reading:
  (status,TagType) = MIFAREReader.MFRC522_Request(MIFAREReader.PICC_REQIDL)
  if status == MIFAREReader.MI_OK:
    print "Card detected"
  (status,backData) = MIFAREReader.MFRC522_Anticoll()
  if status == MIFAREReader.MI_OK:
    print "Card read UID: "+str(backData[0])+","+str(backData[1])+","+str(backData[2])+","+str(backData[3])+","+str(backData[4])
    msg = " "+str(backData[0])+","+str(backData[1])+","+str(backData[2])
    tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    dest = (hostIp, hostPort)
    tcp.connect(dest)
    tcp.send(msg)
    tcp.close()

    msg = " "+","+str(backData[3])+","+str(backData[4])
    tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    dest = (hostIp, hostPort)
    tcp.connect(dest)
    tcp.send(msg)
    tcp.close()
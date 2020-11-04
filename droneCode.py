from tello import Tello
import sys
from datetime import datetime
import time
import serial
commandsList = []
start_time = str(datetime.now())
ser = serial.Serial('COM10', 9600)
time.sleep(2)
#file_name = sys.argv[1]
#f = open(file_name, "r")
#commands = f.readlines()
tello = Tello()
tello.send_command("command")
tello.send_command("takeoff")
for x in range (0, 10):
   receivedCommand = ser.readline()
   string = receivedCommand.decode()
   string = string.rstrip()
   commandsList.append(string)
   print(string)
   tello.send_command(commandsList[-1])
   if string == "land":
       break;
tello.send_command("land")
'''
for command in commands:
   if command != '' and command != '\n':
       command = command.rstrip()
       if command.find('delay') != -1:
           sec = float(command.partition('delay')[2])
           print 'delay %s' % sec
           time.sleep(sec)
           pass
       else:
           tello.send_command(command)
log = tello.get_log()
out = open('log/' + start_time + '.txt', 'w')
for stat in log:
   stat.print_stats()
   str = stat.return_stats()
   out.write(str)
'''

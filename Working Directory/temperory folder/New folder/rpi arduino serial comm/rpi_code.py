import serial
import time
ser=serial.Serial('/dev/ttyAMA0',9600,timeout=1)
ser.open()

def  user_input(value) :
	if value=='1' :
		
		ser.write(1)
		time.sleep(1)
		x=ser.read()
		print "The state is:" 
		print(x)
 	elif value==2 :
		ser.write(2)
		time.sleep(1)
		print "success"
			

try:
    while 1:
	     value=input("Enter the no:") 
	     user_input(value);			

except KeyboardInterrupt:
    ser.close()
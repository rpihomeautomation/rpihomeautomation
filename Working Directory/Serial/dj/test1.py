import serial 
import time 
ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
ser.open()
i=0

#ser.write("testing")
try:
        while 1:
		if i==0:	
			ser.write("a")
		elif i==1:
			ser.write("b")
		elif i==2:
			ser.write("c")
		elif i==3:
			ser.write("d")
		else:
			ser.write("e")
		i=i+1
		if i==5:
			i=0
		time.sleep(0.5)
        response = ser.read(2)
		print response
		if response[0] =="1":
			if response[1]=='5':
				print "Got \'a\'"
			elif response[1]=="9":
				print "Got \'b\'"
		elif response[0]=="2":
			if response[1]=="2":
				print "Got \'c\'"
			elif response[1]=="7":
				print "Got \'d\'"
		else:
			print "Dunno"
		time.sleep(0.2)
except KeyboardInterrupt:
        ser.close()

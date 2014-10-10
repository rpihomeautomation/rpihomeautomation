import time
import serial
ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
ser.open()

def log(x):
    t=time.strftime("%H:%M:%S")
    path = "/home/pi/datalog/" + t +".txt"
    rpilog=open(path,'a')
    t=time.strftime("%H:%M:%S")
    rpilog.write('\n'+repr(t)+'\t')
    rpilog.write(x)
    rpilog.close()
    
try:
    while 1:
        response = ser.read(2)
        print response
        if response[0] =="2":
			if response[1]=='1':
				log("Adaptive Internal Lighting system - OFF - Auto Mode")
			elif response[1]=="2":
				log("Adaptive Internal Lighting system - ON - Auto Mode")
                        elif response[1]=="3":
				log("Adaptive Internal Lighting system - OFF - Manual Mode")
			elif response[1]=="4":
				log("Adaptive Internal Lighting system - ON - Manual Mode")
	elif response[0]=="3":
			if response[1]=="1":
				log("External Lighting system - OFF - Auto Mode")
			elif response[1]=="2":
				log("External Lighting system - ON - Auto Mode")
			elif response[1]=="3":
				log("External Lighting system - OFF - Manual Mode")
			elif response[1]=="1":
				log("External Lighting system - ON - Manual Mode")
	elif response[0]=="4":
			if response[1]=="1":
				log("Water pumping system - OFF - Auto Mode")
			elif response[1]=="2":
				log("Water pumping system - ON - Auto Mode")
			elif response[1]=="3":
				log("Water pumping system - OFF - Manual Mode")
			elif response[1]=="1":
				log("Water pumping system - ON - Manual Mode")
	elif response[0]=="5":
			if response[1]=="1":
				log("Door is open")
			elif response[1]=="2":
				log("Door is closed")
			elif response[1]=="3":
				log("Password enterned incorrect")
        elif response[0]=="6":
                        if response[1]=='1':
                                temp = ser.read(4)
                                i=0
                                adc=0
                                while(i<4):
                                    if i=1:
                                        k=10
                                    elif i=2:
                                        k=100
                                    elif i=3:
                                        k=1000
                                    if temp[i]=='0':
                                        adc = adc*k+ 0
                                    elif temp[i]=='1': 
                                        adc = adc*k + 1
                                    elif temp[i]=='2': 
                                        adc = adc*k + 2
                                    elif temp[i]=='3': 
                                        adc = adc*k + 3
                                    elif temp[i]=='4': 
                                        adc = adc*k + 4
                                    elif temp[i]=='5': 
                                        adc = adc*k + 5
                                    elif temp[i]=='6': 
                                        adc = adc*k + 6
                                    elif temp[i]=='7': 
                                        adc = adc*k + 7
                                    elif temp[i]=='8': 
                                        adc = adc*k + 8
                                    elif temp[i]=='9': 
                                        adc = adc*k + 9
                                log(str(adc))
        time.sleep(0.2)
                                
except KeyboardInterrupt:
        ser.close()
 
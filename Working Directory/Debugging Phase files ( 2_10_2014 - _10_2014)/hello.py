import time

def log(x):
    rpilog=open('C:/Users/Deepak J Puthukkaden/Desktop/abc.txt','a')
    t=time.strftime("%H:%M:%S")
    rpilog.write('\n'+repr(t)+'\t')
    rpilog.write(x)
    rpilog.close()

i=1
while i==1:
    log("HELLO")
    i=i-1
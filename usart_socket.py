import serial
import socket
import time
import threading
import os
import sys
def remote_local(sk,ser):
    try:
        while(1):
            data = sk.recv(1024)
            if(data != ''):
                ser.write(data)
                ser.flush()
                print '' 
                print ('from remote',data)
            else:
                raise Exception('an error occurs')

    finally:
        
            sk.close()
            ser.close()
             

def local_remote(sk,ser):
    try:
        while 1:
            ch = ser.read(1)
            # print('local_remote',ch)
            sk.send(ch)
            if(ch == 'S'):
                print ''
            print ch,



    finally:
        sk.close()
        ser.close()



if __name__ == '__main__':
    
    sk = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    ser = None
    try:
        if(sys.argv[1] == 'remote'):
            sk.connect(('66.112.219.161',60000))
	else:
	    sk.connect(('127.0.0.1',60000))
	

        print 'sk connected'
        if os.name == 'nt':
            ser = serial.Serial('COM4',38400)
        elif os.name == 'posix':
            ser =  serial.Serial('/dev/ttyUSB0',38400)

        print 'ser connected'
        t1 = threading.Thread(target=remote_local,args=(sk,ser))
        t1.setDaemon(True)
        t2 = threading.Thread(target=local_remote,args=(sk,ser))
        t2.setDaemon(True)
        t1.start()
        t2.start()
        time.sleep(2000)


    finally:
        try:
            sk.close()
            ser.close()
        except Exception,e:
            pass




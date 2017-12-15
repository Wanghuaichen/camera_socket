#-*-encoding=utf-8 -*-
import socket
import time
import  sys
import os
import datetime
import pytz

class FileProcess(object):
    """docstring for FileProcess"""


    def __init__(self):
        super(FileProcess, self).__init__()
        if(len(sys.argv) == 2):
            self.max_pic_num = 10;
        else:
            self.max_pic_num = int(sys.argv[2]);
            self.data = '';
            self.files = []


    def del_extra_file(self):
        if(os.path.exists('pics')):
            files = ['pics/'+f for f in os.listdir('pics')]

            if(len(files) > self.max_pic_num):
                for i in range(0,(len(files)-self.max_pic_num)):
                    os.remove(files[i])




    def create_jpg(self,data):
        self.data = data  
        if not os.path.exists('pics'):
            os.mkdir('pics')
        if os.path.exists('pics'):
            files = ['pics/' + f for f in os.listdir('pics')]

        if len(files) >= self.max_pic_num:
            oldest_file = self.get_oldest_file(files)
            os.remove(oldest_file)
            print 'the oldest file %s is removed'%(oldest_file,)

        self.create_new_file()



        


    def get_oldest_file(self,files):
        oldest_file = files[0]
        for f in files:
            if os.stat(f).st_ctime < os.stat(oldest_file).st_ctime:
                oldest_file = f
        return oldest_file


    def create_new_file(self):
        data = self.data
        f = None
        try:
            os.chdir('pics')
            tz = pytz.timezone('Asia/Shanghai')
            now = datetime.datetime.now(tz)
            now = now.strftime('%Y-%m-%d_%H%M%S')
            filename = 'pic'+now+'.jpg'
            f = open(filename,'wb')
            f.write(data)
            print 'picture generated!'
            os.chdir('..')
        finally:
            try:
                f.close()
            except Exception,e:
                pass

    def create_html(self):
        # self.files

        self.files = ['pics/' + f for f in os.listdir('pics')]

	self.files.sort()
        strs = ''.join("<center><img src='%s'/></center><center>%s</center>"%(i,i) for i in self.files)

        print strs

        html_model = '''
                <html>
                <title>camera test</title>
                <body>
                %s
                </body>
                </html>
                ''' % (strs,)
        f = open('index.html','w+')
        f.write(html_model)
        f.flush()
        f.close()
    

if __name__ == '__main__':

    skServer = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

    try:
        if  sys.argv[1] == 'local' :
            skServer.bind(('127.0.0.1',66666))
        elif sys.argv[1] == 'remote':
            skServer.bind(('66.112.219.161', 66666))
        else:
            skServer.bind((sys.argv[1],66666))


        cfp = FileProcess()
        cfp.del_extra_file()


        #
        skServer.listen(1)

        while 1:#create a pic

            try:
                conn,client_address = skServer.accept()
                print 'address %s on'%(client_address,)

                address = 0
                file_data = []

                while 1:#process fragments

                    #head: ST:
                    while 1:
                        recv_data = ''
                        while(len(recv_data)<3):
                            recv_ch = conn.recv(1)
                            if recv_ch == '':
                                time.sleep(0.5)
                                raise Exception('recv_ch == null')
                            recv_data = recv_data + recv_ch
                            if recv_data != '' and recv_data[0] != 'S':
                                recv_data = ''

                        if(recv_data == 'ST:'):
                            print 'ST:',
                            break

                    #len+add+data or END
                    recv_data = ''
                    while(len(recv_data) < 4 and recv_data[-3:] != 'END'):
                        recv_ch = conn.recv(1)
                        if recv_ch == '':
                            time.sleep(0.5)
                            raise Exception('recv_ch == null')
                        recv_data = recv_data + recv_ch


                    if(recv_data[-3:] == 'END'):
                        print 'blocks:',len(file_data)
                        d = ''.join(file_data[i] for i in range(len(file_data)))
                        print 'total bytes:',len(d)
                        f = None
                        try:
                            # f = open('write.jpg','wb')
                            # f.write(d)
                            if(d != ''):
                                cfp.create_jpg(d)
                                cfp.create_html()

                        finally:
                            address = 0
                            file_data = []
                        conn.send('OK:END\n')
                        time.sleep(10)
                        conn.recv(1024)
                        continue



                    #process the data
                    str_recv_address = recv_data[2] + recv_data[3]
                    recv_address = (ord(recv_data[2]) << 8) + ord(recv_data[3])
                    data_length = (ord(recv_data[0])<<8) + ord(recv_data[1])


                    print 'recv_address:%d, recv_data_length:%d,current address:%d'%(recv_address,data_length,address)

                    if(recv_address < address):
                        conn.send('OK:'+str_recv_address+'\r\n')
                        print 'fault sendback str_recv_addr: %s'%(repr(str_recv_address),)

                    elif(recv_address == address):
                        recv_data = ''
                        while len(recv_data) < data_length:
                            recv_ch = conn.recv(1)
                            if recv_ch == '':
                                time.sleep(0.5)
                                raise Exception('recv_ch == null')
                            recv_data = recv_data + recv_ch
                        file_data.append(recv_data)
                        # print recv_data[0:10],recv_data[-10:]
                        print 'fragment:%d recvd,frag[0]=%s,frag[1]=%s'%(address,repr(recv_data[0]),repr(recv_data[1]))

                        conn.send('OK:'+str_recv_address+'\r\n')
                        address = address + data_length

                    else:
                        print 'recv_address > address'
                        conn.send('OK:'+str_recv_address+'\r\n')


            except Exception,e:
                print 'an error occurs'
                print e

            finally:
                try:
                    conn.close()
                except Exception,e:
                    print e


    # except Exception,e:
    #     print 'big problem',e
    finally:
        skServer.close()

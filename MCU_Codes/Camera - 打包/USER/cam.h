#ifndef CAM_H_
#define CAM_H_
#include <stdio.h>
#include <stm32f103.h>
void SendChars(char* s, int len);//发送数组到串口，参数1为数组名，参数2为数组的长度，该函数可不受'\0'字符约束
void CamInit(void);//初始化摄像头，在main函数内调用
void CamReset(void);//摄像头复位
void CamClearPic(void);//摄像头清除原来数据
void CamTakeOnePic(void);//摄像头拍摄一张照片
void CamGetPicSize(void);//摄像头获取照片的大小
void CamReadPicBySize(int addr, int len,int total);//摄像头传回照片的原始数据
int CamCheckout(char* data,int len);//检查接收到的数据是否有问题，暂时没有内容

void GenerateData(char* recv,int recv_len,int address,char* send,int* send_len);//根据所收到的字符串数据及相应长度，和第一位数据所在地址以及这段数据的长度，发送数据片段
void SendToSocket(char* send_data, int send_len);//将生成的数据发送到socket

#endif



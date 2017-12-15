#include "menu.h"
#include "OLED.h"
#include "stdio.h"
#include "stdlib.h"
#include "delay.h"
#include "math.h"
#include "string.h"
#include "key.h"
#include "encoder.h"

#define MAX_ITEM_COUNT 5
#define MAX_POS 7

#define DATA_NUM 5


extern int gKeyNum;
extern int gKeyPressed;


int gMenuPage = 0;
float* pValue[MAX_ITEM_COUNT] = {0};
char strItem[MAX_ITEM_COUNT][20] = {"Val1","Val2","Val3","Val4","Val5123"};
int gCurItem = 0;
int gCurShow = 0;
int gIsSettingParameter = 0;

float gGlobal[10] = {0};

float* pData[DATA_NUM] = {0};
float Data[DATA_NUM] = {0};
char strDataItem[DATA_NUM][50] = {"D1","D2","D3","D4","D5"};
int gCurDataPage = 0;
int gMenuUpdate = 0;


float dir = 0 ;

void Menu_Config(void)
{
    pValue[0] = &gGlobal[0];
    pValue[1] = &gGlobal[0];
    pValue[2] = &gGlobal[0];
    pValue[3] = &gGlobal[0];
    pValue[4] = &gGlobal[0]; 
    pData[0] = (&gGlobal[0]);
    pData[1] = (&gGlobal[1]);
    pData[2] = (&gGlobal[0]);

    
}

void Menu_Choose(int key)//called by main:while or timer
{
    /*
    if(gKeyPressed == 1)
    {
        if(gKeyNum == 101)
        {
            gIsSettingParameter ^= 1;
            gKeyPressed = 0;
            
            if(gIsSettingParameter == 1)
            {
                gCurItem = gCurShow = 0;
                Menu_Show_Item(0);
                Menu_Show_Val(0);
                Menu_Show_Point(0);
            }
            else
            {
                gCurDataPage = 0;
                Menu_Show_Data();
            }
            
            
            return;
        }   
    }
       
    if(gIsSettingParameter == 0)
    {
        if(gKeyPressed)
        {
            gKeyPressed = 0;
            Menu_Show_Data(gKeyNum);
            
        }
        else if(gKeyPressed == 0)
        {
            static int count = 0;
            count++;
            if(count >= 10000)
            {
                Menu_Show_Data();
                count = 0;
            }
        }
    }
    else if(gIsSettingParameter == 1)
    {
        if(gKeyPressed)
        {
            gKeyPressed = 0;
            Menu_Set_Parameter(gKeyNum);
        }
    }
    
    
    
    */
    
    
    
}





void Menu_Show_Item(int index)
{
    int x = 20,y = 0,i = 0;
    // show 3 items from index
    for(i=0;i<3;i++)
    {
        if(index + i > MAX_ITEM_COUNT-1)
        {
            break;
        }

        OLED_ShowString(x,y+i*3,(uint8_t*)strItem[index+i],16);
        Delayms(100);
    }
}


void Menu_Show_Val(int index)
{
    int x = 60,y=0,i=0;
    char strValue[MAX_ITEM_COUNT][10] = {0};
    
    for(i=0;i<MAX_ITEM_COUNT;i++)
    {
        sprintf((char*)strValue[i],"% 8g",*(pValue[i]));
    }

    for(i=0;i<3;i++)
    {
        if(index + i > MAX_ITEM_COUNT-1)
        {
            break;
        }

        OLED_ShowString(x,y+i*3,(uint8_t*)strValue[index+i],16);
    }
    
}


void Menu_Show_Point(int index)
{
    //clear all the point
    OLED_ShowString(0,0," ",16);
    OLED_ShowString(0,3," ",16);
    OLED_ShowString(0,6," ",16);
    // set the point
    OLED_ShowString(0,index*3,"*",16);
}




void Menu_Set_Parameter(int key)
{
//    static double   KeyInput_Val = 0.0;                                    //¼üÅÌÊäÈëÖµ
    static uint32_t Input_Integer = 0;                                     //¼üÅÌÊäÈëÕûÊý²¿·Ö
    static uint32_t Input_Decimal = 0;                                     //¼üÅÌÊäÈëÐ¡Êý²¿·Ö
    static uint8_t Point_Flag = 0;                                         //Ð¡ÊýµãÊäÈë±êÖ¾Î»£¬ÓÐÐ¡ÊýµãÊäÈëÎª1£¬·ñÔòÎª0
    static uint8_t temp = 0;                                       //Ð¡ÊýÎ»Êý    
    static int pos = 0;
    switch(key)
    {

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 0:             
            if(pos == 0)
            {
                OLED_ShowString(60,(gCurItem-gCurShow)*3,"        ",16);
            }
            else if(pos >= MAX_POS)
            {
                return;
            }
            
            if(Point_Flag == 0)
            {
                Input_Integer = 10 * Input_Integer + key;
            }
            else 
            {
                temp++;
                Input_Decimal = 10 * Input_Decimal + key;
            }


            pos++;
            Menu_Show_CharSmall(gCurItem-gCurShow,pos,key-0+'0');
            break;

        case 200://OK
           
            if(pos == 0)
                return;
            *(pValue[gCurItem]) = Input_Integer + Input_Decimal * pow(10,-temp);
        
            pos = 0;
            temp = 0;                            
            Input_Integer = 0;                   
            Input_Decimal = 0;                   
            Point_Flag = 0;                      
            
            Menu_Show_Val(gCurShow);
            //set the global value to the KeyInput_Val
            //.....
            //Show the result
            //Menu_Show_SingleVal(gCurItem-gCurShow,KeyInput_Val,16);

            break;
        case 201://up
            if(pos != 0)
                return;
            gCurItem = (gCurItem >0)?gCurItem-1:0;
            if(gCurItem >=gCurShow && gCurItem <= gCurShow+2)
            {
                //Menu_Show_Item(gCurShow);
                //Menu_Show_Val(gCurShow);
                Menu_Show_Point(gCurItem - gCurShow);
            }
            else if(gCurItem <= gCurShow)
            {
                gCurShow = gCurItem - 2;
                OLED_Clear();
                Menu_Show_Item(gCurShow);
                Menu_Show_Val(gCurShow);
                Menu_Show_Point(2);
            }
            else if(gCurItem > gCurShow +2)
            {
                gCurShow = gCurItem;
                OLED_Clear();
                Menu_Show_Item(gCurShow);
                Menu_Show_Val(gCurShow);
                Menu_Show_Point(0);
            }
            break;
        case 202://down
            if(pos != 0)
                return;
            gCurItem = (gCurItem <= MAX_ITEM_COUNT-2)?gCurItem+1:MAX_ITEM_COUNT-1;
            if(gCurItem >=gCurShow && gCurItem <= gCurShow+2)
            {
                Menu_Show_Point(gCurItem - gCurShow);
                //Menu_Show_Item(gCurShow);
                //Menu_Show_Val(gCurShow);
                
            }
            else if(gCurItem <= gCurShow)
            {
                gCurShow = gCurItem - 2;
                OLED_Clear();
                Menu_Show_Item(gCurShow);
                Menu_Show_Val(gCurShow);
                Menu_Show_Point(2);
            }
            else if(gCurItem > gCurShow +2)
            {
                gCurShow = gCurItem;
                OLED_Clear();
                Menu_Show_Item(gCurShow);
                Menu_Show_Val(gCurShow);
                Menu_Show_Point(0);
            }

            break;

        case 203://.
            if(Point_Flag == 1)
                return;
            if(pos >= MAX_POS)
                return;
            
            Point_Flag = 1;
            
            
            pos++;
            Menu_Show_CharSmall(gCurItem-gCurShow,pos,'.');
            
            break;

        case 204://clear
            
            Input_Integer = 0;
            Input_Decimal = 0;
//            KeyInput_Val = 0.0;
            Point_Flag = 0;
            temp = 0;  

            pos = 0;
            Menu_Show_Val(gCurShow);

            break;

        case 205://back
            if(Point_Flag == 0)
            {
                Input_Integer = Input_Integer/10;
                
            }
            else
            {
                temp--;
                Input_Decimal = Input_Decimal/10;

                if(temp == 255)                                      //Çå³ýÐ¡Êýµã
                {
                    temp = 0;
                    Point_Flag = 0;
                }
            }
            
            pos = (pos >0)?pos-1:0;
            Menu_Show_CharSmall(gCurItem-gCurShow,pos+1,' ');
            
            break;

        default:
            break;
    }
}



void Menu_Show_CharSmall(int line,int pos,char ch)
{
    OLED_ShowChar(60+pos*7,line*3,ch,12);
}





void Menu_Show_Data(int key)
{
    int i = 0;
    char str[100] = {0};
    if(key == 102)
    {
        OLED_Clear();
        for(i=0;i<3;i++)
        {
            sprintf(str,"% .2f",*(pData[gCurDataPage*3+i]));
            OLED_ShowString(0,i*3,(uint8_t*)strDataItem[gCurDataPage*3+i],16);
            OLED_ShowString(50,i*3,(uint8_t*)str,16);
            if(gCurDataPage * 3 + i == DATA_NUM -1)
            {
                break;
            }
        }
    }
    if(key == 201)
    {
        gCurDataPage = (gCurDataPage > 0)? gCurDataPage - 1 : 0;
        OLED_Clear();
        for(i=0;i<3;i++)
        {
            sprintf(str,"% .2f",*(pData[gCurDataPage*3+i]));
            OLED_ShowString(0,i*3,(uint8_t*)strDataItem[gCurDataPage*3+i],16);
            OLED_ShowString(50,i*3,(uint8_t*)str,16);
            if(gCurDataPage * 3 + i == DATA_NUM -1)
            {
                break;
            }
        }
        
    }
    else if(key == 202)
    {
        gCurDataPage = (gCurDataPage < (DATA_NUM-1)/3)?gCurDataPage + 1:gCurDataPage;
        OLED_Clear();
        for(i=0;i<3;i++)
        {
            sprintf(str,"% .2f",*(pData[gCurDataPage*3+i]));
            OLED_ShowString(0,i*3,(uint8_t*)strDataItem[gCurDataPage*3+i],16);
            OLED_ShowString(50,i*3,(uint8_t*)str,16);
            if(gCurDataPage * 3 + i == DATA_NUM -1)
            {
                break;
            }
        }
    }
    else
    {
        for(i=0;i<3;i++)
        {
            sprintf(str,"% .2f",*(pData[gCurDataPage*3+i]));
            OLED_ShowString(50,i*3,(uint8_t*)str,16);
            if(gCurDataPage * 3 + i == DATA_NUM -1)
            {
                break;
            }
        }
    }
    
    
    
    
}



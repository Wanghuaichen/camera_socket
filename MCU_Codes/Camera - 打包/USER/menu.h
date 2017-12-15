#ifndef _MENU_H_
#define _MENU_H_ 


extern int gCurItem;
extern int gCurShow;
extern int gCurDataPage;
extern int gMenuUpdate;

void Menu_Config(void);
void Menu_Show(void);
void Menu_Choose(int key);
void Menu_Show_CharSmall(int line,int pos,char ch);

void Menu_Show_Item(int index);
void Menu_Show_Val(int index);
void Menu_Show_Point(int index);
void Menu_Set_Parameter(int key);

void Menu_Show_Data(int key);
#endif

#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cstring>
#include <conio.h>
#include <iostream>
#include <fstream>
#define BRIDGE_WIDE 52                                                          //�ܿ��(���������ߵ���)
#define BRIDGE_X 10                                                            //�����߾�,��X,Y��0��ʼ�����Ͻ�Ϊ{0,0},����ΪX�ᣬ����ΪY��
#define BRIDGE_END_X 68                                                         //��ܽ����߾�
#define BRIDGE_START_Y 2                                                        //��ʼ��ӭ��Y���꣬
#define BRIDGE_MAP_Y 5                                                          //��ܵ�ͼ��ʼY����
#define BRIDGE_MAP_INFOR_Y 10                                                   //��Ϣ��ʼY ����
#define BRIDGE_MAP_INFOR_END_Y 29                                               //��Ϣ������Y ����
#define	MAP_INFOR_ROW 18                                                        //��Ϣ��ʾ������

using namespace std;
//ѧ����
class Students {
public:
	int id;//ѧ�����
	char name[50];//ѧ������
	int couserid[4];//ѡ�εı��
	char major[4][20];//��ѡרҵ������
	int grade[4];//��ѡ�γ̵ĳɼ�
}students[200];
class Couser {
public:
	int  coursenum; //�γ̱���
	char coursename[20]; //�γ�����
	int credit; //�γ�ѧ��
	int hour; //�γ�ѧʱ
};
void Input();//¼��ѧ����Ϣ
void Calculate();//���㵱ǰѧ���ĸ���
void Change(Students& students, int changeid);//�޸�ѧ�����ſε���Ϣ /*����1λҪ�޸ĵ�ѧ����Ϣ������2ΪҪ�޸ĵĿγ̵ı��*/
void CourseChange(Students& student);//�޸Ŀγ̳ɼ�
void ShowInformation();//չʾ����ѧ����Ϣ
void Initialize();//��ʼ������
void SaveInformation();//������Ϣ
void SeekInformation();//����ѧ����Ϣ
void DeleteInformation();//ɾ��ѧ����Ϣ
void DrawGameLine();//���
#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cstring>
#include <conio.h>
#include <iostream>
#include <fstream>
#define BRIDGE_WIDE 52                                                          //总宽度(不计算两边的线)
#define BRIDGE_X 10                                                            //框架左边距,（X,Y从0开始，左上角为{0,0},向右为X轴，向下为Y轴
#define BRIDGE_END_X 68                                                         //框架结束边距
#define BRIDGE_START_Y 2                                                        //起始欢迎语Y坐标，
#define BRIDGE_MAP_Y 5                                                          //框架地图起始Y坐标
#define BRIDGE_MAP_INFOR_Y 10                                                   //信息起始Y 坐标
#define BRIDGE_MAP_INFOR_END_Y 29                                               //信息区结束Y 坐标
#define	MAP_INFOR_ROW 18                                                        //信息显示区行数

using namespace std;
//学生类
class Students {
public:
	int id;//学生编号
	char name[50];//学生姓名
	int couserid[4];//选课的编号
	char major[4][20];//所选专业的名称
	int grade[4];//所选课程的成绩
}students[200];
class Couser {
public:
	int  coursenum; //课程编码
	char coursename[20]; //课程名称
	int credit; //课程学分
	int hour; //课程学时
};
void Input();//录入学生信息
void Calculate();//计算当前学生的个数
void Change(Students& students, int changeid);//修改学生该门课的信息 /*参数1位要修改的学生信息，参数2为要修改的课程的编号*/
void CourseChange(Students& student);//修改课程成绩
void ShowInformation();//展示所有学生信息
void Initialize();//初始化函数
void SaveInformation();//保存信息
void SeekInformation();//查找学生信息
void DeleteInformation();//删除学生信息
void DrawGameLine();//框架
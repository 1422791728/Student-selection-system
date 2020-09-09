#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cstring>
#include <conio.h>
#include <iostream>
#include <fstream>
#define BRIDGE_WIDE 67                                                         //总宽度(不计算两边的线)
#define BRIDGE_X 10                                                            //框架左边距,（X,Y从0开始，左上角为{0,0},向右为X轴，向下为Y轴
#define BRIDGE_END_X 78                                                         //框架结束边距
#define BRIDGE_MAP_Y 1                                                          //起始Y坐标
#define BRIDGE_MAP_END_Y 28                                                   //结束Y 坐标
#define BRIDGE_HIGH 	27													//总高度

using namespace std;
//学生类
class Students {
public:
	int id;//学生编号
	char name[50];//学生姓名
	char major[4][20];//所选专业的名称
	int couserid[4];//选课的编号
	int grade[4];//所选课程的成绩
};
class Couser {
public:
	int  coursenum; //课程编码
	char coursename[20]; //课程名称
	int credit; //课程学分
	int hour; //课程学时
};
Couser cousers[4] = {
	{1,"数学",4,72},
	{2,"物理",2,36},
	{3,"计算机",4,54},
	{4,"英语",4,72}
};
Students students[200];
int max;//寻找学生ID最大值
void Input();//录入学生信息
void Calculate();//计算当前学生的个数
void Change(Students& students, int changeid);//修改学生该门课的信息 /*参数1位要修改的学生信息，参数2为要修改的课程的编号*/
void CourseChange(Students& student);//修改课程成绩
void ShowInformation(int i);//展示所有学生信息
void Initialize();//初始化函数
void SaveInformation();//保存信息
void SeekInformation();//查找学生信息
void DeleteInformation();//删除学生信息
void DrawGameLine();//框架
//修改控制台标题
void SetTitle(char* title);
//清空显示区
void clear(int x, int y, int row);
//设置控制台的前景色和背景色
void SetColor(int foreColor, int backColor);
//设置光标位置
void SetPosition(int x, int y);
// 设置控0制台的前景色和背景色
void SetColor(int foreColor, int backColor)
{
	HANDLE winHandle;  //句柄
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置文字颜色
	SetConsoleTextAttribute(winHandle, foreColor + backColor * 0x10);
}
//设置光标的位置
void SetPosition(int x, int y)
{
	HANDLE winHandle;  //句柄
	COORD pos = { x,y };
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置光标的位置
	SetConsoleCursorPosition(winHandle, pos);
}
//清空显示区
void clear(int x, int y, int row)//传入位置，和要清空的行数
{
	//每行内容用空格替代
	int i, j;
	for (i = 0; i < row; i++)
	{
		SetPosition(x, y + i);//开始清空的位置
		for (j = 0; j < BRIDGE_WIDE; j++)
		{
			printf(" ");
		}
	}
}
void Initialize()
{
	FILE* StudentsCouser = nullptr;//指针
	errno_t err;//用来看是否打开游戏
	err = fopen_s(&StudentsCouser, "Debug\\student\\studentGoal.txt", "r");//打开文件
	
	int i = 0;


	while (fscanf_s(StudentsCouser, "%d %s\n%s %d %d\n%s %d %d\n%s %d %d\n%s %d %d\n", &students[i].id, students[i].name, 50,
			students[i].major[0], 20, &students[i].couserid[0], &students[i].grade[0], 
			students[i].major[1], 20, &students[i].couserid[1], &students[i].grade[1], 
			students[i].major[2], 20, &students[i].couserid[2], &students[i].grade[2],
			students[i].major[3], 20, &students[i].couserid[3], &students[i].grade[3]) == 14)//从文件中读取信息*/
	{	
		i++;
	}
	fclose(StudentsCouser);
	return;
}
void SaveInformation()//保存信息
{
	FILE* StudentsGoal = nullptr;
	errno_t err;//用来看是否打开文档
	err = fopen_s(&StudentsGoal, "Debug\\student\\studentGoal.txt", "w");//打开文件
	//把文件从头开始往里面复制信息
	int i = 0;
	
	while(fprintf(StudentsGoal, "%d %s %s %d %d \n%s %d %d %s %d %d %s %d %d\n", &students[i].id, students[i].name, 50,
			students[i].major[0], 50, &students[i].couserid[0], &students[i].grade[0],
			students[i].major[1], 50, &students[i].couserid[1], &students[i].grade[0],
			students[i].major[2], 50, &students[i].couserid[2], &students[i].grade[2],
			students[i].major[3], &students[i].couserid[3], &students[i].grade[3]) == 14)//保存至文件中
	{
		i++;
	}

	fclose(StudentsGoal);
	return;
}
void DeleteInformation()//删除学生的信息
{
	clear(BRIDGE_X + 1, BRIDGE_MAP_Y + 1, BRIDGE_HIGH - 1);
	SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 2);
	cout << "请输入要删除的学生的ID";
	int deleteID;//要删除的学生的ID
	int deleteIndex = -1;//要删除学生的下标
	cin >> deleteID;
	for (int i = 0; i < max; i++)
	{
		if (deleteID == students[i].id)//验证是否有此ID
		{
			deleteIndex = i;//记录下来删除的下标
			break;
		}
	}
	if (deleteIndex == -1)
	{
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 3);
		cout << "对不起您输入的学生ID不存在请核对后输入" << endl;
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 4);
		cout << "是否重新输入(y/n)" << endl;
		char ch;
		fflush(stdin);
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 5);
		cout << "请输入";
		ch = _getch();
		fflush(stdin);
		if (ch == 'y' || ch == 'Y')
		{
			DeleteInformation();
		}
		else
		{
			if (ch == -32)//抵消方向键的光标
			{
				_getch();
			}
			return;
		}
	}
	else//存在
	{
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 6);
		cout << "删除成功" << endl;
		for (int i = deleteIndex; i < max; i++)
		{
			//下标为max里面数据为00000相当于把总长度 - 1了
			if (i != max - 1)
			{
				students[i + 1].id = i + 1;
			}
			memcpy(&students[i], &students[i + 1], sizeof(Students));//把删掉的抵消
		}
		ShowInformation(0);
		_getch();
		return;
	}
}
void Input()//录入学生信息
{
	Calculate();//每次录入之前算一下学生ID
	students[max].id = max + 1;
	clear(BRIDGE_X + 1, BRIDGE_MAP_Y + 1, BRIDGE_HIGH - 1);
	SetPosition(BRIDGE_X + 2, BRIDGE_MAP_Y + 2);
	cout << "学生学号: " << students[max].id ;
	SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 2);
	cout << "请输入学生姓名: ";
	cin >> students[max].name;
	SetPosition(BRIDGE_X + 10, BRIDGE_MAP_Y + 4);
	cout << "请输入学生选修课程的名称及该课程的分数（中间用空格隔开）: " << endl;
	
	for (int i = 0; i < 4; i++)
	{
		SetPosition(BRIDGE_X + 10, BRIDGE_MAP_Y + 5 + 2 * i);
		cin >> students[max].major[i] >> students[max].grade[i];
		int j;
		for (j = 0; j < 4; j++)//查找该课是否存在
		{
			if (strcmp(students[max].major[i], cousers[j].coursename) == 0)//存在
			{
				students[max].couserid[i] = cousers[j].coursenum;//记录下该课程的编号
				break;
			}
		}
		if (j == 4)//j == 4时候不存在该课程
		{
			clear(BRIDGE_X + 1, BRIDGE_MAP_Y + 5 + i,2);//只用清除输入错的那两行即可
			SetPosition(BRIDGE_X + 5, BRIDGE_MAP_Y + 5 );
			SetColor(9,0);
			cout << "您所输入的课程在所有选课列表中不存在是否重新录入(y/n)" << endl;
			SetColor(10,0);
			fflush(stdin);
			char ch = _getch();
			fflush(stdin);
			if (ch == 'y')
			{
				SetPosition(BRIDGE_X + 5, BRIDGE_MAP_Y + 5 + 2 * i);
				cin >> students[max].major[i] >> students[max].grade[i];
				i--;
			}
		}
		SetPosition(BRIDGE_X + 5, BRIDGE_MAP_Y + 7 + 2 * i);
		cout << "录入其他门课成绩请按任意键（不录入该按0退出）" << endl;
		char ch;
		fflush(stdin);
		SetPosition(BRIDGE_X + 5, BRIDGE_MAP_Y + 8 + 2 * i);
		ch = _getch();
		fflush(stdin);
		if (ch == '0')	//退出该功能
		{
			break;
		}
		if (i == 3)
		{
			SetPosition(BRIDGE_X + 10, BRIDGE_MAP_END_Y - 5);
			cout << "对不起，每人最多只有选修四门" << endl;
		}
	}
	for (int i = 0; i < 3; i++)//录入完把课程编号排序
	{
		for (int j = 0; j < 3 - i; j++)
		{
			if (students[max].couserid[i] != 0)//该课程必须存在
			{
				if (students[max].couserid[i] > students[max].couserid[i + 1])
				{
					swap(students[max].couserid[i], students[max].couserid[i + 1]);
					swap(students[max].major[i], students[max].major[i + 1]);
					swap(students[max].grade[i], students[max].grade[i + 1]);
				}
			}

		}
	}
	SetPosition(BRIDGE_X + 10, BRIDGE_MAP_END_Y - 4);
	cout << "是否录入其他学生信息(y/n)" << endl;
	fflush(stdin);
	SetPosition(BRIDGE_X + 10, BRIDGE_MAP_Y - 2);
	char ch = _getch();
	fflush(stdin);
	if (ch == 'y') //继续录入
	{
		Input();
	}
	return;
}
void CourseChange(Students& student)
{

	char tempcouser[50];
	SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 11);
	cout << "请选择要修改成绩的课程名称" << endl;
	SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 12);
	cin >> tempcouser;
	int j;
	for (j = 0; j < 4; j++)
	{
		if (strcmp(student.major[j], tempcouser) == 0)//如果存在
		{
			Change(student, j + 1);//前一个为学生的类后一个为所选课程编号
			break;
		}
	}
	if (j == 4)
	{
		SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 13);
		cout << "此学生并未选修此门课程请核对后再查询" << endl;
		SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 14);
		_getch();
	}
}
void SeekInformation()
{
	char tempname[50];//临时名字
	clear(BRIDGE_X + 1, BRIDGE_MAP_Y + 1, BRIDGE_HIGH - 1);
	SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 2);
	cout << "请输入要查询的学生名称" ;
	cin >> tempname;
	int i;
	for (i = 0; i < 200; i++)
	{
		if (strcmp(tempname, students[i].name) == 0)//是否存在该学生
		{
			//把当前 i 记录下来为学生ID - 1
			break;
		}
	}
	if (i == 200)
	{
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 3);
		SetColor(13, 0);
		cout << "您输入的学生姓名不存在" << endl;
		SetColor(10, 0);
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 5);
		cout << "是否重新输入(y/n)" << endl;
		fflush(stdin);
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 6);
		char ch = _getch();
		fflush(stdin);
		if (ch == 'y') //重新录入
		{
			SeekInformation();
		}
		else
		{
			return;
		}
	}
	SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 3);
	cout << "该学生选了如下的课程" << endl;
	SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 4);
	cout << std::left << setw(8) << "编号" << setw(8) << "名称" << setw(8) << "分数";
	int j;
	for (j = 0; j < 4; j++)
	{
		if (students[i].couserid[j] != 0)//不等于0 说明存在
		{
			SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 5 + j);
			cout << std::left << setw(8) << students[i].couserid[j] << setw(8) << students[i].major[j] << setw(8) << students[i].grade[j];
		}
		else//只要该课程不存在则后面的课程也不存在
		{
			break;
		}
	}
	SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 6 + j);
	cout << "是否修改其课程（y/n）" << endl;
	fflush(stdin);
	SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 7 + j);
	char ch = _getch();
	fflush(stdin);
	if (ch == 'y' || ch == 'Y') //重新录入
	{
		CourseChange(students[i]);
	}
	else
	{
		return;
	}

}
void Change(Students& student, int changeid)
{
	SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 13);
	cout << "您要修改的课程信息如下" << endl;
	SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 14);
	cout << student.major[changeid - 1] << '\t' << student.grade[changeid - 1];
	SetPosition(BRIDGE_X + 4, BRIDGE_MAP_Y + 15);
	cout << "请输入新的成绩";
	cin >> student.grade[changeid - 1];
}
void ShowInformation(int i)
{
	clear(BRIDGE_X + 1, BRIDGE_MAP_Y + 1, BRIDGE_HIGH - 1);
	int k = 0;
	for (; i < max; i++)
	{
		SetPosition(BRIDGE_X + 2, BRIDGE_MAP_Y + 2 + 6 *k);
		cout << "学生ID为";
		cout << students[i].id << endl;
		SetPosition(BRIDGE_X + 12, BRIDGE_MAP_Y + 2 + 6 * k);
		cout << "学生的姓名";
		cout << students[i].name << endl;
		SetPosition(BRIDGE_X + 2, BRIDGE_MAP_Y + 3 + 6 * k);
		cout << "成绩：";
		SetPosition(BRIDGE_X + 12, BRIDGE_MAP_Y + 3 + 6 * k);
		cout << std::left << setw(8) << "编号" << setw(8) << "名称" << setw(8) << "分数";
		int total = 0;//总成绩
		//以上为固定坐标
		for (int j = 0; j < 4; j++)
		{
			if (students[i].couserid[j] != 0)//不等于0 说明存在
			{
				SetPosition(BRIDGE_X + 12, BRIDGE_MAP_Y + 4 + 6 * k + j);
				cout << std::left << setw(8) << students[i].couserid[j] << setw(8)
					<< students[i].major[j] << setw(8) << students[i].grade[j];
				total += students[i].grade[j];
			}
			else//只要该课程不存在则后面的课程也不存在
			{
				break;
			}
		}
		cout << "该学生总分为" << total;
		k++;
		if (i + 1 == max)//到最后一位学生了了
		{
			SetPosition(BRIDGE_END_X - 20, BRIDGE_MAP_END_Y - 1);
			cout << "到最后一页了";
		}
		if ((i % 2 == 0 && i != 0) || max == i + 1)
		{
			SetPosition(BRIDGE_END_X - 24, BRIDGE_MAP_END_Y - 2);
			cout << "按上下键翻页其他键退出" << endl; 
			fflush(stdin);
			SetPosition(BRIDGE_END_X - 20, BRIDGE_MAP_END_Y - 1);
			char ch = _getch();
			fflush(stdin);
			if (ch == -32)
			{
					fflush(stdin);
					ch = _getch();
					fflush(stdin);
					if (ch == 80)//按下键
					{
						if (i + 1 == max)//到最后一位学生了了
						{
							SetPosition(BRIDGE_END_X - 20, BRIDGE_MAP_END_Y - 1);
							cout << "到最后一页了";
							ShowInformation(max - max % 3);
				
						}
						else if(i + 1 != max)
						{
							ShowInformation(i + 1);
						}
						else
						{
							break;
						}
					}
					else if (ch == 72)//上键
					{
						if (i == 2)
						{
							SetPosition(BRIDGE_END_X - 20, BRIDGE_MAP_END_Y - 1);
							cout << "已经是第一页了";
							ShowInformation(0);

						}
						else
						{
							ShowInformation(i - 3);
						}
					}
					else
					{
						break;
					}

			}
			else
			{
				break;
			}
		}
	}
	return;
}
void Calculate()
{
	max = students[0].id;//找出最大的ID；
	for (int i = 0; i < 200; i++)
	{
		if (students[i].id > max)
		{
			max = students[i].id;
		}
	}
}

void DrawGameLine()//游戏总框架
{
	for (int i = 0; i < BRIDGE_HIGH; i++)
	{
		SetPosition(BRIDGE_X, BRIDGE_MAP_Y + i);
		cout << "|" << endl;
		SetPosition(BRIDGE_END_X, BRIDGE_MAP_Y + i);
		cout << "|" << endl;
	}

	for (int i = 0; i < BRIDGE_WIDE + 2; i++)
	{
		SetPosition(BRIDGE_X + i, BRIDGE_MAP_Y);
		cout << "-" << endl;
	}
	for (int i = 0; i < BRIDGE_WIDE + 2; i++)
	{
		SetPosition(BRIDGE_X + i, BRIDGE_MAP_END_Y);
		cout << "-" << endl;
	}
}

int main()
{
	Initialize();
	Calculate();
	DrawGameLine();
	while (1)
	{
		clear(BRIDGE_X + 1, BRIDGE_MAP_Y + 1, BRIDGE_HIGH - 1);
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 2);
		SetColor(12,0);
		cout << "欢迎来到学生选课系统" << endl;
		SetColor(10, 0);
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 4);
		cout << "1.录入学生信息";
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 6);
		cout << "2.查找某学生信息(可修改该学生信息)";
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 8);
		cout << "3.删除某位学生信息";
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 10);
		cout << "4.展示所有学生信息";
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 12);
		cout << "5.储存信息";
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 14);
		cout << "6.退出系统" << endl;
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 16);
		cout << "请输入您选择的功能" << endl;
		SetPosition(BRIDGE_X + 20, BRIDGE_MAP_Y + 18);
		fflush(stdin);
		char choice = _getch();
		fflush(stdin);
		switch (choice)
		{
		case '1':
			Input();
			break;
		case '2':
			SeekInformation();
			break;
		case '3':
			DeleteInformation();
			break;
		case '4':
			ShowInformation(0);
			break;
		case '5':
			SaveInformation();
			break;
		case '6':
			exit(0);
			break;
		}
			
	}
}

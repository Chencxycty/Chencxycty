#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEFAULT_SZ 3


typedef struct Dr_massage
{
	char name[40];
	char phonenum[15];
	char sex[20];
	char id[10];
	char key[10];
	char major[60];
	char time[2][20];
	int num[2][3];
	int record[2][3];
	struct Dr_massage* next;
}Dr_Node;

typedef struct Patient_massage
{
	char name[40];
	char sex[20];
	char phonenum[15];
	char id[10];
	char key[10];
	struct Patient_massage* next;
}Patient_Node;

typedef struct Advance_massage
{
	char Dr_name[40];
	char Patient_name[40];
	char major[60];
	char time[40];
	int i;//用于记录日期
	int j;//用于记录时段
	int num;//预约时的编号
	struct Advance_massage* next;
}Advance;

//声明函数
//从文件中读取医生的数据
void Dr_LoadContact(Dr_Node** ps);
//医生的菜单函数
void Dr_meun();
//医生信息录入函数
void Dr_getInput(Dr_Node* person);
//医生信息注册
void add_Dr_register(Dr_Node** data);
//医生信息登录
Dr_Node* loading_Dr(Dr_Node* person);
//医生查找
Dr_Node* find_Dr(Dr_Node* person);
//医生信息删除
void del_Dr(Dr_Node** data, Patient_Node* patient, Advance* advance);
//医生信息修改
void modify_Dr(Dr_Node* person, Advance* data);
//医生个人信息展示函数
void Dr_deplay(Dr_Node* ps);
//预约时间修改函数（医生）
void change_advance_time(Dr_Node* dr);
//预约人数修改函数（医生）
void change_advance_num(Dr_Node* dr);
//通过医生姓名查找对应医生的函数
Dr_Node* find_Dr_byname(Dr_Node* person, char input[]);
//医生信息保存函数
void Dr_Save(Dr_Node* ps);
//查找和展示预约病人的函数
int find_Patient_byDrname(Advance* data, Dr_Node* dr, Patient_Node* patient);
//单日预约病人展示函数
int search_patientby_date(Advance* data, Dr_Node* dr, Patient_Node* patient);
//病人排号整理函数
void Dr_reline(Advance* data, Dr_Node* dr);




//从文件中读取患者的数据
void Patient_LoadContact(Patient_Node** ps);
//患者的菜单函数
void Patient_meun();
//患者信息录入函数
void Patient_getInput(Patient_Node* person);
//患者信息注册
void add_Patient_register(Patient_Node** data);
//患者信息登录 
Patient_Node* loading_Patient(Patient_Node* person);
//患者查找
Patient_Node* find_Patient(Patient_Node* person);
//患者信息删除
void del_Patient(Patient_Node** data, Dr_Node* dr, Advance*advance);
//患者信息修改
void modify_Patient(Patient_Node* person, Advance* data);
//患者个人信息展示函数
void Patient_deplay(Patient_Node* ps);
//患者信息保存函数
void Patient_Save(Patient_Node* data);
//通过病人名字查找医生（病人的预约信息查看函数）
int find_Dr_byPatientname(Advance* data, Dr_Node* dr, Patient_Node* patient);



//预约系统
Advance* Advance_Menu(Patient_Node* patient, Dr_Node* dr,Advance* advance);
//预约单号增加函数
void add_Advance_register(Patient_Node* patient, Dr_Node* dr, Advance** data);
//预约信息保存
void Advance_Save(Advance* data);
//预约信息加载到链表
void Advance_LoadContact(Advance** file);
//预约病人查找函数
Advance* search(Advance* data);
//自主操作预约信息删除函数
void del_Advance(Advance** data, Dr_Node* ps);
//预约信息修改函数
void modify_advance(Patient_Node* patient, Dr_Node* dr, Advance* data);
//因为患者信息删除而取消的预约函数
void del_Pat_Advance(Advance** data, Patient_Node* psp, Dr_Node* dr);
//因为医生信息删除而取消的预约函数
void del_Dr_Advance(Advance** data, Patient_Node* patient, Dr_Node* psd);
//患者排号函数
int advance_num(Dr_Node* dr, int i, int j, Advance* advance);
//预约时间和 医生相同的患者查找
Advance* find_advancebyname(Advance* data, Dr_Node* dr, int i, int j);
//上一个号码的查找函数
int lastnum_find(Advance* data, Dr_Node* dr, int i, int j);
//有患者取消预约后重新排序函数
void requeue(Advance* data, Dr_Node* ps, int delnum, int i, int j, char input[]);
//链表释放函数
void release(Dr_Node** Dr, Patient_Node** Patient, Advance** advance);
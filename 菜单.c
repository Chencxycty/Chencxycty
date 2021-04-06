#define _CRT_SECURE_NO_WARNINGS 1

#include "课设.h"

Patient_Node* Patient;
Dr_Node* Dr;
Advance* advance;
//医生菜单界面和选择功能 
void Dr_meun()
{
	//定义一些需要用到的变量 
	int code;
	char ch;
	int test;
	Dr_Node* person;
	person = (Dr_Node*)malloc(sizeof(Dr_Node));
	if (person == NULL)
	{
		printf("内存分配失败！\n");
		exit(1);
	}
	//正式进入医生的管理系统 
	person = find_Dr(Dr);
	if (person != NULL)
	{
		person = loading_Dr(person);
		if (person != NULL)
		{
			system("cls");
			printf("你好，%s医生！\n", person->name);
			printf("当前预约情况:\n");
			printf("上午（1/2/3天后）：\t%d\t%d\t%d\n", person->num[0][0], person->num[0][1], person->num[0][2]);
			printf("下午（1/2/3天后）：\t%d\t%d\t%d\n", person->num[1][0], person->num[1][1], person->num[1][2]);
			printf("|**********************|\n");
			printf("|-请选择您要进行的服务-|\n");
			printf("|----1.全部病人查看----|\n");
			printf("|----2.单日病人查看----|\n");
			printf("|----3.病人排号整理----|\n");
			printf("|----4.更改预约时段----|\n");
			printf("|----5.更改就诊人数----|\n");
			printf("|----6.修改个人信息----|\n");
			printf("|----7.删除个人信息----|\n");
			printf("|----8.注销------------|\n");
			printf("|**********************|\n");
			while (1)
			{
				printf("请选择您要进行的操作：");
				scanf("%d", &code);
				switch (code)
				{
				case 1:test = find_Patient_byDrname(advance, Dr, Patient);
					if (test == 0)
					{
						printf("无病人信息！\n");
					}
					break;
				case 2:test = search_patientby_date(advance, Dr, Patient);
					if (test == 0)
					{
						printf("无病人信息！\n");
					}
					break;
				case 3:
					Dr_reline(advance, Dr);
					printf("整理完毕！\n");
					break;
				case 4:
					change_advance_time(Dr);
					printf("保存成功！\n");
					break;
				case 5:
					change_advance_num(Dr);
					printf("保存成功！\n");
					break;
				case 6:
					modify_Dr(Dr, advance);
					system("cls");
					printf("|**********************|\n");
					printf("|-请选择您要进行的服务-|\n");
					printf("|----1.全部病人查看----|\n");
					printf("|----2.单日病人查看----|\n");
					printf("|----3.病人排号整理----|\n");
					printf("|----4.更改预约时段----|\n");
					printf("|----5.更改就诊人数----|\n");
					printf("|----6.修改个人信息----|\n");
					printf("|----7.删除个人信息----|\n");
					printf("|----8.注销------------|\n");
					printf("|**********************|\n");
					break;
				case 7:
					printf("是否要进行删除（Y/N）：");
					scanf("%c", &ch);
					scanf("%c", &ch);
					if (ch == 'Y')
					{
						del_Dr(&Dr, Patient, advance);
						printf("删除成功！\n");
					}
					return;
				case 8:
					Dr_Save(Dr);
					return;
				}
			}
		}
		else
		{
			printf("密码输入错误!\n");
			return;
		}
	}
	else
	{
		printf("找不到该用户!\n");
		printf("是否需要注册账号（Y/N）:");
		scanf("%c", &ch);
		scanf("%c", &ch);
		if (ch == 'Y')
		{
			add_Dr_register(&Dr);
			Dr_meun();
		}
		else
			return;
	}
}

//患者菜单界面和选择功能
void Patient_meun()
{
	int code;
	char ch;
	int test;
	Patient_Node* person;
	Patient_Node* psp;
	psp = (Patient_Node*)malloc(sizeof(Patient_Node));
	person = (Patient_Node*)malloc(sizeof(Patient_Node));
	if (person == NULL||psp==NULL)
	{
		printf("内存分配失败！\n");
		exit(1);
	}
	//正式进入患者的管理系统 
	person = find_Patient(Patient);
	if (person != NULL)
	{
		person = loading_Patient(person);
		if (person != NULL)
		{
			system("cls");
			printf("你好，%s同学！\n", person->name);
			printf("|**********************|\n");
			printf("|-请选择您要进行的服务-|\n");
			printf("|----1.查看医生信息----|\n");
			printf("|----2.修改预约信息----|\n");
			printf("|----3.进行预约挂号----|\n");
			printf("|----4.查看预约信息----|\n");
			printf("|----5.删除预约信息----|\n");
			printf("|----6.修改个人信息----|\n");
			printf("|----7.删除个人信息----|\n");
			printf("|----8.注销------------|\n");
			printf("|**********************|\n");
			while (1)
			{
				printf("请选择您要进行的操作：");
				scanf("%d", &code);
				switch (code)
				{
				case 1:Dr_deplay(Dr);
					break;
				case 2:modify_advance(Patient, Dr, advance);
					printf("修改成功！\n");
					break;
				case 3:
					add_Advance_register(Patient, Dr, &advance);
					break;
				case 4:test = find_Dr_byPatientname(advance, Dr, Patient);
					if (test == 0)
					{
						printf("无预约信息！\n");
					}
					break;
				case 5:
					printf("是否要进行删除（Y/N）：");
					scanf("%c", &ch);
					scanf("%c", &ch);
					if (ch == 'Y')
					{
						del_Advance(&advance, Dr);
						printf("删除成功！\n");
					}
					break;
				case 6:modify_Patient(Patient, advance);
					system("cls");
					printf("|**********************|\n");
					printf("|-请选择您要进行的服务-|\n");
					printf("|----1.查看医生信息----|\n");
					printf("|----2.修改预约信息----|\n");
					printf("|----3.进行预约挂号----|\n");
					printf("|----4.查看预约信息----|\n");
					printf("|----5.删除预约信息----|\n");
					printf("|----6.修改个人信息----|\n");
					printf("|----7.删除个人信息----|\n");
					printf("|----8.注销------------|\n");
					printf("|**********************|\n");
					break;
				case 7:
					printf("是否要进行删除（Y/N）：");
					scanf("%c", &ch);
					scanf("%c", &ch);
					if (ch == 'Y')
					{
						del_Patient(&Patient, Dr, advance);
						printf("删除成功！\n");
					}
					return;
				case 8:
					Patient_Save(Patient);
					return;
				}
			}
		}
		else
		{
			printf("密码错误!\n");
			return;
		}
	}
	else
	{
		printf("找不到该用户!\n");
		printf("是否需要注册账号（Y/N）:");
		scanf("%c", &ch);
		scanf("%c", &ch);
		if (ch == 'Y')
		{
			add_Patient_register(&Patient);
			Patient_meun();
		}
		else
			return;
	}
}

int main()
{
	//正式进入预约挂号系统 
	int code;
	//char input[20];
	Dr_LoadContact(&Dr);
	Patient_LoadContact(&Patient);
	Advance_LoadContact(&advance);
	printf("|***************************|\n");
	printf("|-欢迎使用医院预约挂号系统!-|\n");
	printf("|--请选择您的身份(输入数字)-|\n");
	printf("|----------1. 医生----------|\n");
	printf("|----------2. 患者----------|\n");
	printf("|***************************|\n");
	printf("请选择您的身份:");
	scanf_s("%d", &code);
	switch (code)
	{
	case 1:
		Dr_meun();
		break;
	case 2:
		Patient_meun();
		break;
	}
	Patient_Save(Patient);
	Dr_Save(Dr);
	Advance_Save(advance);
	//release(&Dr,&Patient,&advance);
	return 0;
}
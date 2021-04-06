#define _CRT_SECURE_NO_WARNINGS 1

#include "课设.h"

//把文件中的信息加载到系统中
void Patient_LoadContact(Patient_Node** ps)
{
	Patient_Node *person;
	FILE* pfRead = fopen("Patient_file.dat", "r");
	if (pfRead == NULL)
	{
		printf("文件打开失败！\n");
		return;
	}
	person = (Patient_Node*)malloc(sizeof(Patient_Node));
	if (person == NULL)
	{
		printf("内存分配失败！\n");
		exit(1);
	}

	//读取文件，存放患者系统中
	Patient_Node* temp;
	while (fread(person, sizeof(Patient_Node), 1, pfRead))
	{
		if (*ps != NULL)
		{
			temp =* ps;
			*ps = person;
			person->next = temp;
		}
		else
		{
			*ps = person;
			person->next = NULL;
		}
		person = (Patient_Node*)malloc(sizeof(Patient_Node));
		if (person == NULL)
		{
			printf("内存分配失败！\n");
			exit(1);
		}
	}

	fclose(pfRead);
	pfRead = NULL;
}
//患者信息输入函数 
void Patient_getInput(Patient_Node* person)
{
	printf("请输入姓名：");
	scanf("%s", person->name);
	printf("请输入电话号码：");
	scanf("%s", person->phonenum);
	printf("请输入性别：");
	scanf("%s", person->sex);
	printf("请输入学号：");
	scanf("%s", person->id);
	printf("请输入密码：");
	scanf("%s", person->key);
	printf("信息录入完毕！\n");
}
//患者信息注册 
void add_Patient_register(Patient_Node** data)
{
	Patient_Node* p1, * temp;
	p1 = (Patient_Node*)malloc(sizeof(Patient_Node));
	if (p1 == NULL)
	{
		printf("内存分配失败！\n");
		exit(1);
	}
	Patient_getInput(p1);
	if (*data != NULL)
	{
		temp = *data;
		*data = p1;
		p1->next = temp;
	}
	else
	{
		*data = p1;
		p1->next = NULL;
	}
	Patient_Save(p1);
}
//患者信息登录 
Patient_Node* loading_Patient(Patient_Node* person)
{
	Patient_Node* p;
	char input[10];
	printf("请输入您的密码：");
	scanf("%s", input);
	p = person;
	if (strcmp(person->key, input) == 0)
		return p;
	else
		return NULL;
}
//患者信息查找 
Patient_Node* find_Patient(Patient_Node* person)
{
	Patient_Node* p;
	char input[10];
	printf("请输入您的学号：");
	scanf("%s", input);
	p = person;
	while (p != NULL && strcmp(p->id, input))
	{
		p = p->next;
	}
	return p;
}
//患者信息删除 
void del_Patient(Patient_Node** data, Dr_Node* dr, Advance*advance)
{
	Patient_Node* previous;
	Patient_Node* current;
	Patient_Node* person;
	//调用查找函数找到联系人所在节点 	
	person = find_Patient(*data);
	if (person == NULL)
	{
		printf("找不到该联系人！\n");
	}
	else
	{
		current = *data;
		previous = NULL;

		while (current != NULL && current != person)
		{
			previous = current;
			current = current->next;
		}
		if (previous == NULL)
		{
			*data = current->next;
		}
		else
		{
			previous->next = current->next;
		}
	}
	del_Pat_Advance(&advance, person,dr);
	Patient_Save(*data);
}
//患者信息修改 
void modify_Patient(Patient_Node* person,Advance*data)
{
	Patient_Node* patient;
	Advance* temp = data;
	patient = find_Patient(person);
	char input[40];
	strcpy(input, patient->name);
	int code;
	if (patient == NULL)
	{
		printf("找不到该用户！\n");
	}
	else
	{
		system("cls");
		printf("**********************\n");
		printf("*请选择您要修改的信息*\n");
		printf("*-----1.姓名---------*\n");
		printf("*-----2.电话---------*\n");
		printf("*-----3.性别---------*\n");
		printf("*-----4.密码---------*\n");
		printf("**********************\n");
		scanf_s("%d", &code);
		switch (code)
		{
		case 1:
			printf("目前姓名为:%s\n", patient->name);
			printf("新录入姓名:");
			scanf("%s", patient->name);
			while (temp != NULL)
			{
				if (strcmp(temp->Patient_name, input) == 0)
					strcpy(temp->Patient_name, patient->name);
				temp = temp->next;
			}
			printf("修改成功！\n");
			break;
		case 2:
			printf("目前电话为:%s\n", patient->phonenum);
			printf("新录入电话:");
			scanf("%s", patient->phonenum);
			printf("修改成功！\n");
			break;
		case 3:
			printf("目前性别为:%s\n", patient->sex);
			printf("新录入性别:");
			scanf("%s", patient->sex);
			printf("修改成功！\n");
		case 4:
			printf("目前密码为:%s\n", patient->key);
			printf("新录入密码:");
			scanf("%s", patient->key);
			printf("修改成功！\n");
			break;
		}
	}
}
//患者信息展示函数
void Patient_deplay(Patient_Node* ps)
{
	Patient_Node* temp;
	temp = ps;
	if (ps == NULL)
	{
		printf("没有医生信息！\n");
	}
	else
	{
		//标题
		printf("%-20s\t%-20s\t%-12s\t%-12s\n", "名字", "电话", "性别", "学号");
		//数据
		while (temp != NULL)
		{
			printf("%-20s\t%-20s\t%-12s\t%-12s\n",
				temp->name,
				temp->phonenum,
				temp->sex,
				temp->id);
			temp = temp->next;
		}
	}
}
//患者信息保存函数
void Patient_Save(Patient_Node* data)
{
	FILE* pfWrite = fopen("Patient_file.dat", "w");
	if (pfWrite == NULL)
	{
		printf("文件打开失败！\n");
		exit(EXIT_FAILURE);
	}
	Patient_Node* temp = data;

	//写链表中数据到为文件中
	while (temp != NULL)
	{
		fwrite(temp, sizeof(Patient_Node), 1, pfWrite);
		temp = temp->next;
	}

	fclose(pfWrite);
	pfWrite = NULL;
}
//通过医生姓名查找对应医生的函数
Dr_Node* find_Dr_byname(Dr_Node* person, char input[])
{
	Dr_Node* temp = person;
	while (temp != NULL && strcmp(temp->name, input))
	{
		temp = temp->next;
	}
	return temp;
}
//通过病人名字查找医生（病人的预约信息查看函数）
int find_Dr_byPatientname(Advance*data, Dr_Node* dr, Patient_Node* patient)
{
	Patient_Node* temp1 = find_Patient(patient);
	Advance* temp2 = data;
	Dr_Node* ps = dr;
	int test = 0;
	printf("%-10s\t%-10s\t%-12s\t%-15s\n", "医生姓名", "学生姓名", "预约科室", "时间");
	while (temp2 != NULL)
	{
		if (strcmp(temp1->name, temp2->Patient_name) == 0)
		{
			printf("%-10s\t%-10s\t%-12s\t%d天后：%-15s\n",
				temp2->Dr_name,
				temp2->Patient_name,
				temp2->major,
				temp2->i,
				temp2->time);
			test = 1;
		}
		temp2 = temp2->next;
	}
	return test;
}
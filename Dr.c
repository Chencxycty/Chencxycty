#define _CRT_SECURE_NO_WARNINGS 1

#include "课设.h"

//把文件中的信息加载到系统中
void Dr_LoadContact(Dr_Node** ps)
{
	Dr_Node* person;
	FILE* pfRead = fopen("Dr_file.dat", "r");
	if (pfRead == NULL)
	{
		printf("文件打开失败\n");
		exit(EXIT_FAILURE);
	}
	person = (Dr_Node*)malloc(sizeof(Dr_Node));
	if (person == NULL)
	{
		printf("内存分配失败！\n");
		exit(1);
	}
	//读取文件，存放医生系统中
	Dr_Node* temp=NULL;
	while (fread(person, sizeof(Dr_Node), 1, pfRead))
	{

		if (*ps!= NULL)
		{
			temp = *ps;
			*ps = person;
			person->next = temp;
		}
		else
		{
			*ps = person;
			person->next = NULL;
		}
		person = (Dr_Node*)malloc(sizeof(Dr_Node));
		if (person == NULL)
		{
			printf("内存分配失败！\n");
			exit(EXIT_FAILURE);
		}
	}
	fclose(pfRead);
	pfRead = NULL;
	return;
}
//医生信息输入函数 
void Dr_getInput(Dr_Node* person)
{
	int i, j;
	printf("请输入姓名：");
	scanf("%s", person->name);
	printf("请输入电话号码：");
	scanf("%s", person->phonenum);
	printf("请输入性别：");
	scanf("%s", person->sex);
	printf("请输入工号：");
	scanf("%s", person->id);
	printf("请输入密码：");
	scanf("%s", person->key);
	printf("请输入科室：");
	scanf("%s", person->major);
	printf("请输入你要添加的时间(上午&下午)：");
	scanf("%s %s", &person->time[0], &person->time[1]);
	printf("请分别输入这三天允许的预约人数!\n");
	printf("上午：");
	scanf("%d %d %d", &person->num[0][0], &person->num[0][1], &person->num[0][2]);
	printf("下午：");
	scanf("%d %d %d", &person->num[1][0], &person->num[1][1], &person->num[1][2]);
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			person->record[i][j] = person->num[i][j];
		}
	}
	printf("信息录入完毕！\n");
}
//医生信息注册 
void add_Dr_register(Dr_Node** data)
{
	Dr_Node* p1, * temp;
	p1 = (Dr_Node*)malloc(sizeof(Dr_Node));
	if (p1 == NULL)
	{
		printf("内存分配失败！\n");
		exit(1);
	}
	Dr_getInput(p1);
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
	Dr_Save(p1);
}
//医生信息登录
Dr_Node* loading_Dr(Dr_Node* person)
{
	Dr_Node* p;
	char input[10];
	printf("请输入您的密码：");
	scanf("%s", input);
	p = person;
	if (strcmp(person->key, input)==0)
		return p;
	else
		return NULL;
}
//医生信息查找 
Dr_Node* find_Dr(Dr_Node* person)
{
	Dr_Node* p;
	char input[20];
	printf("请输入您的工号：");
	scanf("%s", input);
	p = person;
	while (p != NULL && strcmp(p->id, input))
	{
		p = p->next;
	}
	return p;
}
//医生信息删除 
void del_Dr(Dr_Node** data,Patient_Node*patient,Advance*advance)
{
	Dr_Node* previous;
	Dr_Node* current;
	Dr_Node* person;
	//调用查找函数找到联系人所在节点 	
	person = find_Dr(*data);
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
	del_Dr_Advance(&advance, patient, person);
	Dr_Save(*data);
}
//医生信息修改 
void modify_Dr(Dr_Node* person,Advance*data)
{
	Dr_Node* dr;
	Advance* temp = data;
	char input[40];
	char input1[60];
	dr = find_Dr(person);
	strcpy(input, dr->name);
	strcpy(input1, dr->major);
	int code;
	if (dr == NULL)
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
		printf("*-----4.科室---------*\n");
		printf("*-----5.密码---------*\n");
		printf("**********************\n");
		scanf_s("%d", &code);
		switch (code)
		{
		case 1:
			printf("目前姓名为:%s\n", dr->name);
			printf("新录入姓名:");
			scanf("%s", dr->name);
			while (temp != NULL)
			{
				if (strcmp(temp->Dr_name, input) == 0)
					strcpy(temp->Dr_name, dr->name);
				temp = temp->next;
			}
			printf("修改成功！\n");
			break;
		case 2:
			printf("目前电话为:%s\n", dr->phonenum);
			printf("新录入电话:");
			scanf("%s", dr->phonenum);
			printf("修改成功！\n");
			break;
		case 3:
			printf("目前性别为:%s\n", dr->sex);
			printf("新录入性别:");
			scanf("%s", dr->sex);
			printf("修改成功！\n");
			break;
		case 4:
			printf("目前科室为:%s\n", dr->major);
			printf("新录入科室:");
			scanf("%s", dr->major);
			while (temp != NULL)
			{
				if (strcmp(temp->major, input1) == 0)
					strcpy(temp->major, dr->major);
				temp = temp->next;
			}
			printf("修改成功！\n");
			break;
		case 5:
			printf("目前密码为:%s\n", dr->key);
			printf("新录入密码:");
			scanf("%s", dr->key);
			printf("修改成功！\n");
			break;
		}
	}
	Dr_Save(person);
}
//医生信息展示函数
void Dr_deplay(Dr_Node* ps)
{
	Dr_Node* temp;
	temp = ps;
	if(ps== NULL)
	{
		printf("没有医生信息！\n");
	}
	else
	{
		//标题
		printf("%-10s\t%-10s\t%-5s\t%-12s\t%-5s\t%-20s\t%-20s\n", "名字", "电话", "性别", "工号", "科室","预约时段","可预约人数");
		//数据
		while(temp!=NULL)
		{
			printf("%-10s\t%-10s\t%-5s\t%-12s\t%-5s\t上午：%s\t一天后：%d 两天后：%d 三天后：%d\n\t\t\t\t\t\t\t\t下午：%s\t一天后：%d 两天后：%d 三天后: %d\n",
				temp->name,
				temp->phonenum,
				temp->sex,
				temp->id,
				temp->major,
				&temp->time[0], temp->num[0][0],temp->num[0][1],temp->num[0][2],
				&temp->time[1],temp->num[1][0],temp->num[1][1], temp->num[1][2]);
			temp = temp->next;
		}
	}
}
//医生信息保存函数
void Dr_Save(Dr_Node *data)
{
	FILE* pfWrite = fopen("Dr_file.dat", "w");
	if (pfWrite == NULL)
	{
		printf("文件打开失败！\n");
		exit(EXIT_FAILURE);
	}
	Dr_Node* temp= data;

	//写链表中数据到为文件中
	while (temp != NULL)
	{
		fwrite(temp, sizeof(Dr_Node), 1, pfWrite);
		temp = temp->next;
	}

	fclose(pfWrite);
	pfWrite = NULL;
}
//查找预约了自己的患者的函数
int find_Patient_byDrname(Advance* data, Dr_Node* dr,Patient_Node*patient)
{
	Dr_Node* temp1 = find_Dr(dr);
	Advance* temp2 = data;
	Patient_Node* ps=patient;
	int i,j;
	int test = 0;
	printf("%-10s\t%-10s\t%-12s\t%-15s\t%15s\n", "姓名", "性别", "学号", "时间","号数");
	if (ps == NULL)
		return test;
	while (temp2 != NULL)
	{
		ps = patient;
		if (strcmp(temp1->name,temp2->Dr_name)==0)
		{
			while (ps != NULL && strcmp(ps->name, temp2->Patient_name))
			{
				ps = ps->next;
			}
			j = temp2->j;
			i = temp2->i;
			printf("%-10s\t%-10s\t%-12s\t%d天后：%-15s\t%5d\n",
				ps->name,
				ps->sex,
				ps->id,
				i,
				&temp1->time[j],
				temp2->num);
			//printf("success!\n");
			test = 1;
		}
		temp2 = temp2->next;
	}
	return test;
}
//单日预约病人展示函数
/*int search_patientby_date(Advance* data, Dr_Node* dr, Patient_Node* patient)
{
	int i, j;//i用来记录日期，j用来记录时段
	int k;//用于循环；
	int test = 0;//判断是否有信息的标准，t=1有，t=0没有
	Advance* temp = data;
	Advance* temp1 = data;
	Patient_Node* p = patient;
	Dr_Node* ps = find_Dr(dr);
	int cnt = 1;
	printf("请输入你要查找的日期（1/2/3天后）：");
	scanf("%d", &i);
	printf("%-10s\t%-10s\t%-12s\t%-15s\t%15s\n", "姓名", "性别", "学号", "时间", "号数");
	while (temp != NULL)
	{
		while (temp1 != NULL)
		{
			p = patient;
			if (strcmp(temp1->Dr_name, ps->name) == 0)
			{
				if (temp1->i == i&& temp1->num == cnt)
				{
					while (p != NULL && strcmp(p->name, temp1->Patient_name))
					{
						p = p->next;
					}
					j = temp1->j;
					printf("%-10s\t%-10s\t%-12s\t%d天后：%-15s\t%5d\n",
						p->name,
						p->sex,
						p->id,
						i,
						&ps->time[j],
						temp1->num);
					test = 1;
				}
			}
			temp1 = temp1->next;
		}
		temp1 = data;
		cnt++;
		temp = temp->next;
	}
	Advance_Save(data);
	return test;
}*/
//单日预约病人展示函数
int search_patientby_date(Advance* data, Dr_Node* dr, Patient_Node* patient)
{
	int i, j;//i用来记录日期，j用来记录时段
	int k;//用于循环；
	int test = 0;//判断是否有信息的标准，t=1有，t=0没有
	Advance* temp = data;
	Advance* temp1 = data;
	Patient_Node* p = patient;
	Dr_Node* ps = find_Dr(dr);
	int cnt = 1;
	printf("请输入你要查找的日期（1/2/3天后）：");
	scanf("%d", &i);
	printf("%-10s\t%-10s\t%-12s\t%-15s\t%15s\n", "姓名", "性别", "学号", "时间", "号数");
	for(k=0;k<20;k++)
	{
		while (temp1 != NULL)
		{
			p = patient;
			if (strcmp(temp1->Dr_name, ps->name) == 0)
			{
				if (temp1->i == i && temp1->num == cnt)
				{
					while (p != NULL && strcmp(p->name, temp1->Patient_name))
					{
						p = p->next;
					}
					j = temp1->j;
					printf("%-10s\t%-10s\t%-12s\t%d天后：%-15s\t%5d\n",
						p->name,
						p->sex,
						p->id,
						i,
						&ps->time[j],
						temp1->num);
					test = 1;
					temp = temp->next;
				}
			}
			temp1 = temp1->next;
		}
		temp1 = data;
		cnt++;
	}
	Advance_Save(data);
	return test;
}
//添加/更改预约时间的函数
void change_advance_time(Dr_Node* dr)
{
	Dr_Node* p;
	char input[20];
	p = find_Dr(dr);
	printf("请输入你要修改的时段(上午/下午)：");
	scanf("%s", input);
	if (strcmp(input ,"上午")==0)
	{
		printf("目前的预约时段是:%s\n", &p->time[0]);
		printf("请输入新的时间：");
		scanf("%s", &p->time[0]);
	}
	else if (strcmp(input, "下午")==0)
	{
		printf("目前的预约时段是:%s\n", &p->time[1]);
		printf("请输入新的时间：");
		scanf("%s", &p->time[1]);
	}
	
	Dr_Save(dr);
}
//添加/更改预约人数的函数
void change_advance_num(Dr_Node* dr)
{
	Dr_Node* p;
	int i;
	char input[20];
	p = find_Dr(dr);
	printf("输入你要修改预约人数的时间（1/2/3天后）：");
	scanf("%d", &i);
	printf("输入你要修改预约人数的时段（上午/下午）：");
	scanf("%s", input);
	if (strcmp(input, "上午") == 0)
	{
		printf("目前的预约人数限制是：%d\n", p->num[0][i-1]);
		printf("输入新的预约人数：");
		scanf("%d", &p->num[0][i - 1]);
		p->record[0][i - 1] = p->num[0][i - 1];
	}
	else if (strcmp(input, "下午") == 0)
	{
		printf("目前的预约人数限制是：%d\n", p->num[1][i-1]);
		printf("输入新的预约人数：");
		scanf("%d", &p->num[1][i - 1]);
		p->record[1][i - 1] = p->num[1][i - 1];
	}
	
	Dr_Save(dr);
}
//病人排号整理函数
void Dr_reline(Advance* data, Dr_Node* dr)
{
	int max = 0;
	int i;
	printf("请输入你要整理的日期（1/2/3天后）:");
	scanf("%d", &i);
	Dr_Node* ps = find_Dr(dr);
	Advance* temp = data;
	while (temp != NULL)
	{
		if (temp->j == 0 && temp->i == i && strcmp(temp->Dr_name, ps->name) == 0 && temp->num > max)
		{
			max = temp->num;
		}
		temp = temp->next;
	}
	temp = data;
	while (temp != NULL)
	{
		if (temp->j == 1 && temp->i == i && strcmp(temp->Dr_name, ps->name) == 0)
		{
			temp->num = max + 1;
			max++;
		}
		temp = temp->next;
	}
	Advance_Save(data);
}

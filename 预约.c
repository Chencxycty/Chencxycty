#define _CRT_SECURE_NO_WARNINGS 1

#include "课设.h"

//预约信息加载到链表
void Advance_LoadContact(Advance** file)
{
	Advance* data;
	FILE* pfRead = fopen("Advance_file.dat", "r");
	if (pfRead == NULL)
	{
		printf("文件打开失败\n");
		exit(EXIT_FAILURE);
	}
	data = (Advance*)malloc(sizeof(Advance));
	if (data == NULL)
	{
		printf("内存分配失败！\n");
		exit(1);
	}
	//读取文件，存放预约系统中
	Advance* temp = NULL;
	while (fread(data, sizeof(Advance), 1, pfRead))
	{

		if (*file != NULL)
		{
			temp = *file;
			*file = data;
			data->next = temp;
		}
		else
		{
			*file = data;
			data->next = NULL;
		}
		data = (Advance*)malloc(sizeof(Advance));
		if (data == NULL)
		{
			printf("内存分配失败！\n");
			exit(EXIT_FAILURE);
		}
	}
	fclose(pfRead);
	pfRead = NULL;
	return;
}
//预约单号增加函数
void add_Advance_register(Patient_Node* patient, Dr_Node* dr,Advance** data)
{
	Advance* p1, * temp;
	Advance* p = *data;
	p1 = (Advance*)malloc(sizeof(Advance));
	if (p1 == NULL)
	{
		printf("内存分配失败！\n");
		exit(EXIT_FAILURE);
	}
	p1=Advance_Menu(patient, dr,p);
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
	Advance_Save(p1);
}
//预约系统
Advance* Advance_Menu(Patient_Node* patient, Dr_Node* dr,Advance*advance)
{
	char ch;
	char input[20],a[20];
	int i,j;
	int num;
	Dr_Node* ps;
	Patient_Node* p;
	Advance* data;
	data = (Advance*)malloc(sizeof(Advance));
	if (data == NULL)
	{
		printf("内存分配失败！\n");
		exit(EXIT_FAILURE);
	}
	printf("是否要进行预约(Y/N):");
	scanf("%c", &ch);
	scanf("%c", &ch);
	if (ch == 'Y')
	{
		printf("请输入要预约的医生的姓名：");
		scanf("%s", input);
		ps = find_Dr_byname(dr, input);
		if (ps == NULL)
		{
			printf("并没有该医生的信息\n");
			printf("请检查信息是否输入错误！\n");
			exit(EXIT_FAILURE);
		}
		printf("请输入你要预约的时间（1/2/3天后）：");
		scanf("%d", &i);
		printf("请输入你要预约的时段（上午/下午）：");
		scanf("%s", a);
		if (strcmp(a, "上午") == 0)
		{
			j = 0;
		}
		else if (strcmp(a, "下午") == 0)
		{
			j = 1;
		}
		strcpy(data->Dr_name, input);
		p = find_Patient(patient);
		strcpy(data->Patient_name, p->name);
		data->i = i;
		data->j = j;//预约日期
		if (ps->num[j][i - 1] == 0)
		{
			printf("该时段预约号已满，无法再进行预约！\n");
		}
		else
		{
			ps->num[j][i - 1]--;
			strcpy(data->time, (*ps).time[j]);
			strcpy(data->major, ps->major);
			num = advance_num(ps, i, j, advance);
			data->num = num;
			printf("预约成功！\n");
		}
		Patient_Save(patient);
		Dr_Save(dr);
		return data;
	}
	else
	{
		Patient_Save(patient);
		return data;
	}
}
//预约病人查找函数
Advance* search(Advance* data)
{
	Advance* p;
	char pat[40], dr[40], input[20];
	int i, j = 0;
	printf("请输入您的姓名：");
	scanf("%s", pat);
	printf("请输入已预约医生的姓名：");
	scanf("%s", dr);
	printf("请输入你已预约的时段（上午/下午）和日期（1/2/3天后）：");
	scanf("%s %d", input, &i);
	if (strcmp(input, "上午") == 0)
	{
		j = 0;
	}
	else if (strcmp(input, "下午") == 0)
		{
			j = 1;
		}
	p = data;
		while (p != NULL)
		{
			if (p->i != i || p->j != j || strcmp(p->Dr_name, dr)|| strcmp(p->Patient_name, pat))
				p = p->next;
			else
				break;
		}

	return p;
}
//自主操作预约信息删除函数
void del_Advance(Advance** data,Dr_Node*ps)
{
	Advance* previous;
	Advance* current;
	Advance* person;
	Advance* p = *data;
	Dr_Node* dr;
	char input[40];
	int i, j, delnum;
	//调用查找函数找到联系人所在节点 	
	person = search(*data);
	if (person == NULL)
	{
		printf("找不到该患者的预约信息！\n");
		printf("请检查信息是否输入错误！\n");
	}
	else
	{
		i = person->i;
		j = person->j;
		delnum = person->num;
		strcpy(input, person->Dr_name);
		dr = find_Dr_byname(ps,input);
		dr->num[person->j][person->i-1]++;
		current = *data;
		previous = NULL;

		while (current != NULL && current != person)
		{
			previous = current;
			current = current->next;
		}
		if (previous != NULL)
		{
			previous->next = current->next;
		}
		else
		{
			*data = current->next;
		}
	}
	requeue(p, ps,delnum,i,j,input);
	Advance_Save(*data);
	Dr_Save(ps);
}
//有患者取消预约后重新排序函数
void requeue(Advance* data, Dr_Node* ps, int delnum, int i, int j,char input[])
{
	Advance* temp = data;
	Dr_Node* dr;
	dr = find_Dr_byname(ps, input);
	if (j == 0)
	{
		while (temp != NULL)
		{
			if (temp->i == i && temp->j == j && temp->num > delnum && strcmp(temp->Dr_name, dr->name)==0)
				temp->num--;
			temp = temp->next;
		}
	}
	else if (j == 1)
	{
		while (temp != NULL)
		{
			if (temp->i == i && temp->j == j && temp->num > delnum && strcmp(temp->Dr_name, dr->name)==0)
				temp->num--;
			temp = temp->next;
		}
	}
}
//预约信息修改函数
void modify_advance(Patient_Node* patient, Dr_Node* dr,Advance*data)
{
	Advance* p = search(data);
	if (p == NULL)
	{
		printf("无该预约信息！\n");
		return;
	}
	Patient_Node* ps1 = patient;
	Dr_Node* ps2 = dr;
	int i,j;
	char input[20],input1[20];
	strcpy(input,p->Dr_name);
	ps2= find_Dr_byname(dr, input);
	char ch;
	printf("是否要修改预约信息（Y/N）：");
	scanf("%c", &ch);
	scanf("%c", &ch);
	if (ch == 'Y')
	{
		i = p->i;
		j = p->j;
		ps2->num[j][i-1]++;
		printf("请输入新选择的医生:");
		scanf("%s", input);
		ps2 = find_Dr_byname(dr, input);
		p->num = advance_num(ps2, i, j, data);
		printf("请输入你要修改的日期(1/2/3天后):");
		scanf("%d", &i);
		p->i = i;
		printf("请输入你要修改的时段（上午/下午）：");
		scanf("%s", input1);
		if (strcmp(input, "上午") == 0)
		{
			j = 0;
		}
		else if (strcmp(input, "下午") == 0)
		{
			j = 1;
		}
		p->j = j;
		ps2->num[j][i - 1]--;
		strcpy(p->Dr_name, ps2->name);
		strcpy(p->major,ps2->major);
		strcpy(p->time, (*ps2).time[j]);
		Patient_Save(patient);
		Dr_Save(dr);
		Advance_Save(data);
	}
	else
	{
		return;
	}
}
//因为患者信息删除而取消的预约函数
void del_Pat_Advance(Advance** data, Patient_Node* psp, Dr_Node* dr)
{
	Advance* previous;
	Advance* current;
	Advance* temp = *data;
	Dr_Node* psd;
	char input[40];
	while(temp!=NULL)
	{
		if (strcmp(temp->Patient_name, psp->name) == 0)
		{
			strcpy(input, temp->Dr_name);
			psd = find_Dr_byname(dr, input);
			dr->num[temp->j][temp->i - 1]++;
			current = *data;
			previous = NULL;

			while (current != NULL && current != temp)
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
		temp = temp->next;
	}
	Advance_Save(*data);
	Dr_Save(dr);
}
//因为医生信息删除而取消的预约函数
void del_Dr_Advance(Advance** data, Patient_Node* patient, Dr_Node* psd)
{
	Advance* previous;
	Advance* current;
	Advance* temp = *data;
	while (temp != NULL)
	{
		if (strcmp(temp->Dr_name, psd->name) == 0)
		{
			current = *data;
			previous = NULL;

			while (current != NULL && current != temp)
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
		temp = temp->next;
	}
	Advance_Save(*data);
	Patient_Save(patient);
}
//患者排号函数
int advance_num(Dr_Node* dr, int i, int j,Advance*advance)
{
	Advance* p;
	int max;
	int t=1;
	p = find_advancebyname(advance,dr,i,j);
	if (p == NULL)
	{
		if (j==1)
		{
			t = dr->record[0][i-1] + 1;
		}
		else if(j == 0)
		{
			t = 1;
		}
	}
	else
	{
		max = lastnum_find(advance,dr, i,j);
		t = max + 1;
	}
	return t;
}
//预约时间和 医生相同的患者查找
Advance* find_advancebyname(Advance* data, Dr_Node* dr,int i,int j)
{
	Advance* temp=data;
	while (temp != NULL)
	{
		if (i != temp->i || j != temp->j|| strcmp(temp->Dr_name, dr->name))
			temp = temp->next;
		else
			break;
	}
	return temp;
}
//上一个号码的查找函数
int lastnum_find(Advance* data,Dr_Node* dr, int i, int j)
{
	Advance* temp = data;;
	int max = 0;
		while (temp != NULL)
		{
			if (strcmp(temp->Dr_name, dr->name) == 0 && i == temp->i && j == temp->j && temp->num > max)
				max = temp->num;
				temp = temp->next;
		}
	return max;
}
//预约信息保存
void Advance_Save(Advance* data)
{
	FILE* pfWrite = fopen("Advance_file.dat", "w");
	if (pfWrite == NULL)
	{
		printf("文件打开失败！\n");
		exit(EXIT_FAILURE);
	}
	Advance* temp = data;

	//写链表中数据到为文件中
	while (temp != NULL)
	{
		fwrite(temp, sizeof(Advance), 1, pfWrite);
		temp = temp->next;
	}

	fclose(pfWrite);
	pfWrite = NULL;
}
//链表释放函数
void release(Dr_Node** Dr, Patient_Node** Patient, Advance** advance)
{
	Dr_Node* temp1;
	Patient_Node* temp2;
	Advance* temp3;
	while (*Dr != NULL)
	{
		temp1 = *Dr;
		*Dr = (*Dr)->next;
		free(temp1);
	}
	while (*Patient != NULL)
	{
		temp2 = *Patient;
		*Patient = (*Patient)->next;
		free(temp2);
	}
	while (*advance != NULL)
	{
		temp3 = *advance;
		*advance = (*advance)->next;
		free(temp3);
	}
}
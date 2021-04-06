#define _CRT_SECURE_NO_WARNINGS 1

#include "����.h"

//���ļ��е���Ϣ���ص�ϵͳ��
void Dr_LoadContact(Dr_Node** ps)
{
	Dr_Node* person;
	FILE* pfRead = fopen("Dr_file.dat", "r");
	if (pfRead == NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(EXIT_FAILURE);
	}
	person = (Dr_Node*)malloc(sizeof(Dr_Node));
	if (person == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		exit(1);
	}
	//��ȡ�ļ������ҽ��ϵͳ��
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
			printf("�ڴ����ʧ�ܣ�\n");
			exit(EXIT_FAILURE);
		}
	}
	fclose(pfRead);
	pfRead = NULL;
	return;
}
//ҽ����Ϣ���뺯�� 
void Dr_getInput(Dr_Node* person)
{
	int i, j;
	printf("������������");
	scanf("%s", person->name);
	printf("������绰���룺");
	scanf("%s", person->phonenum);
	printf("�������Ա�");
	scanf("%s", person->sex);
	printf("�����빤�ţ�");
	scanf("%s", person->id);
	printf("���������룺");
	scanf("%s", person->key);
	printf("��������ң�");
	scanf("%s", person->major);
	printf("��������Ҫ��ӵ�ʱ��(����&����)��");
	scanf("%s %s", &person->time[0], &person->time[1]);
	printf("��ֱ����������������ԤԼ����!\n");
	printf("���磺");
	scanf("%d %d %d", &person->num[0][0], &person->num[0][1], &person->num[0][2]);
	printf("���磺");
	scanf("%d %d %d", &person->num[1][0], &person->num[1][1], &person->num[1][2]);
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			person->record[i][j] = person->num[i][j];
		}
	}
	printf("��Ϣ¼����ϣ�\n");
}
//ҽ����Ϣע�� 
void add_Dr_register(Dr_Node** data)
{
	Dr_Node* p1, * temp;
	p1 = (Dr_Node*)malloc(sizeof(Dr_Node));
	if (p1 == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
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
//ҽ����Ϣ��¼
Dr_Node* loading_Dr(Dr_Node* person)
{
	Dr_Node* p;
	char input[10];
	printf("�������������룺");
	scanf("%s", input);
	p = person;
	if (strcmp(person->key, input)==0)
		return p;
	else
		return NULL;
}
//ҽ����Ϣ���� 
Dr_Node* find_Dr(Dr_Node* person)
{
	Dr_Node* p;
	char input[20];
	printf("���������Ĺ��ţ�");
	scanf("%s", input);
	p = person;
	while (p != NULL && strcmp(p->id, input))
	{
		p = p->next;
	}
	return p;
}
//ҽ����Ϣɾ�� 
void del_Dr(Dr_Node** data,Patient_Node*patient,Advance*advance)
{
	Dr_Node* previous;
	Dr_Node* current;
	Dr_Node* person;
	//���ò��Һ����ҵ���ϵ�����ڽڵ� 	
	person = find_Dr(*data);
	if (person == NULL)
	{
		printf("�Ҳ�������ϵ�ˣ�\n");
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
//ҽ����Ϣ�޸� 
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
		printf("�Ҳ������û���\n");
	}
	else
	{
		system("cls");
		printf("**********************\n");
		printf("*��ѡ����Ҫ�޸ĵ���Ϣ*\n");
		printf("*-----1.����---------*\n");
		printf("*-----2.�绰---------*\n");
		printf("*-----3.�Ա�---------*\n");
		printf("*-----4.����---------*\n");
		printf("*-----5.����---------*\n");
		printf("**********************\n");
		scanf_s("%d", &code);
		switch (code)
		{
		case 1:
			printf("Ŀǰ����Ϊ:%s\n", dr->name);
			printf("��¼������:");
			scanf("%s", dr->name);
			while (temp != NULL)
			{
				if (strcmp(temp->Dr_name, input) == 0)
					strcpy(temp->Dr_name, dr->name);
				temp = temp->next;
			}
			printf("�޸ĳɹ���\n");
			break;
		case 2:
			printf("Ŀǰ�绰Ϊ:%s\n", dr->phonenum);
			printf("��¼��绰:");
			scanf("%s", dr->phonenum);
			printf("�޸ĳɹ���\n");
			break;
		case 3:
			printf("Ŀǰ�Ա�Ϊ:%s\n", dr->sex);
			printf("��¼���Ա�:");
			scanf("%s", dr->sex);
			printf("�޸ĳɹ���\n");
			break;
		case 4:
			printf("Ŀǰ����Ϊ:%s\n", dr->major);
			printf("��¼�����:");
			scanf("%s", dr->major);
			while (temp != NULL)
			{
				if (strcmp(temp->major, input1) == 0)
					strcpy(temp->major, dr->major);
				temp = temp->next;
			}
			printf("�޸ĳɹ���\n");
			break;
		case 5:
			printf("Ŀǰ����Ϊ:%s\n", dr->key);
			printf("��¼������:");
			scanf("%s", dr->key);
			printf("�޸ĳɹ���\n");
			break;
		}
	}
	Dr_Save(person);
}
//ҽ����Ϣչʾ����
void Dr_deplay(Dr_Node* ps)
{
	Dr_Node* temp;
	temp = ps;
	if(ps== NULL)
	{
		printf("û��ҽ����Ϣ��\n");
	}
	else
	{
		//����
		printf("%-10s\t%-10s\t%-5s\t%-12s\t%-5s\t%-20s\t%-20s\n", "����", "�绰", "�Ա�", "����", "����","ԤԼʱ��","��ԤԼ����");
		//����
		while(temp!=NULL)
		{
			printf("%-10s\t%-10s\t%-5s\t%-12s\t%-5s\t���磺%s\tһ���%d �����%d �����%d\n\t\t\t\t\t\t\t\t���磺%s\tһ���%d �����%d �����: %d\n",
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
//ҽ����Ϣ���溯��
void Dr_Save(Dr_Node *data)
{
	FILE* pfWrite = fopen("Dr_file.dat", "w");
	if (pfWrite == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(EXIT_FAILURE);
	}
	Dr_Node* temp= data;

	//д���������ݵ�Ϊ�ļ���
	while (temp != NULL)
	{
		fwrite(temp, sizeof(Dr_Node), 1, pfWrite);
		temp = temp->next;
	}

	fclose(pfWrite);
	pfWrite = NULL;
}
//����ԤԼ���Լ��Ļ��ߵĺ���
int find_Patient_byDrname(Advance* data, Dr_Node* dr,Patient_Node*patient)
{
	Dr_Node* temp1 = find_Dr(dr);
	Advance* temp2 = data;
	Patient_Node* ps=patient;
	int i,j;
	int test = 0;
	printf("%-10s\t%-10s\t%-12s\t%-15s\t%15s\n", "����", "�Ա�", "ѧ��", "ʱ��","����");
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
			printf("%-10s\t%-10s\t%-12s\t%d���%-15s\t%5d\n",
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
//����ԤԼ����չʾ����
/*int search_patientby_date(Advance* data, Dr_Node* dr, Patient_Node* patient)
{
	int i, j;//i������¼���ڣ�j������¼ʱ��
	int k;//����ѭ����
	int test = 0;//�ж��Ƿ�����Ϣ�ı�׼��t=1�У�t=0û��
	Advance* temp = data;
	Advance* temp1 = data;
	Patient_Node* p = patient;
	Dr_Node* ps = find_Dr(dr);
	int cnt = 1;
	printf("��������Ҫ���ҵ����ڣ�1/2/3��󣩣�");
	scanf("%d", &i);
	printf("%-10s\t%-10s\t%-12s\t%-15s\t%15s\n", "����", "�Ա�", "ѧ��", "ʱ��", "����");
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
					printf("%-10s\t%-10s\t%-12s\t%d���%-15s\t%5d\n",
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
//����ԤԼ����չʾ����
int search_patientby_date(Advance* data, Dr_Node* dr, Patient_Node* patient)
{
	int i, j;//i������¼���ڣ�j������¼ʱ��
	int k;//����ѭ����
	int test = 0;//�ж��Ƿ�����Ϣ�ı�׼��t=1�У�t=0û��
	Advance* temp = data;
	Advance* temp1 = data;
	Patient_Node* p = patient;
	Dr_Node* ps = find_Dr(dr);
	int cnt = 1;
	printf("��������Ҫ���ҵ����ڣ�1/2/3��󣩣�");
	scanf("%d", &i);
	printf("%-10s\t%-10s\t%-12s\t%-15s\t%15s\n", "����", "�Ա�", "ѧ��", "ʱ��", "����");
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
					printf("%-10s\t%-10s\t%-12s\t%d���%-15s\t%5d\n",
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
//���/����ԤԼʱ��ĺ���
void change_advance_time(Dr_Node* dr)
{
	Dr_Node* p;
	char input[20];
	p = find_Dr(dr);
	printf("��������Ҫ�޸ĵ�ʱ��(����/����)��");
	scanf("%s", input);
	if (strcmp(input ,"����")==0)
	{
		printf("Ŀǰ��ԤԼʱ����:%s\n", &p->time[0]);
		printf("�������µ�ʱ�䣺");
		scanf("%s", &p->time[0]);
	}
	else if (strcmp(input, "����")==0)
	{
		printf("Ŀǰ��ԤԼʱ����:%s\n", &p->time[1]);
		printf("�������µ�ʱ�䣺");
		scanf("%s", &p->time[1]);
	}
	
	Dr_Save(dr);
}
//���/����ԤԼ�����ĺ���
void change_advance_num(Dr_Node* dr)
{
	Dr_Node* p;
	int i;
	char input[20];
	p = find_Dr(dr);
	printf("������Ҫ�޸�ԤԼ������ʱ�䣨1/2/3��󣩣�");
	scanf("%d", &i);
	printf("������Ҫ�޸�ԤԼ������ʱ�Σ�����/���磩��");
	scanf("%s", input);
	if (strcmp(input, "����") == 0)
	{
		printf("Ŀǰ��ԤԼ���������ǣ�%d\n", p->num[0][i-1]);
		printf("�����µ�ԤԼ������");
		scanf("%d", &p->num[0][i - 1]);
		p->record[0][i - 1] = p->num[0][i - 1];
	}
	else if (strcmp(input, "����") == 0)
	{
		printf("Ŀǰ��ԤԼ���������ǣ�%d\n", p->num[1][i-1]);
		printf("�����µ�ԤԼ������");
		scanf("%d", &p->num[1][i - 1]);
		p->record[1][i - 1] = p->num[1][i - 1];
	}
	
	Dr_Save(dr);
}
//�����ź�������
void Dr_reline(Advance* data, Dr_Node* dr)
{
	int max = 0;
	int i;
	printf("��������Ҫ��������ڣ�1/2/3���:");
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

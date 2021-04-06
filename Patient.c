#define _CRT_SECURE_NO_WARNINGS 1

#include "����.h"

//���ļ��е���Ϣ���ص�ϵͳ��
void Patient_LoadContact(Patient_Node** ps)
{
	Patient_Node *person;
	FILE* pfRead = fopen("Patient_file.dat", "r");
	if (pfRead == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
	person = (Patient_Node*)malloc(sizeof(Patient_Node));
	if (person == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		exit(1);
	}

	//��ȡ�ļ�����Ż���ϵͳ��
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
			printf("�ڴ����ʧ�ܣ�\n");
			exit(1);
		}
	}

	fclose(pfRead);
	pfRead = NULL;
}
//������Ϣ���뺯�� 
void Patient_getInput(Patient_Node* person)
{
	printf("������������");
	scanf("%s", person->name);
	printf("������绰���룺");
	scanf("%s", person->phonenum);
	printf("�������Ա�");
	scanf("%s", person->sex);
	printf("������ѧ�ţ�");
	scanf("%s", person->id);
	printf("���������룺");
	scanf("%s", person->key);
	printf("��Ϣ¼����ϣ�\n");
}
//������Ϣע�� 
void add_Patient_register(Patient_Node** data)
{
	Patient_Node* p1, * temp;
	p1 = (Patient_Node*)malloc(sizeof(Patient_Node));
	if (p1 == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
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
//������Ϣ��¼ 
Patient_Node* loading_Patient(Patient_Node* person)
{
	Patient_Node* p;
	char input[10];
	printf("�������������룺");
	scanf("%s", input);
	p = person;
	if (strcmp(person->key, input) == 0)
		return p;
	else
		return NULL;
}
//������Ϣ���� 
Patient_Node* find_Patient(Patient_Node* person)
{
	Patient_Node* p;
	char input[10];
	printf("����������ѧ�ţ�");
	scanf("%s", input);
	p = person;
	while (p != NULL && strcmp(p->id, input))
	{
		p = p->next;
	}
	return p;
}
//������Ϣɾ�� 
void del_Patient(Patient_Node** data, Dr_Node* dr, Advance*advance)
{
	Patient_Node* previous;
	Patient_Node* current;
	Patient_Node* person;
	//���ò��Һ����ҵ���ϵ�����ڽڵ� 	
	person = find_Patient(*data);
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
	del_Pat_Advance(&advance, person,dr);
	Patient_Save(*data);
}
//������Ϣ�޸� 
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
		printf("**********************\n");
		scanf_s("%d", &code);
		switch (code)
		{
		case 1:
			printf("Ŀǰ����Ϊ:%s\n", patient->name);
			printf("��¼������:");
			scanf("%s", patient->name);
			while (temp != NULL)
			{
				if (strcmp(temp->Patient_name, input) == 0)
					strcpy(temp->Patient_name, patient->name);
				temp = temp->next;
			}
			printf("�޸ĳɹ���\n");
			break;
		case 2:
			printf("Ŀǰ�绰Ϊ:%s\n", patient->phonenum);
			printf("��¼��绰:");
			scanf("%s", patient->phonenum);
			printf("�޸ĳɹ���\n");
			break;
		case 3:
			printf("Ŀǰ�Ա�Ϊ:%s\n", patient->sex);
			printf("��¼���Ա�:");
			scanf("%s", patient->sex);
			printf("�޸ĳɹ���\n");
		case 4:
			printf("Ŀǰ����Ϊ:%s\n", patient->key);
			printf("��¼������:");
			scanf("%s", patient->key);
			printf("�޸ĳɹ���\n");
			break;
		}
	}
}
//������Ϣչʾ����
void Patient_deplay(Patient_Node* ps)
{
	Patient_Node* temp;
	temp = ps;
	if (ps == NULL)
	{
		printf("û��ҽ����Ϣ��\n");
	}
	else
	{
		//����
		printf("%-20s\t%-20s\t%-12s\t%-12s\n", "����", "�绰", "�Ա�", "ѧ��");
		//����
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
//������Ϣ���溯��
void Patient_Save(Patient_Node* data)
{
	FILE* pfWrite = fopen("Patient_file.dat", "w");
	if (pfWrite == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(EXIT_FAILURE);
	}
	Patient_Node* temp = data;

	//д���������ݵ�Ϊ�ļ���
	while (temp != NULL)
	{
		fwrite(temp, sizeof(Patient_Node), 1, pfWrite);
		temp = temp->next;
	}

	fclose(pfWrite);
	pfWrite = NULL;
}
//ͨ��ҽ���������Ҷ�Ӧҽ���ĺ���
Dr_Node* find_Dr_byname(Dr_Node* person, char input[])
{
	Dr_Node* temp = person;
	while (temp != NULL && strcmp(temp->name, input))
	{
		temp = temp->next;
	}
	return temp;
}
//ͨ���������ֲ���ҽ�������˵�ԤԼ��Ϣ�鿴������
int find_Dr_byPatientname(Advance*data, Dr_Node* dr, Patient_Node* patient)
{
	Patient_Node* temp1 = find_Patient(patient);
	Advance* temp2 = data;
	Dr_Node* ps = dr;
	int test = 0;
	printf("%-10s\t%-10s\t%-12s\t%-15s\n", "ҽ������", "ѧ������", "ԤԼ����", "ʱ��");
	while (temp2 != NULL)
	{
		if (strcmp(temp1->name, temp2->Patient_name) == 0)
		{
			printf("%-10s\t%-10s\t%-12s\t%d���%-15s\n",
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
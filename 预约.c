#define _CRT_SECURE_NO_WARNINGS 1

#include "����.h"

//ԤԼ��Ϣ���ص�����
void Advance_LoadContact(Advance** file)
{
	Advance* data;
	FILE* pfRead = fopen("Advance_file.dat", "r");
	if (pfRead == NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(EXIT_FAILURE);
	}
	data = (Advance*)malloc(sizeof(Advance));
	if (data == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		exit(1);
	}
	//��ȡ�ļ������ԤԼϵͳ��
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
			printf("�ڴ����ʧ�ܣ�\n");
			exit(EXIT_FAILURE);
		}
	}
	fclose(pfRead);
	pfRead = NULL;
	return;
}
//ԤԼ�������Ӻ���
void add_Advance_register(Patient_Node* patient, Dr_Node* dr,Advance** data)
{
	Advance* p1, * temp;
	Advance* p = *data;
	p1 = (Advance*)malloc(sizeof(Advance));
	if (p1 == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
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
//ԤԼϵͳ
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
		printf("�ڴ����ʧ�ܣ�\n");
		exit(EXIT_FAILURE);
	}
	printf("�Ƿ�Ҫ����ԤԼ(Y/N):");
	scanf("%c", &ch);
	scanf("%c", &ch);
	if (ch == 'Y')
	{
		printf("������ҪԤԼ��ҽ����������");
		scanf("%s", input);
		ps = find_Dr_byname(dr, input);
		if (ps == NULL)
		{
			printf("��û�и�ҽ������Ϣ\n");
			printf("������Ϣ�Ƿ��������\n");
			exit(EXIT_FAILURE);
		}
		printf("��������ҪԤԼ��ʱ�䣨1/2/3��󣩣�");
		scanf("%d", &i);
		printf("��������ҪԤԼ��ʱ�Σ�����/���磩��");
		scanf("%s", a);
		if (strcmp(a, "����") == 0)
		{
			j = 0;
		}
		else if (strcmp(a, "����") == 0)
		{
			j = 1;
		}
		strcpy(data->Dr_name, input);
		p = find_Patient(patient);
		strcpy(data->Patient_name, p->name);
		data->i = i;
		data->j = j;//ԤԼ����
		if (ps->num[j][i - 1] == 0)
		{
			printf("��ʱ��ԤԼ���������޷��ٽ���ԤԼ��\n");
		}
		else
		{
			ps->num[j][i - 1]--;
			strcpy(data->time, (*ps).time[j]);
			strcpy(data->major, ps->major);
			num = advance_num(ps, i, j, advance);
			data->num = num;
			printf("ԤԼ�ɹ���\n");
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
//ԤԼ���˲��Һ���
Advance* search(Advance* data)
{
	Advance* p;
	char pat[40], dr[40], input[20];
	int i, j = 0;
	printf("����������������");
	scanf("%s", pat);
	printf("��������ԤԼҽ����������");
	scanf("%s", dr);
	printf("����������ԤԼ��ʱ�Σ�����/���磩�����ڣ�1/2/3��󣩣�");
	scanf("%s %d", input, &i);
	if (strcmp(input, "����") == 0)
	{
		j = 0;
	}
	else if (strcmp(input, "����") == 0)
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
//��������ԤԼ��Ϣɾ������
void del_Advance(Advance** data,Dr_Node*ps)
{
	Advance* previous;
	Advance* current;
	Advance* person;
	Advance* p = *data;
	Dr_Node* dr;
	char input[40];
	int i, j, delnum;
	//���ò��Һ����ҵ���ϵ�����ڽڵ� 	
	person = search(*data);
	if (person == NULL)
	{
		printf("�Ҳ����û��ߵ�ԤԼ��Ϣ��\n");
		printf("������Ϣ�Ƿ��������\n");
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
//�л���ȡ��ԤԼ������������
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
//ԤԼ��Ϣ�޸ĺ���
void modify_advance(Patient_Node* patient, Dr_Node* dr,Advance*data)
{
	Advance* p = search(data);
	if (p == NULL)
	{
		printf("�޸�ԤԼ��Ϣ��\n");
		return;
	}
	Patient_Node* ps1 = patient;
	Dr_Node* ps2 = dr;
	int i,j;
	char input[20],input1[20];
	strcpy(input,p->Dr_name);
	ps2= find_Dr_byname(dr, input);
	char ch;
	printf("�Ƿ�Ҫ�޸�ԤԼ��Ϣ��Y/N����");
	scanf("%c", &ch);
	scanf("%c", &ch);
	if (ch == 'Y')
	{
		i = p->i;
		j = p->j;
		ps2->num[j][i-1]++;
		printf("��������ѡ���ҽ��:");
		scanf("%s", input);
		ps2 = find_Dr_byname(dr, input);
		p->num = advance_num(ps2, i, j, data);
		printf("��������Ҫ�޸ĵ�����(1/2/3���):");
		scanf("%d", &i);
		p->i = i;
		printf("��������Ҫ�޸ĵ�ʱ�Σ�����/���磩��");
		scanf("%s", input1);
		if (strcmp(input, "����") == 0)
		{
			j = 0;
		}
		else if (strcmp(input, "����") == 0)
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
//��Ϊ������Ϣɾ����ȡ����ԤԼ����
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
//��Ϊҽ����Ϣɾ����ȡ����ԤԼ����
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
//�����źź���
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
//ԤԼʱ��� ҽ����ͬ�Ļ��߲���
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
//��һ������Ĳ��Һ���
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
//ԤԼ��Ϣ����
void Advance_Save(Advance* data)
{
	FILE* pfWrite = fopen("Advance_file.dat", "w");
	if (pfWrite == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(EXIT_FAILURE);
	}
	Advance* temp = data;

	//д���������ݵ�Ϊ�ļ���
	while (temp != NULL)
	{
		fwrite(temp, sizeof(Advance), 1, pfWrite);
		temp = temp->next;
	}

	fclose(pfWrite);
	pfWrite = NULL;
}
//�����ͷź���
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
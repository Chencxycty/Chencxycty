#define _CRT_SECURE_NO_WARNINGS 1

#include "����.h"

Patient_Node* Patient;
Dr_Node* Dr;
Advance* advance;
//ҽ���˵������ѡ���� 
void Dr_meun()
{
	//����һЩ��Ҫ�õ��ı��� 
	int code;
	char ch;
	int test;
	Dr_Node* person;
	person = (Dr_Node*)malloc(sizeof(Dr_Node));
	if (person == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		exit(1);
	}
	//��ʽ����ҽ���Ĺ���ϵͳ 
	person = find_Dr(Dr);
	if (person != NULL)
	{
		person = loading_Dr(person);
		if (person != NULL)
		{
			system("cls");
			printf("��ã�%sҽ����\n", person->name);
			printf("��ǰԤԼ���:\n");
			printf("���磨1/2/3��󣩣�\t%d\t%d\t%d\n", person->num[0][0], person->num[0][1], person->num[0][2]);
			printf("���磨1/2/3��󣩣�\t%d\t%d\t%d\n", person->num[1][0], person->num[1][1], person->num[1][2]);
			printf("|**********************|\n");
			printf("|-��ѡ����Ҫ���еķ���-|\n");
			printf("|----1.ȫ�����˲鿴----|\n");
			printf("|----2.���ղ��˲鿴----|\n");
			printf("|----3.�����ź�����----|\n");
			printf("|----4.����ԤԼʱ��----|\n");
			printf("|----5.���ľ�������----|\n");
			printf("|----6.�޸ĸ�����Ϣ----|\n");
			printf("|----7.ɾ��������Ϣ----|\n");
			printf("|----8.ע��------------|\n");
			printf("|**********************|\n");
			while (1)
			{
				printf("��ѡ����Ҫ���еĲ�����");
				scanf("%d", &code);
				switch (code)
				{
				case 1:test = find_Patient_byDrname(advance, Dr, Patient);
					if (test == 0)
					{
						printf("�޲�����Ϣ��\n");
					}
					break;
				case 2:test = search_patientby_date(advance, Dr, Patient);
					if (test == 0)
					{
						printf("�޲�����Ϣ��\n");
					}
					break;
				case 3:
					Dr_reline(advance, Dr);
					printf("������ϣ�\n");
					break;
				case 4:
					change_advance_time(Dr);
					printf("����ɹ���\n");
					break;
				case 5:
					change_advance_num(Dr);
					printf("����ɹ���\n");
					break;
				case 6:
					modify_Dr(Dr, advance);
					system("cls");
					printf("|**********************|\n");
					printf("|-��ѡ����Ҫ���еķ���-|\n");
					printf("|----1.ȫ�����˲鿴----|\n");
					printf("|----2.���ղ��˲鿴----|\n");
					printf("|----3.�����ź�����----|\n");
					printf("|----4.����ԤԼʱ��----|\n");
					printf("|----5.���ľ�������----|\n");
					printf("|----6.�޸ĸ�����Ϣ----|\n");
					printf("|----7.ɾ��������Ϣ----|\n");
					printf("|----8.ע��------------|\n");
					printf("|**********************|\n");
					break;
				case 7:
					printf("�Ƿ�Ҫ����ɾ����Y/N����");
					scanf("%c", &ch);
					scanf("%c", &ch);
					if (ch == 'Y')
					{
						del_Dr(&Dr, Patient, advance);
						printf("ɾ���ɹ���\n");
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
			printf("�����������!\n");
			return;
		}
	}
	else
	{
		printf("�Ҳ������û�!\n");
		printf("�Ƿ���Ҫע���˺ţ�Y/N��:");
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

//���߲˵������ѡ����
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
		printf("�ڴ����ʧ�ܣ�\n");
		exit(1);
	}
	//��ʽ���뻼�ߵĹ���ϵͳ 
	person = find_Patient(Patient);
	if (person != NULL)
	{
		person = loading_Patient(person);
		if (person != NULL)
		{
			system("cls");
			printf("��ã�%sͬѧ��\n", person->name);
			printf("|**********************|\n");
			printf("|-��ѡ����Ҫ���еķ���-|\n");
			printf("|----1.�鿴ҽ����Ϣ----|\n");
			printf("|----2.�޸�ԤԼ��Ϣ----|\n");
			printf("|----3.����ԤԼ�Һ�----|\n");
			printf("|----4.�鿴ԤԼ��Ϣ----|\n");
			printf("|----5.ɾ��ԤԼ��Ϣ----|\n");
			printf("|----6.�޸ĸ�����Ϣ----|\n");
			printf("|----7.ɾ��������Ϣ----|\n");
			printf("|----8.ע��------------|\n");
			printf("|**********************|\n");
			while (1)
			{
				printf("��ѡ����Ҫ���еĲ�����");
				scanf("%d", &code);
				switch (code)
				{
				case 1:Dr_deplay(Dr);
					break;
				case 2:modify_advance(Patient, Dr, advance);
					printf("�޸ĳɹ���\n");
					break;
				case 3:
					add_Advance_register(Patient, Dr, &advance);
					break;
				case 4:test = find_Dr_byPatientname(advance, Dr, Patient);
					if (test == 0)
					{
						printf("��ԤԼ��Ϣ��\n");
					}
					break;
				case 5:
					printf("�Ƿ�Ҫ����ɾ����Y/N����");
					scanf("%c", &ch);
					scanf("%c", &ch);
					if (ch == 'Y')
					{
						del_Advance(&advance, Dr);
						printf("ɾ���ɹ���\n");
					}
					break;
				case 6:modify_Patient(Patient, advance);
					system("cls");
					printf("|**********************|\n");
					printf("|-��ѡ����Ҫ���еķ���-|\n");
					printf("|----1.�鿴ҽ����Ϣ----|\n");
					printf("|----2.�޸�ԤԼ��Ϣ----|\n");
					printf("|----3.����ԤԼ�Һ�----|\n");
					printf("|----4.�鿴ԤԼ��Ϣ----|\n");
					printf("|----5.ɾ��ԤԼ��Ϣ----|\n");
					printf("|----6.�޸ĸ�����Ϣ----|\n");
					printf("|----7.ɾ��������Ϣ----|\n");
					printf("|----8.ע��------------|\n");
					printf("|**********************|\n");
					break;
				case 7:
					printf("�Ƿ�Ҫ����ɾ����Y/N����");
					scanf("%c", &ch);
					scanf("%c", &ch);
					if (ch == 'Y')
					{
						del_Patient(&Patient, Dr, advance);
						printf("ɾ���ɹ���\n");
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
			printf("�������!\n");
			return;
		}
	}
	else
	{
		printf("�Ҳ������û�!\n");
		printf("�Ƿ���Ҫע���˺ţ�Y/N��:");
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
	//��ʽ����ԤԼ�Һ�ϵͳ 
	int code;
	//char input[20];
	Dr_LoadContact(&Dr);
	Patient_LoadContact(&Patient);
	Advance_LoadContact(&advance);
	printf("|***************************|\n");
	printf("|-��ӭʹ��ҽԺԤԼ�Һ�ϵͳ!-|\n");
	printf("|--��ѡ���������(��������)-|\n");
	printf("|----------1. ҽ��----------|\n");
	printf("|----------2. ����----------|\n");
	printf("|***************************|\n");
	printf("��ѡ���������:");
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
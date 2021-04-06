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
	int i;//���ڼ�¼����
	int j;//���ڼ�¼ʱ��
	int num;//ԤԼʱ�ı��
	struct Advance_massage* next;
}Advance;

//��������
//���ļ��ж�ȡҽ��������
void Dr_LoadContact(Dr_Node** ps);
//ҽ���Ĳ˵�����
void Dr_meun();
//ҽ����Ϣ¼�뺯��
void Dr_getInput(Dr_Node* person);
//ҽ����Ϣע��
void add_Dr_register(Dr_Node** data);
//ҽ����Ϣ��¼
Dr_Node* loading_Dr(Dr_Node* person);
//ҽ������
Dr_Node* find_Dr(Dr_Node* person);
//ҽ����Ϣɾ��
void del_Dr(Dr_Node** data, Patient_Node* patient, Advance* advance);
//ҽ����Ϣ�޸�
void modify_Dr(Dr_Node* person, Advance* data);
//ҽ��������Ϣչʾ����
void Dr_deplay(Dr_Node* ps);
//ԤԼʱ���޸ĺ�����ҽ����
void change_advance_time(Dr_Node* dr);
//ԤԼ�����޸ĺ�����ҽ����
void change_advance_num(Dr_Node* dr);
//ͨ��ҽ���������Ҷ�Ӧҽ���ĺ���
Dr_Node* find_Dr_byname(Dr_Node* person, char input[]);
//ҽ����Ϣ���溯��
void Dr_Save(Dr_Node* ps);
//���Һ�չʾԤԼ���˵ĺ���
int find_Patient_byDrname(Advance* data, Dr_Node* dr, Patient_Node* patient);
//����ԤԼ����չʾ����
int search_patientby_date(Advance* data, Dr_Node* dr, Patient_Node* patient);
//�����ź�������
void Dr_reline(Advance* data, Dr_Node* dr);




//���ļ��ж�ȡ���ߵ�����
void Patient_LoadContact(Patient_Node** ps);
//���ߵĲ˵�����
void Patient_meun();
//������Ϣ¼�뺯��
void Patient_getInput(Patient_Node* person);
//������Ϣע��
void add_Patient_register(Patient_Node** data);
//������Ϣ��¼ 
Patient_Node* loading_Patient(Patient_Node* person);
//���߲���
Patient_Node* find_Patient(Patient_Node* person);
//������Ϣɾ��
void del_Patient(Patient_Node** data, Dr_Node* dr, Advance*advance);
//������Ϣ�޸�
void modify_Patient(Patient_Node* person, Advance* data);
//���߸�����Ϣչʾ����
void Patient_deplay(Patient_Node* ps);
//������Ϣ���溯��
void Patient_Save(Patient_Node* data);
//ͨ���������ֲ���ҽ�������˵�ԤԼ��Ϣ�鿴������
int find_Dr_byPatientname(Advance* data, Dr_Node* dr, Patient_Node* patient);



//ԤԼϵͳ
Advance* Advance_Menu(Patient_Node* patient, Dr_Node* dr,Advance* advance);
//ԤԼ�������Ӻ���
void add_Advance_register(Patient_Node* patient, Dr_Node* dr, Advance** data);
//ԤԼ��Ϣ����
void Advance_Save(Advance* data);
//ԤԼ��Ϣ���ص�����
void Advance_LoadContact(Advance** file);
//ԤԼ���˲��Һ���
Advance* search(Advance* data);
//��������ԤԼ��Ϣɾ������
void del_Advance(Advance** data, Dr_Node* ps);
//ԤԼ��Ϣ�޸ĺ���
void modify_advance(Patient_Node* patient, Dr_Node* dr, Advance* data);
//��Ϊ������Ϣɾ����ȡ����ԤԼ����
void del_Pat_Advance(Advance** data, Patient_Node* psp, Dr_Node* dr);
//��Ϊҽ����Ϣɾ����ȡ����ԤԼ����
void del_Dr_Advance(Advance** data, Patient_Node* patient, Dr_Node* psd);
//�����źź���
int advance_num(Dr_Node* dr, int i, int j, Advance* advance);
//ԤԼʱ��� ҽ����ͬ�Ļ��߲���
Advance* find_advancebyname(Advance* data, Dr_Node* dr, int i, int j);
//��һ������Ĳ��Һ���
int lastnum_find(Advance* data, Dr_Node* dr, int i, int j);
//�л���ȡ��ԤԼ������������
void requeue(Advance* data, Dr_Node* ps, int delnum, int i, int j, char input[]);
//�����ͷź���
void release(Dr_Node** Dr, Patient_Node** Patient, Advance** advance);
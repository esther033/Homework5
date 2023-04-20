#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; //char���� element�� ����
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //queue[4]�迭 ����
	int front, rear; //int�� ���� front,rear ����
}QueueType; //QueueType ����ü ����


QueueType *createQueue(); //����ť�� �����ϴ� �Լ�
int freeQueue(QueueType *cQ); //�����޸� �Ҵ� �� ����ť �޸� ����
int isEmpty(QueueType *cQ); //����ť�� ����ִ��� Ȯ���ϴ� �Լ�
int isFull(QueueType *cQ); //����ť�� ���� ���ִ��� Ȯ���ϴ� �Լ�
void enQueue(QueueType *cQ, element item); //����ť�� item �߰�
void deQueue(QueueType *cQ, element* item); //����ť�� item ����(������ ���� ���ŵ����� �ʴ´�)
void printQ(QueueType *cQ); //����ť ���
void debugQ(QueueType *cQ); //����ť ����� (front�� rear �׸��� ����Ǿ� �ִ� ���� ���)
element getElement();//����ڿ��� item�� �Է¹޴� �Լ�


int main(void)
{
	
    printf("[----- [�ڿ�����]  [20220410154] -----]\n"); 
	QueueType *cQ = createQueue(); //QueueType����ü ���� *cQ���� �� createQueue()�� ȣ���Ͽ� ����
	element data; //element(char) ���� data ����
	for(int i=0;i<MAX_QUEUE_SIZE;i++) //�ݺ����� ����Ͽ�
	{
		cQ->queue[i]='\0';
	}
	char command; //char�� ���� command ���� ����

	do{
		printf("\n-----------------------------------------------------\n"); //�޴� ���
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//����ڿ��� command�� �Է¹޴´�

		switch(command) {//command���� ���� ����
		case 'i': case 'I': //command�� i or I�϶�
			data = getElement(); //data�� ����ڿ��� ���ڸ� �Է¹޴� �Լ��� ȣ���Ͽ� �� ���� ����
			enQueue(cQ, data); //enQueue�� ȣ���Ͽ� cQ�� data�߰�
			break;
		case 'd': case 'D': //command�� d or D�϶�
			deQueue(cQ,&data); //deQueue�� ȣ���Ͽ� cQ���� data�� ����(������ ���� ���ŵ����� �ʴ´�)
			break;
		case 'p': case 'P': //command�� p or P�϶�
			printQ(cQ); //printQ�Լ��� ȣ���Ͽ� cQ���
			break;
		case 'b': case 'B': //command�� b or B�϶�
			debugQ(cQ); //debugQ�Լ��� ȣ��
			break;
		case 'q': case 'Q': //command�� q or Q�϶�
			free(cQ); //cQ�޸� ����
			break;
		default: //command�� ���� ����� �ٸ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //""���� ���� ���
			break; 
		}

	}while(command != 'q' && command != 'Q'); //command�� q or Q�϶� �ݺ��� ����


	return 1;
}

QueueType *createQueue() //QueueType����ü createQueue() �Լ�
{
	QueueType *cQ; //QueueType ����ü�� ��ü *cQ����
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cq�� ���� �޸� �Ҵ��Ѵ�
	cQ->front = 0; //cQ�� ������� front=0
	cQ->rear = 0; //cQ�� ������� rear=0
	return cQ;//cQ ����
}

int freeQueue(QueueType *cQ) //cQ �޸𸮸� �����ϴ� �Լ�
{
    if(cQ == NULL) return 1; //cQ�� NULL�̸� �Լ� ����
    free(cQ); //cQ�޸� ����
    return 1;// �Լ� ����
}

element getElement()// ����ڿ��� ���ڸ� �Է¹޴� �Լ�
{
	element item; //element(char)�� ���� item ����
	printf("Input element = ");//""�� ���� ���
	scanf(" %c", &item); //����ڿ��� item������ �Է¹޴´�
	return item; //item ����
}


int isEmpty(QueueType *cQ) //cQ�� ����ִ��� Ȯ���ϴ� �Լ�
{
	if (cQ->front == cQ->rear){ //cQ�� ������� front�� rear�� ������ �� cQ�� ����ִ�
		printf("Circular Queue is empty!"); //""���� ���
		return 1;//�Լ� ����
	}
	else return 0; //�Լ�����
}

int isFull(QueueType *cQ) //cQ�� ���� ���ִ��� Ȯ���ϴ� �Լ�
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) { //cQ�� ������� front�� (rear+1)%MAX_QUEUE_SIZE�� ������ �� cQ�� ���� �� �ִ�
		printf(" Circular Queue is full!"); //""���� ���
		return 1; //�Լ�����
	}
	else return 0; //�Լ�����
}

void enQueue(QueueType *cQ, element item) //cQ�� item�� �߰��ϴ� �Լ�
{
	if(isFull(cQ)) return; //cq�� ���� �������� �Լ� ����
	else { //cQ�� ���� ������ ������
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //cQ�Ǹ������rear�� (cQ->rear + 1) % MAX_QUEUE_SIZE����
		cQ->queue[cQ->rear] = item; //cQ�� ������� queue[cQ->rear]�� item�� ����
	}
}

void deQueue(QueueType *cQ, element *item) //cQ�� item�� �����ϴ� �Լ�
{
	if(isEmpty(cQ)) return; //cq�� ��� ������ �Լ� ����
	else { //cQ�� ��� ���� ������
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; //cQ�Ǹ������ front�� (cQ->front + 1) % MAX_QUEUE_SIZE�� ���ش�
		*item = cQ->queue[cQ->front]; //*item�� cQ�� ������� queue[cQ->front]����(�ڵ屸���� �ǹ� ���� �ڵ������� �����ؾ��� ���� item�� �����Ѵ�) 
		cQ->queue[cQ->front]='\0'; 
		return; //�Լ� ����
	}
}


void printQ(QueueType *cQ) //cQ�� ����ϴ� �Լ�
{
	int i, first, last; //���� i, first, last���� 

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //first�� (cQ->front + 1)%MAX_QUEUE_SIZE�� ����
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //last�� (cQ->rear + 1)%MAX_QUEUE_SIZE�� ����

	printf("Circular Queue : ["); //""���� ���� ��� 

	i = first; //i�� first�� ����
	while(i != last){ //i�� last�϶� �ݺ��� ����
		printf("%3c", cQ->queue[i]); //cQ->queue[i] ���
		i = (i+1)%MAX_QUEUE_SIZE; //i�� (i+1)%MAX_QUEUE_SIZE�� ����

	}
	printf(" ]\n"); //""���� ���� ���
}


void debugQ(QueueType *cQ) //����ť ����� (front�� rear �׸��� ����Ǿ� �ִ� ���� ���)
{

	printf("\n---DEBUG\n"); //""���� ���� ���
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) //i<MAX_QUEUE_SIZE���� �ݺ��ϴ� �ݺ���
	{
		if(i == cQ->front) { //i�� cQ�� ������� front�� ������ ��
			printf("  [%d] = front\n", i); //"[i��]=front" ���
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //"[i��]=cQ->queue[i]��" ���

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //cQ�� ������� front�� rear ���
}



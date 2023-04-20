#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; //char형을 element로 정의
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //queue[4]배열 선언
	int front, rear; //int형 변수 front,rear 선언
}QueueType; //QueueType 구조체 선언


QueueType *createQueue(); //원형큐룰 생성하는 함수
int freeQueue(QueueType *cQ); //동적메모리 할당 된 원형큐 메모리 해제
int isEmpty(QueueType *cQ); //원형큐가 비어있는지 확인하는 함수
int isFull(QueueType *cQ); //원형큐가 가득 차있는지 확인하는 함수
void enQueue(QueueType *cQ, element item); //원형큐에 item 추가
void deQueue(QueueType *cQ, element* item); //원형큐에 item 제거(실제로 값이 제거되지는 않는다)
void printQ(QueueType *cQ); //원형큐 출력
void debugQ(QueueType *cQ); //원형큐 디버그 (front와 rear 그리고 저장되어 있는 값을 출력)
element getElement();//사용자에게 item을 입력받는 함수


int main(void)
{
	
    printf("[----- [박에스더]  [20220410154] -----]\n"); 
	QueueType *cQ = createQueue(); //QueueType구조체 변수 *cQ선언 후 createQueue()를 호출하여 저장
	element data; //element(char) 변수 data 선언
	for(int i=0;i<MAX_QUEUE_SIZE;i++) //반복문을 사용하여
	{
		cQ->queue[i]='\0';
	}
	char command; //char형 변수 command 변수 선언

	do{
		printf("\n-----------------------------------------------------\n"); //메뉴 출력
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//사용자에게 command를 입력받는다

		switch(command) {//command값에 따라 실행
		case 'i': case 'I': //command가 i or I일때
			data = getElement(); //data에 사용자에게 문자를 입력받는 함수를 호출하여 그 값을 저장
			enQueue(cQ, data); //enQueue를 호출하여 cQ에 data추가
			break;
		case 'd': case 'D': //command가 d or D일때
			deQueue(cQ,&data); //deQueue를 호출하여 cQ에서 data값 제거(실제로 값이 제거되지는 않는다)
			break;
		case 'p': case 'P': //command가 p or P일때
			printQ(cQ); //printQ함수를 호출하여 cQ출력
			break;
		case 'b': case 'B': //command가 b or B일때
			debugQ(cQ); //debugQ함수를 호출
			break;
		case 'q': case 'Q': //command가 q or Q일때
			free(cQ); //cQ메모리 해제
			break;
		default: //command가 위의 값들과 다를때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //""안의 내용 출력
			break; 
		}

	}while(command != 'q' && command != 'Q'); //command가 q or Q일때 반복문 종료


	return 1;
}

QueueType *createQueue() //QueueType구조체 createQueue() 함수
{
	QueueType *cQ; //QueueType 구조체의 객체 *cQ선언
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cq를 동적 메모리 할당한다
	cQ->front = 0; //cQ의 멤버변수 front=0
	cQ->rear = 0; //cQ의 멤버변수 rear=0
	return cQ;//cQ 리턴
}

int freeQueue(QueueType *cQ) //cQ 메모리를 해제하는 함수
{
    if(cQ == NULL) return 1; //cQ가 NULL이면 함수 종료
    free(cQ); //cQ메모리 해제
    return 1;// 함수 종료
}

element getElement()// 사용자에게 문자를 입력받는 함수
{
	element item; //element(char)형 변수 item 선언
	printf("Input element = ");//""의 내용 출력
	scanf(" %c", &item); //사용자에게 item변수를 입력받는다
	return item; //item 리턴
}


int isEmpty(QueueType *cQ) //cQ가 비어있는지 확인하는 함수
{
	if (cQ->front == cQ->rear){ //cQ의 멤버변수 front와 rear가 동일할 때 cQ는 비어있다
		printf("Circular Queue is empty!"); //""내용 출력
		return 1;//함수 종료
	}
	else return 0; //함수종료
}

int isFull(QueueType *cQ) //cQ가 가득 차있는지 확인하는 함수
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) { //cQ의 멤버변수 front와 (rear+1)%MAX_QUEUE_SIZE가 동일할 때 cQ는 가득 차 있다
		printf(" Circular Queue is full!"); //""내용 출력
		return 1; //함수종료
	}
	else return 0; //함수종료
}

void enQueue(QueueType *cQ, element item) //cQ에 item을 추가하는 함수
{
	if(isFull(cQ)) return; //cq가 가득 차있을시 함수 종료
	else { //cQ가 가득 차있지 않을때
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //cQ의멤버변수rear에 (cQ->rear + 1) % MAX_QUEUE_SIZE저장
		cQ->queue[cQ->rear] = item; //cQ의 멤버변수 queue[cQ->rear]에 item을 저장
	}
}

void deQueue(QueueType *cQ, element *item) //cQ에 item을 제거하는 함수
{
	if(isEmpty(cQ)) return; //cq가 비어 있을시 함수 종료
	else { //cQ가 비어 있지 않을때
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; //cQ의멤버변수 front에 (cQ->front + 1) % MAX_QUEUE_SIZE를 해준다
		*item = cQ->queue[cQ->front]; //*item에 cQ의 멤버변수 queue[cQ->front]저장(코드구현에 의미 없는 코드이지만 삭제해야할 값을 item에 저장한다) 
		cQ->queue[cQ->front]='\0'; 
		return; //함수 종료
	}
}


void printQ(QueueType *cQ) //cQ를 출력하는 함수
{
	int i, first, last; //변수 i, first, last선언 

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //first에 (cQ->front + 1)%MAX_QUEUE_SIZE값 저장
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //last에 (cQ->rear + 1)%MAX_QUEUE_SIZE값 저장

	printf("Circular Queue : ["); //""안의 내용 출력 

	i = first; //i에 first값 저장
	while(i != last){ //i가 last일때 반복문 종료
		printf("%3c", cQ->queue[i]); //cQ->queue[i] 출력
		i = (i+1)%MAX_QUEUE_SIZE; //i에 (i+1)%MAX_QUEUE_SIZE값 저장

	}
	printf(" ]\n"); //""안의 내용 출력
}


void debugQ(QueueType *cQ) //원형큐 디버그 (front와 rear 그리고 저장되어 있는 값을 출력)
{

	printf("\n---DEBUG\n"); //""안의 내용 출력
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) //i<MAX_QUEUE_SIZE까지 반복하는 반복문
	{
		if(i == cQ->front) { //i가 cQ의 멤버변수 front와 동일할 때
			printf("  [%d] = front\n", i); //"[i값]=front" 출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //"[i값]=cQ->queue[i]값" 출력

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //cQ의 멤버변수 front와 rear 출력
}



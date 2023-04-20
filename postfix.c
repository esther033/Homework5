#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 6,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 4,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE]; //중위표기수식을 저장하는 배열 선언
char postfixExp[MAX_EXPRESSION_SIZE]; //후위표기수식을 저장하는 배열 선언
char postfixStack[MAX_STACK_SIZE]; //중위표기수식실행할 때 스택을 나타낼 배열 선언
int evalStack[MAX_STACK_SIZE]; //연산자 스택을 나타낼 배열 선언

int postfixStackTop = -1; //후위표기 수식의 top을 선언 후 -1로 초기화
int evalStackTop = -1;  //연산자스택의 top을 선언 후 -1로 초기화

int evalResult = 0; 

void postfixPush(char x);  //postfixstack에 x를 저장하는 함수
char postfixPop(); //postfixstack에서 저장된값을 내보내는 함수
void evalPush(int x); //evalstack에서 x를 저장하는 함수
int evalPop(); //evalstack에서 저장된 값을 내보내는 함수
void getInfix(); //사용자에게 중위표기수식을 입력받는 함수
precedence getToken(char symbol); //token선택 후 분류
precedence getPriority(char x); //token의 우선순위를 계산하는 함수
void charCat(char* c);//c를infixexp에 추가하는 함수
void toPostfix(); //infix를 postfix로 변환
void debug(); //debug하는 함수
void reset(); //값을 초기화 하는 함수
void evaluation(); //계산하는 함수

int main()
{
	
    printf("[----- [박에스더]  [2022041054] -----]\n"); 
	char command; //사용자에게 command를 입력받는 변수

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자에게 command를 입력받는다

		switch(command) {//command값에 따라 실행
		case 'i': case 'I': //command가 i,I일때
			getInfix(); //getInfix함수 호출
			break;
		case 'p': case 'P': //command가 p,P일때
			toPostfix(); //toPostfix함수 호출
			break;
		case 'e': case 'E': //command가 e,E일때
			evaluation(); //evaluation함수 호출
			break;
		case 'd': case 'D': //command가 d,D일때
			debug(); //debug함수 호출
			break;
		case 'r': case 'R': //command가 r,R일때
			reset(); //reset함수 호출
			break;
		case 'q': case 'Q': //command가 q,Q일때
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;


}

void postfixPush(char x) //후위표기수식을 스택에 저장하는 함수
{
    postfixStack[++postfixStackTop] = x; //후위표기 수식의스택에서 [top+1]에 x저장
}

char postfixPop() //후위표기수식의 스택에서 저장된 값을 가져오는 함수
{
	char x; //변수 x선언
    if(postfixStackTop == -1) //top이 -1일때
        return '\0'; //함수종료
    else {
    	x = postfixStack[postfixStackTop--]; //x에 후위표기수식의 스택에서[top-1]값 저장
    }
    return x;
}

void evalPush(int x)//연산스택에 저장하는 함수
{
    evalStack[++evalStackTop] = x; //연산자스택에서 [top+1]에 x저장
}

int evalPop()//연산스택에서 저장된 값을 가져오는 함수
{
    if(evalStackTop == -1)//top이 -1일때
        return -1;//-1값을 리턴하며 함수종료
    else
        return evalStack[evalStackTop--]; //연산자 스택[top-1]을 리턴
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */

void getInfix() //중위표시수식을 입력받는 함수
{
    printf("Type the expression >>> "); 
    scanf("%s",infixExp); //사용자에게 중위표시 수식을 입력받는다 
}

precedence getToken(char symbol) //token을 리턴하는 함수
{
	switch(symbol) { //symbol의 값에따라 리턴값이 달라진다
	case '(' : return lparen; 
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x) //우선순위를 리턴하는 함수
{
	return getToken(x); //token(x)를 호출하여 저장한다
}


void charCat(char* c) //문자를 입력받아 postfixExp에 추가
{
	if (postfixExp == '\0') //postfirxExp가 \0일??
		strncpy(postfixExp, c, 1); //postfirxExp에 c복사
	else
		strncat(postfixExp, c, 1);//postfirxExp에 c추가
}


void toPostfix() //후위표시연산으로 바꾸는 함수
{
	
	char *exp = infixExp; /* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char x; //변수 x선언

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0') //exp가 NULL일때까지 반복
	{
		if(getPriority(*exp) == operand) //우선순위가 피연산자일때
		{
			x = *exp; //x에 exp저장
        	charCat(&x); //postfixExp에x추가
		}
        else if(getPriority(*exp) == lparen) { //우선순위가 lparen일때

        	postfixPush(*exp); //postfix 스택에 *exp 저장
        }
        else if(getPriority(*exp) == rparen) //우선순위가 rparen일때
        {
        	while((x = postfixPop()) != '(') { //postfix 스택에서 (일때까지 반복
        		charCat(&x);//postfixExp에 x추가
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))//postfix스택의 우선순위가 exp의 우선순위보다 같거나 클때
            {
            	x = postfixPop(); //x는 postfix스택에 저장된 값을 가져온다
            	charCat(&x);//postfixExp에 x추가
            }
            postfixPush(*exp); //postfix스택에 *exp를저장한다
        }
        exp++; //exp를 1 증가시킨다
	}

    while(postfixStackTop != -1) //postfix스택의 top이 -1일때까지 반복
    {
    	x = postfixPop(); //x에 postfix스택의 저장된값을 가져온다
    	charCat(&x); //postfixExp에 x추가 
    }

}

void debug() //debug하는 함수
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); //중위표시연산 출력
	printf("postExp =  %s\n", postfixExp); //후위표시연산 출력
	printf("eval result = %d\n", evalResult); //계산값 출력

	printf("postfixStack : "); 
	for(int i = 0; i < MAX_STACK_SIZE; i++) //반복문을 사용하여 후위표시연산 스택을 출력한다
		printf("%c  ", postfixStack[i]); 

	printf("\n");

}

void reset() //초기화 하는 함수
{
	infixExp[0] = '\0'; //infixExp[0]에 NULL저장
	postfixExp[0] = '\0'; //infixExp[0] NULL저장

	for(int i = 0; i < MAX_STACK_SIZE; i++) //반복문을 사용하여 postfix스택의 값을 NULL저장
		postfixStack[i] = '\0';
         
	postfixStackTop = -1; //postfix스택의 top에 -1 저장
	evalStackTop = -1; //evalStackTop에 -1 저장
	evalResult = 0; //evalResult에 0저장
}
void evaluation() //수식을 계산하는 함수
{
	int opr1, opr2, i; //opr1, opr2, i변수 선언

	int length = strlen(postfixExp); //length는 postfixExp의 길이를 저장
	char symbol; //symbol변수 선언
	evalStackTop = -1; //evalStacktop에 -1저장

	for(i = 0; i < length; i++) //postfixExp의 길이만큼 반복하는 반복문
	{
		symbol = postfixExp[i]; //symbol에 postfixExp[i]저장
		if(getToken(symbol) == operand) { //symbol이 피연산자일때
			evalPush(symbol - '0'); //eval스택에 symbol-'0'을하여 아스키코드값의 차이를 이용하여 정수로 바꾼후 evalstack에 저장
		}
		else {
			opr2 = evalPop(); //evalstack에 저장된 피연산자 저장
			opr1 = evalPop(); //evalstack에 저장된 피연산자 저장
			switch(symbol) { //토큰을 구하는 함수의 리턴값에 따라 실행
			case '+': evalPush(opr1 + opr2); break; //plus일때 opr1+opr2하여 evalstack에 저장
			case '-': evalPush(opr1 - opr2); break; //minus일때 opr1-opr2하여 evalstack에 저장
			case '*': evalPush(opr1 * opr2); break; //times일때 opr1*opr2하여 evalstack에 저장
			case '/': evalPush(opr1 / opr2); break; //divide일때 opr1/opr2하여 evalstack에 저장
			default: break;
			}
		}
	}
	evalResult = evalPop();//연산결과에 evalstack에 저장된 연산결과를 저장
}


#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack ������ �켱������ ��������, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 6,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 4,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE]; //����ǥ������� �����ϴ� �迭 ����
char postfixExp[MAX_EXPRESSION_SIZE]; //����ǥ������� �����ϴ� �迭 ����
char postfixStack[MAX_STACK_SIZE]; //����ǥ����Ľ����� �� ������ ��Ÿ�� �迭 ����
int evalStack[MAX_STACK_SIZE]; //������ ������ ��Ÿ�� �迭 ����

int postfixStackTop = -1; //����ǥ�� ������ top�� ���� �� -1�� �ʱ�ȭ
int evalStackTop = -1;  //�����ڽ����� top�� ���� �� -1�� �ʱ�ȭ

int evalResult = 0; 

void postfixPush(char x);  //postfixstack�� x�� �����ϴ� �Լ�
char postfixPop(); //postfixstack���� ����Ȱ��� �������� �Լ�
void evalPush(int x); //evalstack���� x�� �����ϴ� �Լ�
int evalPop(); //evalstack���� ����� ���� �������� �Լ�
void getInfix(); //����ڿ��� ����ǥ������� �Է¹޴� �Լ�
precedence getToken(char symbol); //token���� �� �з�
precedence getPriority(char x); //token�� �켱������ ����ϴ� �Լ�
void charCat(char* c);//c��infixexp�� �߰��ϴ� �Լ�
void toPostfix(); //infix�� postfix�� ��ȯ
void debug(); //debug�ϴ� �Լ�
void reset(); //���� �ʱ�ȭ �ϴ� �Լ�
void evaluation(); //����ϴ� �Լ�

int main()
{
	
    printf("[----- [�ڿ�����]  [2022041054] -----]\n"); 
	char command; //����ڿ��� command�� �Է¹޴� ����

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //����ڿ��� command�� �Է¹޴´�

		switch(command) {//command���� ���� ����
		case 'i': case 'I': //command�� i,I�϶�
			getInfix(); //getInfix�Լ� ȣ��
			break;
		case 'p': case 'P': //command�� p,P�϶�
			toPostfix(); //toPostfix�Լ� ȣ��
			break;
		case 'e': case 'E': //command�� e,E�϶�
			evaluation(); //evaluation�Լ� ȣ��
			break;
		case 'd': case 'D': //command�� d,D�϶�
			debug(); //debug�Լ� ȣ��
			break;
		case 'r': case 'R': //command�� r,R�϶�
			reset(); //reset�Լ� ȣ��
			break;
		case 'q': case 'Q': //command�� q,Q�϶�
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;


}

void postfixPush(char x) //����ǥ������� ���ÿ� �����ϴ� �Լ�
{
    postfixStack[++postfixStackTop] = x; //����ǥ�� �����ǽ��ÿ��� [top+1]�� x����
}

char postfixPop() //����ǥ������� ���ÿ��� ����� ���� �������� �Լ�
{
	char x; //���� x����
    if(postfixStackTop == -1) //top�� -1�϶�
        return '\0'; //�Լ�����
    else {
    	x = postfixStack[postfixStackTop--]; //x�� ����ǥ������� ���ÿ���[top-1]�� ����
    }
    return x;
}

void evalPush(int x)//���꽺�ÿ� �����ϴ� �Լ�
{
    evalStack[++evalStackTop] = x; //�����ڽ��ÿ��� [top+1]�� x����
}

int evalPop()//���꽺�ÿ��� ����� ���� �������� �Լ�
{
    if(evalStackTop == -1)//top�� -1�϶�
        return -1;//-1���� �����ϸ� �Լ�����
    else
        return evalStack[evalStackTop--]; //������ ����[top-1]�� ����
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */

void getInfix() //����ǥ�ü����� �Է¹޴� �Լ�
{
    printf("Type the expression >>> "); 
    scanf("%s",infixExp); //����ڿ��� ����ǥ�� ������ �Է¹޴´� 
}

precedence getToken(char symbol) //token�� �����ϴ� �Լ�
{
	switch(symbol) { //symbol�� �������� ���ϰ��� �޶�����
	case '(' : return lparen; 
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x) //�켱������ �����ϴ� �Լ�
{
	return getToken(x); //token(x)�� ȣ���Ͽ� �����Ѵ�
}


void charCat(char* c) //���ڸ� �Է¹޾� postfixExp�� �߰�
{
	if (postfixExp == '\0') //postfirxExp�� \0��??
		strncpy(postfixExp, c, 1); //postfirxExp�� c����
	else
		strncat(postfixExp, c, 1);//postfirxExp�� c�߰�
}


void toPostfix() //����ǥ�ÿ������� �ٲٴ� �Լ�
{
	
	char *exp = infixExp; /* infixExp�� ���� �ϳ����� �б����� ������ */
	char x; //���� x����

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0') //exp�� NULL�϶����� �ݺ�
	{
		if(getPriority(*exp) == operand) //�켱������ �ǿ������϶�
		{
			x = *exp; //x�� exp����
        	charCat(&x); //postfixExp��x�߰�
		}
        else if(getPriority(*exp) == lparen) { //�켱������ lparen�϶�

        	postfixPush(*exp); //postfix ���ÿ� *exp ����
        }
        else if(getPriority(*exp) == rparen) //�켱������ rparen�϶�
        {
        	while((x = postfixPop()) != '(') { //postfix ���ÿ��� (�϶����� �ݺ�
        		charCat(&x);//postfixExp�� x�߰�
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))//postfix������ �켱������ exp�� �켱�������� ���ų� Ŭ��
            {
            	x = postfixPop(); //x�� postfix���ÿ� ����� ���� �����´�
            	charCat(&x);//postfixExp�� x�߰�
            }
            postfixPush(*exp); //postfix���ÿ� *exp�������Ѵ�
        }
        exp++; //exp�� 1 ������Ų��
	}

    while(postfixStackTop != -1) //postfix������ top�� -1�϶����� �ݺ�
    {
    	x = postfixPop(); //x�� postfix������ ����Ȱ��� �����´�
    	charCat(&x); //postfixExp�� x�߰� 
    }

}

void debug() //debug�ϴ� �Լ�
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); //����ǥ�ÿ��� ���
	printf("postExp =  %s\n", postfixExp); //����ǥ�ÿ��� ���
	printf("eval result = %d\n", evalResult); //��갪 ���

	printf("postfixStack : "); 
	for(int i = 0; i < MAX_STACK_SIZE; i++) //�ݺ����� ����Ͽ� ����ǥ�ÿ��� ������ ����Ѵ�
		printf("%c  ", postfixStack[i]); 

	printf("\n");

}

void reset() //�ʱ�ȭ �ϴ� �Լ�
{
	infixExp[0] = '\0'; //infixExp[0]�� NULL����
	postfixExp[0] = '\0'; //infixExp[0] NULL����

	for(int i = 0; i < MAX_STACK_SIZE; i++) //�ݺ����� ����Ͽ� postfix������ ���� NULL����
		postfixStack[i] = '\0';
         
	postfixStackTop = -1; //postfix������ top�� -1 ����
	evalStackTop = -1; //evalStackTop�� -1 ����
	evalResult = 0; //evalResult�� 0����
}
void evaluation() //������ ����ϴ� �Լ�
{
	int opr1, opr2, i; //opr1, opr2, i���� ����

	int length = strlen(postfixExp); //length�� postfixExp�� ���̸� ����
	char symbol; //symbol���� ����
	evalStackTop = -1; //evalStacktop�� -1����

	for(i = 0; i < length; i++) //postfixExp�� ���̸�ŭ �ݺ��ϴ� �ݺ���
	{
		symbol = postfixExp[i]; //symbol�� postfixExp[i]����
		if(getToken(symbol) == operand) { //symbol�� �ǿ������϶�
			evalPush(symbol - '0'); //eval���ÿ� symbol-'0'���Ͽ� �ƽ�Ű�ڵ尪�� ���̸� �̿��Ͽ� ������ �ٲ��� evalstack�� ����
		}
		else {
			opr2 = evalPop(); //evalstack�� ����� �ǿ����� ����
			opr1 = evalPop(); //evalstack�� ����� �ǿ����� ����
			switch(symbol) { //��ū�� ���ϴ� �Լ��� ���ϰ��� ���� ����
			case '+': evalPush(opr1 + opr2); break; //plus�϶� opr1+opr2�Ͽ� evalstack�� ����
			case '-': evalPush(opr1 - opr2); break; //minus�϶� opr1-opr2�Ͽ� evalstack�� ����
			case '*': evalPush(opr1 * opr2); break; //times�϶� opr1*opr2�Ͽ� evalstack�� ����
			case '/': evalPush(opr1 / opr2); break; //divide�϶� opr1/opr2�Ͽ� evalstack�� ����
			default: break;
			}
		}
	}
	evalResult = evalPop();//�������� evalstack�� ����� �������� ����
}


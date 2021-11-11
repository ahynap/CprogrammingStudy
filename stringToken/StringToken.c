#include <stdio.h>
#include <string.h> //�Ѵ��â�ͤ���
#include <stdlib.h> //�ŧ���ʵ�ԧ����Ţ �ŧ�Ţ���ʵ�ԧ
#include <ctype.h> //�Ѵ��õ���ѡ�� 1 ���

void add_space(char *str)
{
    char buff[255] = "",j[255] ="";
    int i,max;
    for (i=0,max=strlen(str) ; i<max ; i++) //ǹ�ͺ�Ӷ֧��Ƿ�� '\0' ���͹����Դʵ�ԧ buff
    {
        if(strchr("+-*/^()",str[i]) != NULL) //��Ǩ�ͺ����յ�Ƿ����+-*/^() �������
            sprintf(buff,"%s %c ",j,str[i]); //����� ��������ä��ҧ˹����Т�ҧ��ѧ��ǹ��
        else
            sprintf(buff,"%s%c",j,str[i]); //�������� ����ͧ�����ä��
        strcpy(j,buff); //�Ѵ�͡ buff ��ѧ j ���͵�Ǩ�ͺ��ǶѴ�
    }
    strcpy(str,buff);//�Ѵ�͡ buff ��ѧ��µ����� str �����觤׹�ӵͺ
}

int string_segment(char word[][100],char *buff) //�ѧ���蹵Ѵʵ�ԧ���������������
{
    char *token;
    int count=0;
    token=strtok(buff," "); //�������¡ʵ�ԧ �����觤��á �����ͧ��ҧ�繵����
    while (token!=NULL) //���ʵ�ԧ�ѧ����������� loop ���
    {
        strcpy(word[count++],token); //�Ѵ�͡���������������
        token = strtok(NULL," "); //�觤ӵ���� �����ͧ��ҧ (\0) �繵����
    }
    return count; //�觤׹��� count
}

int is_function(char *token) //�ѧ�������º��º��Ң������������͹�ѹ������� �����ҿѧ���蹵��⡳�Ե�
{
    int i;
    char fname[11][10] = {"sin","cos","tan","asin","acos","atan","sqrt","pow","log","exp","abs"}; //�ͧ������ 11 ��� ���������Թ 10 ����ѡ�� ����Ѻ�线ѧ���蹵��⡳
    for(i=0; i<10; i++)
    {
        if(strcmp(fname[i],token)==0) //������ strcmp ���º��º������ 2 �ش ��� fname ��� token
            return 1; //��� fname ����͹�Ѻ token �ء��� (strcmp(fname[i],token)==0) ��� return 1
    }
    return 0; //����������͹��� return 0
}

int is_operator(char *token) //���ҧ�ѧ���蹵�Ǩ�ͺ����� operator ������� �����º��º��Ң������������͹�ѹ�������
{
    int i;
    char fname[8][7] = {"+", "-", "*", "/", "^", "(", ")" }; //�ͧ������ 8 ��� ���������Թ 7 ����ѡ�� ����Ѻ�� operator
    for(i=0; i<7; i++)
    {
        if(strcmp(fname[i],token)==0) //������ strcmp ���º��º������ 2 �ش ��� fname ��� token
            return 1; //��� fname ����͹�Ѻ token �ء��� (strcmp(fname[i],token)==0) ��� return
    }
    return 0; //����������͹��� return 0
}

int is_number (char *token) //���ҧ�ѧ���蹵�Ǩ�ͺ����繵���Ţ������� �µ�Ǩ�ͺ���¨ش�ȹ���
{
    int i,dot_count=0;
    for(i=0; i<strlen(token); i++)
    {
        if(isdigit(token[i])==0 && token[i]!= '.') //��Ǩ�ͺ��Ң�鹵鹴��µ���Ţ���ͨش�������
            return 0; //�������繵���Ţ��������ش ��� return 0
        if(token[i]=='.')
            dot_count++; //����ͨش ������� dot_count ������� 1
    }
    if(dot_count>1)
        return 0; //��� dot_count �ҡ���� 1 ��� return 0
    else
        return 1; //��� dot_count ���¡�����ҡѺ 1 ��� return 1
}

int is_iden(char *token) //���ҧ�ѧ���蹵�Ǩ�ͺ����� identifier ������� �����º��º��Ң������������͹�ѹ�������
{
    int i;
    if(isdigit(token[0]))
        return 0; //����յ���Ţ� index �á ��� return 0
    for(i=0; i<strlen(token); i++)
    {
        if(isalpha(token[i]) == 0 && token[i] != '_' && isdigit(token[i])== 0) //��Ǩ�ͺ��Ң�鹵鹴��µ���Ţ ��� ��鹵鹴��� _ ������� ��� ��鹵鹴����ѡ����������
            return 0; //����� ��� return 0
    }
    return 1; //����������� return 1
}

int main ()
{
    char str[100],buff[100],token[100][100];
    int i,len,count,mean[5][100],type;
    do
    {
        int count_mean[5] = {0,0,0,0,0}; //��˹���� count_mean �� 0 ������
        printf("enter your data : ");
        gets(str); //get string
        strcpy(buff,str); //�Ѵ�͡ str ��ѧ��µ����� buff
        strlwr(buff); //�ŧ����繵�Ǿ�������
        add_space(buff); //���������ä

        printf("your string is : %s",buff); //�ʴ���ʵ�ԧ�������¹�繵�Ǿ�����������������ä���Ƿ�����

        count = string_segment(token,buff); //�Ѻ�ӹǹ�ӷ���Ѻ�ҡ user
        if(count == 1) //������� 1 ��
        {
            if(strcmp(token,"end")==0||strcmp(token,"exit")==0) //����Ǩ�ͺ���������� end ���� exit ���������
            {
                printf("\t\nend program"); //����� ����ʴ����Ҩ������
                return 0; //�������
            }
        }

        printf("\ncount data : %d \n\n",count); //�ʴ���� count

        for(i=0; i<count; i++)
        {
            if(is_number(token[i]) == 1) //��Ǩ�ͺ��Ҥ�ҷ���Ѻ�ҡ������� number ���������
            {
                mean[0][count_mean[0]++] = i;
                type = 0;   //����� number ����դ����ҡѺ type 0
            }
            else if(is_operator(token[i]) == 1) //�������� ���Ǩ�ͺ������ ��ҷ���Ѻ�ҡ������� operator ���������
            {
                mean[1][count_mean[1]++] = i;
                type = 1;   //����� operator ����դ����ҡѺ type 1
            }
            else if(is_function(token[i]) == 1) //�������� ���Ǩ�ͺ������ ��ҷ���Ѻ�ҡ������� function ���������
            {
                mean[2][count_mean[2]++] = i;
                type = 2;  //����� function ����դ����ҡѺ type 2
            }
            else if(is_iden(token[i]) == 1) //�������� ���Ǩ�ͺ������ ��ҷ���Ѻ�ҡ������� identifier ���������
            {
                mean[3][count_mean[3]++] = i;
                type = 3;  //����� identifier ����դ����ҡѺ type 3
            }
            else //�����������Ţ operator �ѧ���� ���� identifier
            {
                mean[4][count_mean[4]++] = i;
                type = 4; //����դ����ҡѺ type 4
            }
            printf("\t%s is ",token[i]); //�ʴ���� index �ͧ��������

            if(type == 0) //����� type 0
                printf("a number.\n"); //�ʴ�������繵���Ţ
            else if(type == 1) //����� type 1
                printf("an operator.\n"); //�ʴ�������� operator
            else if(type == 2) //����� type 2
                printf("a function.\n");  //�ʴ�������� function
            else if(type == 3) //����� type 3
                printf("an identifier.\n"); //�ʴ�������� identifier
            else if(type == 4) //����� type 4
                printf("an error.\n"); //�ʴ�������� error
        }

        printf("\nyou have %d numbers, that is : ",count_mean[0]); //�ʴ�������� number ����� �������ú�ҧ
        i =0;
        while(i<count_mean[0])
        {
            printf("%s ",token[mean[0][i]]);
            i++;
        }

        printf("\nyou have %d operators, that is : ",count_mean[1]); //�ʴ�������� �perator ����� �������ú�ҧ
        i=0;
        while(i<count_mean[1])
        {
            printf("%s ",token[mean[1][i]]);
            i++;
        }

        printf("\nyou have %d functions, that is : ",count_mean[2]); //�ʴ�������� function ����� �������ú�ҧ
        i=0;
        while(i<count_mean[2])
        {
            printf("%s ",token[mean[2][i]]);
            i++;
        }

        printf("\nyou have %d identifier, that is : ",count_mean[3]); //�ʴ�������� identifier ����� �������ú�ҧ
        i=0;
        while(i<count_mean[3])
        {
            printf("%s ",token[mean[3][i]]);
            i++;
        }

        printf("\nyou have %d errors, that is : ",count_mean[4]); //�ʴ�������� error ����� �������ú�ҧ
        i=0;
        while(i<count_mean[4])
        {
            printf("%s ",token[mean[4][i]]);
            i++;
        }
        printf("\n\n");
        system("pause");
        system("cls"); //clear screen
    } while (1); //�ӫ�Ө����� user �����͡�������
}

#include<stdio.h>
#include <time.h>

int fibonacci(int n)
{
    int f_at_n;
    if (n==0)
    {
        f_at_n = 0;
    }
    else if (n==1||n==2)
    {
        f_at_n = 1;
    }
    else
        f_at_n = fibonacci(n-2)+fibonacci(n-1);
    return f_at_n;
}

int factorial(int n)
{
    int f_at_n;
    if (n==0)
    {
        f_at_n = 1;
    }
    else
        f_at_n = n*factorial(n-1);
    return f_at_n;
}

int GCD(int n1,int n2)
{
    int denominator;
    if(n1<n2)
    {
        denominator = n1;
    }
    else
        denominator = n2;

    while(n1%denominator!=0 || n2%denominator!=0)
    {
        denominator = denominator-1;
    }
    return denominator;
}

int guessnumber(int n)
{
    int x,count;
    srand(time(NULL));
    x = (int)rand() %100 +1;
    count = 0;

    do
    {
        count = count+1;
        printf("\n\t\t\tenter the number that you guess : ");
        n = get_int(0,100);
        if (x==n)
        {
            printf("\n\t\t\t   CORRECT! YOU ARE THE WINNER :]\n");
        }
        else if(x>n)
        {
            printf("\t\tWRONG! your number is LESS THAN answer. try again.");
        }
        else
        {
            printf("\t\tWRONG! your number is MORE THAN answer. try again.");
        }

        if(x!=n)
        {
            printf("\n\t\t\t     ** NOW YOU HAVE %d CHANCE **\n\n",7-count);
        }
    }
    while(count<6 && x!=n);

    if(count>=6 && x!=n)
    {
        printf("\n\t\t\tenter the number that you guess : ");
        n = get_int(0,100);
        if (x==n)
        {
            printf("\n\t\t\t   CORRECT! YOU ARE THE WINNER :]\n");
        }
        else if (x!=n)
        {
            printf("\n\t\t\t\tYOU'RE LOSE NOW :[\n\t\t\t\t(%d is in my mind)\n",x);
        }
    }
    return 0;
}

int get_int(int min,int max)
{
    int userinput;

    while((scanf("%d",&userinput)==0)||(userinput<min)||(userinput>max))
    {
        rewind(stdin);
        printf("\tyour number isn't between %d and %d. please try again.\n",min,max);
        printf("\tenter your number again : ");
    }
    return userinput;
}

int get_manu()
{
    int select;
    select = get_int(0,4);
    return select;
}

int main()
{
    int select,answer,n,r,combination;

    printf("\n\n\t\t\t _______________________________");
    printf("\n\t\t\t|                               |");
    printf("\n\t\t\t| RECURSIVE FUNCTION CALCULATOR |");
    printf("\n\t\t\t|_______________________________|");

    printf("\n\n\n\tattention : this program is a recursive function calculator program.");
    printf("\n\t\t    so you should to get the menu for start this program.");
    printf("\n\n\t\t\tenter 1 : calculate fibonacci");
    printf("\n\t\t\tenter 2 : calculate combinaton");
    printf("\n\t\t\tenter 3 : calculate GCD(x,y)");
    printf("\n\t\t\tenter 4 : guess number game");
    printf("\n\t\t\tenter 0 : exit");
    printf("\n\n\t--------------------------------------------------------------------");

    do
    {
        printf("\n\n\twhat do you want to calculate? : ");
        select = get_manu();
        rewind(stdin);
        if (select==1)
        {
            printf("\n\n\t\t\t\tWELCOME TO FIBONACCI\n");
            printf("\t\t\t\t____________________\n");
            printf("\n\t\t\tenter number between 0-45 : ");
            n = get_int(0,45);
            rewind(stdin);
            answer = fibonacci(n);
            printf("\n\t\t\t-> finonacci of %d is %d\n",n,answer);
            printf("\t\t\t\t____________________\n\n\n");
        }
        else if (select==2)
        {
            printf("\n\n\t\t\t\tWELCOME TO COMINATION\n");
            printf("\t\t\t\t_____________________\n");
            printf("\n\t\t\tenter 1st number between 0-15 : ");
            n = get_int(0,15);
            printf("\n\t\tenter 2nd number between 0-15 and less than 1st number : ");
            r = get_int(0,n);
            combination = factorial(n)/(factorial(n-r)*factorial(r));
            printf("\n\t\t\t-> combination of %d and %d is %d\n",n,r,combination);
            printf("\t\t\t\t____________________\n\n\n");
        }
        else if(select==3)
        {
            printf("\n\n\t\t\t\tWELCOME TO GCD(x,y)\n");
            printf("\t\t\t\t___________________\n");
            printf("\n\t\t\t    enter your 1st number : ");
            n = get_int(0,10000);
            printf("\n\t\t\t    enter your 2nd number : ");
            r = get_int(0,10000);
            printf("\n\t\t\t     -> gcd of %d and %d is %d\n",n,r,GCD(n,r));
            printf("\t\t\t\t___________________\n\n\n");
        }
        else if (select==4)
        {
            printf("\n\n\t\t\t    WELCOME TO GUESS NUMBER GAME\n");
            printf("\t\t\t    ____________________________\n");
            printf(guessnumber(n));
            printf("\t\t\t    ____________________________\n\n\n");
        }
    }
    while (select!=0);
    printf("\n\n\t\t\t\t    END PROGRAM\n");
    printf("\t\t\t\t    ___________\n");
    return 0;

}

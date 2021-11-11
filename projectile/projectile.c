#include <stdio.h>
#include <math.h>
int main ()
{
    double U,angle,x,radian,Ux,Uy,Sy,Sx,t,Tx,Hx,distance,input;
    double g = (-9.81),pi = acos(-1);
    char charac;
    do
    {
        printf("\n\t///////////////////////////////////////////////////////////////");
        printf("\n\n\n\t\t\tWELCOME TO PROJECTILE CALCULATOR");

        printf("\n\n\n# please key your football information\n");

        printf("\n   - velocity : ");
        input = scanf("%lf",&U);
        rewind(stdin);
        while (input==0)
        {
            printf("\tOH! YOUR NUMBER DOESN'T MEET THE CONDITIONS, KEY AGAIN : ");
            input = scanf("%d",&U);
            rewind(stdin);
        }


        printf("   - angle (in degree) : ");
        input = scanf("%lf",&angle);
        rewind(stdin);
        while (input==0)
        {
            printf("\tOH! YOUR NUMBER DOESN'T MEET THE CONDITIONS, KEY AGAIN : ");
            input = scanf("%d",&angle);
            rewind(stdin);
        }


        printf("   - distance form start point to goal : ");
        input = scanf("%lf",&x);
        rewind(stdin);
        while (input==0)
        {
            printf("\tOH! YOUR NUMBER DOESN'T MEET THE CONDITIONS, KEY AGAIN : ");
            input = scanf("%lf",&x);
            rewind(stdin);
        }

        radian = angle*(pi/180);
        Uy = U*sin(radian);
        Ux = U*cos(radian);
        //สูงสุดเท่าไหร่
        Sy = (Uy*Uy)/((-2)*g);
        //อยู่ในอากาศได้นานเท่าไหร่
        t = ((-2)*Uy)/g;
        //ไกลสุดเท่าไหร่
        Sx = Ux*t;
        //goal
        //เวลาเมื่อถึงจุด x
        Tx = x/Ux;
        //ที่จุด x บอลจะสูง
        Hx = (Uy*Tx)+(0.5*g*Tx*Tx);

        printf("\n    _______________________________________________________________________");
        printf("\n   |                                                                       |");
        printf("\n   |                                                                       |\n   |\t\t THIS'S YOUR BALL'S GENERAL INFORMATION :) \t\t   |");
        printf("\n   |\t\t ----------------------------------------- \t\t   |");
        printf("\n   |                                                                       |");
        printf("\n   |\t   > maximum hight before fall = %.2lf m. \t\t\t   |",Sy);
        printf("\n   |\t   > maximum distance before fall = %.2lf m. \t\t\t   |",Sx);
        printf("\n   |\t   > maximum time when the ball is in the air = %.2lf sec. \t   |",t);

        if (Sx<x)
        {
            distance = x-Sx;
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |\n   |\t\t    AT GOAL POINT YOUR BALL WILL... :) \t\t\t   |");
            printf("\n   |\t\t    ---------------------------------- \t\t\t   |");
            printf("\n   |\t   > %.2lf meters away from the goal \t\t\t   \t   |",distance);
            printf("\n   |\t   > the ball is in the air for %.2lf sec. \t\t\t   |",t);
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n   |   \t\t\t\t\t    |\\ \t\t\t\t   |");
            printf("\n   |   \t\t\t\t\t    | \\ \t\t\t   |");
            printf("\n   |   \t\t    ___________________o____|__\\_____ \t\t\t   |");
            printf("\n   |                                                                       |");
            printf("\n   |\t\t\tthe ball fall BEFORE GOAL ! \t\t\t   |");
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n    _______________________________________________________________________");

        }
        else if (Tx>0.5)
        {
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |\n   |\t\t    AT GOAL POINT YOUR BALL WILL... :) \t\t\t   |");
            printf("\n   |\t\t    ---------------------------------- \t\t\t   |");
            printf("\n   |\t   > hight %.2lf meters from ground \t\t\t   \t   |",Hx);
            printf("\n   |\t   > the ball is in the air for %.2lf sec. \t\t\t   |",Tx);
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n   |   \t\t\t\t\t    |\\ \t\t\t\t   |");
            printf("\n   |   \t\t\t\t\t   O| \\ \t\t\t   |");
            printf("\n   |   \t\t    ______________________oi|__\\_____ \t\t\t   |");
            printf("\n   |                                                                       |");
            printf("\n   |\t\t\t\t  CAN SAVE ! \t\t\t\t   |");
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n    _______________________________________________________________________");

        }
        else if (Hx>=2.44)
        {
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |\n   |\t\t    AT GOAL POINT YOUR BALL WILL... :) \t\t\t   |");
            printf("\n   |\t\t    ---------------------------------- \t\t\t   |");
            printf("\n   |\t   > hight %.2lf meters from ground \t\t\t   \t   |",Hx);
            printf("\n   |\t   > the ball is in the air for %.2lf sec. \t\t\t   |",Tx);
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n   |   \t\t\t\t\t     O \t\t\t\t   |");
            printf("\n   |   \t\t\t\t\t    |\\ \t\t\t\t   |");
            printf("\n   |   \t\t\t\t\t    | \\ \t\t\t   |");
            printf("\n   |   \t\t    ________________________|__\\_____ \t\t\t   |");
            printf("\n   |                                                                       |");
            printf("\n   |\t\t\t     OVER THE GOAL ! \t\t\t\t   |");
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n    _______________________________________________________________________");
        }
        else
        {
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |\n   |\t\t    AT GOAL POINT YOUR BALL WILL... :) \t\t\t   |");
            printf("\n   |\t\t    ---------------------------------- \t\t\t   |");
            printf("\n   |\t   > hight %.2lf meters from ground \t\t\t   \t   |",Hx);
            printf("\n   |\t   > the ball is in the air for %.2lf sec. \t\t\t   |",Tx);
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n   |   \t\t\t\t\t    |\\ \t\t\t\t   |");
            printf("\n   |   \t\t\t\t\t    | \\ \t\t\t   |");
            printf("\n   |   \t\t    ________________________|O_\\_____ \t\t\t   |");
            printf("\n   |                                                                       |");
            printf("\n   |\t\t\t     !!!!! GOAL !!!!! \t\t\t\t   |");
            printf("\n   |                                                                       |");
            printf("\n   |                                                                       |");
            printf("\n    _______________________________________________________________________");
        }

        printf("\n\n\n\n\n\tattention ; If you want to use this program again please enter y.\n");
        printf("\t but if you don't need to use, you can enter anything except y. \n");


        printf("\n\n\t\t\tDO YOU WANT TO CALCULATE AGAIN? : ");
        scanf("%c",&charac);
        rewind(stdin);
    }
    while(charac=='y');
    printf("\n\n\t\t\t\t  END GAME :)\n\n");
    printf("\n\t///////////////////////////////////////////////////////////////\n\n");


    return 0;



}

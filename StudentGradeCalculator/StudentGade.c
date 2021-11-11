#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct grade_info //ประกาศโครงสร้างข้อมูลประเภท structure เพื่อนำไปใช้จองตัวแปร
{
    long long id ;
    char name[40] ;
    double mid, final, atten, total, gpoint ;
    char grade[3] ;
}  gradetype; //กำหนดชื่อใหม่ให้กับ struct grade_info

void load_student_file (gradetype st[], int *stcount)
{
    FILE *fp; //จองตัวแปรเพื่อใช้เป็นไฟล์
    gradetype x; //จองตัวแปรเพื่ออ่านข้อมูล 1 ตัว
    if ((fp = fopen("score.csv", "r")) != NULL ) //ตรวจสอบการเปิดไฟล์
    {
        *stcount=0; //กำหนดค่าเริ่มตัวนับจำนวนข้อมูล
        while (fscanf(fp,"%llu ,%[^,] ,%lf ,%lf ,%lf", &x.id, x.name, &x.mid,&x.final,&x.atten)==5)
        {
            x.total = x.mid+x.final+x.atten;//คำนวณคะแนนรวม
            st[*stcount] = x; //นำข้อมูล x ที่อ่านได้ไปเก็บใน st
            *stcount = *stcount+1; //นับเพิ่มจำนวนข้อมูลที่อ่านได้
        }
        fclose(fp); //ปิดไฟล์
        printf("\nTotal read %d records. \n",*stcount); //แสดงจำนวนข้อมูลทั้งหมด
    }
    else
        printf("\nError Can't Read File score.csv\n"); //แสดงว่าไม่สามารถอ่านไฟล์ได้
}

void Find_Statistic (gradetype st[], int stcount, double *min, double *max, double *mean, double *sd,double *avg) //ฟังก์ชั่นคำนวณหาค่าทางสถิติ
{
    int i;
    double sum=0, sumsqr=0;
    *min = *max = st[0].total ;
    for (i=0; i<stcount; i++)
    {
        avg[0]+=st[i].mid; //ผลรวมของคะแนน mid
        avg[1]+=st[i].final; //ผลรวมของคะแนน final
        avg[2]+=st[i].atten; //ผลรวมของคะแนน atten
        if (st[i].total < *min) //ตรวจสอบหาคะแนนรวมต่ำสุด
            *min = st[i].total;
        if (st[i].total > *max) //ตรวจสอบหาคะแนนรวมสูงสุด
            *max = st[i].total;
        sum = sum+st[i].total; //หาค่าผลรวมคะแนนทั้งหมด
        sumsqr = sumsqr + pow(st[i].total,2); //ใช้หาค่า sd
    }
    avg[0]=avg[0]/stcount; //หาค่าเฉลี่ยของคะแนน  mid
    avg[1]=avg[1]/stcount; //หาค่าเฉลี่ยของคะแนน  final
    avg[2]=avg[2]/stcount; //หาค่าเฉลี่ยของคะแนน  atten
    *mean = sum/stcount; //หาค่า mean
    *sd = sqrt(sumsqr/stcount - pow(*mean, 2)); //หาค่า sd
}

void Grade_setting(gradetype st[], int stcount, double a, double bp, double b, double cp, double c, double dp, double d) //ฟังก์ชั่นกำหนดตัดเกรด
{
    int i,countg[8]= {0,0,0,0,0,0,0,0} ;
    double gpa = 0;
    for (i=0; i<stcount; i++)
    {
        if (st[i].total >=a) //ถ้าผลรวมคะแนนมากกว่าหรือเท่ากับค่าของ a (ที่ผู้ใช้กำหนด เพื่อตัดเกรด A)
        {
            strcpy(st[i].grade,"A"); //ให้ได้เกรด A
            st[i].gpoint=4.0; //ให้ gpa = 4.00
            countg[0]++; //นับจำนวนคนที่ได้เกรด A
        }
        else if (st [i].total >=bp) //ถ้าผลรวมคะแนนมากกว่าหรือเท่ากับค่าของ bp (ที่ผู้ใช้กำหนด เพื่อตัดเกรด B+)
        {
            strcpy(st[i].grade,"B+"); //ให้ได้เกรด B+
            st[i].gpoint=3.5; //ให้ gpa = 3.50
            countg[1]++; //นับจำนวนคนที่ได้เกรด B+
        }
        else if (st[i].total >=b) //ถ้าผลรวมคะแนนมากกว่าหรือเท่ากับค่าของ b (ที่ผู้ใช้กำหนด เพื่อตัดเกรด B)
        {
            strcpy(st[i].grade,"B"); //ให้ได้เกรด B
            st[i].gpoint=3.0; //ให้ gpa = 3.00
            countg[2]++; //นับจำนวนคนที่ได้เกรด B
        }
        else if (st[i].total >=cp) //ถ้าผลรวมคะแนนมากกว่าหรือเท่ากับค่าของ cp (ที่ผู้ใช้กำหนด เพื่อตัดเกรด C+)
        {
            strcpy(st[i].grade,"C+"); //ให้ได้เกรด C+
            st[i].gpoint=2.5; //ให้ gpa = 2.50
            countg[3]++; //นับจำนวนคนที่ได้เกรด C+
        }
        else if (st[i].total >=c) //ถ้าผลรวมคะแนนมากกว่าหรือเท่ากับค่าของ c (ที่ผู้ใช้กำหนด เพื่อตัดเกรด C)
        {
            strcpy(st[i].grade,"C"); //ให้ได้เกรด C
            st[i].gpoint=2.0; //ให้ gpa = 2.00
            countg[4]++; //นับจำนวนคนที่ได้เกรด C
        }
        else if (st[i].total >=dp) //ถ้าผลรวมคะแนนมากกว่าหรือเท่ากับค่าของ dp (ที่ผู้ใช้กำหนด เพื่อตัดเกรด D+)
        {
            strcpy(st[i].grade,"D+"); //ให้ได้เกรด D+
            st[i].gpoint=1.5; //ให้ gpa = 1.50
            countg[5]++; //นับจำนวนคนที่ได้เกรด D+
        }
        else if (st[i].total >=d) //ถ้าผลรวมคะแนนมากกว่าหรือเท่ากับค่าของ d (ที่ผู้ใช้กำหนด เพื่อตัดเกรด D)
        {
            strcpy(st[i].grade,"D"); //ให้ได้เกรด D
            st[i].gpoint=1.0; //ให้ gpa = 1.00
            countg[6]++; //นับจำนวนคนที่ได้เกรด D
        }
        else //ถ้าหากไม่เข้าเงื่อนไขใดเลย
        {
            strcpy(st[i].grade,"F") ; //ให้ตัดเกรด F
            st[i].gpoint=0; //ให้ gpa = 0.00
            countg[7]++; //นับจำนวนคนที่ได้เกรด F
        }
    }

    printf("\n grade");
    printf("\n  -----------------------------------------------\n");
    printf(" | %2s %2s %2s %2s %2s %2s %2s %2s %2s %2s %2s %2s %2s %2s %2s %2s\n","A","|","B+","|","B","|","C+","|","C","|","D+","|","D","|","F","|");
    printf(" |------------------------------------------------\n");
    printf(" | %2d %2s %2d %2s %2d %2s %2d %2s %2d %2s %2d %2s %2d %2s %2d %2s",countg[0],"|",countg[1],"|",countg[2],"|",countg[3],"|",countg[4],"|",countg[5],"|",countg[6],"|",countg[7],"|");
    printf("\n  -----------------------------------------------"); //แสดงผลคะแนน

    for(i=0; i<stcount; i++)
    {
        gpa += st[i].gpoint; //หาผลรวมของ gpa ทั้งหมด
    }
    printf("\n GPA = %.2lf\n",(gpa/stcount)); //แสดงค่าเฉลี่ยของ gpa
}

void print_data(gradetype x) //ฟังก์ชั่นแสดงข้อมูล 1 คน ออกทางจอภาพ
{
    printf("%llu  %-30s %5.1lf  %5.1lf  %5.1lf  %5.1lf   %-2s %5.1lf\n", x.id, x.name,x.mid, x.final,x.atten, x.total, x.grade,x.gpoint);
}

void Search_Name (gradetype st[], int stcount) //ฟังก์ชั่นสำหรับหาข้อมูลจากการกรอกชื่อ
{
    char key[16]; //กำหนดสตริงชื่อ key ขนาด 16
    int i, count;
    do
    {
        printf("\n Enter Search key (0 = Exit) : ");
        scanf("%15s", key); //อ่านสตริงความยาวไม่เกิน 15 อักขระ
        strupr(key); //ทำให้ทุกตัวเป็นตัวพิมพ์ใหญ่
        count = 0;
        if (strcmp(key,"0") != 0) //ถ้าผู้ใช้ไม่ได้กรอก 0
            for (i = 0; i<stcount; i++)
                if (strstr(st[i].name, key) != NULL) //ตรวจสอบว่าตัวอักษรใดในข้อมูลที่ตรงกับตัวอักษรที่ผู้ใช้กรอก
                {
                    count = count + 1;
                    printf("%-2d . ",count);
                    print_data(st[i]); //แสดงผลข้อมูลที่เหมือนกับที่ผู้ใช้กรอก
                }
    }
    while (strcmp(key,"0")!=0);
}

void Search_Score (gradetype st[], int stcount) //ฟังก์ชั่นสำหรับหาข้อมูลจากการกรอกช่วงคะแนน
{
    double min, max;
    int i, count;
    char ch ;
    do
    {
        printf("Enter score range (min-max) : ");
        scanf("%lf-%lf", &min, &max); //รับค่าช่วงคะแนนสูงงต่ำจากผู้ใช้
        count = 0;
        for (i = 0; i<stcount; i++)
        {
            if (st[i].total >= min && st[i].total <= max) //เปรียบเทียบคะแนนทั้งหมดกับค่าสูงต่ำที่ผู้ใช้กรอก
            {
                count = count + 1;
                printf("%-2d . ",count);
                print_data(st[i]); //แสดงข้อมูลที่อยู่ในช่วงที่ผู้ใช้กรอก
            }
        }
        printf("\n\n Enter \"y\" to search again or \"n\" to exit : \n"); //ให้ผู้ใช้เลือกกรอกต่อหรือออกจากส่วนนี้
        ch = getch();
    }
    while (ch == 'y'); //ทำการถามซ้ำจนกว่าผู้ใช้จะเลือกออก n
}

void Sort_by_total (gradetype st[], int stcount) //ฟังก์ชั่นเรียงคะแนน
{
    int i, j ;
    gradetype x;
    for (i = 0; i < stcount-1; i++) //ให้ i แทน index เดิม
        for (j = i+1; j < stcount; j++) //ให้ j แทน index ถัดไป
            if (st[j].total > st[i].total) //ถ้าข้อมูล j มากกว่า i
            {
                x = st[i]; //สลับข้อมูล ให้ j อยู่ก่อน i
                st[i] = st[j];
                st[j] = x;
            }
}

void Sort_by_id (gradetype st[], int stcount) //ฟังก์ชั่นเรียงตามเลขประจำตัว
{
    int i, j ;
    gradetype x;
    for (i = 0; i < stcount-1; i++) //ให้ i แทน index เดิม
        for (j = i+1; j < stcount; j++) //ให้ j แทน index ถัดไป
            if (st[j].id < st[i].id) //ถ้าข้อมูล j น้อยกว่า i
            {
                x = st[i]; //สลับข้อมูล ให้ i อยู่ก่อน j
                st[i] = st[j];
                st[j] = x;
            }
}

void Search_Grade (gradetype st[], int stcount) //ฟังก์ชั่นเรียงตามเกรด
{
    char key[3];
    int i, count ;
    do
    {
        printf("\n Enter grade (A-F) that you want to know or enter 0 for exit : ");
        scanf("%2s", key); //รับค่าข้อมูลเกรดที่ผู้ใช้ต้องการทราบ อ่ารนสตริงไม่เกิน 2 ตัวอักษร
        strupr(key); //ทำให้เป็นตัวพิมพ์ใหญ่
        count = 0;
        if (strcmp(key,"0") != 0)
            for (i = 0; i<stcount; i++)
            {
                if (strcmp(st[i].grade,key)==0) //เปรียบเทียบข้อมูลที่รับกับเกรดในข้อมูล
                {
                    count = count + 1;
                    printf("%-2d . ",count);
                    print_data(st[i]);
                }
            }
    }
    while (strcmp(key, "0") !=0);
}

void Show_All_Data (gradetype st[], int stcount) //ฟังก์ชั่นแสดงข้อมูลทั้งหมด
{
    int i,count=0;
    printf("%-4s %-11s  %-30s  %-4s   %-4s  %-4s %-4s %-4s %-4s\n","No.","ID","Name","mid","final","attend","total","grade","gpoint");
    for (i = 0; i<stcount; i++)
    {
        count = count + 1;
        printf("%-2d . ",count);
        print_data(st[i]); //แสดงข้อมูลทั้งหมด
    }
}

int get_int(int min, int max) //สร้างฟังก์ชั่นเพื่อกำหนดขอบเขต min max ที่รับจากผู้ใช้
{
    int num;
    char ch;
    while((scanf("%d%c",&num,&ch)!=2)||ch !='\n'|| num<min ||num>max)
    {
        rewind(stdin);
        printf("Error, please enter between %d - %d : ",min,max); //ถ้าผู้ใช้กรอกข้อมูบเกิน max min ที่กำหนดให้ขึ้นว่า error
    }
    return num;
}

int get_menu() //ฟังก์ชั่นสำหรับเลือกเมนู
{
    int select;
    printf("\n\n\n\t- Enter your menu : ");
    select = get_int(0,9); //กำหนดให้มี 10 เมนู คือ เมนูที่ 0-9
    return select;
}

int main()
{
    struct grade_info x,st[100] ;
    int select,stcount,a,bp,b,cp,c,dp,d,countload=0,grade=0;
    double min,max,mean,sd,avg[3];

    printf("\n\t\t _______________");
    printf("\n\t\t|               |");
    printf("\n\t\t| STUDENT GRADE |");
    printf("\n\t\t|_______________|");

    printf("\nTHE MANU IS ; \n");
    printf(" 1. read file\n");
    printf(" 2. grade\n");
    printf(" 3. statistic\n");
    printf(" 4. show all student's data\n");
    printf(" 5. show from hight to low\n");
    printf(" 6. show from student ID\n");
    printf(" 7. show from score range\n");
    printf(" 8. show only grade that you want\n");
    printf(" 9. show form name\n");
    printf(" 0. exit\n");
    printf(" _______________________________________________\n"); //แสดงวิธีการใช้โปรแกรม

    do
    {
        select = get_menu(); //รับค่าเมนูจากผู้ใช้
        rewind(stdin);

        if(select == 1) //ถ้าผู้ใช้เลือกเมนูที่ 1
        {
            load_student_file(st,&stcount); //เรียกใช้ฟังก์ชั่น load_student_file เพื่ออ่านข้อมูล
            countload = 1; //ให้ countload เท่ากับ 1 แทนการแสดงว่าโหลดไฟล์แล้ว
        }

        if(countload==0) //ถ้าผู้ใช้ยังไม่ได้เลือกเมนูที่ 1 (ยังไม่โหลดไฟล์)
        {
            printf("\nError! please load file\n"); //ให้แสดงผลว่า error ยังไม่ได้โหลดไฟล์
        }
        else
        {
            if(select == 2) //ถ้าผู้ใช้เลือกเมนูที่ 2
            {
                avg[0]=0;
                avg[1]=0;
                avg[2]=0;
                printf("\nEnter score for A  : ");
                scanf("%d",&a); //รับคะแนนที่จะใช้ตัด A จากผู้ใช้
                printf("Enter score for B+ : ");
                scanf("%d",&bp); //รับคะแนนที่จะใช้ตัด B+ จากผู้ใช้
                printf("Enter score for B  : ");
                scanf("%d",&b); //รับคะแนนที่จะใช้ตัด B จากผู้ใช้
                printf("Enter score for C+ : ");
                scanf("%d",&cp); //รับคะแนนที่จะใช้ตัด C+ จากผู้ใช้
                printf("Enter score for C  : ");
                scanf("%d",&c); //รับคะแนนที่จะใช้ตัด C จากผู้ใช้
                printf("Enter score for D+ : ");
                scanf("%d",&dp); //รับคะแนนที่จะใช้ตัด D+ จากผู้ใช้
                printf("Enter score for D  : ");
                scanf("%d",&d); //รับคะแนนที่จะใช้ตัด D จากผู้ใช้

                Find_Statistic(st,stcount,&min,&max,&mean,&sd,avg); //เรีกช้ฟังก์ชั่น Find_Statistic เพื่อคำนวณคะแนน
                printf("\n total");
                printf("\n  ---------------------------------------------\n");
                printf(" |%5s%3s%8s%6s%9s%5s%5s%5s\n","min","|","max","|","mean","|","SD","|");
                printf(" |---------------------------------------------|\n");
                printf(" | %.2lf%2s%9.2lf%5s%9.2lf%5s%7.2lf%3s",min,"|",max,"|",mean,"|",sd,"|");
                printf("\n |---------------------------------------------|"); //แสดงผล total เป็นตาราง

                printf("\n mean");
                printf("\n  ---------------------------------------------\n");
                printf(" |%5s%3s%8s%6s%9s%5s%7s%3s\n","mid","|","final","|","attend","|","total","|");
                printf(" |---------------------------------------------|\n");
                printf(" | %.2lf%2s%9.2lf%5s%9.2lf%5s%7.2lf%3s",avg[0],"|",avg[1],"|",avg[2],"|",mean,"|");
                printf("\n |---------------------------------------------|");//แสดงผล  mean เป็นตาราง
                Grade_setting(st,stcount,a,bp,b,cp,c,dp,d); //เรียกใช้ฟังก์ชั่น  Grade_setting เพื่อแสดง gpa
                grade = 1; //ให้ grade = 1 เพื่อให้แสดงว่าได้เรียกใช้เมนูนี้แล้ว
            }

            else if(select == 3 ) //ถ้าผู้ใช้เลือกเมนูที่ 3
            {
                if(grade == 0) //ถ้า grade = 0 (ยังไม่ได้เลือกใช้เมนูที่ 2)
                {
                    printf("\nPlease enter menu 2 first\n"); //แสดงผลว่ายังไม้ได้เลือกใช้เมนูที่ 2 จึงไม่สามารถใช้เมนูที่ 3 ได้
                }
                else //ถ้าเลือกใช้เมนูที่ 2 แล้ว
                {
                    Find_Statistic(st,stcount,&min,&max,&mean,&sd,avg);
                    printf("\n total");
                    printf("\n  ---------------------------------------------\n");
                    printf(" |%5s%3s%8s%6s%9s%5s%5s%5s\n","min","|","max","|","mean","|","SD","|");
                    printf(" |---------------------------------------------|\n");
                    printf(" | %.2lf%2s%9.2lf%5s%9.2lf%5s%7.2lf%3s",min,"|",max,"|",mean,"|",sd,"|");
                    printf("\n |---------------------------------------------|"); //แสดงผล total เป็นตาราง

                    printf("\n mean");
                    printf("\n  ---------------------------------------------\n");
                    printf(" |%5s%3s%8s%6s%9s%5s%7s%3s\n","mid","|","final","|","attend","|","total","|");
                    printf(" |---------------------------------------------|\n");
                    printf(" | %.2lf%2s%9.2lf%5s%9.2lf%5s%7.2lf%3s",avg[0],"|",avg[1],"|",avg[2],"|",mean,"|");
                    printf("\n |---------------------------------------------|");//แสดงผล total เป็นตาราง
                    Grade_setting(st,stcount,a,bp,b,cp,c,dp,d); //เรียกใช้ฟังก์ชั่น  Grade_setting เพื่อแสดง gpa
                }
            }

            else if(select == 4) //ถ้าผู้ใช้เลือกเมนูที่ 4
            {
                Show_All_Data(st,stcount); //เรียกใช้ฟังก์ชั่น Show_All_Data เพื่อแสดงข้อมูลทั้งหมด
            }

            else if(select == 5) //ถ้าผู้ใช้เลือกเมนูที่ 5
            {
                Sort_by_total(st,stcount); // เรียกใช้ฟังก์ชั่น  Sort_by_total เพื่อเรียงคะแนนขากมากไปน้อบ
                Show_All_Data(st,stcount); //เรียกใช้ฟังก์ชั่น Show_All_Data เพื่อแสดงข้อมูลทั้งหมด
            }

            else if(select == 6) //ถ้าผู้ใช้เลือกเมนูที่ 6
            {
                Sort_by_id(st,stcount); // เรียกใช้ฟังก์ชั่น Sort_by_id เพื่อเรียงข้อมูลจากเลขประจำตัวมากไปน้อบ
            }

            else if(select == 7) //ถ้าผู้ใช้เลือกเมนูที่ 7
            {
                Search_Score(st,stcount); // เรียกใช้ฟังก์ชั่น Search_Score เพื่อหาข้อมูลที่มีตะแนนตามที่ผู้ใช้ต้องการ
            }

            else if(select == 8) //ถ้าผู้ใช้เลือกเมนูที่ 8
            {
                Search_Grade(st,stcount); // เรียกใช้ฟังก์ชั่น Search_Grade เพื่อหาข้อมูลที่มีเกรดตามที่ผู้ใช้ต้องการ
            }

            else if(select == 9) //ถ้าผู้ใช้เลือกเมนูที่ 9
            {
                Search_Name(st,stcount); // เรียกใช้ฟังก์ชั่น Search_Name เพื่อหาข้อมูลที่มีชื่อตามที่ผู้ใช้ต้องการ
            }
        }
    }
    while(select!=0); //ทำซ้ำจนกว่าผู้ใช้จะเลือกเมนูที่ 0
    return 0; //จบโปรแกรม
}

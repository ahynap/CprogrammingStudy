#include <stdio.h>
#include <string.h> //จัดการข้อความ
#include <stdlib.h> //แปลงค่าสตริงไปเป้นเลข แปลงเลขไปเป็นสตริง
#include <ctype.h> //จัดการตัวอักษร 1 ตัว

void add_space(char *str)
{
    char buff[255] = "",j[255] ="";
    int i,max;
    for (i=0,max=strlen(str) ; i<max ; i++) //วนรอบทำถึงตัวที่ '\0' เพื่อนำไปใช้ปิดสตริง buff
    {
        if(strchr("+-*/^()",str[i]) != NULL) //ตรวจสอบว่ามีตัวที่เป็น+-*/^() หรือไม่
            sprintf(buff,"%s %c ",j,str[i]); //ถ้ามี ให้เว้นวรรคข้างหน้าและข้างหลังตัวนั้น
        else
            sprintf(buff,"%s%c",j,str[i]); //ถ้าไม่มี ไม่ต้องเว้นวรรคใดๆ
        strcpy(j,buff); //คัดลอก buff ไปยัง j เพื่อตรวจสอบตัวถัดไป
    }
    strcpy(str,buff);//คัดลอก buff ไปยังพอยต์เตอร์ str เพื่อส่งคืนคำตอบ
}

int string_segment(char word[][100],char *buff) //ฟังก์ชั่นตัดสตริงไปเก็บไว้ในอาร์เรย์
{
    char *token;
    int count=0;
    token=strtok(buff," "); //ใช้คำสั่งแยกสตริง เพื่อแบ่งคำแรก โดยใช้ช่องว่างเป็นตัวแบ่ง
    while (token!=NULL) //ถ้าสตริงยังไม่หมดให้ทำใน loop นี้
    {
        strcpy(word[count++],token); //คัดลอกไปเก็บไว้ในอาร์เรย์
        token = strtok(NULL," "); //แบ่งคำต่อๆไป โดยใช้ช่องว่าง (\0) เป็นตัวแบ่ง
    }
    return count; //ส่งคืนค่า count
}

int is_function(char *token) //ฟังก์ชั่นเปรียบเทียบค่าข้อมูลว่าเหมือนกันหรือไม่ เพื่อหาฟังก์ชั่นตรีโกณมิติ
{
    int i;
    char fname[11][10] = {"sin","cos","tan","asin","acos","atan","sqrt","pow","log","exp","abs"}; //จองที่ไว้ 11 ตัว ตัวละไม่เกิน 10 ตัวอักษร สำหรับเก็บฟังก์ชั่นตรีโกณ
    for(i=0; i<10; i++)
    {
        if(strcmp(fname[i],token)==0) //ใช้คำสั่ง strcmp เปรียบเทียบข้อมูล 2 ชุด คือ fname และ token
            return 1; //ถ้า fname เหมือนกับ token ทุกตัว (strcmp(fname[i],token)==0) ให้ return 1
    }
    return 0; //ถ้าไม่เหมือนให้ return 0
}

int is_operator(char *token) //สร้างฟังก์ชั่นตรวจสอบว่าเป็น operator หรือไม่ โดยเปรียบเทียบค่าข้อมูลว่าเหมือนกันหรือไม่
{
    int i;
    char fname[8][7] = {"+", "-", "*", "/", "^", "(", ")" }; //จองที่ไว้ 8 ตัว ตัวละไม่เกิน 7 ตัวอักษร สำหรับเก็บ operator
    for(i=0; i<7; i++)
    {
        if(strcmp(fname[i],token)==0) //ใช้คำสั่ง strcmp เปรียบเทียบข้อมูล 2 ชุด คือ fname และ token
            return 1; //ถ้า fname เหมือนกับ token ทุกตัว (strcmp(fname[i],token)==0) ให้ return
    }
    return 0; //ถ้าไม่เหมือนให้ return 0
}

int is_number (char *token) //สร้างฟังก์ชั่นตรวจสอบว่าเป็นตัวเลขหรือไม่ โดยตรวจสอบด้วยจุดทศนิยม
{
    int i,dot_count=0;
    for(i=0; i<strlen(token); i++)
    {
        if(isdigit(token[i])==0 && token[i]!= '.') //ตรวจสอบว่าขึ้นต้นด้วยตัวเลขหรือจุดหรือไม่
            return 0; //ถ้าไม่เป็นตัวเลขและไม่ใช่จุด ให้ return 0
        if(token[i]=='.')
            dot_count++; //ถ้าเจอจุด ให้ตัวแปร dot_count เพิ่มขึ้น 1
    }
    if(dot_count>1)
        return 0; //ถ้า dot_count มากกว่า 1 ให้ return 0
    else
        return 1; //ถ้า dot_count น้อยกว่าเท่ากับ 1 ให้ return 1
}

int is_iden(char *token) //สร้างฟังก์ชั่นตรวจสอบว่าเป็น identifier หรือไม่ โดยเปรียบเทียบค่าข้อมูลว่าเหมือนกันหรือไม่
{
    int i;
    if(isdigit(token[0]))
        return 0; //ถ้ามีตัวเลขใน index แรก ให้ return 0
    for(i=0; i<strlen(token); i++)
    {
        if(isalpha(token[i]) == 0 && token[i] != '_' && isdigit(token[i])== 0) //ตรวจสอบว่าขึ้นต้นด้วยตัวเลข และ ขึ้นต้นด้วย _ หรือไม่ และ ขึ้นต้นด้วยอักขระหรือไม่
            return 0; //ถ้าใช่ ให้ return 0
    }
    return 1; //ถ้าไม่ใช่ให้ return 1
}

int main ()
{
    char str[100],buff[100],token[100][100];
    int i,len,count,mean[5][100],type;
    do
    {
        int count_mean[5] = {0,0,0,0,0}; //กำหนดให้ count_mean เป็น 0 ทั้งหมด
        printf("enter your data : ");
        gets(str); //get string
        strcpy(buff,str); //คัดลอก str ไปยังพอยต์เตอร์ buff
        strlwr(buff); //แปลงให้เป็นตัวพิมพ์เล็ก
        add_space(buff); //เพิ่มเว้นวรรค

        printf("your string is : %s",buff); //แสดงผลสตริงที่เปลี่ยนเป็นตัวพิมเล็กและเพิ่มเว้นวรรคแล้วทั้งหมด

        count = string_segment(token,buff); //นับจำนวนคำที่รับจาก user
        if(count == 1) //ถ้ามีแค่ 1 คำ
        {
            if(strcmp(token,"end")==0||strcmp(token,"exit")==0) //ให้ตรวจสอบว่าใช่คำว่่า end หรือ exit ใช่หรือไม่
            {
                printf("\t\nend program"); //ถ้าใช่ ให้แสดงผว่าจบโปรแกรม
                return 0; //จบโปรแกรม
            }
        }

        printf("\ncount data : %d \n\n",count); //แสดงค่า count

        for(i=0; i<count; i++)
        {
            if(is_number(token[i]) == 1) //ตรวจสอบว่าค่าที่รับจากผู้ใช้เป็น number ใช่หรือไม่
            {
                mean[0][count_mean[0]++] = i;
                type = 0;   //ถ้าเป็น number ให้มีค่าเท่ากับ type 0
            }
            else if(is_operator(token[i]) == 1) //ถ้าไม่ใช่ ให้ตวจสอบต่อว่า ค่าที่รับจากผู้ใช้เป็น operator ใช่หรือไม่
            {
                mean[1][count_mean[1]++] = i;
                type = 1;   //ถ้าเป็น operator ให้มีค่าเท่ากับ type 1
            }
            else if(is_function(token[i]) == 1) //ถ้าไม่ใช่ ให้ตวจสอบต่อว่า ค่าที่รับจากผู้ใช้เป็น function ใช่หรือไม่
            {
                mean[2][count_mean[2]++] = i;
                type = 2;  //ถ้าเป็น function ให้มีค่าเท่ากับ type 2
            }
            else if(is_iden(token[i]) == 1) //ถ้าไม่ใช่ ให้ตวจสอบต่อว่า ค่าที่รับจากผู้ใช้เป็น identifier ใช่หรือไม่
            {
                mean[3][count_mean[3]++] = i;
                type = 3;  //ถ้าเป็น identifier ให้มีค่าเท่ากับ type 3
            }
            else //ถ้าไม่ใช่ตัวเลข operator ฟังก์ชั่น หรือ identifier
            {
                mean[4][count_mean[4]++] = i;
                type = 4; //ให้มีค่าเท่ากับ type 4
            }
            printf("\t%s is ",token[i]); //แสดงค่า index ของอาร์เรย์

            if(type == 0) //ถ้าเป็น type 0
                printf("a number.\n"); //แสดงผลว่าเป็นตัวเลข
            else if(type == 1) //ถ้าเป็น type 1
                printf("an operator.\n"); //แสดงผลว่าเป็น operator
            else if(type == 2) //ถ้าเป็น type 2
                printf("a function.\n");  //แสดงผลว่าเป็น function
            else if(type == 3) //ถ้าเป็น type 3
                printf("an identifier.\n"); //แสดงผลว่าเป็น identifier
            else if(type == 4) //ถ้าเป็น type 4
                printf("an error.\n"); //แสดงผลว่าเป็น error
        }

        printf("\nyou have %d numbers, that is : ",count_mean[0]); //แสดงผลว่ามี number กี่ตัว ได้แก่อะไรบ้าง
        i =0;
        while(i<count_mean[0])
        {
            printf("%s ",token[mean[0][i]]);
            i++;
        }

        printf("\nyou have %d operators, that is : ",count_mean[1]); //แสดงผลว่ามี นperator กี่ตัว ได้แก่อะไรบ้าง
        i=0;
        while(i<count_mean[1])
        {
            printf("%s ",token[mean[1][i]]);
            i++;
        }

        printf("\nyou have %d functions, that is : ",count_mean[2]); //แสดงผลว่ามี function กี่ตัว ได้แก่อะไรบ้าง
        i=0;
        while(i<count_mean[2])
        {
            printf("%s ",token[mean[2][i]]);
            i++;
        }

        printf("\nyou have %d identifier, that is : ",count_mean[3]); //แสดงผลว่ามี identifier กี่ตัว ได้แก่อะไรบ้าง
        i=0;
        while(i<count_mean[3])
        {
            printf("%s ",token[mean[3][i]]);
            i++;
        }

        printf("\nyou have %d errors, that is : ",count_mean[4]); //แสดงผลว่ามี error กี่ตัว ได้แก่อะไรบ้าง
        i=0;
        while(i<count_mean[4])
        {
            printf("%s ",token[mean[4][i]]);
            i++;
        }
        printf("\n\n");
        system("pause");
        system("cls"); //clear screen
    } while (1); //ทำซ้ำจนกว่า user จะเลือกจบโปรแกรม
}

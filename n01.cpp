#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNAME  20
#define MAXADDRESS 20
#define TEL	11
#define EMAIL 30
#define BIRTH 14

struct Students{				//学生信息的结构模板 
	char name[MAXNAME];               
	int studyNum;
	int studentAge;
	int studentSex;
	char address[MAXADDRESS];
	char studentTel[TEL];
	char studentEmail[EMAIL];
	char studentBirth[BIRTH];
	struct Students * next; 		//指向链表中的下一个结构 
}; 
struct Students * head = NULL;//链表头指针
struct Students * head1 = NULL;//存放排序后的数据 
struct Students * head2 = NULL;//存放排序后的数据
struct Students * prev=NULL, *current=NULL;

char *s_gets(char * st,int n);	//字符串输入函数 
int  menu();					//主目录菜单 
void addStudents();				//添加学生信息 
void DisplayStudents(struct Students *head,int flag);//展示学生信息
void Save();					//保存链表中的数据到文件中 
void saveData(char inputName[MAXNAME], int inputNum, int inputAge, int inputSex, char inputAddress[MAXADDRESS],char inputTel[TEL], char inputEmail[EMAIL],char inputBirth[BIRTH]);//将文件中的数据储存到链表中 
void load();					//将文件中获得的数据写入到链表中
void exit0();					//退出 
void deleteStudents();			//删除学生信息 
void moditfInfo();				//修改学生信息 
int dismenu();					//查询子目录 
void DeleteMemory(struct Students *head);
struct Students *sortbynum(struct Students *head);  //从小到大按照学号排序 
struct Students *sortbyage(struct Students *head);  //从小到大按照年龄排序 
void fineInName();				//按照姓名查找
void fineInId();			    //按照学号查找 
char *s_gets(char *st,int n)	//字符串输入函数 
{
	char *ret_val;
	char *find;
	ret_val=fgets(st,n,stdin);
	if(ret_val)
	{
		find=strchr(st,'\n');
		if(find)
		*find='\0';
		else
		while(getchar()!='\n')
		continue;
	}
	return ret_val;
 } 

int  menu()						//主目录菜单 
{
	int n;
	puts("       *****************学生成绩管理系统*****************\n");
	puts("       **		1、浏览所有信息			**\n");
	puts("       **		2、添加信息			**\n");
	puts("       **		3、删除信息			**\n"); 
	puts("       **		4、修改信息			**\n");
	puts("       **		5、信息排序			**\n");
	puts("       **		6、按照姓名查找			**\n");
	puts("       **		7、按照学号查找			**\n");
	puts("       **		0、退出				**\n");
	puts("       **		亲，请输入您的选择：		**\n");
	scanf("%d",&n);
	switch(n)
	{
		case 1:DisplayStudents(head,1);break;
		case 2:addStudents();break;
		case 3:deleteStudents();break;
		case 4:moditfInfo();break;
		case 5:dismenu();break;
		case 6:fineInName();break;
		case 7:fineInId();break;
		case 0:exit0();break;
	}
	return n; 	
 }
void exit0()					//退出 
{
	struct Students *p = head;
	while(p!= NULL)
	{
		free(p);
		p = p->next;		
	}
	printf("Bye!"); 
	exit(0);
}
void fineInName()				//按照姓名查找 
{
	struct Students *p = head;
    char studentName[MAXNAME] = "";
    if (head == NULL)
    {
        printf("没有数据查找\n");
        return;
    }
    printf("请输入你要查找的学生的姓名：");
    scanf("%s", studentName);
    while (0!=strcmp(studentName,p->name)&&p->next != NULL)
    {
        p = p->next;
    }
    if (0==strcmp(studentName,p->name))
    {
        puts("    姓名        学号       年龄       性别    地址             手机号\t\t邮箱\t\t    出生年月");
        printf("%10s%10d%10d%10d%10s%20s%20s%20s", p->name, p->studyNum, p->studentAge,p->studentSex, p->address, p->studentTel,p->studentEmail,p->studentBirth);
        printf("\n");
    }
    else{
        printf("没有你要查找的数据\n");
    }
    return;
	
}
void fineInId()				//按照学号查找 
{
	struct Students *p = head;
    int studentID=0;
    if (head == NULL)
    {
        printf("没有数据查找");
        return;
    }
    printf("请输入你要查找的学生的学号：");
    scanf("%d", &studentID);
    while (studentID != p->studyNum&&p->next != NULL)
    {
        p = p->next;
    }
    if (studentID == p->studyNum)
    {
        puts("    姓名        学号       年龄       性别    地址             手机号\t\t邮箱\t\t    出生年月");
        printf("%10s%10d%10d%10d%10s%20s%20s%20s", p->name, p->studyNum, p->studentAge,p->studentSex, p->address, p->studentTel,p->studentEmail,p->studentBirth);
        printf("\n");
    }
    else{
        printf("没有你要查找的数据");
    }
    return;
	
}
int dismenu()					//查询子目录 
 {
 	int n; 
 	
	puts("       1、按年龄由小到大排序\n"); 
	puts("       2、按学号由小到大排序\n");
	puts("       0、返回主菜单\n");
	printf("       请选择：\n");
	scanf("%d",&n);
	switch(n)
	{
		case 0:menu();return 0;
		case 2:head1 = sortbynum(head);DisplayStudents(head1,1);break;
	    case 1:head2 = sortbyage(head);DisplayStudents(head2,1);break;
		default:printf("error!\n");break;
	}
	return n;
 }
void DeleteMemory(struct Students *head)
{
    struct Students *p = head, *pr = NULL;
    while (p != NULL)
    {
        pr = p;
        p = p->next;
        free(pr);
    }
    
}
struct Students *sortbynum(struct Students *head)  //从小到大按照学号排序 
{  
    struct Students *first; 
    struct Students *t;  
    struct Students *p;   
    struct Students *q;   

    first = head->next;   
    head->next = NULL; 

    while (first != NULL)   
    {  
        for (t = first, q = head; ((q != NULL) && (q->studyNum < t->studyNum)); p = q, q = q->next);   

        first = first->next; 

        if (q == head)   
        {  
            head = t;  
        }  
        else 
        {  
            p->next = t;  
        }  
        t->next = q; 

    }  
    return head;  
}
struct Students *sortbyage(struct Students *head)  //从小到大按照年龄排序 
{  
    struct Students *first; 
    struct Students *t;  
    struct Students *p;   
    struct Students *q;   

    first = head->next;   
    head->next = NULL; 

    while (first != NULL)   
    {  
        for (t = first, q = head; ((q != NULL) && (q->studentAge < t->studentAge)); p = q, q = q->next);   

        first = first->next; 

        if (q == head)   
        {  
            head = t;  
        }  
        else 
        {  
            p->next = t;  
        }  
        t->next = q; 

    }  
    return head;  
}
void addStudents()				//添加学生信息 
{
	char ch = getchar();//消除换行符的影响 
	char inputName[MAXNAME];
	char inputAddress[MAXADDRESS];
	char inputTel[TEL];
	char inputEmail[EMAIL];
	char inputBirth[BIRTH];
	int inputNum;
	int inputAge;
	int inputSex;
	int sexNum; 
	puts("Enter the first student's name!");
    while (gets(inputName) != NULL && inputName[0] != '\0')
    {

        puts("Enter student's studentNum");	//输入学号 
		scanf("%d", &inputNum);
		puts("Enter student's studyAge");	//输入年龄 
		scanf("%d", &inputAge);
		puts("Enter student's studentSex");//输入性别 
		puts("1、帅哥\n");
		puts("2、美女\n");
		puts("亲，请输入您的选择");
		scanf("%d", &sexNum);
		switch(sexNum)
		{
			case 1:
				inputSex=1; break;
			case 2:
				inputSex=2; break;
		}
		getchar();//消除换行符的影响 
		puts("Enter student's address");//输入地址 
		gets(inputAddress);

		puts("Enter student's studentTel");//输入电话号码 
		gets(inputTel);

		puts("Enter student's studentEmail");//输入邮箱 
		gets(inputEmail);

		puts("Enter student's studentBirth ,格式为 ‘1997/05/12’");//输入出生年月 
		gets(inputBirth);
		
        while (getchar() != '\n')
        {
        	puts("录入成功");
			continue;
		}
           

        puts("Enter next  the student's name!(empty line to stop):");
		saveData(inputName, inputNum, inputAge, inputSex,inputAddress,inputTel,inputEmail,inputBirth);//将输入的数据读取到链表中 
		
    }
    Save();
	DisplayStudents(head,1);//将链表的数据储存到文件中 
	
}

void deleteStudents()			//删除学生信息 
{
	struct Students *p = head, *pr = head;
    char studentName[10] = "";
    if (head == NULL) {
        printf("对不起，没有数据可以删除");
        return;
    }
    printf("请输入你要删除的学生的姓名:");
    scanf("%s", studentName);
    while (0!=strcmp(studentName,p->name)&&p->next != NULL)
    {
        pr = p;
        p = p->next;
    }
    if (0==strcmp(studentName, p->name))
    {
        if (p == head) {
            head = p->next;//重置头指针 
        }
        else
        {
            pr->next = p->next;//跳过这个内存 
        }
        free(p);//释放内存 
        Save();
		puts("删除成功！"); 
    }
    else
    {
        printf("你要查找的这个数据未找到");
    }
    return;
	
}

void moditfInfo()				//修改学生信息 
{
	struct Students *p = head, *pr = head;
    char studentName[MAXNAME] = "";
    char inputName[MAXNAME];
	char inputAddress[MAXADDRESS];
	char inputTel[TEL];
	char inputEmail[EMAIL];
	char inputBirth[BIRTH];
	int inputNum;
	int inputAge;
	int inputSex;
	int sexNum; 
	
    if (head == NULL) {
        printf("对不起，没有数据可以修改，请添加学生信息\n");
        return;
    }
    printf("请输入你要修改的学生的姓名:");
    scanf("%s", studentName);
    while (0!=strcmp(studentName,p->name)&&p->next != NULL)
    {
        pr = p;
        p = p->next;
    }
    if (0==strcmp(studentName, p->name))
    {
    	//找到匹配的学生，准备修改
		 
        puts("查找成功，请重新修改该项内容");
        getchar();//消除\n的影响 
        puts("Enter student's name");	//输入姓名 
        gets(inputName);
        strcpy(p->name, inputName);  
		puts("Enter student's studentNum");	//输入学号 
		scanf("%d", &p->studyNum);
		puts("Enter student's studyAge");	//输入年龄 
		scanf("%d", &p->studentAge);
		puts("Enter student's studentSex");//输入性别 
		puts("1、帅哥\n");
		puts("2、美女\n");
		puts("亲，请输入您的选择");
		scanf("%d", &sexNum);
		switch(sexNum)
		{
			case 1:
				p->studentSex=1; break;
			case 2:
				p->studentSex=2; break;
		}
		getchar();//消除换行符的影响 
		puts("Enter student's address");//输入地址 
		gets(inputAddress);
		strcpy(p->address, inputAddress);
		puts("Enter student's studentTel");//输入电话号码 
		gets(inputTel);
		strcpy(p->studentTel, inputTel);
		puts("Enter student's studentEmail");//输入邮箱 
		gets(inputEmail);
		strcpy(p->studentEmail, inputEmail);
		puts("Enter student's studentBirth ,格式为 ‘1997/05/12’");//输入出生年月 
		gets(inputBirth); 
		strcpy(p->studentBirth, inputBirth);
		puts("修改成功!");
		Save(); 
    }
    else
    {
        printf("你要查找的这个数据未找到");
    }
    return;
}

void Save()						//保存链表中的数据
{ 
    FILE *fp;
    struct Students *p = head;
    if ((fp = fopen("data.txt", "w")) == NULL)
    {
        printf("打开文件失败");
        return;
    }
    while (p != NULL)
    {
        fprintf(fp, "%20s%20d%20d%20d%20s%20s%20s%20s", p->name, p->studyNum, p->studentAge,p->studentSex, p->address, p->studentTel,p->studentEmail,p->studentBirth);
		
        p = p->next;
    }
    fclose(fp);
    return;
}

void DisplayStudents(struct Students *head,int flag)	//打印链表中的数据 
{
    struct Students *p = head;
    if (p == NULL)
    {
        return;
    }
    if(flag == 1)
    {
    	puts("    姓名        学号       年龄       性别    地址             手机号\t\t邮箱\t\t    出生年月");
	}
    printf("%10s%10d%10d%10d%10s%20s%20s%20s", p->name, p->studyNum, p->studentAge,p->studentSex, p->address, p->studentTel,p->studentEmail,p->studentBirth);
    printf("\n");
    DisplayStudents(p->next,0);
}

void load()						//将文件中获得的数据写入到链表中
{
    char inputName[MAXNAME];
	char inputAddress[MAXADDRESS];
	char inputTel[TEL];
	char inputEmail[EMAIL];
	char inputBirth[BIRTH];
	int inputNum;
	int inputAge;
	int inputSex;
	int sexNum; 
    FILE *fp;
    char c;
    if ((fp = fopen("data.txt", "r")) == NULL)
    {
        printf("文件打开失败");
        return;
    }
    while ((c = fgetc(fp))!=EOF)
    {
        fscanf(fp, "%20s", &inputName);
        fscanf(fp, "%20d", &inputNum);
        fscanf(fp, "%20d",  &inputAge);
        fscanf(fp, "%20d",  &inputSex);
        fscanf(fp, "%20s", &inputAddress);
        fscanf(fp, "%20s", &inputTel);
        fscanf(fp, "%20s", &inputEmail);
        fscanf(fp, "%20s", &inputBirth);
        saveData(inputName, inputNum, inputAge, inputSex,inputAddress,inputTel,inputEmail,inputBirth);//将文件中的数据读取到链表中 
    }
    fclose(fp);
}

void saveData(char inputName[MAXNAME], int inputNum, int inputAge, int inputSex, char inputAddress[MAXADDRESS],char inputTel[TEL], char inputEmail[EMAIL],char inputBirth[BIRTH])//将文件中的数据读取到链表中 
{
	struct Students *p = NULL, *pr = head;
    p = (struct Students *) malloc(sizeof(struct Students));
    if (p == NULL)
    {
        printf("申请内存失败");
        return;
    }
    if (head == NULL)
    {
        head = p;
    }
    else {
        while (pr->next != NULL)
        {
            pr = pr->next;
        }
        pr->next = p;
    }
    strcpy(p->name, inputName);              
	p->studyNum = inputNum;
	p->studentAge = inputAge;
	p->studentSex = inputSex;
	strcpy(p->address, inputAddress);
	strcpy(p->studentTel, inputTel);
	strcpy(p->studentEmail, inputEmail);
	strcpy(p->studentBirth, inputBirth);
    
    p->next = NULL;
    return;
} 


int main(){
	

	system("color 3f");											//设置颜色主题 
 	puts("       ***********************************************************");
 	puts("       ***********************************************************");
 	puts("       ***********************************************************");
 	puts("                       ***************************"); 
 	printf("                         欢迎使用学生信息管理系统\n");
 	puts("                       ***************************");
 	puts("       ***********************************************************");
 	puts("       ***********************************************************");
 	puts("       ***********************************************************");
 	printf("\n");
 	printf("\n");
	load();//加载上次保存的数据 
	while(menu())
 	{
 			
	}
	return 0;
} 


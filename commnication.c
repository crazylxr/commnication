	/*3.25 手机通信录管理（难度系数：3级）
模拟手机通信录管理系统，实现对手机中的通信录进行管理。
功能要求
 	查看功能：选择此功能时，列出下列三类选择。
 	A  办公类  B  个人类 C 商务类 ，当选中某类时，显示出此类所有数据中的姓名和电话号码）
 	增加功能：能录入新数据（一个结点包括：姓名、电话号码、分类（可选项有：A  办公类  B  个人类 C 商务类）、电子邮件）。例如
杨春   13589664454  商务类  chuny@126.com
当录入了重复的姓名和电话号码时，则提示数据录入重复并取消录入；当通信录中超过15条信息时，存储空间已满，不能再录入新数据；录入的新数据能按递增的顺序自动进行条目编号。
 	拔号功能：能显示出通信录中所有人的姓名，当选中某个姓名时，屏幕上模拟打字机的效果依次显示出此人的电话号码中的各个数字，并伴随相应的拔号声音。
 	修改功能：选中某个人的姓名时，可对此人的相应数据进行修改
 	删除功能：选中某个人的姓名时，可对此人的相应数据进行删除，并自动调整后续条目的编号。*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
typedef struct com
{
	char name[20];
	char no[12];
	char Class[20];
	char Email[30];
	struct com *next;
}note;
int sum=0;
void tip()
{
	printf("                       ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	printf("                             欢迎进入手机通讯录\n");
	printf("                       ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("     【功能】 1-查看功能  2-增加功能  3-拨号功能   4-修改功能  5-删除功能\n");
	printf("-------------------------------------------------------------------------------\n");
}
void tip1()
{
	printf("-------------------------------------------------------------------------------\n");
	printf("     【功能】 1-查看功能  2-增加功能  3-拨号功能   4-修改功能  5-删除功能\n");
	printf("-------------------------------------------------------------------------------\n");
}
note *crete()
{
	note *head=NULL,*p=NULL,*p1=NULL;
	printf("请输入姓名，电话号码，类型，电子邮件,姓名为0退出\n");
	for(;;)
	{
		p=(note*)malloc(sizeof(note));
		fflush(stdin);
		gets(p->name);
		if(*(p->name)=='0')
			break;
		fflush(stdin);
		gets(p->no);
		fflush(stdin);
		gets(p->Class);
		fflush(stdin);
		gets(p->Email);
		fflush(stdin);
		p->next=NULL;
		sum++;
		if(p1==NULL)
			head=p1=p;
		else
		{
			p1->next=p;
			p1=p;
		}	
	}
	return head;
}
void Display()
{
	note *p=NULL,*p1=NULL,*head=NULL;
	FILE *fp=fopen("communication.txt","r");
	if(fp==NULL)
	{
		printf("打开失败\n");
		return;
	}
	printf("-------------------------------------------------------------------------------\n");
	printf("    姓名        电话号码            类型           邮箱\n");
	printf("-------------------------------------------------------------------------------\n");
	for(p=head;;)
	{   
		p=(note*)malloc(sizeof(note));
		fscanf(fp,"%s%s%s%s",p->name,p->no,p->Class,p->Email);
		p->next=NULL;
		if(p1==NULL)
			head=p1=p;
		else
		{
			p1->next=p;
			p1=p;
		}	
		if(feof(fp)!=0)//重要
			break;
		printf("    %-7s",p->name);
		printf("     %-13s",p->no);
		printf("       %-8s",p->Class);
		printf("        %-15s\n\n",p->Email);
		
	}
	fclose(fp);
	printf("-------------------------------------------------------------------------------\n");
}
//储存
void save(note *head)
{

	note *p;
	FILE *fp=fopen("communication.txt","w");
	if(fp==NULL)
	{
		printf("打开失败\n");
		return;
	}
	for(p=head;p!=NULL;)
	{
		fprintf(fp,"%s %s %s %s ",p->name,p->no,p->Class,p->Email);
		p=p->next;
	}
	fclose(fp);
}
// 修改
note * alter(char *name1)
{
	int sel1;
	char no1[20],name2[20],class1[20],Email1[20];
	note *p=NULL,*p1=NULL,*head=NULL;
	FILE *fp=fopen("communication.txt","r");
	if(fp==NULL)
	{
		printf("打开失败\n");
	}
	for(p=head;;)
	{  
		if(feof(fp)!=0)//重要
			break;
		p=(note*)malloc(sizeof(note));
		fscanf(fp,"%s%s%s%s",p->name,p->no,p->Class,p->Email);
		p->next=NULL;
		if(p1==NULL)
			head=p1=p;
		else
		{
			p1->next=p;
			p1=p;
		}	
		if(strcmp(p->name,name1)==0)
		{
			while(1)
			{
			printf("-------------------------------------------------------------------------------\n");
			printf("      【修改选择】 1-姓名  2-电话号码  3-类型   4-电子邮箱  0-修改完成\n");
			printf("-------------------------------------------------------------------------------\n");
			scanf("%d",&sel1);
			if(sel1==0)
			{
				printf("                            ☆☆☆☆☆☆☆☆☆\n");
				printf("                            ☆恭喜你修改成功☆\n");
				printf("                            ☆☆☆☆☆☆☆☆☆\n");
				break;
			}
			switch(sel1)
			{
				case 1:
					{
						printf("请输入姓名:");
						scanf("%s",name2);
						strcpy(p->name,name2);
					}
					break;
				case 2:
					{
						printf("请输入号码:");
						scanf("%s",no1);
						strcpy(p->no,no1);
					}
					break;
				case 3:
					{
						printf("请输入类型:");
						scanf("%s",class1);
						strcpy(p->Class,class1);
					}
					break;
				case 4:
					{
						printf("请输入邮箱:");
						scanf("%s",Email1);
						strcpy(p->Email,Email1);
					}
					break;

			}
			}
		}
	}
	fclose(fp);
	printf("\n");
	return head;
}
void save1(note *head)
{

	note *p;
	FILE *fp=fopen("communication.txt","w");
	if(fp==NULL)
	{
		printf("打开失败\n");
		return;
	}
	for(p=head;;)
	{
		fprintf(fp,"%s %s %s %s ",p->name,p->no,p->Class,p->Email);
		p=p->next;
		if(p->next==NULL)
			break;
	}
	fclose(fp);
}
note *Insert()    //增添节点
{
	note *p,*p1=NULL,*head=NULL,*p2=NULL;
	FILE *fp=fopen("communication.txt","r");
	if(fp==NULL)
	{
		printf("打开失败\n");
	}
	for(p=head;;)
	{
		if(feof(fp)!=0)//重要
			break;
		p=(note*)malloc(sizeof(note));
		fscanf(fp,"%s%s%s%s",p->name,p->no,p->Class,p->Email);
		p->next=NULL;
		if(p1==NULL)
			head=p1=p;
		else
		{
			p1->next=p;
			p1=p;
		}
		
	}
			p2=(note*)malloc(sizeof(note));
			fflush(stdin);
			/*gets(p2->name);
			fflush(stdin);
			gets(p2->no);
			fflush(stdin);
			gets(p2->Class);
			fflush(stdin);
			gets(p2->Email);*/
				printf("请输入你要添加联系人的信息：\n");
				printf("姓名：");
			fflush(stdin);
			scanf("%s",p2->name);
			printf("电话号码：");
			fflush(stdin);
			scanf("%s",p2->no);
			printf("类型：");
			fflush(stdin);
			scanf("%s",p2->Class);
			printf("电子邮箱：");
			fflush(stdin);
			scanf("%s",p2->Email);
		//	scanf("%s%s%s%s",p2->name,p2->no,p2->Class,p2->Email);
			p2->next=head;
			head=p2;
				printf("                            ☆☆☆☆☆☆☆☆☆\n");
				printf("                            ☆恭喜你添加成功☆\n");
				printf("                            ☆☆☆☆☆☆☆☆☆\n");
			return head;
}
note *Delete()
{
	char name3[20];
	note *head=NULL,*p=NULL,*p1=NULL;
	FILE *fp=fopen("communication.txt","r");
	printf("请输入你要删除人联系人的姓名：");
	fflush(stdin);
	gets(name3);
	if(fp==NULL)
	{
		printf("打开失败\n");
	}
	for(p=head;;)
	{
		if(feof(fp)!=0)//重要
			break;
		p=(note*)malloc(sizeof(note));
		fscanf(fp,"%s%s%s%s",p->name,p->no,p->Class,p->Email);
		p->next=NULL;
		if(p1==NULL)
			head=p1=p;
		else
		{
			p1->next=p;
			p1=p;
		}
	}
	for(p1=p=head;p!=NULL;)
	{
		if(strcmp(head->name,name3)==0)
		{
			head=p->next;
		}
		if(strcmp(p->name,name3)==0)
				p1->next=p->next;
			p1=p;
			p=p->next;
	}	
				printf("                            ☆☆☆☆☆☆☆☆☆\n");
				printf("                            ☆恭喜你删除成功☆\n");
				printf("                            ☆☆☆☆☆☆☆☆☆\n");
	return head;
}
void Dial()
{
	char name4[20],no5[20];
	int i;
	note *head=NULL,*p=NULL,*p1=NULL;
	FILE *fp=fopen("communication.txt","r");
	printf("请输入你要拨号人的姓名:");
	fflush(stdin);
	gets(name4);
	if(fp==NULL)
	{
		printf("打开失败\n");
	}
	for(p=head;;)
	{
		if(feof(fp)!=0)//重要
			break;
		p=(note*)malloc(sizeof(note));
		fscanf(fp,"%s%s%s%s",p->name,p->no,p->Class,p->Email);
		p->next=NULL;
		if(p1==NULL)
			head=p1=p;
		else
		{
			p1->next=p;
			p1=p;
		}
	}
		for(p=head;p->next!=NULL;)
		{
			if(strcmp(p->name,name4)==0)
			{
				strcpy(no5,p->no);
				for(i=0;i<(int)strlen(p->no);i++)
				{
					if(i==0)
					PlaySound(TEXT("475.wav"),NULL,SND_FILENAME|SND_ASYNC);//播放声音
					printf("%c",no5[i]);
					Sleep(555);//控制时间
					
				}
				printf("\n");
				printf("                            ☆☆☆☆☆☆☆☆☆\n");
				printf("                            ☆恭喜你删除成功☆\n");
				printf("                            ☆☆☆☆☆☆☆☆☆\n");
			}
			p=p->next;
		}
	
}
void Display1(char *CLASS)
{
	note *p=NULL,*p1=NULL,*head=NULL;
	FILE *fp=fopen("communication.txt","r");
	if(fp==NULL)
	{
		printf("打开失败\n");
		return;
	}
	printf("-------------------------------------------------------------------------------\n");
	printf("    姓名        电话号码            类型           邮箱\n");
	printf("-------------------------------------------------------------------------------\n");
	for(p=head;;)
	{   
		p=(note*)malloc(sizeof(note));
		fscanf(fp,"%s%s%s%s",p->name,p->no,p->Class,p->Email);
		p->next=NULL;
		if(p1==NULL)
			head=p1=p;
		else
		{
			p1->next=p;
			p1=p;
		}	
		if(feof(fp)!=0)//重要
			break;
		
		if(strcmp(p->Class,CLASS)==0)
		{
		printf("    %-7s",p->name);
		printf("     %-13s",p->no);
		printf("       %-8s",p->Class);
		printf("        %-15s\n\n",p->Email);
		}
	}
	fclose(fp);
	printf("-------------------------------------------------------------------------------\n");
}
void main()
{
	int sel;
	char class2;
	char name1[20];
	char A[10]={"个人类"},B[10]={"商务类"},C[10]={"办公类"};
	note *head=NULL;
	tip();
	for(;;)
	{
		printf("请选择>>:");
		scanf("%d",&sel);
		if(sel>5)
			break;
		switch(sel)
		{
			case 1:
				{
					system("cls");
					printf("-------------------------------------------------------------------------------\n");
					printf("            A-个人类****B-商务类****C-办公类****D-查看所有人\n");
					printf("-------------------------------------------------------------------------------\n");
					printf("请选择>>:");
					
					fflush(stdin);
					scanf("%c",&class2);
					if(class2=='D'||class2=='d')
						Display();
					if(class2=='A'||class2=='a')
						Display1(A);
					if(class2=='B'||class2=='b')
						Display1(B);
					if(class2=='C'||class2=='c')
						Display1(C);
					tip1();
				}
				break;
			case 2:
				{
					system("cls");
					head=Insert();
					save1(head);
					tip1();
				}
				break;
			case 3:
				{
					system("cls");
					Dial();
					tip1();
				}
				break;
			case 4:
				{
					system("cls");
					printf("请输入你要修改数据人的姓名：");
					fflush(stdin);
					scanf("%s",name1);
					head=alter(name1);
					save1(head);
					tip1();
				}
				break;
			case 5:
				{
					head=Delete();
					save1(head);
					tip1();
				}
				break;
			case 0:
				{
					system("cls");
					head=crete();
					save(head);
					tip1();
				}
				break;
		}	
	}
}
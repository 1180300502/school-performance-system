#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include<assert.h>
#define N 30
#define COURSE 6
int n=100,m=100;     //����ȫ�ֱ���������������������ʱ��������ݸ���
typedef struct STUDENT             //�ṹ������������
{
    long number;
    char name[20];
    int score[COURSE];
    long total;
    double aver;
    int order;
}student;
typedef struct STUDENT1
{
    long number;
    char name[20];
    int score[COURSE];
    struct STUDENT1 *next;
}student1;
void menu();                           //����ԭ������
void readscore(student a[]);
void course_total_aver(student a[],long b[],double c[]);
void student_total_aver(student a[],long b[],double c[]);
void descending_sort(student *p[], int left, int right);
void ascending_merge(student *sourceArr[],student *tempArr[], int startIndex, int midIndex, int endIndex);
void ascending_mergeSort(student *sourceArr[], student *tempArr[], int startIndex, int endIndex);
void ascending_insertion_sort(student *array[]);
void bubble_name_sort(student *a[]);
void printf_put(student *a[]);
void sort_in_type(student *a[], int level[][5], float percentage[][5]);
void vague_searching_studentID(student *a[]);
void vague_searching_name(student *a[]);
char * IND(char * str, char * substr);

int main()                  //������
{
    long course_total[COURSE],student_total[N];
    double corse_aver[COURSE],student_aver[N];
    int order[N];
    student stu[N];
    menu();        //���ò˵�����
    int a,i,j;
    for(i=0;i<N;i++)   //��ʼ��
    {
        student_total[i]=0;
        student_aver[i]=0;
        order[i]=0;
    }
    for(i=0;i<COURSE;i++)
    {
        course_total[i]=0;
        corse_aver[i]=0;
    }
    scanf("%d",&a);
    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
    {
        printf("Please enter your choice:(a>-1 and a<12)\n");
        scanf("%d",&a);
    }
    while(a!=1)
    {
        printf("you do not input the information\n");
        printf("Please enter your choice:(a=1)\n");
        scanf("%d",&a);
    }
    while(a!=0)      //�����벻��0ʱ�����в˵�ѡ��
    {
        switch(a)
        {
            case 1:           //����ѧ������
                {
                    readscore(stu);     //���ú�������ѧ������
                    for(i=0;i<n;i++)         //��ƽ���ֺ��ܷ�¼��ṹ������
                    {
                        stu[i].total=student_total[i];
                        stu[i].aver=student_aver[i];
                        stu[i].order=order[i];
                    }
                    printf("\n");
                    Sleep(800);  //ͣ��0.8�룬��ֹ���ò˵���������
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 2:           //����γ�ƽ���ֺ��ܷ�
                {
                    course_total_aver(stu,course_total,corse_aver);      //���ü���γ�ƽ���ֺ��ֵܷĺ���
                    for(i=0;i<m;i++)          //��ӡ�γ�ƽ���ֺ��ܷ�
                    {
                        printf("the total score of course %d is             %ld\n",i+1,course_total[i]);
                        printf("the average score of course %d is           %lf\n",i+1,corse_aver[i]);
                    }
                    printf("\n");
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 3:          //����ѧ��ƽ���ֺ��ܷ�
                {
                    student_total_aver(stu,student_total,student_aver);         //���ü���ѧ��ƽ���ֺ��ֵܷĺ���
                    for(i=0;i<n;i++)
                    {
                        printf("the total score of student %d is %ld\n",i+1,student_total[i]);       //��ӡѧ��ƽ���ֺ��ܷ�
                        printf("the average score of student %d is %.4lf\n",i+1,student_aver[i]);
                    }
                    for(i=0;i<n;i++)         //��ƽ���ֺ��ܷ�¼��ṹ������
                    {
                        stu[i].total=student_total[i];
                        stu[i].aver=student_aver[i];
                    }
                    printf("\n");
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 4:         //���ÿ������к�������ÿ��ѧ���ܷ��ɸߵ���������α�
                {
                    student *pointer1[N];       //����ָ�����飬��ÿ�����ݵ�ַ��ֵ��ÿ��ָ��
                    for(i=0;i<n;i++)
                    {
                        pointer1[i]=&stu[i];
                    }
                    int w=1;                //û�м���ѧ��ƽ���ֺ��ܷ�ʱ�����������µ��ò˵�������ѡ��
                    for(i=0;i<n;i++)
                    {
                        if(pointer1[i]->total!=0)
                            w=0;
                    }
                    if(w==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                        Sleep(2800);
                        menu();
                        scanf("%d",&a);
                        while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                        {
                            printf("Please enter your choice:(a>-1 and a<12)\n");
                            scanf("%d",&a);
                        }
                        break;
                    }
                    descending_sort(pointer1,0,n-1);    //���ý������еĿ��������㷨
                    for(i=0;i<n;i++)
                    {
                        pointer1[i]->order=i+1;
                    }
                    printf("the league tables of student total score in descending order is\n");           //������α�
                    printf_put(pointer1);
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 5:          //���ù鲢���к�������ÿ��ѧ���ܷ��ɵ͵���������α�
                {
                    student *pointer2[N];       //����ָ�����飬��ÿ�����ݵ�ַ��ֵ��ÿ��ָ��
                    for(i=0;i<n;i++)
                    {
                        pointer2[i]=&stu[i];
                    }
                    student *pointer3[N];       //����һ���յ�ָ�������Թ��鲢���к���ʹ��
                    int w=1;                //û�м���ѧ��ƽ���ֺ��ܷ�ʱ�����������µ��ò˵�������ѡ��
                    for(i=0;i<n;i++)
                    {
                        if(pointer2[i]->total!=0)
                            w=0;
                    }
                    if(w==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                        Sleep(2800);
                        menu();
                        scanf("%d",&a);
                        while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                        {
                            printf("Please enter your choice:(a>-1 and a<12)\n");
                            scanf("%d",&a);
                        }
                        break;
                    }
                    ascending_mergeSort(pointer2,pointer3,0,n-1);         //���ù鲢���к�����������
                    for(i=n-1,j=0;i>=0;i--,j++)
                    {
                        pointer2[j]->order=i+1;
                    }
                    printf("the league tables of student total score in ascending order is\n");           //������α�
                    printf_put(pointer2);
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 6:          //��ѧ�Ŵ�С������α�
                {
                    student *pointer4[N];       //����ָ�����飬��ÿ�����ݵ�ַ��ֵ��ÿ��ָ��
                    for(i=0;i<n;i++)
                    {
                        pointer4[i]=&stu[i];
                    }
                    ascending_insertion_sort(pointer4);    //������������ѧ�ŵ�ֱ�Ӳ���������
                    int w=1;                //û�м���ѧ��ƽ���ֺ��ܷ�
                    for(i=0;i<n;i++)
                    {
                        if(pointer4[i]->total!=0)
                            w=0;
                    }
                    if(w==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                    }
                    printf("the league tables of studentID in ascending order is\n");           //������α�
                    printf_put(pointer4);
                    if(w==1)
                    {
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                    }
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 7:       //�������ֵ����ű�
                {
                    student *pointer5[N];       //����ָ�����飬��ÿ�����ݵ�ַ��ֵ��ÿ��ָ��
                    for(i=0;i<n;i++)
                    {
                        pointer5[i]=&stu[i];
                    }
                    bubble_name_sort(pointer5);
                    int w=1;                //û�м���ѧ��ƽ���ֺ��ܷ�
                    for(i=0;i<n;i++)
                    {
                        if(pointer5[i]->total!=0)
                            w=0;
                    }
                    if(w==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                    }
                    printf("the league tables of studentID in ascending order is\n");           //������α�
                    printf_put(pointer5);
                    if(w==1)
                    {
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                    }
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 8:         //����ģ����ѯ��ѧ�Ų�ѯѧ�����������Գɼ�
                {
                    student *pointer6[N];       //����ָ�����飬��ÿ�����ݵ�ַ��ֵ��ÿ��ָ��
                    for(i=0;i<n;i++)
                    {
                        pointer6[i]=&stu[i];
                    }
                    int w=1,qw=1;                //û�м���ѧ��ƽ���ֺ��ܷ�
                    for(i=0;i<n;i++)
                    {
                        if(pointer6[i]->total!=0)
                            w=0;
                        if(pointer6[i]->order!=0)
                            qw=0;
                    }
                    if(w==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                    }
                    if(qw==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not order the total score  score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not order the total score  score!!!!!!!----------\n");
                        printf("\n");
                    }
                    vague_searching_studentID(pointer6);      //����ģ����ѯ����
                    if(w==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                    }
                    if(qw==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not order the total score  score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not order the total score  score!!!!!!!----------\n");
                        printf("\n");
                    }
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 9:
                {
                    student *pointer7[N];       //����ָ�����飬��ÿ�����ݵ�ַ��ֵ��ÿ��ָ��
                    for(i=0;i<n;i++)
                    {
                        pointer7[i]=&stu[i];
                    }
                    int w=1,qw=1;                //û�м���ѧ��ƽ���ֺ��ܷ�
                    for(i=0;i<n;i++)
                    {
                        if(pointer7[i]->total!=0)
                            w=0;
                        if(pointer7[i]->order!=0)
                            qw=0;
                    }
                    if(w==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                    }
                    if(qw==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not order the total score  score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not order the total score  score!!!!!!!----------\n");
                        printf("\n");
                    }
                    vague_searching_name(pointer7);      //����ģ����ѯ����
                    if(w==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                    }
                    if(qw==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not order the total score  score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not order the total score  score!!!!!!!----------\n");
                        printf("\n");
                    }
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 10:          //ͳ�Ƹ��γ̸��ȼ��������Ͱٷֱ�
                {
                    int level[N][5],i,j;
                    float percentage[N][5];
                    student *pointer8[N];       //����ָ�����飬��ÿ�����ݵ�ַ��ֵ��ÿ��ָ��
                    for(i=0;i<n;i++)
                    {
                        pointer8[i]=&stu[i];
                    }
                    sort_in_type(pointer8,level,percentage);
                    for(i=0;i<m;i++)
                    {
                        printf("course%d    level            number      percentage\n",i+1);
                        printf("           excellent(A)      %2d         %.2f%%\n",level[i][0],percentage[i][0]*100);
                        printf("           good(B)           %2d         %.2f%%\n",level[i][1],percentage[i][1]*100);
                        printf("           medium(C)         %2d         %.2f%%\n",level[i][2],percentage[i][2]*100);
                        printf("           pass(D)           %2d         %.2f%%\n",level[i][3],percentage[i][3]*100);
                        printf("           fail(E)           %2d         %.2f%%\n",level[i][4],percentage[i][4]*100);
                    }
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 11:      //��ӡѧ����Ϣ
                {
                    student *pointer9[N];       //����ָ�����飬��ÿ�����ݵ�ַ��ֵ��ÿ��ָ��
                    for(i=0;i<n;i++)
                    {
                        pointer9[i]=&stu[i];
                    }
                    int w=1;                //û�м���ѧ��ƽ���ֺ��ܷ�
                    for(i=0;i<n;i++)
                    {
                        if(pointer9[i]->total!=0)
                            w=0;
                    }
                    if(w==1)
                    {
                        printf("\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                    }
                    printf("the league tables is\n");           //������α�
                    printf_put(pointer9);
                    course_total_aver(stu,course_total,corse_aver);      //���ü���γ�ƽ���ֺ��ֵܷĺ���
                    for(i=0;i<m;i++)          //��ӡ�γ�ƽ���ֺ��ܷ�
                    {
                        printf("the total score of course %d is          %ld\n",i+1,course_total[i]);
                        printf("the average score of course %d is        %lf\n",i+1,corse_aver[i]);
                    }
                    if(w==1)
                    {
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("----------!!!!!!!you do not calculate the total score and average score!!!!!!!----------\n");
                        printf("\n");
                    }
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //���������ã�������ֵ�����жϣ���ֹ�Ƿ�ֵ����
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 0:    //�˳�����
                {
                    exit(0);
                }
        }
    }
    return 0;
}

void menu()      //�˵�����
{
    printf("1.Input record\n");
    printf("2.Calculate total and average score of every course\n");
    printf("3.Calculate total and average score of every student\n");
    printf("4.Sort in descending order by total score of every student\n");
    printf("5.Sort in ascending order by total score of every student\n");
    printf("6.Sort in ascending oder by number\n");
    printf("7.Sort in descending oder by number\n");
    printf("8.Search by number\n");
    printf("9.Search by name\n");
    printf("10.Statistic analysis for course\n");
    printf("11.List record\n");
    printf("0.Exit\n");
    printf("Please enter your choice:\n");
}

void readscore(student a[])  //��������¼��ѧ��ѧ�š��������ɼ�
{
    int i,j,l=1;
    while(n>30||n<1)        //��������������ѧ������������ֹ�Ƿ�ֵ����
    {
        printf("Please input the number of student(n<=30)\n");
        scanf("%d",&n);
    }
    while(m<1||m>6)        //��������������γ�����������ֹ�Ƿ�ֵ����
    {
        printf("Please input the number of course(m<=6)\n");
        scanf("%d",&m);
    }
    student1 *head,*pr,*p,*qw;
    p=(student1*)malloc(sizeof(student1));      //����ͷ�ڵ�����
    if (p==NULL)             //�����ڴ�ʧ������ѭ��
    {
        printf("memory is not enough!\n");
        exit(0);
    }
    printf("Please input the ID number of student %d\n",l);
    scanf("%ld",&p->number);
    printf("Please input the name of student %d\n",l);
    getchar();
    gets(p->name);
    printf("Please input the score of student %d (<=100)\n",l);
    for(j=0;j<m;j++)
    {
        scanf("%d",&p->score[j]);
    }
    head=p;
    pr=p;
    pr->next=NULL;
    student1 *p1;
    int k=2;
    while(k<=n)                   //��������ڵ�����
    {
        l++;
        p1=(struct STUDENT1*)malloc(sizeof(struct STUDENT1));
        if(p1==NULL)              //�����ڴ�ʧ������ѭ��
        {
            printf("memory is not enough!\n");
            exit(0);
        }
        printf("Please input the ID number of student %d\n",l);
        scanf("%ld",&p1->number);
        printf("Please input the name of student %d\n",l);
        getchar();
        gets(p1->name);;
        printf("Please input the score of student %d\n",l);
        for(j=0;j<m;j++)
        {
            scanf("%d",&p1->score[j]);
        }
        pr->next=p1;
        pr=p1;
        pr->next=NULL;
        k++;
    }
    for(i=0;i<n;i++)
    {
        a[i].number=head->number;
        strcpy(a[i].name,head->name);
        for(j=0;j<m;j++)
        {
            a[i].score[j]=head->score[j];
        }
        head=head->next;
    }
    for(i=0;i<n;i++)     //�ͷ��ڴ�
    {
        break;
        qw=head->next;
        free(head);
        if(qw==NULL)
        {
            break;
        }
        head=qw;
    }
}

void course_total_aver(student a[],long b[],double c[])      //����γ�ƽ���ֺ��ܷ�
{
    int i,j;
    for(i=0;i<m;i++)
    {
        b[i]=0;
    }
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            b[i]+=a[j].score[i];
        }
    }
    for(i=0;i<m;i++)
    {
        c[i]=(double)b[i]/n;
    }
}

void student_total_aver(student a[],long b[],double c[])     //����ѧ��ƽ���ֺ��ܷ�
{
    int i,j;
    for(i=0;i<n;i++)
    {
        b[i]=0;
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            b[i]+=a[i].score[j];
        }
    }
    for(i=0;i<n;i++)
    {
        c[i]=(double)b[i]/m;
    }
}

void descending_sort(student *p[], int left, int right)  //�ÿ�������ʵ�ֽ������к���
{
    if(left >= right)     //�ж������Ƿ����
    {
        return ;
    }
    int i = left;
    int j = right;
    int key = p[left]->total;    //����һ�����Ƚ�ֵ
    while(i < j)
    {
        while(i < j && key >= p[j]->total)     //����keyֵ��ķ������
        {
            j--;
        }
        p[i]->total = p[j]->total;
        while(i < j && key <= p[i]->total)     //����keyֵС�ķ����ұ�
        {
            i++;
        }
        p[j]->total = p[i]->total;
    }
    p[i]->total = key;       //��keyֵ�����м䣬���һ�����򣨽���key��ķ�����ߣ���ketС�ķ����ұߣ�
    descending_sort(p, left, i - 1);   //�ݹ�ķ������ϵ����������keyֵ��ߵ�����
    descending_sort(p, i + 1, right);  //�ݹ�ķ������ϵ����������keyֵ�ұߵ����� ���ݿ�ͷ���ж������ж������Ƿ���ɣ�����ɣ�����������
}

void ascending_merge(student *sourceArr[],student *tempArr[], int startIndex, int midIndex, int endIndex)    //�鲢���к������Ӻ��������鲢�����������
{
    int i = startIndex, j=midIndex+1, k = startIndex;
    while(i!=midIndex+1 && j!=endIndex+1)
    {
        if(sourceArr[i]->total > sourceArr[j]->total)
            tempArr[k++] = sourceArr[j++];
        else
            tempArr[k++] = sourceArr[i++];
    }
    while(i != midIndex+1)
        tempArr[k++] = sourceArr[i++];
    while(j != endIndex+1)
        tempArr[k++] = sourceArr[j++];
    for(i=startIndex; i<=endIndex; i++)
        sourceArr[i] = tempArr[i];
}

void ascending_mergeSort(student *sourceArr[], student *tempArr[], int startIndex, int endIndex)       //�鲢����������
{
    int midIndex;
    if(startIndex < endIndex)
    {
        midIndex = startIndex + (endIndex-startIndex) / 2;               //�������int
        ascending_mergeSort(sourceArr, tempArr, startIndex, midIndex);             //�ڲ��ݹ����
        ascending_mergeSort(sourceArr, tempArr, midIndex+1, endIndex);
        ascending_merge(sourceArr, tempArr, startIndex, midIndex, endIndex);      //�����Ӻ���
    }
}

void ascending_insertion_sort(student *array[])        //��ѧ���������е�ֱ�Ӳ���������
{
    int i,j;
    student *temp;
    for(i=1;i<n;i++)
    {
        temp=array[i];
        j=i-1;
        while((j>=0)&&(array[j]->number > temp->number))        //�������������һ�Ƚϣ�����tempʱ�������ƺ�
        {
            array[j+1]=array[j];
            j--;
        }

        if(j!=i-1)        //���ڴ���temp����
            array[j+1]=temp;
    }
}

void bubble_name_sort(student *a[])     //���������ֵ������е�ð��������
{
    int i,j;
    student *temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if(strcmp(a[j]->name,a[j+1]->name)>0)
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}

void printf_put(student *a[])      //��ӡ�ɼ���ĺ���
{
        int i,j;
        printf("     studentID         name          score                   total score        average score       order\n");
        for(i=0;i<n;i++)
        {
            if(i<9)
            {
                printf("%d   ",i+1);
                printf(" %10ld%13s      ",a[i]->number,a[i]->name);
            }
            else
            {
                printf("%d   ",i+1);
                printf("%10ld%13s      ",a[i]->number,a[i]->name);
            }
            for(j=0;j<m;j++)
            {
                printf("%4d",a[i]->score[j]);
            }
            if(m<=3)
                printf("              ");
            printf("%12d             ",a[i]->total);
            printf("%8.4lf",a[i]->aver);
            printf("%13d",a[i]->order);
            printf("\n");
        }
        printf("\n");
}

void sort_in_type(student *a[], int level[][5], float percentage[][5])      //���ȼ���ÿ�ſγ�ÿ�������������з���ͳ��
{
    int i,j;
    for(i=0;i<m;i++)           //��ʼ����ά����level,ʹ��ȫΪ0
    {
        for(j=0;j<5;j++)
        {
            level[i][j]=0;
        }
    }
    for(i=0;i<m;i++)         //ͳ��ÿ�ſγ�ÿ����������
    {
        for(j=0;j<n;j++)
        {
            if(a[j]->score[i]>=90&&a[j]->score[i]<=100)
                level[i][0]++;
            else if(a[j]->score[i]>=80&&a[j]->score[i]<=89)
                level[i][1]++;
            else if(a[j]->score[i]>=70&&a[j]->score[i]<=79)
                level[i][2]++;
            else if(a[j]->score[i]>=60&&a[j]->score[i]<=69)
                level[i][3]++;
            else
                level[i][4]++;
        }
    }
    for(i=0;i<m;i++)        //����ÿ�ſγ�ÿ������������ռ�ı���
    {
        for(j=0;j<5;j++)
        {
            percentage[i][j]=(float)level[i][j]/n;
        }
    }
}

void vague_searching_studentID(student *a[])      //����ģ����ѯʵ�ְ�ѧ�Ų�ѯѧ���ɼ�
{
    int i,j;
    long d[N];
    for(i=0;i<n;i++)      //��ѧ�������ֵ���ά������
    {
        d[i]=a[i]->number;
    }
    char e[N][20];
    int wo=0;
    for(i=0;i<n;i++)
    {
        ltoa(d[i],e[i],10);  //���ú�������long�͵�ѧ��ת��Ϊchar��
    }
    char find[20];
    int flag=1;
    getchar();
    printf("please input the studentID of the student which you want to find\n");
    fgets(find, 19, stdin);  //��ֹ����ֵ����
              //ģ����ѯ������ʼ
    for(i=0;i<n;i++)
    {
        flag=1;
        char *res;
        res=IND(e[i],find);     //ģ������
        if(res==NULL)    //û�в�ѯ����������һ��
        {
            continue;
        }
        else
        {
            flag=2;
        }
        if (flag==2)    //�ҵ�ʱ����ӡѧ����Ϣ
        {
            printf("\n");
            printf("studentID         name          score                   total score        average score       order\n");
            printf("%10ld%13s      ",a[i]->number,a[i]->name);
            for(j=0;j<m;j++)
            {
                printf("%4d",a[i]->score[j]);
            }
            if(m<=3)
                printf("              ");
            printf("%12d             ",a[i]->total);
            printf("%8.4lf",a[i]->aver);
            printf("%13d",a[i]->order);
            printf("\n");
            wo=1;     //�ж��Ƿ������ҵ���������Ϣ��ѧ��
            flag=1;
        }
    }
    if(wo==0)
    {
        printf("\n");
        printf("there is not a student whose studentID is %s",find);
        printf("\n");
    }
}

void vague_searching_name(student *a[])      //����ģ����ѯʵ�ְ�������ѯѧ���ɼ�
{
    int i,j;
    char find[20];
    int flag=1;
    int wo=0;
    getchar();
    printf("please input the name of the student which you want to find\n");
    fgets(find, 19, stdin);  //��ֹ����ֵ����
    char *res;          //ģ����ѯ������ʼ
    for(i=0;i<n;i++)
    {
        flag=1;
        res=IND(a[i]->name,find);     //ģ������
        if(res==NULL)    //û�в�ѯ����������һ��
        {
            continue;
        }
        else
        {
            flag=2;
        }
        if (flag==2)    //�ҵ�ʱ����ӡѧ����Ϣ
        {
            printf("\n");
            printf("studentID         name          score                   total score        average score       order\n");
            printf("%10ld%13s      ",a[i]->number,a[i]->name);
            for(j=0;j<m;j++)
            {
                printf("%4d",a[i]->score[j]);
            }
            if(m<=3)
                printf("              ");
            printf("%12d             ",a[i]->total);
            printf("%8.4lf",a[i]->aver);
            printf("%13d",a[i]->order);
            printf("\n");
            wo=1;     //�ж��Ƿ������ҵ���������Ϣ��ѧ��
        }
    }
    if(wo==0)
    {
        printf("\n");
        printf("there do not exit such a student !");
        printf("\n");
    }
}

char * IND(char * str, char * substr) //ģ����ѯ����
{
    assert(substr != NULL && str != NULL);
    char * psub = substr;
    char * pstr = str;

    while (*pstr)
    {

        char * tmp = pstr;
        while (*tmp++ == *psub++);

        if (*psub == '\0')
            return pstr;

        psub = substr;
        pstr++;
    }

    return NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include<assert.h>
#define N 30
#define COURSE 6
int n=100,m=100;     //定义全局变量，减少其他函数调用时的入口数据个数
typedef struct STUDENT             //结构体类型声明；
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
void menu();                           //函数原型声明
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

int main()                  //主函数
{
    long course_total[COURSE],student_total[N];
    double corse_aver[COURSE],student_aver[N];
    int order[N];
    student stu[N];
    menu();        //调用菜单函数
    int a,i,j;
    for(i=0;i<N;i++)   //初始化
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
    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
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
    while(a!=0)      //当输入不是0时，进行菜单选择
    {
        switch(a)
        {
            case 1:           //输入学生数据
                {
                    readscore(stu);     //调用函数输入学生数据
                    for(i=0;i<n;i++)         //将平均分和总分录入结构体数组
                    {
                        stu[i].total=student_total[i];
                        stu[i].aver=student_aver[i];
                        stu[i].order=order[i];
                    }
                    printf("\n");
                    Sleep(800);  //停滞0.8秒，防止调用菜单函数过快
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 2:           //计算课程平均分和总分
                {
                    course_total_aver(stu,course_total,corse_aver);      //调用计算课程平均分和总分的函数
                    for(i=0;i<m;i++)          //打印课程平均分和总分
                    {
                        printf("the total score of course %d is             %ld\n",i+1,course_total[i]);
                        printf("the average score of course %d is           %lf\n",i+1,corse_aver[i]);
                    }
                    printf("\n");
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 3:          //计算学生平均分和总分
                {
                    student_total_aver(stu,student_total,student_aver);         //调用计算学生平均分和总分的函数
                    for(i=0;i<n;i++)
                    {
                        printf("the total score of student %d is %ld\n",i+1,student_total[i]);       //打印学生平均分和总分
                        printf("the average score of student %d is %.4lf\n",i+1,student_aver[i]);
                    }
                    for(i=0;i<n;i++)         //将平均分和总分录入结构体数组
                    {
                        stu[i].total=student_total[i];
                        stu[i].aver=student_aver[i];
                    }
                    printf("\n");
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 4:         //调用快速排列函数，按每个学生总分由高到低输出名次表
                {
                    student *pointer1[N];       //定义指针数组，将每个数据地址赋值于每个指针
                    for(i=0;i<n;i++)
                    {
                        pointer1[i]=&stu[i];
                    }
                    int w=1;                //没有计算学生平均分和总分时操作错误，重新调用菜单，重新选择
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
                        while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                        {
                            printf("Please enter your choice:(a>-1 and a<12)\n");
                            scanf("%d",&a);
                        }
                        break;
                    }
                    descending_sort(pointer1,0,n-1);    //调用降序排列的快速排列算法
                    for(i=0;i<n;i++)
                    {
                        pointer1[i]->order=i+1;
                    }
                    printf("the league tables of student total score in descending order is\n");           //输出名次表
                    printf_put(pointer1);
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 5:          //调用归并排列函数，按每个学生总分由低到高输出名次表
                {
                    student *pointer2[N];       //定义指针数组，将每个数据地址赋值于每个指针
                    for(i=0;i<n;i++)
                    {
                        pointer2[i]=&stu[i];
                    }
                    student *pointer3[N];       //定义一个空的指针数组以供归并排列函数使用
                    int w=1;                //没有计算学生平均分和总分时操作错误，重新调用菜单，重新选择
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
                        while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                        {
                            printf("Please enter your choice:(a>-1 and a<12)\n");
                            scanf("%d",&a);
                        }
                        break;
                    }
                    ascending_mergeSort(pointer2,pointer3,0,n-1);         //调用归并排列函数升序排列
                    for(i=n-1,j=0;i>=0;i--,j++)
                    {
                        pointer2[j]->order=i+1;
                    }
                    printf("the league tables of student total score in ascending order is\n");           //输出名次表
                    printf_put(pointer2);
                    Sleep(800);
                    menu();
                    scanf("%d",&a);
                    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 6:          //按学号大小输出名次表
                {
                    student *pointer4[N];       //定义指针数组，将每个数据地址赋值于每个指针
                    for(i=0;i<n;i++)
                    {
                        pointer4[i]=&stu[i];
                    }
                    ascending_insertion_sort(pointer4);    //调用升序排列学号的直接插入排序函数
                    int w=1;                //没有计算学生平均分和总分
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
                    printf("the league tables of studentID in ascending order is\n");           //输出名次表
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
                    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 7:       //按姓名字典序排表
                {
                    student *pointer5[N];       //定义指针数组，将每个数据地址赋值于每个指针
                    for(i=0;i<n;i++)
                    {
                        pointer5[i]=&stu[i];
                    }
                    bubble_name_sort(pointer5);
                    int w=1;                //没有计算学生平均分和总分
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
                    printf("the league tables of studentID in ascending order is\n");           //输出名次表
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
                    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 8:         //利用模糊查询按学号查询学生排名及考试成绩
                {
                    student *pointer6[N];       //定义指针数组，将每个数据地址赋值于每个指针
                    for(i=0;i<n;i++)
                    {
                        pointer6[i]=&stu[i];
                    }
                    int w=1,qw=1;                //没有计算学生平均分和总分
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
                    vague_searching_studentID(pointer6);      //调用模糊查询函数
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
                    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 9:
                {
                    student *pointer7[N];       //定义指针数组，将每个数据地址赋值于每个指针
                    for(i=0;i<n;i++)
                    {
                        pointer7[i]=&stu[i];
                    }
                    int w=1,qw=1;                //没有计算学生平均分和总分
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
                    vague_searching_name(pointer7);      //调用模糊查询函数
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
                    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 10:          //统计各课程各等级的人数和百分比
                {
                    int level[N][5],i,j;
                    float percentage[N][5];
                    student *pointer8[N];       //定义指针数组，将每个数据地址赋值于每个指针
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
                    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 11:      //打印学生信息
                {
                    student *pointer9[N];       //定义指针数组，将每个数据地址赋值于每个指针
                    for(i=0;i<n;i++)
                    {
                        pointer9[i]=&stu[i];
                    }
                    int w=1;                //没有计算学生平均分和总分
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
                    printf("the league tables is\n");           //输出名次表
                    printf_put(pointer9);
                    course_total_aver(stu,course_total,corse_aver);      //调用计算课程平均分和总分的函数
                    for(i=0;i<m;i++)          //打印课程平均分和总分
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
                    while(a>12||a<0)   //防御性设置，对输入值进行判断，防止非法值输入
                    {
                        printf("Please enter your choice:(a>-1 and a<12)\n");
                        scanf("%d",&a);
                    }
                    break;
                }
            case 0:    //退出程序
                {
                    exit(0);
                }
        }
    }
    return 0;
}

void menu()      //菜单函数
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

void readscore(student a[])  //利用链表录入学生学号、姓名、成绩
{
    int i,j,l=1;
    while(n>30||n<1)        //函数防御，输入学生数量，并防止非法值输入
    {
        printf("Please input the number of student(n<=30)\n");
        scanf("%d",&n);
    }
    while(m<1||m>6)        //函数防御，输入课程数量，并防止非法值输入
    {
        printf("Please input the number of course(m<=6)\n");
        scanf("%d",&m);
    }
    student1 *head,*pr,*p,*qw;
    p=(student1*)malloc(sizeof(student1));      //输入头节点数据
    if (p==NULL)             //申请内存失败跳出循环
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
    while(k<=n)                   //输入后续节点数据
    {
        l++;
        p1=(struct STUDENT1*)malloc(sizeof(struct STUDENT1));
        if(p1==NULL)              //申请内存失败跳出循环
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
    for(i=0;i<n;i++)     //释放内存
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

void course_total_aver(student a[],long b[],double c[])      //计算课程平均分和总分
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

void student_total_aver(student a[],long b[],double c[])     //计算学生平均分和总分
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

void descending_sort(student *p[], int left, int right)  //用快速排序实现降序排列函数
{
    if(left >= right)     //判断排序是否完成
    {
        return ;
    }
    int i = left;
    int j = right;
    int key = p[left]->total;    //设置一个被比较值
    while(i < j)
    {
        while(i < j && key >= p[j]->total)     //将比key值大的放在左边
        {
            j--;
        }
        p[i]->total = p[j]->total;
        while(i < j && key <= p[i]->total)     //将比key值小的放在右边
        {
            i++;
        }
        p[j]->total = p[i]->total;
    }
    p[i]->total = key;       //将key值放在中间，完成一次排序（将比key大的放在左边，比ket小的放在右边）
    descending_sort(p, left, i - 1);   //递归的方法不断调用自身，完成key值左边的排序
    descending_sort(p, i + 1, right);  //递归的方法不断调用自身，完成key值右边的排序 根据开头的判断条件判断排序是否完成，若完成，则跳出函数
}

void ascending_merge(student *sourceArr[],student *tempArr[], int startIndex, int midIndex, int endIndex)    //归并排列函数的子函数，供归并函数主体调用
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

void ascending_mergeSort(student *sourceArr[], student *tempArr[], int startIndex, int endIndex)       //归并排序函数主体
{
    int midIndex;
    if(startIndex < endIndex)
    {
        midIndex = startIndex + (endIndex-startIndex) / 2;               //避免溢出int
        ascending_mergeSort(sourceArr, tempArr, startIndex, midIndex);             //内部递归调用
        ascending_mergeSort(sourceArr, tempArr, midIndex+1, endIndex);
        ascending_merge(sourceArr, tempArr, startIndex, midIndex, endIndex);      //调用子函数
    }
}

void ascending_insertion_sort(student *array[])        //按学号升序排列的直接插入排序函数
{
    int i,j;
    student *temp;
    for(i=1;i<n;i++)
    {
        temp=array[i];
        j=i-1;
        while((j>=0)&&(array[j]->number > temp->number))        //与已排序的数逐一比较，大于temp时，该数移后
        {
            array[j+1]=array[j];
            j--;
        }

        if(j!=i-1)        //存在大于temp的数
            array[j+1]=temp;
    }
}

void bubble_name_sort(student *a[])     //按姓名的字典序排列的冒泡排序函数
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

void printf_put(student *a[])      //打印成绩表的函数
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

void sort_in_type(student *a[], int level[][5], float percentage[][5])      //按等级对每门课程每个类别的人数进行分类统计
{
    int i,j;
    for(i=0;i<m;i++)           //初始化二维数组level,使其全为0
    {
        for(j=0;j<5;j++)
        {
            level[i][j]=0;
        }
    }
    for(i=0;i<m;i++)         //统计每门课程每个类别的人数
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
    for(i=0;i<m;i++)        //计算每门课程每个类别的人数所占的比例
    {
        for(j=0;j<5;j++)
        {
            percentage[i][j]=(float)level[i][j]/n;
        }
    }
}

void vague_searching_studentID(student *a[])      //利用模糊查询实现按学号查询学生成绩
{
    int i,j;
    long d[N];
    for(i=0;i<n;i++)      //将学号逆序拆分到二维数组中
    {
        d[i]=a[i]->number;
    }
    char e[N][20];
    int wo=0;
    for(i=0;i<n;i++)
    {
        ltoa(d[i],e[i],10);  //调用函数，将long型的学号转换为char型
    }
    char find[20];
    int flag=1;
    getchar();
    printf("please input the studentID of the student which you want to find\n");
    fgets(find, 19, stdin);  //防止多余值输入
              //模糊查询函数开始
    for(i=0;i<n;i++)
    {
        flag=1;
        char *res;
        res=IND(e[i],find);     //模糊查找
        if(res==NULL)    //没有查询到，查找下一个
        {
            continue;
        }
        else
        {
            flag=2;
        }
        if (flag==2)    //找到时，打印学生信息
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
            wo=1;     //判断是否曾经找到过符合信息的学生
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

void vague_searching_name(student *a[])      //利用模糊查询实现按姓名查询学生成绩
{
    int i,j;
    char find[20];
    int flag=1;
    int wo=0;
    getchar();
    printf("please input the name of the student which you want to find\n");
    fgets(find, 19, stdin);  //防止多余值输入
    char *res;          //模糊查询函数开始
    for(i=0;i<n;i++)
    {
        flag=1;
        res=IND(a[i]->name,find);     //模糊查找
        if(res==NULL)    //没有查询到，查找下一个
        {
            continue;
        }
        else
        {
            flag=2;
        }
        if (flag==2)    //找到时，打印学生信息
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
            wo=1;     //判断是否曾经找到过符合信息的学生
        }
    }
    if(wo==0)
    {
        printf("\n");
        printf("there do not exit such a student !");
        printf("\n");
    }
}

char * IND(char * str, char * substr) //模糊查询函数
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

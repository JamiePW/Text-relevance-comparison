#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char stopword[10000000][40],diction[10000000][40];//�������ʱ�
int stoptop=0,dictop=0;//����������ʱ�Ķ���
struct statis
{
    char word[40];
    int count;
}result1[10000000],result2[10000000],exchange;//exchange��������ʱ����˳��
int top1=0,top2=0;//����Ѿ�ͳ�Ƶĵ��ʵĸ���

int b_search (char wordlist[][40], char obj[], int top)//���ֲ��Һ������ҵ�����λ�ã�û�ҵ�����-1
{
    int high,low,mid;
    low=0;
    high=top-1;
    mid=(low+high)/2;
    while (low<=high)
    {
        mid=(high+low)/2;
        if (strcmp(obj,wordlist[mid])==0)
            return mid;
        else if (strcmp(obj,wordlist[mid])>0)
            low=mid+1;
        else if (strcmp(obj,wordlist[mid])<0)
            high=mid-1;
    }
    return -1;
}

int r_search (struct statis r[], char obj[], int top)//�ҵ�����λ�ã����򷵻�-1���������˳�����
{
    int i;
    for (i=0;i<top;i++)
    {
        if (strcmp(obj,r[i].word)==0)
            return i;
    }
    return -1;
}
int main()
{
    FILE *dic,*stop,*a1,*a2,*out;
    dic=fopen("dictionary.txt","r");
    stop=fopen("stopwords.txt","r");
    a1=fopen("article1.txt","r");
    a2=fopen("article2.txt","r");
    out=fopen("results.txt","w");

    int i,j,k,N;
    char tem[100],c;
    double pro1,pro2,sim;
    long long up,down;//����proʱup�Ƿ��ӣ�down�Ƿ�ĸ

    for (;fscanf(dic,"%s",&diction[dictop])!=EOF;dictop++);//��¼���������ʱ�
    for (;fscanf(stop,"%s",&stopword[stoptop])!=EOF;stoptop++);
    scanf("%d",&N);//����N

    while ((c=fgetc(a1))!=EOF)//ͳ�Ƶ�һƪ���µĴ�Ƶ
    {
        if (isalpha(c)!=0)//�����Ӣ����ĸ���ͼ�������ȥ������һ������
        {
            i=0;
            tem[i]=tolower(c);
            i++;
            while (isalpha(c=fgetc(a1))!=0)
            {
                tem[i]=tolower(c);
                i++;
            }
            tem[i]='\0';
            if (b_search(stopword,tem,stoptop)==-1&&b_search(diction,tem,dictop)!=-1)//����ͣ�ôʶ������ֵ��еĴʲŻᴦ��
            {
                if (r_search(result1,tem,top1)==-1)//�����û��ͳ�ƹ����Ͳ���
                {
                    strcpy(result1[top1].word,tem);
                    result1[top1].count++;
                    top1++;
                }
                else if (r_search(result1,tem,top1)!=-1)
                    result1[r_search(result1,tem,top1)].count++;
            }
        }
    }

    for (i=0;i<top1-1;i++)//�Խ��1��������
    {
        for (j=0;j<top1-1-i;j++)
        {
            if ( result1[j].count < result1[j+1].count || (result1[j].count == result1[j+1].count && strcmp(result1[j].word,result1[j+1].word)>0))//����Ƶ�Ӹߵ��ͣ��ֵ���
            {
                exchange=result1[j];
                result1[j]=result1[j+1];
                result1[j+1]=exchange;
            }
        }
    }

    while ((c=fgetc(a2))!=EOF)//ͳ�Ƶڶ�ƪ���µĴ�Ƶ
    {
        if (isalpha(c)!=0)//�����Ӣ����ĸ���ͼ�������ȥ������һ������
        {
            i=0;
            tem[i]=tolower(c);
            i++;
            while (isalpha(c=fgetc(a2))!=0)
            {
                tem[i]=tolower(c);
                i++;
            }
            tem[i]='\0';
            if (b_search(stopword,tem,stoptop)==-1&&b_search(diction,tem,dictop)!=-1)//����ͣ�ôʶ������ֵ��еĴʲŻᴦ��
            {
                if (r_search(result2,tem,top2)==-1)//�����û��ͳ�ƹ����Ͳ���
                {
                    strcpy(result2[top2].word,tem);
                    result2[top2].count++;
                    top2++;
                }
                else if (r_search(result2,tem,top2)!=-1)
                    result2[r_search(result2,tem,top2)].count++;
            }
        }
    }

    for (i=0;i<top2-1;i++)//�Խ��2��������
    {
        for (j=0;j<top2-1-i;j++)
        {
            if ( result2[j].count < result2[j+1].count || (result2[j].count == result2[j+1].count && strcmp(result2[j].word,result2[j+1].word)>0))//����Ƶ�Ӹߵ��ͣ��ֵ���
            {
                exchange=result2[j];
                result2[j]=result2[j+1];
                result2[j+1]=exchange;
            }
        }
    }

    if (N>top1)
        N=top1;
    if (N>top2)
        N=top2;

    //����pro1
    up=0;
    down=0;//��ʼ��
    for (i=0;i<N;i++)//�����ĸ�ͷ���
    {
        down=down+result1[i].count;
        if (r_search(result2,result1[i].word,N)!=-1)//����ǹ��еĵ��ʣ������ӷ���
            up=up+result1[i].count;
    }
    pro1=((double)up)/((double)down);

    //����pro2
    up=0;
    down=0;//��ʼ��
    for (i=0;i<N;i++)//�����ĸ�ͷ���
    {
        down=down+result2[i].count;
        if (r_search(result1,result2[i].word,N)!=-1)//����ǹ��еĵ��ʣ������ӷ���
            up=up+result2[i].count;
    }
    pro2=((double)up)/((double)down);

    if (pro1>pro2)
        sim=pro2/pro1;
    else
        sim=pro1/pro2;

    //printf("%.5f\n",pro1);
    //printf("%.5f\n",pro2);
    printf("%.5f",sim);

    fprintf(out,"%.5f\n",sim);
    fprintf(out,"\n");
    for (i=0;i<N;i++)
        fprintf(out,"%s %d\n",result1[i].word,result1[i].count);
    fprintf(out,"\n");
    for (i=0;i<N;i++)
        fprintf(out,"%s %d\n",result2[i].word,result2[i].count);

    fclose(dic);
    fclose(stop);
    fclose(a1);
    fclose(a2);
    fclose(out);
    return 0;
}

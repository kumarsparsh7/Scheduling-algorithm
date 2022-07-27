#include <bits/stdc++.h>
using namespace std;
struct Process
{
    int p; // Process ID
    int bt; // Burst Time
    int at; // Arrival Time
    int rt; // Remaining Burst Time
    int wt; // Waiting Time
    int tat; //Turn Around Time
}
p[20], temp, org[20];
struct comp
{
    char algo[20];
    float avg_wt;
    float avg_tat;
}algo[20];

void menu();
void input();
void assign();
void comparator();

void fcfs(int);
void rr(int);
void irr(int);
void irrsjf(int);
void irrsjfdtq(int);

int n;

int main()
{
    cout<<"############################### WELCOME TO OS PROJECT ###############################\n\n";
    menu();
    return 0;
}

void menu()
{
    int ch;
    printf("\n\nTable\n\n1.New Input\n2.FCFS Algorithm\n3.RR Algorithm\n4.IRR Algorithm\n5.IRR_SJF Algorithm\n6.IRR_SJF_DTQ Algorithm\n7.Compare All\n8.Exit");
    printf("\n\nEnter your choice from the above table : ");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:input();break;
        case 2:fcfs(1);break;
        case 3:rr(1);break;
        case 4:irr(1);break;
        case 5:irrsjf(1);break;
        case 6:irrsjfdtq(1);break;
        case 7:comparator();break;
        case 8:exit(0);break;
        default: printf("\n\nPlease enter choice from 1 to 8 only\n");
        menu();
    }
}

void input()
{
    cout<<"\nEnter Number of processes : ";
    cin>>n;
    cout<<"\n\nEnter the Arrival Time of the Processes : \n";
    for(int i=0; i<n; i++)
    {
        cout<<"Process "<<i+1<<" : ";
        cin>>org[i].at;
        org[i].p=i+1;
    }
    cout<<"\n\nEnter the Burst Time of the Processes : \n"; 
    for(int i=0;i<n;i++)
    {
        cout<<"Process "<<i+1<<" : ";
        cin>>org[i].bt;
        org[i].rt=org[i].bt;
    }
    menu();
}

void sort_at()
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(p[j].at>p[j+1].at)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void assign()
{
    for(int i=0; i<n; i++)
        p[i]=org[i];
}

void fcfs(int menu_flag)
{
    cout<<"\n\n############# First Come First Serve #############\n\n";
    assign();
    sort_at();
    int sum=0, tot_tat=0, tot_wt=0;
    for(int i=0; i<n; i++)
    {
        p[i].wt=sum-p[i].at;
        if(p[i].wt<0)
            p[i].wt=0;
        p[i].tat=p[i].bt+p[i].wt;
        sum+=p[i].bt;
        tot_tat+=p[i].tat;
        tot_wt+=p[i].wt;
    }
    cout<<"Process Burst Time Arrival Time Waiting Time Turn Around Time\n";
    for(int i=0; i<n; i++)
        cout<<"     "<<p[i].p<<"\t\t"<<p[i].bt<<"\t\t"<<p[i].at<<"\t\t"<<p[i].wt<<"\t\t"<<p[i].tat<<"\n";
    cout<<"\nAverage Waiting Time = "<<(float)tot_wt/n;
    cout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n";
    strcpy(algo[0].algo,"fcfs");
    algo[0].avg_tat=(float)tot_tat/n;
    algo[0].avg_wt=(float)tot_wt/n;
    if(menu_flag)
        menu();
}

void rr(int menu_flag) 
{ 
    cout<<"\n\n############# Round Robin #############\n\n";
    assign();
    int remain=n, time_quantum, tot_wt=0, tot_tat=0, flag=0; 
    sort_at();
    cout<<"\nEnter Time Quantum : "; 
    cin>>time_quantum; 
    for(int i=0,time=0; remain!=0;) 
    { 
        if(p[i].rt<=time_quantum && p[i].rt>0) 
        { 
            time+=p[i].rt; 
            p[i].rt=0; 
            flag=1; 
        } 
        else if(p[i].rt>0) 
        { 
            p[i].rt-=time_quantum; 
            time+=time_quantum; 
        } 
        if(p[i].rt==0 && flag==1) 
        { 
            remain--; 
            p[i].wt=time-p[i].at-p[i].bt;
            p[i].tat=time-p[i].at;
            tot_wt+=p[i].wt; 
            tot_tat+=p[i].tat; 
            flag=0; 
        } 
        if(i==n-1) 
            i=0; 
        else if(p[i+1].at<=time) 
            i++; 
        else 
            i=0; 
    } 
    cout<<"Process Burst Time Arrival Time Waiting Time Turn Around Time\n";
    for(int i=0; i<n; i++)
        cout<<"    "<<p[i].p<<"\t\t"<<p[i].bt<<"\t\t"<<p[i].at<<"\t\t"<<p[i].wt<<"\t\t"<<p[i].tat<<"\n";
    cout<<"\nAverage Waiting Time = "<<(float)tot_wt/n;
    cout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
    strcpy(algo[1].algo,"rr");
    algo[1].avg_tat=(float)tot_tat/n;
    algo[1].avg_wt=(float)tot_wt/n;
    if(menu_flag)
        menu();
}
void irr(int menu_flag) 
{ 
    cout<<"\n\n############# Improved Round Robin #############\n\n";
    assign();
    int remain=n, rt[n], time_quantum, tot_wt=0, tot_tat=0, flag=0; 
    sort_at();
    for(int i=0; i<n; i++) 
        rt[p[i].p-1]=p[p[i].p-1].bt;
    cout<<"\nEnter Time Quantum : "; 
    cin>>time_quantum; 
    for(int i=0,time=0; remain!=0;) 
    { 
        if(p[i].rt<=time_quantum && p[i].rt>0) 
        { 
            time+=p[i].rt; 
            p[i].rt=0; 
            flag=1; 
        } 
        else if(p[i].rt>time_quantum && p[i].rt>0 && time_quantum*2-p[i].rt>=0)
        { 
            time+=p[i].rt; 
            p[i].rt=0; 
            flag=1; 
        } 
        else if(p[i].rt>0) 
        { 
            p[i].rt-=time_quantum; 
            time+=time_quantum; 
        } 
        if(p[i].rt==0 && flag==1) 
        { 
            remain--; 
            p[i].wt=time-p[i].at-p[i].bt;
            p[i].tat=time-p[i].at;
            tot_wt+=p[i].wt; 
            tot_tat+=p[i].tat; 
            flag=0; 
        } 
        if(i==n-1) 
            i=0; 
        else if(p[i+1].at<=time) 
            i++; 
        else 
            i=0; 
    } 
    cout<<"Process Burst Time Arrival Time Waiting Time Turn Around Time\n";
    for(int i=0; i<n; i++)
        cout<<"     "<<p[i].p<<"\t\t"<<p[i].bt<<"\t\t"<<p[i].at<<"\t\t"<<p[i].wt<<"\t\t"<<p[i].tat<<"\n";
    cout<<"\nAverage Waiting Time = "<<(float)tot_wt/n;
    cout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
    strcpy(algo[2].algo,"irr");
    algo[2].avg_tat=(float)tot_tat/n;
    algo[2].avg_wt=(float)tot_wt/n;
    if(menu_flag)
        menu();
}

void irrsjf(int menu_flag)
{
    cout<<"\n\n############# Imporved Roubd Robin Shortest Job First #############\n\n";
    int time_quantum,tot_tat=0, tot_wt=0;
    int remain=n;
    int time=0; 
    int old_mean=0;
    
    cout<<"\nEnter Time Quantum : "; 
    cin>>time_quantum;
    
    for(int i=0; i<n; i++)
        p[i].rt=p[i].bt;
    while(remain>0)
    {
        //sorting in ascending order
        for(int i=0;i<n;i++)
            for(int j=0;j<n-i-1;j++)
                if(p[j].rt>p[j+1].rt)
                {
                    temp=p[j+1];
                    p[j+1]=p[j];
                    p[j]=temp;
                }
        for(int i=0;i<n;i++) //loop main
        {
            if(p[i].at<=time && p[i].rt!=0)
            {
                if(p[i].rt<time_quantum && p[i].rt!=0)
                {
                    time+=p[i].rt;
                    p[i].rt=0;
                }
                else if(p[i].rt>time_quantum && p[i].rt>0 && time_quantum*2-p[i].rt>=0)
                { 
                    time+=p[i].rt; 
                    p[i].rt=0; 
                }
                else
                {
                    time+=time_quantum;
                    p[i].rt-=time_quantum;
                }
                if(p[i].rt==0)
                {
                    p[i].wt=time-p[i].bt-p[i].at;
                    p[i].tat=time-p[i].at;
                    remain--;
                }
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        tot_wt += p[i].wt;
        tot_tat += p[i].tat; 
    }
    cout<<"Process Burst Time Arrival Time Waiting Time Turn Around Time\n";
    for(int i=0; i<n; i++)
        cout<<"     "<<p[i].p<<"\t\t"<<p[i].bt<<"\t\t"<<p[i].at<<"\t\t"<<p[i].wt<<"\t\t"<<p[i].tat<<"\n";
    cout<<"\nAverage Waiting Time = "<<(float)tot_wt/n;
    cout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
    strcpy(algo[3].algo,"irr_sjf");
    algo[3].avg_tat=(float)tot_tat/n;
    algo[3].avg_wt=(float)tot_wt/n;
    if(menu_flag)
        menu();
}

void irrsjfdtq(int menu_flag)
{
    cout<<"\n\n############# Improved Round Robin Shortest Job First with Dynamic Quantum Time #############\n\n";
    int time_quantum,tot_tat=0, tot_wt=0;
    int remain=n;
    int time=0;
    int max_bt;
    int sum_bt,prq; // prq = process in ready queue
    int old_mean=0;
    
    for(int i=0; i<n; i++)
    {
        p[i].rt=p[i].bt;
        old_mean+=p[i].bt;
    }
    old_mean/=n;
    while(remain>0)
    {
        //sorting in ascending order
        for(int i=0;i<n;i++)
            for(int j=0;j<n-i-1;j++)
                if(p[j].rt>p[j+1].rt)
                {
                    temp=p[j+1];
                    p[j+1]=p[j];
                    p[j]=temp;
                }
        for(int i=0;i<n;i++) //loop main
        {
            prq=0; 
            max_bt=0;
            sum_bt=0;
            for(int j=0;j<n;j++)
            {
                if(p[j].at<=time && p[j].rt!=0)
                {
                    prq++;
                    if(p[j].rt>max_bt)
                        max_bt=p[j].rt;
                    sum_bt+=p[j].rt;
                }
            }
            
            if(prq==0 || (sum_bt/prq) == 0)
                time_quantum = old_mean;
            else
            {
                time_quantum=sum_bt/prq;
                old_mean = time_quantum;
            }
            if(p[i].at<=time && p[i].rt!=0)
            {
                if(p[i].rt<time_quantum && p[i].rt!=0)
                {
                    time+=p[i].rt;
                    p[i].rt=0;
                }
                else if(p[i].rt>time_quantum && p[i].rt>0 && time_quantum*2-p[i].rt>=0)
                { 
                    time+=p[i].rt; 
                    p[i].rt=0; 
                }
                else
                {
                    time+=time_quantum;
                    p[i].rt-=time_quantum;
                }
                
                if(p[i].rt==0)
                {
                    p[i].wt=time-p[i].bt-p[i].at;
                    p[i].tat=time-p[i].at;
                    remain--;
                }
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        tot_wt += p[i].wt;
        tot_tat += p[i].tat; 
    }
    cout<<"Process Burst Time Arrival Time Waiting Time Turn Around Time\n";
    for(int i=0; i<n; i++)
        cout<<" "<<p[i].p<<"\t\t"<<p[i].bt<<"\t\t"<<p[i].at<<"\t\t"<<p[i].wt<<"\t\t"<<p[i].tat<<"\n";
    cout<<"\nAverage Waiting Time = "<<(float)tot_wt/n;
    cout<<"\nAverage Turn Around Time = "<<(float)tot_tat/n<<"\n"; 
    strcpy(algo[4].algo,"irr_sjf_dtq");
    algo[4].avg_tat=(float)tot_tat/n;
    algo[4].avg_wt=(float)tot_wt/n;
    if(menu_flag)
        menu();
}

void comparator()
{
    fcfs(0);
    rr(0);
    irr(0);
    irrsjf(0);
    irrsjfdtq(0);
    cout<<"\n\n############# Comparing All #############\n\n";
    cout<<"\n\n Algorithm\t\tAVG_WT\t\tAVG_TAT\n\n";
    for(int i=0; i<5; i++)
        if(strlen(algo[i].algo)>4)
            cout<<"     "<<algo[i].algo<<"\t\t"<<algo[i].avg_wt<<"\t\t"<<algo[i].avg_tat<<"\n";
        else
            cout<<"     "<<algo[i].algo<<"\t\t\t"<<algo[i].avg_wt<<"\t\t"<<algo[i].avg_tat<<"\n";
    menu();
}

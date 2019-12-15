#include<iostream> 
#include <string.h>      

using namespace  std;    

struct node
{   
    char moves[10];   
   	char edge[100];   
};  
	 
node first,last,open[500000];       
	bool closed[500000]={0}; 
  

 

class Puzzle{

private:

	int head,tail;  
	long Counter;   
	int length;
	
public:
	
	Puzzle()
	{	
		length= 100000;
		Counter=1;
		head=0;
		tail=1;  
	}

 void count(int *r,int *c,node u) 
{   
    int i;   
    
	for(i=0;i<10;i++)   
        if(u.moves[i]=='0')   
        {   
            *r=i/3;*c=i%3;   
            break;   
        }   
}
 
node notpossible()    
{   
    node t;   
    t=open[head++];   
    head=head%length;
    return t;   
} 

int Possiblesteps(node *u,int r,int c,int i,int num)      
{   
    char s;   
    switch(i)   
    {   
    case 0: 
		{
			r--;    
            if(r>=0)   
            {   
                s=u->moves[(r+1)*3+c];   
                u->moves[(r+1)*3+c]=u->moves[r*3+c];   
                u->moves[r*3+c]=s;   
                u->edge[num]=48+i;    
                return 1;   
            }
			break; 
		}
			 
    case 1: 
		{
		  c--;     
          if(c>=0)   
          {   
              s=u->moves[3*r+c+1];   
              u->moves[3*r+c+1]=u->moves[3*r+c];   
              u->moves[3*r+c]=s;   
              u->edge[num]=48+i;     
              return 1;   
          }   
          break; 
		}
		
    case 2:
		{
			r++;    
            if(r<=2)   
            {   
                s=u->moves[(r-1)*3+c];   
                u->moves[(r-1)*3+c]=u->moves[r*3+c];   
                u->moves[r*3+c]=s;   
                u->edge[num]=48+i;  
                return 1;   
            }   
            break;
		}
			  
    case 3: 
		{
		  	c++;       
          	if(c<=2)   
          	{   
              	s=u->moves[3*r+c-1];   
              	u->moves[3*r+c-1]=u->moves[3*r+c];   
              	u->moves[3*r+c]=s;   
              	u->edge[num]=48+i;     
             	return 1;   
          	} 
		}
    }   
    return 0;   
}   

int empty(void)   
{   
    if(head==tail)   
    {   
    return(0);   
    } 
	  
        return 0;   
}   
  
void step(node *u,int r,int c,char ch)   
{   
    char s;   
    switch(ch)   
    {   
    case '0':  
		{
			r--;    
            if(r>=0)   
            {   
                s=u->moves[(r+1)*3+c];   
                u->moves[(r+1)*3+c]=u->moves[r*3+c];   
                u->moves[r*3+c]=s;}   
                break; 
		}
				  
    case '1': 
		{
		  	c--;   
          	if(c>=0)   
          	{   
             	s=u->moves[3*r+c+1];   
              	u->moves[3*r+c+1]=u->moves[3*r+c];   
              	u->moves[3*r+c]=s;
			}   
              	break;
		}
             
    case '2': 
		{
			r++;     
            if(r<=2)   
            {   
                s=u->moves[(r-1)*3+c];   
                u->moves[(r-1)*3+c]=u->moves[r*3+c];   
                u->moves[r*3+c]=s;         
            }   
            break;
		}		
			   
    case '3': 
		{
			c++;   
          	if(c<=2)   
          	{   
              	s=u->moves[3*r+c-1];   
              	u->moves[3*r+c-1]=u->moves[3*r+c];   
              	u->moves[3*r+c]=s;   
          	}
		}		
			     
    }   
}   

int factor(int n)   
{   
    int i,sum=1;   
    for(i=1;i<=n;i++)   
        sum*=i;   
    return sum;   
}     
  
  
int sort(char first[],int a)  
{   
    int i,j,sum,overall=0;   
    for(j=0;j<=a-2;j++)   
    {   
        sum=0;   
        for(i=j+1;i<=a-1;i++)   
        {   
            if(first[j]>first[i])   
                sum++;   
        }   
        sum=sum*factor(a-1-j);   
        overall+=sum;   
    }   
    return overall;   
}     


void pop(node m)       
{   
    Counter++;   
    closed[sort(m.moves,9)]=1;   
} 

 int comparison(node m)     
{   
    if(!strcmp(m.moves,last.moves))   
        return 1;   
    return 0;   
}   
int used(node m)     
{   
    if(closed[sort(m.moves,9)]==1)      
         return 1; 
		   
     return 0;   
} 
   
void push(node m)      
{   
    if((tail+1)%length==head)   
    {   
       
        exit(0);   
    }   
    open[tail++]=m;   
    tail%=length;   
}   
  

node search(int *t)    
{   
    node m[4];   
    int r,c,i,num=0;   
    
	while(!empty())   
    {   
        m[0]=m[1]=m[2]=m[3]=notpossible();  
        num=strlen(m[0].edge); 
        *t=num+1;      
        count(&r,&c,m[0]);  
     for(i=0;i<4;i++)        
        {   
            if(Possiblesteps(&m[i],r,c,i,num))    
            {   
                if(comparison(m[i]))      
                    return m[i];   
                if(!used(m[i]))      
                {   push(m[i]);    
                    pop(m[i]);     
                }   
            }   
        }   
    }   
    return m[0];   
} 

void display(node m,int t)   
{   
    int i,j,c,r;   
    for(i=1;i<=9;i++)   
    {   
        cout << first.moves[i-1]<<"  ";   
        if(i%3==0) 
			cout << endl; 
    }   
       cout << endl;
	      
    for(i=1;i<=t;i++)   
    {   		
		count(&r,&c,first);   
        step(&first,r,c,m.edge[i-1]);    
        for(j=1;j<=9;j++)   
        {   	
          cout <<first.moves[j-1] << "  ";  
            if(j%3==0) 
				cout <<endl;  
        }   
           	cout << endl;
		       
    }   
}  
	
};


int main()   
{   
    Puzzle puzz;
	node step;   
    int counts;   
    
    cout << "Input elements like: 123587640" <<endl; 
    int i;   
    int start[9]={0},end[9]={0};   
    long u;  
	cout<<"Enter your Input : ";
	cin >> first.moves; 
	
    getchar();   
    for(i=0;i<=8;i++)   
    {   
        if(first.moves[i]>'8' || first.moves[i]<'0')   
        {   
            return (0);   
        }   
        start[first.moves[i]-'0']=1;   
    }   
   for(i=0;i<9;i++)   
    {   
        if(start[i]==0)   
        {   
           
            return(0);   
        }   
    }   
	char temp007[10]="012345678";
	     
    for(i=0;i<=8;i++)   
    {
	last.moves[i]=temp007[i];
	 
	}

	for(i=0;i<=8;i++)   
    {   
        if(last.moves[i]>'8' || last.moves[i]<'0')   
        {      
            return(0);   
        }   
    }   
    for(i=0;i<9;i++)   
    {   
        if(start[i]==0)   
        {   
            return(0);   
        }   
    }   
    for(i=0;i<100;i++){   
    last.edge[i]='\0';   
    first.edge[i]='\0';   
    }   
    open[0]=first;   
    u=puzz.sort(first.moves,9);   
    closed[u]=1;   
	
	   
    step=puzz.search(&counts);  
    puzz.display(step,counts);  
	  
	cout << endl << "Total steps: " << counts <<endl; 
	
}  


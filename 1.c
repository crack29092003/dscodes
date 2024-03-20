#include<stdio.h>
#include<stdlib.h>

int size,n;
struct student{
    char name[100];
    int rollnumber;
    float avg;
    int marks[3];

}*st;

void read(){
    printf("enter the number of students\n");
    scanf("%d",&n);
    if(n>size){
        printf("reallocating");
        size=n;
        st=(struct student *)realloc(st,n*sizeof(struct student));
        
        
    }
    for(int i=0;i<n;i++){
        printf("enter the details of %d\n",(i+1));
        printf("enter the name and  register number\n");
        scanf("%s%d",(st+i)->name,&(st+i)->rollnumber);
        printf("enter the marks in 3 subject\n");
        for(int j=0;j<3;j++){
            scanf("%d",&(st+i)->marks[j]);
            
            
        }
    }
    printf("\n");
}
void avg(){
    
    int sum=0;


    if(n==0){
        printf("no details present\n");
        return;
        
        
    }
    for(int i=0;i<n;i++){
        printf(" the details of %d\n",(i+1));
        printf(" the name students is \t%s  regpster  number %d\n",(st+i)->name,(st+i)->rollnumber);
      //  scanf("%s%d",(st+i)->name,(st+i)->rollnumber);
      printf("marks in 3 sub\n");
        for(int j=0;j<3;j++){
            printf("%d\t",(st+i)->marks[j]);
            
            
        }
          int min=(st+i)->marks[0];
          for(int j=0;j<3;j++){
              if((st+i)->marks[j]<min){
                min=(st+i)->marks[j];
              }
              

                  
              }
            sum=(st+i)->marks[0]+(st+i)->marks[1]+(st+i)->marks[2]-min;
            (st+i)->avg=(float)(sum)/2;
            printf("\n the average marks is %f\n",(st+i)->avg);
            
        }
            printf("\n");
        
    }
  void display(){
   
    if(n==0){
        printf("empry\n");
        return;
        
        
    }
    for(int i=0;i<n;i++){
        printf(" the details of %d\n",(i+1));
        printf(" the name of student is \t%s    register number is   %d\n",(st+i)->name,(st+i)->rollnumber);
      //  scanf("%s%d",(st+i)->name,(st+i)->rollnumber);
      printf("marks in 3 subject\n");
        for(int j=0;j<3;j++){
            printf("%d\t",(st+i)->marks[j]);
            
            
        }
        
            
        }
            printf("\n");
        
    }


    void main(){
        int choice;
        printf("enter the size\n");
        scanf("%d",&size);
        st=(struct student*)malloc(size*sizeof(struct student));
        
        while(1){
            printf("enter your choice \n");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                read();
                break;
                case 2:
                avg();
                break;
                case 3:
                display();
                break;
                case 4:
                exit(0);
                default:
                printf("Enter the valid choice\n");

            }
        }
    }
    
    
    
    
    #include<stdio.h>
#include<stdlib.h>
struct time{
    int hr,sec,min;
};
void read(struct time *t){
   printf("Enter the time in hour minute second format\n");
   scanf("%d%d%d",&t->hr,&t->min,&t->sec);

}
void display(struct time* t){
    printf("Time is %d\t%d\t%d\n",t->hr,t->min,t->sec);

}

void update(struct time* t){
    t->sec++;
    if(t->sec>=60){
        t->min++;
        t->sec=t->sec%60;
        if(t->min>=60){
            t->hr++;
            t->min=t->min%60;
            if(t->hr>=24){
                t->min=t->hr=t->sec=0;
            }

        }
    }
    

}
void add(struct time* t1,struct time* t2,struct time* t3){
    (t3->sec)=(t1->sec)+(t2->sec);
     (t3->min)=(t1->min)+(t2->min);
      (t3->hr)=(t1->hr)+(t2->hr);

          if(t3->sec>=60){
        t3->min++;
        t3->sec=t3->sec%60;
        if(t3->min>=60){
            t3->hr++;
            t3->min=t3->min%60;
            if(t3->hr>=24){
                t3->min=t3->hr=t3->sec=0;
            }

        }
    }
    if(t3->min>=60){
            t3->hr++;
            t3->min=t3->min%60;
            if(t3->hr>=24){
                t3->min=t3->hr=t3->sec=0;
            }

        }
         if(t3->hr>=24){
                t3->min=t3->hr=t3->sec=0;
            }

      
}
void main(){
    struct time t1,t2,t3,t4;
    int choice;

    while(1){
        printf("Enter your choice\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            printf("enter the time 1");
            read(&t1);
            printf("entered time is\n");
            display(&t1);
            printf("enter the time 2");
            read(&t2);
            printf("entered time is\n");
            display(&t2);
            break;
            case 2:
            printf("enter the time to be updated \n");
            read(&t3);
            printf("before update\n");
            display(&t3);
            update(&t3);
             printf("after update\n");
             display(&t3);
             break;
             case 3:
             add(&t1,&t2,&t4);
                printf("The sum of time t1 and t2 is ");
                display(&t4);
                break;
            case 4:
            exit(0);
            default:
            printf("enter the valid choice\n");
        
        }
    }
}

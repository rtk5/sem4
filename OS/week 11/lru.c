#include<stdio.h>

int main(){
    int i, j, k, f, pf=0, count[30], rs[25], m[10], n, flag[30],next=0;
    printf("\n Enter length of the refrence string:");
    scanf("%d",&n);
    printf("\n Enter thye refrence string :");
    for(int i=0; i<n; i++){
        scanf("%d",&rs[i]);
    }
    printf("\n Enter the number of frames :");
    scanf("%d",&f);
    for(i=0;i<f;i++){
        m[i]=-1;
        count[i]=0;
    }
    printf("\n LRU page replacement Process \n :");
    if(flag[i]==0){
        if(i<f){
            m[i]=rs[i];
            count[i]=next;
            next ++;
        }
        else{
            int min=0;
            for(j=1;j<f;j++){
                if(count[min]>count[j])
                min=j;
                m[min]=rs[i];
                count[min]=next;
                next++;
            }
            pf++;
        }
        for(j=0;j<f;j++)
            printf("%d\t",m[j]);
        if(flag[i]==0)
            printf("PF NO.%d",pf);
            printf("/n");
    }
    printf("\n The number of page faults using LRU are %d \n ",pf);
}
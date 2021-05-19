#include <stdio.h>
#include <string.h>




int find_index(char name[10], char look_for){
    for(int i=0;i<10;i++){
        if(name[i]==look_for)
            return i;
    }
}
int main(){
    
    int early_start[10]={0,0,0,0,0,0,0,0,0,0};
    int early_finish[10]={0,0,0,0,0,0,0,0,0,0};
    int late_start[10]={0,0,0,0,0,0,0,0,0,0};
    int duration[10]={0,0,0,0,0,0,0,0,0,0};
    int late_finish[10]={0,0,0,0,0,0,0,0,0,0};
    char name[10];
    char predecessor_[10][9];
    int critical[10];
    int critic_count = 0;
    int predecessors[10][9];
    int successors[10][9];
    int childiren_counts[10]={0,0,0,0,0,0,0,0,0,0};
    int float_[10];
    for(int i = 0;i<10;i++)
    {
        predecessor_[i][0] = '\0';
    }
    for(int i=0;i<10;i++){
        printf("Enter name of Activity #%d: ",i+1);
        scanf(" %c",&name[i]);
        printf("Enter duration of Activity #%d: ",i+1);
        scanf(" %d",&duration[i]);
    }
    for(int j=0;j<10;j++){
        
        char opt[10];
        printf("Is there predecessor for %c?: ",name[j]);
        scanf(" %s",opt);
        
        
        if(strcmp(opt,"yes")==0 || strcmp(opt,"y")==0){
            
            int count;
            printf("Number of predecessors?: ");
            scanf(" %d",&count);
            
            for(int i=0;i<count;i++){
                printf("Enter predecessor #%d: ",i+1);
                scanf(" %c",&predecessor_[j][i]);
                getchar();
                predecessors[j][i]=find_index(name,predecessor_[j][i]);
                successors[predecessors[j][i]][childiren_counts[predecessors[j][i]]]=j;
                childiren_counts[predecessors[j][i]]+=1;
            }
            predecessor_[j][count]='\0';
            predecessors[j][count]='\0';            
        } 
    }
    for(int r=0;r<10;r++){
        if(predecessor_[r][0]=='\0'){
            early_start[r]=0;
            early_finish[r]=duration[r];
        }
        else{
            early_start[r]=0;
            for(int k=0;predecessor_[r][k]!='\0';k++){
                
                if(early_finish[predecessors[r][k]]>early_start[r]){
                    early_start[r]=early_finish[predecessors[r][k]];
                    
                }
            }
            early_finish[r]=early_start[r]+duration[r];
        }
    }
    int biggest=0;
    for(int i=0;i<10;i++){
        if(early_finish[i]>biggest)
            biggest=early_finish[i];

    }
    for(int v=9;v>=0;v--){
        if(childiren_counts[v]==0){
            late_finish[v]=biggest;
            late_start[v]=late_finish[v]-duration[v];
        }
        else{
            late_finish[v]=late_start[successors[v][0]];
            for(int u=0;u<childiren_counts[v];u++){
                if(late_finish[v]>late_start[successors[v][u]]){
                    late_finish[v]=late_start[successors[v][u]];
                }
            }
            late_start[v]=late_finish[v]-duration[v];
        }
    }
    for(int f=0;f<10;f++){
            float_[f]=late_finish[f]-early_finish[f];
            if(float_[f] == 0)
                critical[critic_count++] = f;
    }
    for(int y=0;y<10;y++){
        printf("\n Activity name : %c\n",name[y]);
        printf("ES : %d\n",early_start[y]);
        printf("EF : %d\n",early_finish[y]);
        printf("LS : %d\n",late_start[y]);
        printf("LF : %d\n",late_finish[y]);
        printf("Float : %d\n\n\n",float_[y]);
    }

    printf(" \n ---- CRITICAL PATH ----");
    int f = 0;
    while(f==0)
    {
        f=1;
        for(int i = 0;i < critic_count - 1;i++)
        {
            if(late_start[critical[i]] > late_start[critical[i+1]])
            {
                f=0;
                int temp = critical[i];
                critical[i] = critical[i+1];
                critical[i+1] = temp;
            }
        }
    }
    
    printf("\n%c",name[critical[0]]);
    for(int i = 1;i < critic_count;i++)
    {
        printf(" -> %c",name[critical[i]]);
    }

    return 0;
}

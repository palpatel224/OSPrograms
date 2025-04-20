#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BLOCKS 50

int no_of_files=0;
int is_allocated[MAX_BLOCKS];

struct file{
    char name[20];
    int start_block;
    int size;
}files[20];

int space_available(){
    int sum=0;
    for(int i=0;i<MAX_BLOCKS;i++){
        sum+=is_allocated[i];
    }
    int x=MAX_BLOCKS-sum;
    return x;
}
int is_available(int start_block,int size){
    for(int i=start_block;i<size;i++){
        if(is_allocated[i]==1){
            return 0;
        }
    }
    return 1;
}
void print_filetable(){
    printf("\nFile name\tstart block\tfile size");
    for(int i=0;i<no_of_files;i++){
        printf("\n%s\t\t%d\t\t%d ",files[i].name,files[i].start_block,files[i].size);
    }
}
int main(){
    int flag,x=1;
    struct file temp;
    while(1){
        printf("\n\nChose option :  1. Create file, 2. Print filetable 3. exit = ");
        scanf("%d",&flag);
        switch(flag){
            case 1 :
                printf("\nEnter name of file = ");
                scanf("%s",temp.name);
                printf("Enter start block number = ");
                scanf("%d",&temp.start_block);
                printf("Enter number of blocks needed for file = ");
                scanf("%d",&temp.size);
                if(is_available(temp.start_block,temp.size)==0){
                    printf("\nFile is clashing with existing files. Creation terminated");
                    break;
                }
                else if(temp.size>space_available()){
                    printf("\nSize of file exceeds disk space");
                    break;
                }
                else{
                    strcpy(files[no_of_files].name,temp.name);
                    files[no_of_files].start_block=temp.start_block;
                    files[no_of_files].size=temp.size;
                    no_of_files++;
                    for(int i=temp.start_block;i<temp.size;i++){
                        is_allocated[i]=1;
                    }
                    printf("\nFile %s created",temp.name);
                    break;
                }
            case 2 :
                print_filetable();
                break;
            case 3 : 
                exit(1);
                break;
        }
    }
    return 0;
}
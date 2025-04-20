#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BLOCKS 50

int no_of_files=0;
int is_allocated[MAX_BLOCKS];

struct file{
    char name[20];
    int index_block;
    int size;
    int blocks_allocated[MAX_BLOCKS];
}files[20];

int space_available(){
    int sum=0;
    for(int i=0;i<MAX_BLOCKS;i++){
        sum+=is_allocated[i];
    }
    int x=MAX_BLOCKS-sum;
    return x;
}
int is_available(int blocks_to_allocate[],int size,int index_block){
    for(int i=0;i<size;i++){
        if(is_allocated[blocks_to_allocate[i]]==1){
            return 0;
        }
    }
    if(is_allocated[index_block]==1){
        return 0;
    }
    return 1;
}
void print_filetable(){
    printf("\nFile name\tindex block\tfile size\tblocks allocated");
    for(int i=0;i<no_of_files;i++){
        printf("\n%s\t\t->%d\t\t%d\t\t",files[i].name,files[i].index_block,files[i].size);
        for(int j=0;j<files[i].size;j++){
            printf(" %d ",files[i].blocks_allocated[j]);
        }
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
                printf("Enter index block number = ");
                scanf("%d",&temp.index_block);
                printf("Enter number of blocks needed for file = ");
                scanf("%d",&temp.size);
                printf("Enter block numbers of blocks to be allocated to this file = ");
                temp.blocks_allocated[0]=temp.index_block;
                for(int i=0;i<temp.size;i++){
                    scanf("%d",&temp.blocks_allocated[i]);
                }
                if(is_available(temp.blocks_allocated,temp.size,temp.index_block)==0){
                    printf("\nFile allocation is clashing with existing files. Creation terminated");
                    break;
                }
                else if(temp.size + 1 >space_available()){
                    printf("\nSize of file exceeds disk space");
                    break;
                }
                else{
                    strcpy(files[no_of_files].name,temp.name);
                    files[no_of_files].index_block=temp.index_block;
                    files[no_of_files].size=temp.size;
                    for(int i=0;i<temp.size;i++){
                        files[no_of_files].blocks_allocated[i]=temp.blocks_allocated[i];
                    }
                    no_of_files++;
                    for(int i=0;i<temp.size;i++){
                        is_allocated[temp.blocks_allocated[i]]=1;
                    }
                    is_allocated[temp.index_block]=1;
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
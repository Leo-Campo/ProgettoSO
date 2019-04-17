#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "allocator.h"

void* my_alloc(buffer* buff, int size){
	int level= buddylevel(buff,size);
	printf("%d\n", size);
	printf("level %d\n", level);
	int levello = level;
	int k = 0;
	int i=pow(2,level);
	int stop=pow(2,level+1);
	for(;i<stop;i++){
		if(BitMap_get(buff->check,i)==0){
			int j= i/2;
			while(level){
				//printf("%d\n",j);
				if(BitMap_get(buff->check,j)==1) break;
				BitMap_set(buff->check,j);
				level--;
				j=j/2;
			}
			set_children(buff,i,levello);
			int num = buff->max/(pow(2, levello));
			return (void*)&(buff->memory[num*k*buff->block_size]);
		}
		k++;
	}
	  
}


/*void my_free(buffer* b, void* ptr, int size){
  int ind = ptr;
  int start = &(b->memory[0]);
  int number = (ind - start)/4;
  int i;
  int num = size/b->block_size;
  for(i = 0; i < num; i++){
    BitMap_unset(b->check, number+i);
  }
*/

int buddylevel(buffer* buff,int size){ 
     if(size>buff->max){
	fprintf(stderr,"not enough memory!\n");
	exit(1);
}
     int pow=0;
     int aux=buff->max;
     aux=aux/2;
	while (size<=aux){
		pow++;
		aux=aux/2;
    }
	return pow;
	
}

void set_children(buffer*buf,int i,int level){
	BitMap_set(buf->check,i);
	if(level==buf->levels) return;
	else{
		set_children(buf,2*i,level+1);
		set_children(buf,2*i+1,level+1);
	}
}

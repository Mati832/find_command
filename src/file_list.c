#include "../include/file_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



void initList(FileList *list){
  list->start=NULL;
  list->end=NULL;
  list->count=0;
}

void addFile(FileList *list, const char *fullPath){

  FileNode *newNode = malloc(sizeof(FileNode));
  if(!newNode){
    perror("Error at malloc FileNode");
    return;
  }

  newNode->absolutePath= strdup(fullPath);
  if(!newNode->absolutePath){
    free(newNode);
    return;
  }

  newNode->next=NULL;

  if(!list->start){
    list->start=newNode;
    list->end=newNode;
  }
  else{
    list->end->next=newNode;
    list->end=newNode;
  }
  list->count++;
}
void freeList(FileList *list){

  FileNode *current=list->start;

  while(current!=NULL){
    FileNode *temp=current->next;
    free(current->absolutePath);
    free(current);
    current=temp;
  }

  list->start=NULL;
  list->end=NULL;
  list->count=0;
}

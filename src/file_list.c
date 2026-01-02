#include "../include/file_list.h"


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void initList(FileList *list){
  list->start=NULL;
  list->end=NULL;
  list->count=0;
  sem_init(&list->mutex, 0, 1);
}

Node* addFile(FileList *list, const char *fullPath, NodeType type){

  Node *newNode = malloc(sizeof(Node));
  
  
  newNode->absolutePath= strdup(fullPath);
  newNode->type=type;
  newNode->next=NULL;
  newNode->content = NULL;

  if(type == NODE_DIR){
    newNode->content = malloc(sizeof(FileList));
    initList(newNode->content);
  }

  sem_wait(&list->mutex);
  if(!list->start){
    list->start=newNode;
    list->end=newNode;
  }
  else{
    list->end->next=newNode;
    list->end=newNode;
  }
  list->count++;
  sem_post(&list->mutex);
  return newNode;
}

void freeList(FileList *list){

  Node *current=list->start;

  while(current!=NULL){
    if(current->type == NODE_DIR){
      freeList(current->content);
      free(current->content);
    }
    Node *temp=current->next;
    free(current->absolutePath);
    free(current);
    current=temp;
  }

  list->start=NULL;
  list->end=NULL;
  list->count=0;
  sem_destroy(&list->mutex);
}

void printList(FileList *list){
  Node *current = list->start;
  while(current){
    printf("%s\n", current->absolutePath);
    if(current->type == NODE_DIR) printList(current->content);
    current=current->next;
  }
}

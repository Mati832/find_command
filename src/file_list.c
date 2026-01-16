#include "../include/file_list.h"
#include "../include/utils.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

void initList(FileList *list){
  list->start=NULL;
  list->end=NULL;
  list->count=0;
  sem_init(&list->mutex, 0, 1);
}

Node* addFile(FileList *list, const char *fullPath, NodeType type){

  Node *newNode = malloc(sizeof(Node));
  if(newNode == NULL){
    perror("Error: Memory could not be allocated");
    exit(EXIT_FAILURE);
  } 
  newNode->absolutePath= strdup(fullPath);
  if(newNode->absolutePath == NULL){
    perror("Error: Memory could not be allocated");
    exit(EXIT_FAILURE);
  }
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
void printHumanReadableList(FileList *list){
  Node *current = list->start;
  struct stat st;
    
  while (current){
    if(lstat(current->absolutePath, &st)==0){

      char size[10];
      format_size_dynamic(st.st_size, size);

      char time[20];
      struct tm *tm = localtime(&st.st_mtime);
      strftime(time, sizeof(time), "%b %d %H:%M", tm);

      printf(" %s %s %s\n", size, time, current->absolutePath);
    }
    else{
      printf("??? %s\n", current->absolutePath);
    }
    if(current->type == NODE_DIR){
      printHumanReadableList(current->content);
    }
    current=current->next;

  }

}

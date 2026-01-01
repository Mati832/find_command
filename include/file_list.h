#ifndef result_list
#define result_list
#include <semaphore.h>

typedef enum {
  NODE_FILE,
  NODE_DIR
} NodeType;

struct FileList;

typedef struct Node{
  char *absolutePath;
  NodeType type;
  struct Node *next;

  struct FileList *content;
}Node;

typedef struct FileList{
  Node *start;
  Node *end;
  sem_t mutex;
  int count;
}FileList;

void initList(FileList *list);
Node* addFile(FileList *list, const char *fullPath, NodeType type);
void freeList(FileList *list);

#endif

#ifndef result_list
#define result_list

typedef struct FileNode{
  char *absolutePath;
  struct FileNode *next;
}FileNode;

typedef struct{
  FileNode *start;
  FileNode *end;
  int count;
}FileList;

void initList(FileList *list);
void addFile(FileList *list, const char *fullPath);
void freeList(FileList *list);

#endif

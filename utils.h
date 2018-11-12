#pragma once
#include <sys/stat.h>
#include <sys/types.h>
typedef struct nodeSave
{
  char name[25];
  int id;
  int level;
  bool isDir;
  off_t size;
  time_t lastModification;
}nodeSave;

#pragma once
#include <vector>
#include <iostream>
#include "mpich/mpi.h"

#define DISK_TAM 32000

using namespace std;

typedef struct file
{
    string name;
    off_t size;
    int id;
} file;

typedef struct block
{
    int id;
    MPI_Status status;
    //Buffer
} block;

typedef struct disk
{
    int id;
    disk *nextDisk;
    disk *lastDisk;
    off_t size;
    vector<block> blocks[DISK_TAM];

} disk;

class Disk
{
  private:
    disk *disks;

  public:
    Disk();
    bool writeBlock();
    bool readBlock();
    bool writeDisk();
    bool readDisk();
    ~Disk();
};
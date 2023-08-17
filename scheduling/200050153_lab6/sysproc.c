#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_mmap(void){
  int bytes;
  if(argint(0, &bytes) < 0)
    return -1;
  return mmap(bytes);
}



int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

int
sys_helloYou(void)
{
  char* name;
  argstr(0, &name);
  return helloYou(name);
}

int sys_getNumProc(void)
{
  return getNumProc();
}

int
sys_wait2(void)
{
  int* wtime;
  int* rutime;
  if(argptr(0, (void*)&wtime, 8) < 0){
    return -1;
  }
  if(argptr(1, (void*)&rutime, 8) < 0){
    return -1;
  }
  return wait2(wtime, rutime);
}


int
sys_getMaxPid(void)
{
  return getMaxPid();
}

int
sys_current_ps(void)
{
  return current_ps();
}

int
sys_change_priority(void)
{
  int pid, priority;
  if(argint(0, &pid) < 0){
    return -1;
  }
  if(argint(1, &priority) < 0){
    return -1;
  }
  return change_priority(pid, priority);
}


int
sys_get_siblings_info(void){
  return get_siblings_info();
}

int
sys_csinfo(void)
{
  return csinfo();
}

int
sys_freememstat(void){
  return freememstat();
}

int
sys_getmeminfo(void){

  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return getmeminfo(pid);
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

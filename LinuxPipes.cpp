#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#define PROCESSES_NUM 10
#define ARRAY_SIZE 10000

using namespace std;

int prim(int n)
{
for(int i = 2; i <= (n / 2); i++)
 {
 if((n % i) != 0)
 return 0;
 }
 return -1;
}

int main(void) {

int pipes[PROCESSES_NUM * 2][2];
int pids[PROCESSES_NUM];                            // vectorul proceselor dupa ID
int array[ARRAY_SIZE];
static int start[PROCESSES_NUM + 1], end[PROCESSES_NUM + 1];

start[0] = -999;
end[0] = 0;

for(int i = 1; i <= ARRAY_SIZE; i++)
  {
  array[i] = i;
  }

for(int i = 1; i <= PROCESSES_NUM * 2; i++)
  {
    if(pipe(pipes[i]) == -1)
    {
    cout << "Error occured when trying to create pipe.\n";
    return 1;
    }  
  }
  
for(int i = 1; i <= PROCESSES_NUM; i++)
  {
  pids[i] = fork();
  if(pids[i] == -1)
    {
     cout << "Error occured when creating process.\n";
     return 2;
    }
    
  start[i] = start[i - 1] + 1000;
  end[i] = end[i - 1] + 1000;  
   
  if(pids[i] == 0)                                                           // if child
    {
    int j;
    for(j = 1; j <= PROCESSES_NUM * 2; j++)
      {
      if((j != (2 * i) - 1))                                                  //(2i - 1) -> read;  2i -> write
       {
        close(pipes[j][0]);
       }
      if(j != 2 * i)
       {
        close(pipes[j][1]);
       }
       
       int p1 = 2 * i - 1;                                             //read
       int p2 = 2 * i;                                                //write
       for(int x = start[i]; x <= end[i]; x++)
        {
         if(read(pipes[p1][0], &x, sizeof(int)) == -1)
          {
           cout << "Read error occured from pipe " << p1 << " at process " << i << ".\n";
           return 3; 
          }
          
         if(prim(x) == 0)
         {
           if(write(pipes[p2][1], &x, sizeof(int)) == -1)
            {
             cout << " Write error occured from pipe " << p2 << "at process " << i << ".\n";
             return 4; 
            }
         }
        }
        close(pipes[p1][0]);
        close(pipes[p2][1]);
     
     return 0;   
     
       }
      }
       
  // main process
  else
  {
  int k;
    for(k = 1; k <= PROCESSES_NUM * 2; k++)
      {
        if((k != (2 * i) - 1))
        {
         close(pipes[k][1]);
        }
        if(k != 2 * i)
        { 
         close(pipes[k][0]);
        }
      }
        
      int k1 = 2 * i - 1;                                                //write
      int k2 = 2 * i;                                                   //read
      
      start[i] = start[i - 1] + 1000;
      end[i] = end[i - 1] + 1000;
     
     for(k = start[i]; k <= end[i]; k++)
     {
      cout << "Main process sent " << k << ".\n";
      if(write(pipes[k1][1], &k, sizeof(int)) == -1)
      {
      cout << "Write error occured from pipe " << k1 << " at main process.\n";
      return 5;
      }
     }
     
     wait(NULL);
     
     cout << "The prime numbers found between 1 and 10000 are:\n";
     for(k = start[i]; k <= end[i]; k++)
     {
      if(read(pipes[k2][0], &k, sizeof(int)) == -1)
      {
      cout << "Main process received the following prime numbers: " << k << "\n";
      cout << "Read error occured from pipe " << k2 << " at main process.\n";
      return 6;
      }   
     }
  }
 } 

return 0;

}

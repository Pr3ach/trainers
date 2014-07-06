#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <TlHelp32.h>
#include "libColor/color.h"

/*

Memory patcher CoD4 Single Player

Hack all weapons ammo + frag nade + flash nade + m203

Pr3acher @__Pr3__ 

*/

int main()
{
  PROCESSENTRY32 pe32={0};
  HANDLE hSnap=NULL;
  WORD i=0;
  HANDLE hCoD4=NULL;
  const int addr=0x5BFA61;
  unsigned char buff[2]={0};
  int bytesRead=0;
  int writtenBytes=0;
  char r=0;
  BOOL isAlreadyPatched=TRUE;
  char patch[2]={0x31,0xD2};   //mov edx,esi ;esi=1
  char restore[2]={0x8B,0xD6}; //xor edx,edx
  MEMORY_BASIC_INFORMATION mbi={0};
  PDWORD oldProtect=NULL;
  PDWORD oldProtect1=NULL; 
  char p=0;

  system("title CoD 4 Single Player Mem Patcher - By Pr3acher");
  
  pe32.dwSize=sizeof(PROCESSENTRY32);
  
  hSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
  
  if(!Process32First(hSnap,&pe32))
    return 1;
  
  while(stricmp("iw3sp.exe",(const char*)pe32.szExeFile)!=0)
    {
      Process32Next(hSnap,&pe32);
      i++;
      
      if(i>=200)
	{
	  setColor(Red);
	  printf("[!] iw3sp.exe is not running\n");
	  setColor(White);
	  CloseHandle(hSnap);
	  getch();
	  
	  exit(0);
	}
    }
  
  CloseHandle(hSnap); // No more needed
  
  hCoD4=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
  
  if(hCoD4==NULL)
    {
      setColor(Red);
      printf("[!] Fail opening iw3sp.exe\n");
      setColor(White);
      getch();
	    
      exit(1);
    }
  
  VirtualQueryEx(hCoD4,addr,&mbi,2);

  if(mbi.Protect!=0x40) // If no PAGE_EXECUTE_READWRITE set it
    {
      if(!VirtualProtectEx(hCoD4,addr,2,PAGE_EXECUTE_READWRITE,&oldProtect))
	{
	  setColor(Red);
	  printf("[!] Fail changing memory access rights\n");
	  CloseHandle(hCoD4);
	  setColor(White);
	  getch();

	  exit(1);
	}
    }

  ReadProcessMemory(hCoD4,addr,&buff,2,&bytesRead);	
	
  if(bytesRead!=2)
    {
      setColor(Red);
      printf("[!] An error happened during memory operations\n");
      CloseHandle(hCoD4);
      setColor(White);
      getch();
	  
      exit(1);
    }
	
    
  if(buff[0]!=0x31 || buff[1]!=0xD2)
    {
      isAlreadyPatched=FALSE;
    }


  if(isAlreadyPatched==TRUE)
    {
      setColor(Blue);
      printf("[-] CoD4 SP appears to be already patched, apply patch anyways, restore ? [y/n/r]\n");
      setColor(White);
      p=getch();

      if(p!='y')
	{

	  if(p!='r')
	    {	  
	      CloseHandle(hCoD4);
	      exit(0);
	    }

	  for(r=0;r<=2;r++)
	    {
	      patch[r]=restore[r];
	    }

	}
      
    }


  if(isAlreadyPatched!=TRUE)
    {
      setColor(Green);
      printf("[+] Apply patch now ? [y/n]\n");
      setColor(White);
      
      if(getch()!='y')
	{
	  CloseHandle(hCoD4);
	  exit(0);
	}
    }

  WriteProcessMemory(hCoD4,addr,patch,2,&writtenBytes);  
  
  if(writtenBytes!=2)
    {
      setColor(Red);
      printf("[!] An error occured while patching the memory\n");
      CloseHandle(hCoD4);
      setColor(White);
      getch();
      
      exit(1);
    }

  if(oldProtect!=0x40)
    VirtualProtectEx(hCoD4,addr,2,oldProtect,&oldProtect1); // restore original mem protection
  
  CloseHandle(hCoD4);
  
  setColor(Green);
  printf("[+] Memory patched%s\n",p=='r'? " (restored)" : ", enjoy");
  setColor(White);
  getch();

  return 0;
}











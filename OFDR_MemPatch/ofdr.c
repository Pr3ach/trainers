#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <TlHelp32.h>
#include "libColor/color.h"

/*

Memory patcher Operation Flashpoint: Dragon Rising Single Player

locks down all weapons ammo

Pr3acher @__Pr3__ 

*/

int main()
{
  PROCESSENTRY32 pe32={0};
  HANDLE hSnap=NULL;
  WORD i=0;
  HANDLE hOfdr=NULL;
  const int addr=0xF55F8F;
  unsigned char buff[4]={0};
  int bytesRead=0;
  int writtenBytes=0;
  char c=0;
  char r=0;
  BOOL isAlreadyPatched=TRUE;
  char patch[4]={0x90,0x90,0x90,0x90};
  char restore[4]={0x29,0x54,0x81,0x40};
  MEMORY_BASIC_INFORMATION mbi={0};
  PDWORD oldProtect=NULL;
  PDWORD oldProtect1=NULL;
  char p=0;

  system("title OF Dragon Rising Trainer - By Pr3acher");
  
  pe32.dwSize=sizeof(PROCESSENTRY32);
  
  hSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
  
  if(!Process32First(hSnap,&pe32))
    return 1;
  
  while(stricmp("OFDR.exe",(const char*)pe32.szExeFile)!=0)
    {
      Process32Next(hSnap,&pe32);
      i++;
      
      if(i>=200)
	{
	  setColor(Red);
	  printf("[!] OFDR.exe is not running\n");
	  setColor(White);
	  CloseHandle(hSnap);
	  getch();
	  
	  exit(0);
	}
    }
  
  CloseHandle(hSnap); // No more needed
  
  hOfdr=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
  
  if(hOfdr==NULL)
    {
      setColor(Red);
      printf("[!] Fail opening OFDR.exe\n");
      setColor(White);
      getch();
	    
      exit(1);
    }
  
  VirtualQueryEx(hOfdr,addr,&mbi,4);

  if(mbi.Protect!=0x40) // If no PAGE_EXECUTE_READWRITE set it
    {
      if(!VirtualProtectEx(hOfdr,addr,4,PAGE_EXECUTE_READWRITE,&oldProtect))
	{
	  setColor(Red);
	  printf("[!] Fail changing memory access rights\n");
	  CloseHandle(hOfdr);
	  setColor(White);
	  getch();

	  exit(1);
	}
    }

  ReadProcessMemory(hOfdr,addr,&buff,sizeof(buff),&bytesRead);	
	
  if(bytesRead!=4)
    {
      setColor(Red);
      printf("[!] An error happened during memory operations\n");
      CloseHandle(hOfdr);
      setColor(White);
      getch();
	  
      exit(1);
    }
	

  for(c=0;c<=3;c++)
    {
      if(buff[c]!=0x90)
	{
	  isAlreadyPatched=FALSE;
	}
    }
	

  if(isAlreadyPatched==TRUE)
    {
      setColor(Blue);
      printf("[-] OF Dragon Rising appears to be already patched, apply patch anyways, restore ? [y/n/r]\n");
      setColor(White);
      p=getch();

      if(p!='y')
	{
	  if(p!='r')
	    {	  
	      CloseHandle(hOfdr);
	      exit(0);
	    }
	  for(r=0;r<=3;r++)
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
	  CloseHandle(hOfdr);
	  exit(0);
	}
    }

  WriteProcessMemory(hOfdr,addr,patch,4,&writtenBytes);  
  
  if(writtenBytes!=4)
    {
      setColor(Red);
      printf("[!] An error occured while patching the memory\n");
      CloseHandle(hOfdr);
      setColor(White);
      getch();
      
      exit(1);
    }

  if(oldProtect!=0x40)
    VirtualProtectEx(hOfdr,addr,4,oldProtect,&oldProtect1); // restore original mem protection
  
  CloseHandle(hOfdr);
  
  setColor(Green);
  printf("[+] Memory patched%s\n",p=='r'? " (restored)" : ", enjoy");
  setColor(White);
  getch();

  return 0;
}











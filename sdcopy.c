/*
Avalibe platform identfer
MS_WINDOWS - 32 bit Microsoft Windows and 64 bit Microsoft Windows
UNIX_32 - 32 bit Unix like system
UNIX_64 - 64 bit Unix like system
*/
#define MS_WINDOWS
#include "sdcopy.h"

int open_input_file(char *name);
int create_output_file(char *name);
long long int get_file_size(int target);
char *get_memory(size_t blocks);
void show_progress(long long int start, long long int stop);
long long int check_input_file(int input);
void check_argument(char *argument);
unsigned long int get_buffer_size(char *argument);
long long int get_count(char *argument);
void check_range(int target, long long int offset, long long int length);
void copy_file(int input, int output, long long int offset, long long int length, unsigned long int blocks);
void start_job(void);
void end_job(void);
void work(char *source,char *target,char *buffers,char *position,char *amount);
void show_intro(void);
void show_help(void);

int main(int argc, char *argv[])
{
 show_intro();
 switch (argc)
 {
  case 5:
  work(argv[1],argv[2],argv[3],argv[4],NULL);
  break;
  case 6:
  work(argv[1],argv[2],argv[3],argv[4],argv[5]);
  break;
  default:
  show_help();
  break;
 }
 return 0;
}

int open_input_file(char *name)
{
 int target;
 target=open(name,INPUT_FILE_MODE);
 if (target==-1)
 {
  puts("Can't open a source file!");
  exit(1);
 }
 return target;
}

int create_output_file(char *name)
{
 int target;
 target=open(name,OUTPUT_FILE_MODE,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
 if (target==-1)
 {
  puts("Can't create or open a target file!");
  exit(2);
 }
 return target;
}

long long int get_file_size(int target)
{
 long long int length;
 length=file_seek(target,0,SEEK_END);
 file_seek(target,0,SEEK_SET);
 return length;
}

char *get_memory(size_t blocks)
{
 char *memory=NULL;
 memory=(char*)calloc(blocks,1);
 if (memory==NULL)
 {
  puts("Can't allocate memory!");
  exit(3);
 }
 return memory;
}

void show_progress(long long int start, long long int stop)
{
 long long int progress;
 progress=start+1;
 progress*=100;
 progress/=stop;
 printf("\r");
 printf("Current position: %lld.End data position: %lld. Progress:%lld%%",start,stop,progress);
}

void check_argument(char *argument)
{
 unsigned long int index,length;
 length=strlen(argument);
 for (index=0;index<length;index++)
 {
  if (isdigit(argument[index])==0)
  {
   puts("Can't decode argument");
   exit(4);
  }

 }

}

unsigned long int get_buffer_size(char *argument)
{
 unsigned long int length;
 check_argument(argument);
 length=atol(argument);
 if (length<1)
 {
  puts("Buffer length is too small! Minimum buffer length:1 megabyte");
  exit(5);
 }
 if (length>512)
 {
  puts("Buffer length is too big! Maximum buffer length:512 megabytes");
  exit(6);
 }
 return length*1024*1024;
}

long long int get_count(char *argument)
{
 check_argument(argument);
 return atoll(argument);
}

long long int check_input_file(int input)
{
 long long int length;
 length=get_file_size(input);
 if (length==0)
 {
  puts("Input files with zero length not supported");
  exit(7);
 }
 return length;
}

void check_range(int target, long long int offset, long long int length)
{
 long long int amount;
 amount=get_file_size(target);
 if (offset>amount||length>amount)
 {
  puts("Invalid offset!");
  exit(8);
 }
 if (offset<1)
 {
  puts("Invalid start offset! Minimal start offset:1");
  exit(9);
 }

}

void copy_file(int input, int output, long long int offset, long long int length, unsigned long int blocks)
{
 char *data=NULL;
 long long int position;
 long int transfer;
 position=file_seek(input,offset,SEEK_SET);
 if (position==-1)
 {
  puts("Can't jump to start offset!");
  exit(10);
 }
 data=get_memory(blocks);
 transfer=blocks;
 while (position<length)
 {
  if(length-position<=transfer) transfer=length-position;
  if (read(input,data,transfer)==-1)
  {
   putchar('\n');
   puts("Can't read data!");
   exit(11);
  }
  if (write(output,data,transfer)==-1)
  {
   putchar('\n');
   puts("Can't write data!");
   exit(12);
  }
  position+=transfer;
  show_progress(position,length);
 }
 free(data);
}

void start_job(void)
{
 puts("File copying in progress. Please wait");
}

void end_job(void)
{
 putchar('\n');
 puts("File copying successfuly complete.");
}

void work(char *source,char *target,char *buffers,char *position,char *amount)
{
 int input,output;
 long long int offset,length;
 unsigned long int blocks;
 input=open_input_file(source);
 output=create_output_file(target);
 offset=0;
 length=check_input_file(input);
 offset=get_count(position);
 blocks=get_buffer_size(buffers);
 if (amount!=NULL) length=get_count(amount);
 check_range(input,offset,length);
 start_job();
 copy_file(input,output,offset-1,length,blocks);
 end_job();
 close(input);
 close(output);
}

void show_intro(void)
{
 putchar('\n');
 puts("Simple data copier");
 puts("Low-level file copying tool by Popov Evgeniy Alekseyevich, 2015 year");
 puts("Version 1.3");
 puts("This software distributed under GNU GENERAL PUBLIC LICENSE(Version 2 or later) terms");
 putchar('\n');
}

void show_help(void)
{
 puts("You must give right command line argument!");
 puts("Simple data copier usage: sdcopy source target buffer start stop");
 puts("Argument description:");
 puts("source - A input file name.");
 puts("target - A output file name.");
 puts("buffer - Buffer length(in megabytes).");
 puts("start - Offset(in bytes) to start data. 1 is first byte");
 puts("stop - Offset(in bytes) to end data. Optional argument.");
}
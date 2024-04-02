#include "sdcopy.h"

void show_message(const char *message);
int open_input_file(const char *name);
int create_output_file(const char *name);
long long int get_file_size(const int target);
long long int set_position(const int target,const long long int offset);
void read_data(const int target,void *buffer,const size_t amount);
void write_data(const int target,void *buffer,const size_t amount);
char *get_memory(const size_t blocks);
void show_progress(const long long int start,const long long int stop);
long long int check_input_file(const int input);
void check_argument(const char *argument);
long long int get_count(const char *argument);
void check_range(const int target,const long long int offset,const long long int length);
void copy_file(const int input,const int output,const long long int offset,const long long int length);
void work(const char *source,const char *target,const char *position,const char *amount);
void show_intro(void);
void show_help(void);

int main(int argc, char *argv[])
{
 show_intro();
 switch (argc)
 {
  case 3:
  work(argv[1],argv[2],NULL,NULL);
  break;
  case 4:
  work(argv[1],argv[2],argv[3],NULL);
  break;
  case 5:
  work(argv[1],argv[2],argv[3],argv[4]);
  break;
  default:
  show_help();
  break;
 }
 return 0;
}

void show_message(const char *message)
{
 putchar('\n');
 puts(message);
}

int open_input_file(const char *name)
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

int create_output_file(const char *name)
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

long long int get_file_size(const int target)
{
 long long int length;
 length=file_seek(target,0,SEEK_END);
 file_seek(target,0,SEEK_SET);
 return length;
}

long long int set_position(const int target,const long long int offset)
{
 long long int position;
 position=file_seek(target,offset,SEEK_SET);
 if (position==-1)
 {
  puts("Can't jump to start offset!");
  exit(8);
 }
 return position;
}

void read_data(const int target,void *buffer,const size_t amount)
{
 if (read(target,buffer,amount)==-1)
  {
   show_message("Can't read data!");
   exit(9);
  }

}

void write_data(const int target,void *buffer,const size_t amount)
{
 if (write(target,buffer,amount)==-1)
  {
   show_message("Can't write data!");
   exit(10);
  }

}

char *get_memory(const size_t blocks)
{
 char *memory=NULL;
 memory=(char*)calloc(blocks,sizeof(char));
 if (memory==NULL)
 {
  puts("Can't allocate memory!");
  exit(3);
 }
 return memory;
}

void show_progress(const long long int start,const long long int stop)
{
 long long int progress;
 progress=(start+1)*100;
 progress/=stop;
 printf("\r");
 printf("Current position: %lld.End data position: %lld. Progress:%lld%%",start,stop,progress);
}

void check_argument(const char *argument)
{
 size_t index,length;
 length=strlen(argument);
 for (index=0;index<length;++index)
 {
  if (isdigit(argument[index])==0)
  {
   puts("Can't decode argument");
   exit(4);
  }

 }

}

long long int get_count(const char *argument)
{
 check_argument(argument);
 return atoll(argument);
}

long long int check_input_file(const int input)
{
 long long int length;
 length=get_file_size(input);
 if (length==0)
 {
  puts("Input files with zero length not supported");
  exit(5);
 }
 return length;
}

void check_range(const int target,const long long int offset,const long long int length)
{
 long long int amount;
 amount=get_file_size(target);
 if (offset>amount||length>amount)
 {
  puts("Invalid offset!");
  exit(6);
 }
 if (offset<1)
 {
  puts("Invalid start offset! Minimal start offset:1");
  exit(7);
 }

}

void copy_file(const int input,const int output,const long long int offset,const long long int length)
{
 char *data=NULL;
 long long int position;
 size_t transfer;
 transfer=4096;
 position=set_position(input,offset);
 data=get_memory(transfer);
 while (position<length)
 {
  if(length-position<=(long long int)transfer)
  {
   transfer=(size_t)length-(size_t)position;
  }
  read_data(input,data,transfer);
  write_data(output,data,transfer);
  position+=(long long int)transfer;
  show_progress(position,length);
 }
 free(data);
}

void work(const char *source,const char *target,const char *position,const char *amount)
{
 int input,output;
 long long int offset,length;
 input=open_input_file(source);
 output=create_output_file(target);
 offset=1;
 length=check_input_file(input);
 if (amount!=NULL)
 {
  length=get_count(amount);
 }
 if (position!=NULL)
 {
  offset=get_count(position);
 }
 check_range(input,offset,length);
 show_message("File copying in progress. Please wait");
 copy_file(input,output,offset-1,length);
 show_message("File copying successfully complete");
 close(input);
 close(output);
}

void show_intro(void)
{
 putchar('\n');
 puts("Simple data copier");
 puts("Low-level file copying tool by Popov Evgeniy Alekseyevich, 2015-2024 years");
 puts("Version 1.4.6");
 puts("This software distributed under GNU GENERAL PUBLIC LICENSE(Version 2 or later) terms");
}

void show_help(void)
{
 putchar('\n');
 puts("You must give right command line arguments!");
 puts("Simple data copier arguments: source,target,start,stop");
 puts("Argument description:");
 puts("source - A input file name.");
 puts("target - A output file name.");
 puts("start - Offset(in bytes) to start data. 1 is the first byte. It is an optional argument.");
 puts("stop - Offset(in bytes) to end data. It is an optional argument.");
}
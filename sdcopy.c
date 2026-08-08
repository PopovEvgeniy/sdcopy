#include "sdcopy.h"
#include "settings.h"

void show_message(const char *message);
int open_input_file(const char *name);
int create_output_file(const char *name);
long long int set_position(const int target,const long long int offset);
long long int get_file_size(const int target);
void read_data(const int target,char *buffer,const size_t length);
void write_data(const int target,const char *buffer,const size_t length);
void check_range(const long long int length,const long long int offset,const long long int stop);
long long int decode_argument(const char *target);
char *get_memory(const size_t blocks);
void show_progress(const long long int start,const long long int stop);
void force_write(const int target,const size_t block,const size_t limit);
void copy_file(const int input,const int output,const long long int offset,const long long int stop);
void work(const char *source,const char *target,const char *position,const char *block);
void show_intro();
void show_help();

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
 int target=-1;
 if (name==NULL)
 {
  puts("Can't open the source file!");
  exit(1);
 }
 target=open(name,INPUT_FILE_MODE);
 if (target==-1)
 {
  puts("Can't open the source file!");
  exit(1);
 }
 return target;
}

int create_output_file(const char *name)
{
 int target=-1;
 if (name==NULL)
 {
  puts("Can't create or open the target file!");
  exit(2);
 }
 target=open(name,OUTPUT_FILE_MODE,OUTPUT_FILE_PERMISSIONS);
 if (target==-1)
 {
  puts("Can't create or open the target file!");
  exit(2);
 }
 return target;
}

long long int set_position(const int target,const long long int offset)
{
 long long int position=-1;
 position=file_seek(target,offset,SEEK_SET);
 if (position==-1)
 {
  puts("Can't jump to the start offset!");
  exit(3);
 }
 return position;
}

long long int get_file_size(const int target)
{
 long long int length=0;
 length=file_seek(target,0,SEEK_END);
 if (length==-1)
 {
  puts("Can't get the file size!");
  exit(4);
 }
 file_seek(target,0,SEEK_SET);
 return length;
}

void read_data(const int target,char *buffer,const size_t length)
{
 ptrdiff_t chunk=0;
 size_t total=0;
 for (total=0;total<length;total+=chunk)
 {
  chunk=read(target,buffer+total,length-total);
  if (chunk==0)
  {
   break;
  }
  if (chunk==-1)
  {
   show_message("Can't read data!");
   exit(5);
  }

 }

}

void write_data(const int target,const char *buffer,const size_t length)
{
 ptrdiff_t written=0;
 size_t total=0;
 for (total=0;total<length;total+=written)
 {
  written=write(target,buffer+total,length-total);
  if (written<=0)
  {
   show_message("Can't write data!");
   exit(6);
  }

 }

}

void check_range(const long long int length,const long long int offset,const long long int stop)
{
 if (offset>=length)
 {
  puts("The start offset is invalid!");
  exit(7);
 }
 if (stop==offset)
 {
  puts("The block length is invalid!");
  exit(8);
 }
 if (stop>length)
 {
  puts("The block length is too large!");
  exit(9);
 }

}

long long int decode_argument(const char *target)
{
 size_t index=0;
 size_t length=0;
 if (target!=NULL)
 {
  length=strlen(target);
 }
 if (length==0)
 {
  puts("Can't decode an argument");
  exit(10);
 }
 for (index=0;index<length;++index)
 {
  if (isdigit(target[index])==0)
  {
   puts("Can't decode an argument");
   exit(10);
  }

 }
 return strtoll(target,NULL,10);
}

char *get_memory(const size_t blocks)
{
 char *memory=NULL;
 memory=(char*)malloc(blocks);
 if (memory==NULL)
 {
  puts("Can't allocate memory!");
  exit(11);
 }
 return memory;
}

void show_progress(const long long int start,const long long int stop)
{
 putchar('\r');
 printf("The current position: %lld.The end data position: %lld. The operation progress:%lld%%",start,stop,(start*100)/stop);
}

void force_write(const int target,const size_t block,const size_t limit)
{
 static size_t written=0;
 written+=block;
 if (written>=limit)
 {
  file_sync(target);
  written=0;
 }

}

void copy_file(const int input,const int output,const long long int offset,const long long int stop)
{
 char *data=NULL;
 long long int position=0;
 size_t transfer=DATA_BLOCK_LENGTH;
 data=get_memory(transfer);
 for (position=set_position(input,offset);position<stop;position=file_seek(input,0,SEEK_CUR))
 {
  if ((stop-position)<=DATA_BLOCK_LENGTH)
  {
   transfer=(size_t)(stop-position);
  }
  show_progress(position,stop);
  read_data(input,data,transfer);
  write_data(output,data,transfer);
  force_write(output,transfer,DATA_LIMIT);
 }
 free(data);
}

void work(const char *source,const char *target,const char *position,const char *block)
{
 int input=-1;
 int output=-1;
 long long int offset=0;
 long long int stop=0;
 long long int length=0;
 input=open_input_file(source);
 length=get_file_size(input);
 stop=length;
 if (position!=NULL)
 {
  offset=decode_argument(position);
 }
 if (block!=NULL)
 {
  stop=offset+decode_argument(block);
 }
 check_range(length,offset,stop);
 output=create_output_file(target);
 show_message("Working... Please wait");
 copy_file(input,output,offset,stop);
 show_message("Data synchronization in progress. Please wait");
 file_sync(output);
 close(input);
 close(output);
 puts("The work has been finished");
}

void show_intro()
{
 putchar('\n');
 puts("Simple data copier");
 puts("The low-level file copying tool by Popov Evgeniy Alekseyevich, 2015-2026 years");
 puts("Version 2.0.3");
 puts("This software is distributed under the GNU GENERAL PUBLIC LICENSE (version 2 or later) terms");
}

void show_help()
{
 putchar('\n');
 puts("You must give the right command-line arguments!");
 puts("Simple data copier arguments: source,target,start,block");
 puts("source - The input file name.");
 puts("target - The output file name.");
 puts("start - The start offset (in bytes). 0 is the first byte. It is an optional argument.");
 puts("block - The block length (in bytes). It is an optional argument.");
}
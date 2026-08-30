#include "sdcopy.h"
#include "settings.h"
#include "exitcode.h"

void show_intro();
void show_help();
void show_message(const char *message);
void show_error(const char *message);
void show_system_error(const char *message,const int code);
void check_name(const char *name,const char *message,const int code);
void close_input_file(const int target);
void close_output_file(const int target);
int open_input_file(const char *name);
int create_output_file(const char *name);
long long int set_position(const int target,const long long int offset);
long long int get_position(const int target);
long long int get_file_size(const int target);
size_t read_data(const int target,unsigned char *buffer,const size_t length);
size_t write_data(const int target,const unsigned char *buffer,const size_t length);
void check_range(const long long int length,const long long int offset,const long long int stop);
long long int decode_argument(const char *target);
unsigned char *get_memory(const size_t blocks);
void show_progress(const long long int start,const long long int stop);
void force_write(const int target,const size_t block,const size_t limit);
void copy_file(const int input,const int output,const long long int offset,const long long int stop);
void work(const char *source,const char *target,const char *position,const char *block);

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
  exit(COMMAND_LINE_ARGUMENTS_ERROR);
  break;
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("Simple data copier 2.3.4");
 puts("The low-level file copying tool by Popov Evgeniy Alekseyevich, 2015-2026 years");
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

void show_message(const char *message)
{
 putchar('\n');
 puts(message);
}

void show_error(const char *message)
{
 fputc('\n',stderr);
 fputs(message,stderr);
 fputc('\n',stderr);
}

void show_system_error(const char *message,const int code)
{
 show_message(message);
 fputs(strerror(code),stderr);
 fputc('\n',stderr);
}

void check_name(const char *name,const char *message,const int code)
{
 size_t length=0;
 if (name!=NULL)
 {
  length=strlen(name);
 }
 if (length==0)
 {
  show_message(message);
  exit(code);
 }

}

void close_input_file(const int target)
{
 if (close(target)==-1)
 {
  show_system_error("Can't correctly close the source file!",errno);
  exit(CLOSE_SOURCE_ERROR);
 }

}

void close_output_file(const int target)
{
 if (close(target)==-1)
 {
  show_system_error("Can't correctly close the target file!",errno);
  exit(CLOSE_TARGET_ERROR);
 }

}

int open_input_file(const char *name)
{
 int target=-1;
 check_name(name,"The source file name is empty",EMPTY_SOURCE_NAME_ERROR);
 target=open(name,INPUT_FILE_MODE);
 if (target==-1)
 {
  show_system_error("Can't open the source file!",errno);
  exit(OPEN_FILE_ERROR);
 }
 return target;
}

int create_output_file(const char *name)
{
 int target=-1;
 check_name(name,"The target file name is empty",EMPTY_TARGET_NAME_ERROR);
 target=open(name,OUTPUT_FILE_MODE,OUTPUT_FILE_PERMISSIONS);
 if (target==-1)
 {
  show_system_error("Can't create or open the target file!",errno);
  exit(CREATE_FILE_ERROR);
 }
 return target;
}

long long int set_position(const int target,const long long int offset)
{
 long long int position=-1;
 position=file_seek(target,offset,SEEK_SET);
 if (position==-1)
 {
  show_system_error("Can't jump to the start offset!",errno);
  exit(SET_FILE_POSITION_ERROR);
 }
 return position;
}

long long int get_position(const int target)
{
 long long int position=-1;
 position=file_seek(target,0,SEEK_CUR);
 if (position==-1)
 {
  show_system_error("Can't get the current offset!",errno);
  exit(GET_FILE_POSITION_ERROR);
 }
 return position;
}

long long int get_file_size(const int target)
{
 long long int length=0;
 length=file_seek(target,0,SEEK_END);
 if (length==-1)
 {
  show_system_error("Can't get the file size!",errno);
  exit(GET_FILE_SIZE_ERROR);
 }
 file_seek(target,0,SEEK_SET);
 return length;
}

size_t read_data(const int target,unsigned char *buffer,const size_t length)
{
 ssize_t chunk=0;
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
   if (try_again==0)
   {
    show_system_error("Can't read data!",errno);
    exit(READ_DATA_ERROR);
   }
   else
   {
    chunk=0;
    continue;
   }

  }

 }
 return total;
}

size_t write_data(const int target,const unsigned char *buffer,const size_t length)
{
 ssize_t written=0;
 size_t total=0;
 for (total=0;total<length;total+=written)
 {
  written=write(target,buffer+total,length-total);
  if (written<=0)
  {
   if (try_again==0)
   {
    show_system_error("Can't write data!",errno);
    exit(WRITE_DATA_ERROR);
   }
   else
   {
    written=0;
    continue;
   }

  }

 }
 return total;
}

void check_range(const long long int length,const long long int offset,const long long int stop)
{
 if (offset>=length)
 {
  show_error("The start offset is invalid!");
  exit(INVALID_START_OFFSET_ERROR);
 }
 if (stop==offset)
 {
  show_error("The block length is invalid!");
  exit(INVALID_BLOCK_LENGTH_ERROR);
 }
 if (stop>length)
 {
  show_error("The block length is too large!");
  exit(LARGE_BLOCK_ERROR);
 }

}

long long int decode_argument(const char *target)
{
 long long int argument=0;
 size_t index=0;
 size_t length=0;
 if (target!=NULL)
 {
  length=strlen(target);
 }
 if (length==0)
 {
  show_error("Can't decode an argument");
  exit(DECODE_ARGUMENT_ERROR);
 }
 for (index=0;index<length;++index)
 {
  if (isdigit(target[index])==0)
  {
   show_error("Can't decode an argument");
   exit(DECODE_ARGUMENT_ERROR);
  }

 }
 argument=strtoll(target,NULL,10);
 if (errno==ERANGE)
 {
  show_system_error("Can't decode an argument",errno);
  exit(DECODE_ARGUMENT_ERROR);
 }
 return argument;
}

unsigned char *get_memory(const size_t blocks)
{
 unsigned char *memory=NULL;
 memory=(unsigned char*)malloc(blocks);
 if (memory==NULL)
 {
  show_error("Can't allocate memory!");
  exit(MEMORY_ALLOCATION_ERROR);
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
 unsigned char *data=NULL;
 long long int position=0;
 long long int elapsed=0;
 size_t written=0;
 size_t chunk=0;
 size_t transfer=DATA_BLOCK_LENGTH;
 data=get_memory(transfer);
 position=set_position(input,offset);
 while (position<stop)
 {
  elapsed=stop-position;
  if (elapsed<=DATA_BLOCK_LENGTH)
  {
   transfer=(size_t)elapsed;
  }
  chunk=read_data(input,data,transfer);
  if (chunk>0)
  {
   written=write_data(output,data,chunk);
   force_write(output,written,DATA_LIMIT);
  }
  else
  {
   show_message("The unexpected end of data");
   break;
  }
  position=get_position(input);
  show_progress(position,stop);
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
 close_output_file(output);
 close_input_file(input);
 puts("The work has been finished");
}
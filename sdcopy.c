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
void check_argument(const char *target);
long long int decode_argument(const char *target);
long long int check_input_file(const int input);
void check_range(const int target,const long long int offset,const long long int stop);
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
 int target;
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
 int target;
 target=open(name,OUTPUT_FILE_MODE,OUTPUT_FILE_PERMISSIONS);
 if (target==-1)
 {
  puts("Can't create or open the target file!");
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
  puts("Can't jump to the start offset!");
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
 printf("The current position: %lld.The end data position: %lld. The operation progress:%lld%%",start,stop,progress);
}

void check_argument(const char *target)
{
 size_t index,length;
 length=strlen(target);
 for (index=0;index<length;++index)
 {
  if (isdigit(target[index])==0)
  {
   puts("Can't decode an argument");
   exit(4);
  }

 }

}

long long int decode_argument(const char *target)
{
 check_argument(target);
 return atoll(target);
}

long long int check_input_file(const int input)
{
 long long int length;
 length=get_file_size(input);
 if (length==0)
 {
  puts("An input file with zero length is not supported");
  exit(5);
 }
 return length;
}

void check_range(const int target,const long long int offset,const long long int stop)
{
 long long int length;
 length=get_file_size(target);
 if ((offset>length)||(stop>length))
 {
  puts("This offset is invalid!");
  exit(6);
 }
 if (offset<1)
 {
  puts("The start offset is invalid! The minimal start offset: 1");
  exit(7);
 }

}

void copy_file(const int input,const int output,const long long int offset,const long long int stop)
{
 char *data=NULL;
 long long int position;
 size_t transfer;
 transfer=4096;
 position=set_position(input,offset);
 data=get_memory(transfer);
 while (position<stop)
 {
  if ((stop-position)<=(long long int)transfer)
  {
   transfer=(size_t)(stop-position);
  }
  read_data(input,data,transfer);
  write_data(output,data,transfer);
  position=file_seek(output,0,SEEK_CUR);
  show_progress(position,stop);
 }
 free(data);
}

void work(const char *source,const char *target,const char *position,const char *block)
{
 int input,output;
 long long int offset,stop;
 input=open_input_file(source);
 offset=1;
 stop=check_input_file(input);
 if (position!=NULL)
 {
  offset=decode_argument(position);
 }
 if (block!=NULL)
 {
  stop=(offset-1)+decode_argument(block);
 }
 check_range(input,offset,stop);
 output=create_output_file(target);
 show_message("Working... Please wait");
 copy_file(input,output,offset-1,stop);
 show_message("The work has been finished");
 close(input);
 close(output);
}

void show_intro()
{
 putchar('\n');
 puts("Simple data copier");
 puts("The low-level file copying tool by Popov Evgeniy Alekseyevich, 2015-2025 years");
 puts("Version 1.6.4");
 puts("This software is distributed under the GNU GENERAL PUBLIC LICENSE (version 2 or later) terms");
}

void show_help()
{
 putchar('\n');
 puts("You must give the right command-line arguments!");
 puts("Simple data copier arguments: source,target,start,block");
 puts("source - The input file name.");
 puts("target - The output file name.");
 puts("start - The start offset (in bytes). 1 is the first byte. It is an optional argument.");
 puts("block - The block length (in bytes). It is an optional argument.");
}
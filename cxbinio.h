#include<stdio.h>
#include<stdlib.h>
#include<string.h>

namespace cx
{
 template<typename T> int read_raw(const char *name,T*buf ,size_t len,int verbose=1)
 { 
    FILE *fin=fopen(name,"rb");  
    if(!fin){
        printf("Error: cannot open file %s\n",name);
        return 1;
    }
    size_t check=fread(buf,sizeof(T),len,fin);
    if(check!=len){
        printf("Error: cannot read file %s\n",name);
        return 1;
        fclose(fin);
    }
    if(verbose)printf("Read %s\n",name);
    fclose(fin);
    return 0;
 }

 template<typename T> int write_raw(const char *name,T*buf ,size_t len,int verbose=1)
 { 
    FILE *fout=fopen(name,"wb");  
    if(!fout){
        printf("Error: cannot open file %s\n",name);
        return 1;
    }
    size_t check=fwrite(buf,sizeof(T),len,fout);
    if(check!=len){
        printf("Error: cannot write file %s\n",name);
        return 1;
        fclose(fout);
    }   
    if(verbose)printf("Write %s\n",name);
    fclose(fout);
    return 0;
}

    template<typename T> int append_raw(const char *name,T*buf ,size_t len,int verbose=1){ 
        FILE *fout=fopen(name,"ab");
        if(!fout){
            printf("Error: cannot open file %s\n",name);
            return 1;
        }
        int check=(int)fwrite(buf,sizeof(T),len,fout);
        if(check!=len){
            printf("Error: cannot write file %s\n",name);
            return 1;
            fclose(fout);
        }
        if(verbose)printf("Append %s\n",name);
        fclose(fout);
        return 0;
     }

     template<typename T> int read_raw_skip(const char *name,T*buf ,size_t len,size_t skip,int verbose=0)
     { 
        FILE *fin=fopen(name,"rb");  
        if(!fin){
            printf("Error: cannot open file %s\n",name);
            return 1;
        }
        if(fseek(fin,skip*sizeof(T),SEEK_SET)){
            printf("Error: cannot seek file %s\n",name);
            return 1;
        }
        size_t check=fread(buf,sizeof(T),len,fin);
        if(check!=len){
            printf("Error: cannot read file %s\n",name);
            return 1;
            fclose(fin);
        }
        if(verbose)printf("Read %s\n",name);
        fclose(fin);
        return 0;
     }
     template<typename T>size_t length_of(const char*name){
        FILE *fin=fopen(name,"rb");
        if(!fin){
            printf("Error: cannot open file %s\n",name);
            return 1;
        }
        fseek(fin,0,SEEK_END);
        long offset=ftell(fin);
        fclose(fin);
        return len;
     }

     int can_bin_opened(const char *name){
        FILE *fin=fopen(name,"rb");
        if(!fin){
            printf("Error: cannot open file %s\n",name);
            return 1;
        }
        else{
            fclose(fin);
        }
        return 0;
     }
 }


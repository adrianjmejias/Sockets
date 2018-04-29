#include <util.h>
//#include <dirent.h>
vector<char*> segmentFile(char *path){

  File file;

  if((file = fopen(path, "r")) == NULL)
  {
    printf("error al intentar abrir %s\n", path);
    return NULL;
  }
  else
  {
    vector<char *> out;
    int inSize = 0, inChunkSize = 0;
    char in;

    while((in = getc(file)) != EOF){
      fputc(stdout);
    }


    fclose(file);
    return out;
  }

}
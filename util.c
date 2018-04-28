#include <dirent.h>


#include MAXPATH 256
#include FRAGMENT_SIZE 500


*char[] getFileNames(char *in_path){
    // var init 
    char* path;
    struct dirent* dent;
    DIR dirp;


    dirp = opendir(in_path);


    while(dirp != NULL)
    {
        dent = readdir(dirp);
        path = malloc(MAXPATH * sizeof(char));
        dent = sprintf(path);

        path
    }
    //-----------------------------

    void *recorrerArchivos(void *thread)
    {
      int taskid = *(int*)thread;
      DIR *dirp;
      struct dirent* dent;
    
      while(1)
      {
        sem_wait(scola + SEMCONTDIR);
    
        //printf("Paso %d\n", taskid);
        if(sembeta(SEMGTERMINO, &Gtermino, 0) == 1){
          //printf("MUERO %d\n", taskid);
          pthread_exit(0);
        }
        sembeta(SEMHESPERA, &hespera, -1);
        
        nodo nodoAVisitar = Desencolar(&aVisitar);
        dirp = opendir(nodoAVisitar.path);
        if(dirp==NULL){
          printf("NO SE ENCUENTRA EL DIRECTORIO\n");
          exit(0);
        }
        /*Inicio de lectura de directorio*/
        do{
          dent = readdir(dirp);
          if(dent==NULL)break;//NO borrar
          // Genero path
          char *path= malloc(PATHSIZE* sizeof(char));
          sprintf(path, "%s/%s", nodoAVisitar.path, dent->d_name);
    
          if (dent->d_type == DT_DIR)
          {
            if(strcmp(dent->d_name,".")!=0 && strcmp(dent->d_name,"..")!=0)
            { 
              Insertar(&aVisitar, path, NULL);
              sem_post(scola + SEMCONTDIR);//IMPORTANTEEEE
            }
          }
          else if (dent->d_type == DT_REG)
          {
            sol *auxsol=NULL;
            nodo a;
            a.path= path;
            a.hash= generarHash(a.path);
            //printf("\n[%s]---->[%s]\n", a.path, a.hash);
            if((auxsol= hayDuplicado(&visitado,a)) != NULL)
            {
              sem_wait(scola + SEMRESPUESTA);
              if(numDuplicados >= numMaxDuplicados)
              {
                respuesta = realloc (respuesta, (numMaxDuplicados + AUMENTO) * sizeof(sol));
                numMaxDuplicados += AUMENTO;
              }
              respuesta[numDuplicados] = *auxsol;
              numDuplicados++;
              sem_post(scola + SEMRESPUESTA);
            }else{
                Insertar(&visitado, a.path, a.hash);
            }
    
          }
        }while(1);
        closedir(dirp);
    
        if (sembeta(SEMHESPERA, &hespera, 1)==numHilos && colaVacia(&aVisitar))
        {
          //printf("<LIBERO %d>",taskid);
          sembeta(SEMGTERMINO, &Gtermino, 1);
    
          while(sembeta(SEMHESPERA, &hespera,-1)!=-1)
            sem_post(scola + SEMCONTDIR);
          }
    
          //printf("Salgo %d\n", taskid);
      }
    }
    
    sol* hayDuplicado(const Cola *cola, nodo a){
      nodo *aux; //lo usare para iterar
      if(strcmp(a.hash, HASH_EMPTY_FILE)==0){
        return NULL; //NO TOMO EN CUENTA ARCHIVOS VACIOS
      }
      waitpro(cola);
      //printf("hD");
      aux=cola->primero;
      while(aux!=NULL){
        if(strcmp(a.hash,aux->hash)==0){
          sol *respuestica= malloc(sizeof(sol));
          respuestica->a=a.path;
          respuestica->b=aux->path;
          //printf("hD");
          postpro(cola);
          return respuestica;
        }
        aux= aux->siguiente;
      }
      //printf("hD");
      postpro(cola);
      return NULL; 
    }
    
    char* generarHash(char* path){
      char *hash=malloc(HASHSIZE * sizeof(char));
      if(modo=='e')
      {
      pid_t pid; int fd[2], wstatus;
        pipe(fd);
        pid= fork();
        if(pid==0)
        {
          char *dir[]={"./md5",path,(char) 0};
          dup2 (fd[1], STDOUT_FILENO);
          execv("md5", dir);
          close(fd[0]);
          close(fd[1]);
          exit(0);
        }
        wait(&wstatus);
    
        read(fd[0], hash, HASHSIZE);
        close(fd[0]);
        close(fd[1]);
        return hash;
      }
      else
      if(modo='l')
      {
        MDFile(path,  hash);
        return hash;
      }
    }


}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE_BUFFER 2048
char line[SIZE_BUFFER];  		//line of arguments 

#define RECENT_HIST 10

/*
This function shows history for previously entered commands
A history of upto 10 commands is maintained
*/

int past_cmd(char *past[], int present)
{
        int past_num = 1;
        int i = present;
        do {
            if (past[i])
	    {
              printf("%d - %s\n",past_num,past[i]);
              past_num++;
            }
            i = (i + 1) % RECENT_HIST;
        } 
	while (i!= present);
        return 0;
}

/**
This function clears history of all previously entered commands
It clears the buffer which is used to maintain all the commands history 
*/
int clear_past_cmd(char *past[])
{
        int i;
        for (i = 0; i < RECENT_HIST; i++) 
        {
           free(past[i]);
           past[i] = NULL;
        }
        return 0;
}


/*
Funtion to parse commands from shell input
A token is used to separate command arguments and 
stored into argument vector
*/
int parsedArgument(char **argv)
{
	char *token;                        //seprating strings of a command
	int i=0;

	token = strtok(line," ");	
	while(token!=NULL){
	  argv[i]=token;      
	  token = strtok(NULL," ");
	  i++;
	}
	argv[i]=NULL;                     
	return i;	
}

/*
Execute command by forking new process
The child process executes requested command
**/
void executeCmd(char **argv, char *full_dir_struct)
{
	int pid;			//process id      
	pid= fork();			//parent and Child process fork and termination

	//printf("Child process is forked\n");              
	if(pid==0)
	{               
		//printf("Child process in execution\n");
		execvp(full_dir_struct,argv);
		fprintf(stderr, "Error :Invalid command\n");
	}	    
	else
	{                    
	wait(NULL);
	//printf("Child process terminated\n");
	}
	
}

int main(){   

    char full_dir_struct[20];           //full file path
    char* dir_struct= "/bin/";          //set dir_struct at bin   
    int argc;                           //arg count 
    char* argv[100];         		//vector of argument
    char *past[RECENT_HIST];		//buffer to maintain history
    int i, present = 0;			//keep track of current command

    	for (i = 0; i < RECENT_HIST; i++){
                past[i] = NULL;
	}

	//Run the loop continously for shell to be active in terminal
	//"exit" command or Ctrl+C terminates the shell
	    while(1){

		    printf("g15shell>");                        
		    if(!fgets(line,SIZE_BUFFER,stdin)){    
			break;                                 
		    }
		     
		    size_t line_len= strlen(line);
		    if(line[line_len - 1] == '\n'){
		          line[line_len - 1]='\0';
		    }
			           	     
		    if(strcmp(line, "exit")==0){
		        break;
		    }
		    
		    argc=parsedArgument(argv);  		 //set the count of args
				         
		    strcpy(full_dir_struct, dir_struct);         
		    strcat(full_dir_struct, argv[0]);            //add program to path

		    for(i=0; i<strlen(full_dir_struct); i++){    //delete newline
			if(full_dir_struct[i]=='\n'){      
			    full_dir_struct[i]='\0';
			}
		    }

		    free(past[present]);
		    past[present] = strdup(line);
		    present = (present + 1) % RECENT_HIST;

				if (strcmp(line, "history") == 0)	
				{
			                past_cmd(past, present);
				}
			        else if (strcmp(line, "clearhist") == 0)  
				{	                        
					clear_past_cmd(past);
				}			
				else 
				{
		    			executeCmd(argv,full_dir_struct);
		    		}

		}

 return 0;
} 



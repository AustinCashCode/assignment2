#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

#define IO_BUFFER 256



typedef struct my_movie {
    char * title;
    int    year;
    char * language;
    double rating;

    struct my_movie * next;

} movie_t;


void process_file(FILE *file, char * filename) {
    printf("Now processing the chosen file named %s", filename);
    
    return;
}


//Finds the largest movie_*.csv file 
//by filesize and opens it to be processed
//for process_file.
void process_largest() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat file_stat;
    char filepath[2048];
    off_t largest = 0;
    char largest_fname[256] = {0};

    while (entry = readdir(dir)) {
        if(strncmp(entry -> d_name, "movies_", 7) == 0 && strstr(entry -> d_name, ".csv") != NULL) {
            snprintf(filepath, sizeof(filepath), "%s/%s", ".", entry->d_name);

        if (stat(filepath, &file_stat) == 0) {
            if (file_stat.st_size > largest) {
                largest = file_stat.st_size;
                strncpy(largest_fname, filepath, sizeof(largest_fname));
                }
            }   
        }
    }

    closedir(dir);

    if(largest_fname[0]) {
        FILE *file = fopen(largest_fname, "r");

        if(!file) {
            fprintf(stderr, "Could not open largest file\n");
        }

        process_file(file, largest_fname);
        fclose(file);
    }
    else {
        fprintf(stderr, "No file matching format: movies_*.csv\n");
    }

    return;
}



//Finds the smallest movie_*.csv file 
//by filesize and opens it to be processed
//for process_file.
void process_smallest() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat file_stat;
    char filepath[2048];
    off_t smallest = LLONG_MAX;
    char smallest_fname[256] = {0};

    while (entry = readdir(dir)) {
        if(strncmp(entry -> d_name, "movies_", 7) == 0 && strstr(entry -> d_name, ".csv") != NULL) {
            snprintf(filepath, sizeof(filepath), "%s/%s", ".", entry->d_name);

        if (stat(filepath, &file_stat) == 0) {
            if (file_stat.st_size <= smallest) {
                smallest = file_stat.st_size;
                strncpy(smallest_fname, filepath, sizeof(smallest_fname));
                }
            }   
        }
    }

    closedir(dir);

    if(smallest_fname[0]) {
        FILE *file = fopen(smallest_fname, "r");

        if(!file) {
            fprintf(stderr, "Could not open largest file\n");
        }

        process_file(file, smallest_fname);
        fclose(file);
    }
    else {
        fprintf(stderr, "No file matching format: movies_*.csv\n");
    }

    return;
}


//Gets input from the user for which file
//they want to process.
//Returns 1 on succes, and 0 if the file was not found
//Prints an error to stderr if the file was not found
int process_custom() {
    char buffer[IO_BUFFER];
    int length = 0;

    //The next two lines of code is not mine, it was provided by 
    //stackoverflow commenter M.M in 2014. See
    //https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c

    //This loop clears the input buffer. If you are wondering why I don't just use
    //fflush, fflush on stdin is considered undefined behavior, and is not portable.
    //I made the error of including both scanf() and fgets() in this program, so
    //I have to clear the stdin buffer before I can actually do anything else.
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }

    printf("Enter the complete file name: ");
    fgets(buffer, IO_BUFFER, stdin);

    //fgets gets the newline character, so we need to replace it
    //with a null character
    if(length = strlen(buffer)) {
        buffer[length - 1] = '\0';
    }

    FILE *file = fopen(buffer, "r");

    if(!file) {
        fprintf(stderr, "The file %s was not found. Try again\n\n", buffer);
        return 0;
    }
    
    process_file(file, buffer);
    fclose(file);

    return 1;
}



void choose_action() {
    int sw_nav = 0;
    int ret_nav = 0;

    while(ret_nav == 0){
        printf(
            "Which file you want to process?\n"
            "Enter 1 to pick the largest file\n"
            "Enter 2 to pick the smallest file\n"
            "Enter 3 to specify the name of a file\n\n"
            "Enter a choice from 1 to 3:  "
        );

        scanf("%d", &sw_nav);

        //This switch will call the appropriate function.
        //The process functions are really just wrappers
        //for the process_file() function, so we get
        //any input we need in those functions.
        switch (sw_nav) {
            case 1:
                process_largest();
                ret_nav = 1;
                break;

            case 2:
                process_smallest();
                ret_nav = 1;
                break;

            case 3:
                //
                ret_nav = process_custom();
                break;
            
            default:
                fprintf(stderr, "Invalid entry, returning to main menu\n");
                break;
        }
    }
    return;
}




int main(void)
{
    int nav = 0;
    char input[IO_BUFFER];


    while(nav != 2)
    {
        printf("1. Select file to process\n2. Exit the program.\n\n");
        printf("Enter a choice 1 or 2: ");
        scanf("%d", &nav);
        printf("\n");

        if(nav != 1 && nav != 2) {
            fprintf(stderr, "Please enter 1. or 2.\n");
        }
        if (nav == 1) {
            choose_action();
        }
    }
    return EXIT_SUCCESS;
}
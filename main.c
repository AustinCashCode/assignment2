#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IO_BUFFER 1000



typedef struct my_movie {
    char * title;
    int    year;
    char * language;
    double rating;

    struct my_movie * next;

} movie;


void process_file() {
    return;
}



void process_largest() {
    return;
}


void process_smallest() {
    return;
}


void process_custom() {
    return;
}




int main(void)
{
    int nav = 0;
    int sw_nav = 0; //used for the switch statement
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
        else if (nav == 1) {
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
                    break;

                case 2:
                    process_smallest();
                    break;

                case 3:
                    process_custom();
                    break;
                
                default:
                    fprintf(stderr, "Invalid entry, returning to main menu\n");
                    break;
            }
        }
    }
    return EXIT_SUCCESS;
}
// Source: A2.c
// Purpose: Implementation and main program file for Assignment 2
/* Authors:
    mefitzge Fitzgerald, Maeve 500838853 Section 4
    comanuel Manuel, Christian 501001682 Section 4
    irajwani Rajwani, Inaya    501037903 Section 7
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int seed;                       //edited from char *seed
FILE *file;
int card[5][5];
int marks[5][5];

/* FUNCTION PROTOTYPES */

int fileCheck (void);
int cardCheck (void);
int cardDisplay (void);
int getCallNum (void) { return rand () % 75 + 1; } // Returns random number in range [1,75]
int checkMatches (int callNum);
int checkWin (struct List *listAddress);

void main (int argc, char **argv)
{

    /* Command line argument reading */
    seed = atoi (argv[1]);      // convert char[] input seed to int
    file = fopen (argv[2], "r");
    fileCheck ();
    cardCheck ();

    /* Init variables */
    char inputStr[76];
    struct List callList;
    init (&callList, 75);

    srand (seed);                       // set seed for rand()

    system ("clear");           // initial clear and display
    cardDisplay ();
    print (&callList);


    /* RUNTIME LOOP */
    while (1) {


      // Prompt for input, do nothing while input == '\n'
      do {
          fgets (inputStr, 76, stdin);  // ** pauses execution here
        }
      while (inputStr[0] == '\n');

      // Cont. user input loop. Iterate the game as many times as characters inputted by user
      int strInd = 0;
      while (inputStr[strInd] != '\0' && inputStr[strInd] != '\n') {

          if (inputStr[strInd] == 'q') {
              printf ("User exit. Thanks for playing!\n");
              exit (0);
          }

          /* Generate new unique call number */
          int callNum = 0;
          int flag=0;
          while (flag==0) {
              callNum = getCallNum ();  // generate new callNum
              if (!check(&callList, callNum)) {
                   add(&callList,callNum);
                   flag=1;
              }
          } // check if callNum is in the list. if so, then generate new callNum until its unique


          /* Display */
          system("clear");
          checkMatches (callNum);
          cardDisplay ();
          print (&callList);

          /* End display */
          checkWin (&callList); // changed argument type of this function to pass the call list so that we can print it at the end. Sorry!
          strInd++;


        }

    }                           /* END RUNTIME LOOP */

  }                             /* END MAIN */


int fileCheck (void) {

  int c;
  int count = 1;
  int linecount = 0;
  int numPerLine = 0;
  int tens = 0;
  int ones = 0;

  if (file == NULL)
    {
      printf ("cannot find/read file\n");
      exit (1);
    }
  c = fgetc (file);
  while (c != EOF)
    {

      //1. Check for two-digit numbers
      if ((count % 3) == 1)
        {
          int digit = isdigit (c);
          if (!digit)
            {
              printf
                ("The card must be a matrix of two-digit numbers seperated by a space -digit issue\n");
              exit (4);
            }

        }
           if ((count % 3) == 2)
        {
          int digit = isdigit (c);
          if (!digit)
            {
              printf
                ("The card must be a matrix of two-digit numbers seperated by a space -digit issue\n");
              exit (4);
            }
        }

      //2. Check for space between two digit numbers
      if ((count % 3) == 0)
        {
          int space = isspace (c);
          if (!space)
            {
              printf
                ("The card must be a matrix of two-digit numbers seperated by a space -space issue\n");
              exit (4);
            }
          else
            {
              numPerLine++;
            }
        }

      //load card
      if ((count % 3) == 1)
        {
          tens = c - '0';
        }
      if ((count % 3) == 2)
        {
          ones = c - '0';
        }
      if ((count % 3) == 0)
        {
          card[(linecount)][(numPerLine - 1)] = (tens * 10) + ones;
          marks[linecount][(numPerLine - 1)] = 0;
        }

      //3. Process the end of each line, check for 5 2-digit numbers
      if (c == '\n')
        {
          if (numPerLine == 5)
            {
              linecount++;
              numPerLine = 0;
            }

        }

      c = fgetc (file);
      count++;

    }

   //Check the last line's info
  if (numPerLine == 4 && count == 75)
    {
      linecount++;
      numPerLine = 0;
    }
  else if (!c == '\n')
    {
      printf ("Must have 5 2-digit per line, problem at count = %d \n",
              count);
      exit (3);
    }

  //4.Check number of lines
if ((linecount != 5) || (count > 76))
  {
    printf ("Wrong number of lines\n");
    exit (2);
  }



// Done checks; load card into memory
card[linecount][(numPerLine - 1)] = (tens * 10) + ones;
marks[linecount][(numPerLine - 1)] = 0;
marks[2][2] = 1;

c = fgetc (file);
fclose (file);
return 0;
}

int cardCheck (void) {

  int i, j, k;
  for (i = 0; i < 5; i++)
    {
      for (j = 0; j < 5; j++)
        {
          int min = (j * 15) + 1;
          int max = ((j + 1) * 15);
          if (i == 2 && j == 2)
            {
              if (card[i][j] != 0)
                {
                  printf ("Middle space must be 00\n");
                  exit (4);
                }
            }
          else if (card[i][j] < min || (card[i][j] > max))
            {
              printf
                ("Values must be in the correct range of their column\n");
              exit (4);
            }
          for (k = 0; k < 5; k++)
            {
              if ((card[i][j] == card[k][j]) && (i != k))
                {
                  printf ("Card cannot have repeat values\n");
                  exit (4);
                }
            }
        }
    }
}

int cardDisplay (void) {
  printf ("L  I  N  U  X \n");
  int i = 0;
  int j = 0;
  for (i = 0; i < 5; i++)
    {
      for (j = 0; j < 5; j++)
        {
          if (card[i][j] < 10)
            {
              printf ("0");
            }
          printf ("%d", card[i][j]);
          if (marks[i][j])
            {
              printf ("M");
            }
          else
            {
              printf (" ");
            }
        }
      printf ("\n");
    }

}

int checkMatches (int callNum) {
  int i;
  int j;
  for (i = 0; i < 5; i++)
    {
      for (j = 0; j < 5; j++)
        {
          if ((card[i][j]) == callNum)
            {
              marks[i][j] = 1;
            }
        }
    }
}

int checkWin (struct List *listAddress) { // added callList as argument so can print the call list at the end properly
    int i;
    int j;
  for (i = 0; i < 5; i++)
    {
      if (marks[i][0] && marks[i][1] && marks[i][2] && marks[i][3]
          && marks[i][4])
        {
          system ("clear");
          cardDisplay ();
          print(listAddress); // added print of call list to all win messages
          printf ("WINNER\n");
          exit (0);
        }
    }
   for (j = 0; j < 5; j++)
    {
      if (marks[0][j] && marks[1][j] && marks[2][j] && marks[3][j]
          && marks[4][j])
        {
          system ("clear");
          cardDisplay ();
          print(listAddress);
          printf ("WINNER\n");
          exit (0);
        }
    }

  if (marks[0][0] && marks[0][4] && marks[4][0] && marks[4][4])
    {
      system ("clear");
      cardDisplay ();
      print(listAddress);
      printf ("WINNER\n");
      exit (0);
    }
    if (marks[0][0] && marks[1][1] && marks[3][3] && marks[4][4])
    {
      system ("clear");
      cardDisplay ();
      print(listAddress);
      printf ("WINNER\n");
      exit (0);
    }
    if (marks[0][4] && marks[1][3] && marks[3][1] && marks[4][0])
    {
      system ("clear");
      cardDisplay ();
      print(listAddress);
      printf ("WINNER\n");
      exit (0);
    }
  return 0;
}
         
                                                                                                        

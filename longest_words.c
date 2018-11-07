#include <stdio.h>
#include <string.h>

#define LONGEST_WORDS_COUNT     (10)

int main(int argc, char *argv[]){
    char    arrLongestWords[LONGEST_WORDS_COUNT][256];
    int     index_ShortestInArray = 0;
    int     len_ShortestInArray = 0;
    FILE*   fp;
    char *filename = NULL;
    
    memset( arrLongestWords, 0, sizeof(arrLongestWords));

    //1. Input: read the text file from the command line
    if (argc < 2){
        printf("Missing Filename\n");
        return(1);
    }else{
        filename = argv[1];
    }
  
    fp = fopen(filename,"r");
    if ( fp )
    {
        char * sCurWord = NULL;
        size_t len = 0;
        ssize_t read;
        //2. loop through each lines
        while ((read = getline(&sCurWord, &len, fp)) != -1) {
            //3. if the current line is longer than the short one in the array, copy it
            int lenCurWord = (int)strlen(sCurWord);
            if (lenCurWord > len_ShortestInArray ) {
                strcpy(arrLongestWords[index_ShortestInArray], sCurWord);

                //4. Re-calculate, update the shortest word index and len:
                index_ShortestInArray    = 0;
                len_ShortestInArray = (int)strlen(arrLongestWords[0]);
                for( int i=0; i<LONGEST_WORDS_COUNT; i++)
                {
                    if( strlen( arrLongestWords[i]) < strlen( arrLongestWords[index_ShortestInArray]))
                    {
                        index_ShortestInArray = i;
                        len_ShortestInArray = (int)strlen(arrLongestWords[i]);
                    }
                }
                
            }
        }
    }else{
        printf("Failed to open the file\n");
    }
    fclose(fp);
  
    //5. Output: print out the 10 longest words in random order:
    printf("\nThe %d longest words in random order:\n", LONGEST_WORDS_COUNT);
    for( int i=0; i<LONGEST_WORDS_COUNT; i++)
    {
        printf( "%s", arrLongestWords[i]);
    }
    
    return 0;
}

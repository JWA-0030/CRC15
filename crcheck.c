#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N strlen(binArr)
#define G strlen(g)

char* fileArray(FILE *ifp);

char t[64], cs[1000], temp2[12], binArr[1000],temporaryArr[1000], g[]="1010000001010011";
//this is current line
char tempArray[1000];


/*so this is supposted to compared the values at each index and assign
either a zero or one to a new outcome array but it doesnt work. this needs
to move down the binary array and keep looping through the g(given) array
or the polynomial. and keep sending the output to the temporaryArr*/
void xor(int start){

    int end = start + G;
    int k = 0, c;
    for(c = start;c < end; c++){
        temporaryArr[c] = ((binArr[c] == g[k]) ? '0' : '1');
        k++;
    }
}
/*so this should set the beginning of our array to the first array then send in the array to be xorred. */
void crc(){

    int start = 0;

    while(start <= 512)
    {
        if(binArr[start] == '1')
        {
            xor(start);
            start = start + G;
        }
        start++;
    }
}

long decimalToBinary(unsigned n) {

    int remainder;
    long binary = 0, i = 1;

    while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }

    return binary;
}


int main(int argc, char **argv){

    int i, j, k = 0, myArrayLength = 0, var = 0, errflag = 0;
    long tempBin = 0;
    unsigned temp = 0;

    if(strcmp(argv[1], "v") == 0)
        errflag++;
    if(strcmp(argv[1], "c") == 0)
        errflag++;

    if(errflag != 1)
    {
        return 0;
    }

    FILE *ifp = fopen(argv[2], "r");

    if(ifp == NULL)
        return 0;


    char* myArray = fileArray(ifp);

    char* tempArray = calloc(64, 1);

        for(j = 0; j < 64; j++){
            tempArray[j] = myArray[k];
            k++;
        }

    for(i = 0;i < 64; i++){
        tempBin = decimalToBinary((unsigned)tempArray[i]);

        if(var == 0){
            sprintf(binArr, "%08ld", tempBin);
            var = 1;
        }
        else{
            sprintf(temp2, "%08ld", tempBin);
            strcat(binArr, temp2);
        }
    }

    crc();

    myArrayLength = strlen(myArray);

    for(i = 0; i < myArrayLength; i++){
        printf("%c", myArray[i]);
        if(((i + 1) % 64) == 0){
            printf(" - %08x", temp);
              printf("\n");
        }
    }
    //final crc value but havent finished it yet
    printf("%08x - %08x", temp, temp);

    //Cleanup
    fclose(ifp);
    free(myArray);

	return 0;
}


char* fileArray(FILE *ifp){

    int i, k, counter = 0, fileSize = 0;
    char* myArray;

    fseek(ifp, 0L, SEEK_END);
    fileSize = ftell(ifp);
    rewind(ifp);

    myArray = calloc(504, 1);

    if(!myArray){
        exit(1);
    }

    fread(myArray, fileSize, 1, ifp);

    while(fileSize != 504){
        strcat(myArray, ".");
        fileSize++;
    }

    return myArray;
}




#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct possible_indexArray_and_events{
	int event;
	int col;
	int row;
}possible;

void printPuzzle(char puzzle[100][100], int count){
	int i,j;
	for(i=0;i<count;i++){
		for(j=0;j<strlen(puzzle[i]);j++){
			printf("%c",puzzle[i][j]);
		}
		printf("\n");
	}
}

void fill_hor(char puzzle[100][100], char * word, possible hor){
	int col=hor.col;
	int row=hor.row;
	int i,j,k=0;
	for(i=col;i<col+strlen(word); i++){
		puzzle[row][i]=word[k];
		k++	;	
	}
}

void fill_ver(char puzzle[100][100], char * word, possible ver){
	int col=ver.col;
	int row=ver.row;
	int i,k=0;
	for(i=row;i<row+strlen(word); i++){
		puzzle[i][col]=word[k];
		k++;
		
	}
}

possible possible_horizontal(char * word, char puzzle[100][100],int puzzleRows){
	int col, row, q=0;
	int spaces=0;
	possible horizontal;
	horizontal.event=0;

	for (row=0; row<puzzleRows; row++){
		spaces=0;
		for (col=0; col<strlen(puzzle[row]); col++){
			if(puzzle[row][col]=='#' || puzzle[row][col]==word[spaces]){
				spaces++;
			}else{
				if(spaces==strlen(word)){
					horizontal.event++;
					horizontal.row=row;
					horizontal.col=col-strlen(word);
				}
				spaces=0;
			}
		}
		if(spaces==strlen(word)){
			horizontal.event++;
			horizontal.row=row;
			horizontal.col=col-strlen(word);
		}
	}

	return horizontal;
}

possible possible_vertical(char * word, char puzzle[100][100],int puzzleRows){
	int col, row, q=0;
	int spaces=0;
	possible horizontal;
	horizontal.event=0;

	for (col=0; col<strlen(puzzle[0]); col++){
		spaces=0;
		for (row=0; row<puzzleRows; row++){
			if(puzzle[row][col]=='#' || puzzle[row][col]==word[spaces]){
				spaces++;
			}else{
				if(spaces==strlen(word)){
					horizontal.event++;
					horizontal.col=col;
					horizontal.row=row-strlen(word);
				}
				spaces=0;
			}
		}
		if(spaces==strlen(word)){
			horizontal.event++;
			horizontal.col=col;
			horizontal.row=row-strlen(word);
		}
	}

	return horizontal;
}



int main(){
	static char puzzle[100][100];
	char words[100][100];
	char character;
	int i=0,j=0,newline_count=0;
	while (newline_count<2){
		
		scanf("%c", &character);
		
		if(character == '\n'){
			newline_count++;
			
		}else {
			newline_count=0;
			puzzle[i][j]=character;
			j++;
		}
		if(newline_count==1){
				i++;
				words[i][j]='\0';
				j=0;
		}
	}
	
	int row_count=i;
	newline_count = 0;
	i=0; j=0;
	
	while (newline_count<2){
		
		scanf("%c", &character);
		
		if(character == '\n'){
			newline_count++;
			
		}else {
			newline_count=0;
			words[i][j]=toupper(character);
			j++;
		}
		if(newline_count==1){
			i++;
			words[i][j]='\0';
			j=0;
		}
	}
	
	int word_count = i;

	for(i=0;i<word_count;i++){
		possible hor,ver;

		hor = possible_horizontal(words[i],puzzle,row_count);
		ver = possible_vertical(words[i],puzzle,row_count);

		if (hor.event==1){
			fill_hor(puzzle,words[i], hor);
		}else if(ver.event == 1){
			fill_ver(puzzle,words[i], ver);
		}else if(hor.event + ver.event==0){
			printf("IMPOSSIBLE\n");
			return 0;
		}
	}

	
	printPuzzle(puzzle, row_count);

		
return 0;
}

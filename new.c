#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct possible_indexArray_and_events{
	int event;
	int col;
	int row;
}possible;


void printPuzzle(char puzzle[100][100], int count){
	int i,j;
	for(i=0;i<count;i++){
		for(j=0;j!='\0';j++){
			printf("%c",puzzle[i][j]);
		}
		printf("\n");
	}
}

void fill_hor(char puzzle[100][100], char words[100][100], possible hor, int length,int count){
	int col=hor.col;
	int row=hor.row;
	int i,j,k;
	for(i=col;i<=length; i++){
		for(k=0; k<=length; k++){
			puzzle[row][i]=words[count][k];
		}
	}
}

void fill_ver(char puzzle[100][100], char words[100][100], possible ver, int length,int count){
	int col=ver.col;
	int row=ver.row;
	int i,k;
	for(i=row;i<=length; i++){
		for(k=0; k<=length; k++){
			puzzle[row][i]=words[count][k];
		}
	}
}

possible possible_horizontal(int length, char puzzle[100][100],int puzzleRows){
	int col, row;
	int count=0,spaces=0;
	possible horizontal;
	horizontal.event=0;
	for (row=0; row!=puzzleRows; row++){
		for (col=0; col='\0'; col++){
			if(puzzle[row][col]=='#'){
				spaces++;
				count++;
			}else{
				if(spaces==length){
					horizontal.event++;
					horizontal.row=row;
					horizontal.col=col-length;
				}
				spaces=0;
				count=0;
			}
		}
		if(spaces==length){
			horizontal.event++;
			horizontal.row=row;
			horizontal.col=col-length;
		}
		spaces=0;
		count=0;
	}

	return horizontal;
}

possible possible_vertical(int length, char puzzle[100][100], int puzzle_rows){
	int col, row;
	int count=0,spaces=0;
	possible vertical;
	vertical.event=0;
	for (col=0; col='\0'; col++){
		for (row=0; row!=puzzle_rows; row++){
			if(puzzle[row][col]=='#'){
				spaces++;
				count++;
			}else{
				if(spaces==length){
					vertical.event++;
					vertical.row=row-length;
					vertical.col=col;
				}
				spaces=0;
				count=0;
			}
		}
		if(spaces==length){
			vertical.event++;
			vertical.row=row-length;
			vertical.col=col;
		}
		spaces=0;
		count=0;
	}

	return vertical;
}
		

int main(){
	static char puzzle[100][100];// puzzle array
	char line[100]; //scanning words
	char words[100][100];// word array
	int length[10];// array of lengths of words
	char character;// scanning inputs
	int row_p=0,col_p=0,row_w=0,col_w=0,newline_count=0;

	while (newline_count<2){
		scanf("%c", &character);
		if (character!='\n'){
			puzzle[row_p][col_p]=character;
			col_p++;
		}else{
			puzzle[row_p][col_p ++]='\0';
			row_p++;
			col_p=0;
			newline_count++;
		}
			
	}
	int puzzle_rows = row_p;	

	while (newline_count<4){
		scanf("%c", &character);
		if (character!='\n'){
			words[row_w][col_w]=toupper(character);
			col_w++;
		}else{
			puzzle[row_w][col_w ++]='\0';
			row_w++;
			col_w=0;
			newline_count++;
		}
			
	}
	int word_count=row_w;

	int count;
	for (count=0; count<=word_count; count++){
		possible hor,ver;
		int word_length=length[count];

		hor= possible_horizontal(word_length,puzzle,puzzle_rows);
		ver= possible_vertical(word_length,puzzle,puzzle_rows);

		if (hor.event + ver.event==1){
			if(hor.event==1){
				fill_hor(puzzle,words, hor, word_length,count);
			}else{
				fill_ver(puzzle,words, ver, word_length,count);
			}
		}
	}


	
	printPuzzle(puzzle, puzzle_rows);

			
return 0;
}

						/***************************/
						/*                         */
						/*      Osman Çetin        */
						/*       161044069         */
						/*         HW-09           */
						/*		                   */
						/***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/*In this homework, I implemented a game. A botanist looking for a quite rare flower by walking randomly in a forest. He/she is sure about that the rare flower in that forest certainly. He must find the rare flower before his water runs out. Otherwise, he faints in the forest.*/


typedef struct forest{/*this structure contains forest's components*/
	int width;
	int height;
	int **map;
	int flower_x; 
	int flower_y;
}f1; 

typedef struct botanist{/*this structure contains botanist's components*/
	int coord_x;
	int coord_y;
	int water_bootle_size;
}b1;

void init_game (f1 *forest, b1 *botanist);
void print_map(f1 forest);/*these are function's prototypes*/
void search(f1 *forest,b1 *botanist,int *found);

int main(){
	int first_x,first_y,found=5,i;
	srand(time(NULL));
	f1 forest;/*I defined new forest*/
	b1 botanist;/*ı defined new botanist*/
	init_game (&forest, &botanist);
	first_x=botanist.coord_x; first_y=botanist.coord_y;/*these are botanist's first coordinates*/
	print_map(forest);
	printf("\nSearching...\n\n");
	search(&forest,&botanist,&found);
	
	if(found==1){/*this condition works when flower is found*/ 
		forest.map[first_x][first_y]=' ';
		print_map(forest);
		printf("I have found it on (%d,%d)!\n",botanist.coord_x,botanist.coord_y);
	
	}
	else if(found==0){/*this function works when flower is not found*/
		forest.map[first_x][first_y]=' ';
		print_map(forest);
		printf("Help! I am on (%d,%d)!\n",botanist.coord_x,botanist.coord_y);
	}
    for (i = 0; i < forest.height; ++i) {/*this does freeing to forest map*/
        free(forest.map[i]);
    }
    free(forest.map);
}

void init_game (f1 *forest, b1 *botanist){/*This function reads a csv file called "init.csv" and initiates both the forest and the botanist. The first line contains volume of Botanist's water bottle. The second line contains height and width of the forest. Starting from the third line, forest map is defined. Trees, the botanist and the rare flower are illustrated as #, B and F.*/
	
	char a,b,c,temp[100];
	int i=0,j=0,l,k;
	FILE *fl;
	fl=fopen("init.csv","r");/*this function opens text for reading*/
	
	fgets(temp,100,fl);/*this function gets water bootle size from text*/
	botanist->water_bootle_size=atoi(temp);/*aoti function can convert char type to integer*/
	
	fscanf(fl,"%d,%d\n",&forest->height,&forest->width);/*this gets height and width of forest from text*/
		
	
	forest->map = (int **)calloc((forest->height) , sizeof(int*));/*this specify dimentions of map with using calloc function*/
	
	for(k=0;k<forest->height;k++){
		forest->map[k] = (int *)calloc((forest->width) , sizeof(int));
	}
	
	for(i=0;i<forest->height;i++){/*this loop gets map from text letter-by-letter*/	
		for(j=0;j<forest->width;){
			a=fgetc(fl);/*this gets letter from text*/
			if(a=='#' || a==' ' || a=='F' || a=='B'){/*If the letter is one of them, letter assigns to map*/
				forest->map[i][j]=a;
				j++;
			}
			
			if(a=='\n'){/*if cursor comes to line break,cursor goes next line*/ 
				j=forest->width+1;
				i--;
			}
			
			if(a=='B'){/*if cursor comes to 'B', assings coorditanes to botanist's coordinates*/ 
				botanist->coord_x=i;
				botanist->coord_y=j-1;
			}
			
			if(a=='F'){/*if cursor comes to 'F', assings coordinates to flower's coordinates*/
				forest->flower_x=i;
				forest->flower_y=j-1;
			}
		}
	}
	
	fclose(fl);/*this closes text*/

}

void print_map(f1 forest){/*This function shows the forest map on screen.*/
	int i,j;
	for(i=0;i<forest.height;i++){
		for(j=0;j<forest.width;j++){
			printf("%c ",forest.map[i][j]);
		}
		printf("\n");
	}
}

void search(f1 *forest,b1 *botanist,int *found){/*This is a recursive function that walks (up, down, left and right) on the forest to find the rare flower. Botanist is so thirsty that he/she drinks his/her water 1 ml at every step. Botanist says "I have found it on (x,y)!" whenever he/she finds it before his/her water runs out. Otherwise, he shouts out "Help! I am on (x,y)" and faints.*/
	
	int move;

	move=rand()%4;/*this choose move randomly*/
	
	if(botanist->coord_x==forest->flower_x && botanist->coord_y==forest->flower_y){/*if botanist finds flower found will be 1*/
		*found=1;
		
		return ;
	}
	
	if(botanist->water_bootle_size==0){/*if botanist's water run out, found will be 0*/ 
		*found=0;
		forest->map[botanist->coord_x][botanist->coord_y]='B';
		return ;
	}
	
	
	if(move==0 && forest->map[botanist->coord_x-1][botanist->coord_y]!='#' ){/*this is up move condition*/
		botanist->coord_x=botanist->coord_x-1;
		botanist->water_bootle_size=botanist->water_bootle_size-1;
		search(&*forest,&*botanist,&*found);
	}
	
	
	else if(move==1 && botanist->coord_x < forest->height-1 && forest->map[botanist->coord_x+1][botanist->coord_y]!='#' ){/*this is down move condition*/	
			botanist->coord_x=botanist->coord_x+1;
			botanist->water_bootle_size=botanist->water_bootle_size-1;
			search(&*forest,&*botanist,&*found);
		
	}
	
	else if(move==2 && botanist->coord_y > 0 &&forest->map[botanist->coord_x][botanist->coord_y-1]!='#' ){/*this is left move condition*/	
			botanist->coord_y=botanist->coord_y-1;
			botanist->water_bootle_size=botanist->water_bootle_size-1;
			search(&*forest,&*botanist,&*found);
					
	}
	
	else if(move==3 && forest->map[botanist->coord_x][botanist->coord_y+1]!='#' ){/*this is right move condition*/	
		botanist->coord_y=botanist->coord_y+1;
		botanist->water_bootle_size=botanist->water_bootle_size-1;
		search(&*forest,&*botanist,&*found);
	}
	
	else{
		search(&*forest,&*botanist,&*found);	
	}
}

#include <stdio.h> 
#include <time.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Player{
    char name[15]; // name of character (Bulbasaur, Charmander, Squirtle, Eevee)
    char type[15]; // pokemon type (fire, water, grass, normal)
    char skillName[25];
    char line[150];
    int stats[2]; //index 0 = hp, index 1 = dmg, index 3 = leer, index 4 = harden
    float stats2[2]; //stats that include evasion, extra dmg, and extra defense
    int skillLvl;
    int stun; // flag for being stunned
}Player;

typedef struct Enemy{
    char name[20];
    char type[15];
    char skill1[15]; // name of Enemy skill
    char skill2[15];
    char skill3[15];
    char skill4[15];
    float stats2[2];
    int hp, maxhp;
    int extraDmg;
}Enemy;

//FUNCTIONS
void delay(int);
void printIntro();
int printMenu(); 
void printDatabase(); 
void viewHistory();
Player choosePokemon(Player* player);
Player pokemonstats(Player* player);
int startGame(Player* player, Enemy* enemy);
Enemy chooseEnemy(Enemy* enemy);
Enemy enemyTurn(Enemy* enemy, Player* player);
Player nameskill(Player* player);
int playerTurn(Player* player, Enemy* enemy, int);
void printGame(Player* player, Enemy* enemy, int);
void printDialogue(Player* player, Enemy* enemy);
Player pickPrize(Player* player);
void appendHistory(Player* player, int);
void gameOver(int);

int main(){
	int menuChoice = 5, back, score, exit = 0;
	char backFlag;
    Player player;
    Enemy enemy;
    
    srand(time(NULL));
    //flow
    do{
    system("cls"); //clears the console
    printIntro();

    do{
    	system("cls");
    	back = 0;
    	while(menuChoice > 4){
    		menuChoice = printMenu();
		}
		
		system("cls");

		switch(menuChoice){
			case 1:
				choosePokemon(&player);
				system("cls");
                pokemonstats(&player);
                score = startGame(&player, &enemy);
                gameOver(score);
                appendHistory(&player, score);
				break;
			case 2:
				printDatabase();
                printf("\n\n\tPress <Enter> to go back to the main menu");
                scanf("%c",&backFlag);
                back = 1;
				break;
			case 3:
				viewHistory();
                printf("\n\n\tPress <Enter> to go back to the main menu");
                scanf("%c",&backFlag);
                back = 1;
				break;
            case 4:
                printf("\n\n\tThanks for playing!");
                delay(2);
                back = 0;
                exit =1;
                break;
			default:
				printf("Error: Choice not found.");
				break;
		}
        menuChoice = 5;
	}while(back==1);

    }while(exit == 0);
}


void delay(int number_of_seconds){
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void printIntro(){
	char* start;
    printf("\n\n\t+---------------------------------------+");
    printf("\n\t|\t\tWelcome to: \t\t|");
    printf("\n\n\t|\tPokemon: Survival Battle!\t|");
    printf("\n\t+---------------------------------------+");
    printf("\n\n\t\t+------------------------+");
    printf("\n\t\t| Press 'Enter' to START |");
    printf("\n\t\t+------------------------+\n\n\t\t\t     ");
    scanf("%c",&start);
    
    if(start != NULL){
    	system("cls");
	}
}

int printMenu(){
	int choice;
	system("cls");
	printf("\n\n\t\tWhat do you want to do?");
	printf("\n\n\t+-------------------------------------+");
	printf("\n\t|  1: Play Pokemon: Survival Battle!  |");
	printf("\n\t+-------------------------------------+");
	
	printf("\n\n\t+-------------------------------------+");
	printf("\n\t|  2: View Pokemon Database           |");
	printf("\n\t+-------------------------------------+");
	
	printf("\n\n\t+-------------------------------------+");
	printf("\n\t|  3: View History                    |");
	printf("\n\t+-------------------------------------+");

	printf("\n\n\t+-------------------------------------+");
	printf("\n\t|  4: Exit                            |");
	printf("\n\t+-------------------------------------+\n\n\t\t\t");
	
	scanf("%d",&choice);
	return(choice);
}

void printDatabase(){
    FILE *database= fopen ("PokeDatabase.in", "r");
    char contents, backFlag;

    while(fscanf(database, "%c", &contents)!= EOF){
        printf("%c", contents); 
    }
    scanf("%c", &backFlag);
    fclose(database);
}

void viewHistory(){
    char something, backFlag;
    FILE *history = fopen("history.txt","r");
    int size = 256;

    while(fscanf(history, "%c", &something)!= EOF){
        printf("%c", something);
    }
    scanf("%c", &backFlag);
    fclose(history);
}

Player choosePokemon(Player* player){
	int choice;
    char name;
    char* temp;
    do{
       system("cls");
    	printf("\n\n\tChoose your Pokemon: ");
    	printf("\n\n\t+----------------------------+");
    	printf("\n\t|  1: Charmander             |");
	    printf("\n\t+----------------------------+");
	
    	printf("\n\n\t+----------------------------+");
	    printf("\n\t|  2: Squirtle               |");
	    printf("\n\t+----------------------------+");
	
	    printf("\n\n\t+----------------------------+");
	    printf("\n\t|  3: Bulbasaur              |");
	    printf("\n\t+----------------------------+");

	    printf("\n\n\t+----------------------------+");
	    printf("\n\t|  4: Eevee                  |");
	    printf("\n\t+----------------------------+");

        printf("\n \n\t\t");

        scanf("%d",&choice);
    }while(choice > 4 || choice < 1);
	
    switch(choice){
        case 1:
        strcpy((*player).name, "Charmander");
        strcpy((*player).type, "Fire");
        strcpy(player->skillName, "Ember (Level 1)");
        break;
        case 2:
        strcpy((*player).name, "Squirtle");
        strcpy((*player).type, "Water");
        strcpy(player->skillName, "Water Gun (Level 1)");
        break;
        case 3:
        strcpy((*player).name, "Bulbasaur");
        strcpy((*player).type, "Grass");
        strcpy(player->skillName, "Vine Whip (Level 1)");
        break;
        case 4:
        strcpy((*player).name, "Eevee");
        strcpy((*player).type, "Normal");
        strcpy(player->skillName, "Tackle (Level 1)");
        break;
        default:
        printf("Invalid choice!");
        break;
    }
    (*player).skillLvl = 1;
	return(*player); 
}

Enemy enemyTurn(Enemy* enemy, Player* player){
    char moveLine[100];
    char move[15];
    char heal[100];

    int r = (rand() % 4 ) + 1;
    switch(r){
        case 1:
        strcpy(move, enemy->skill1);
        break;
        case 2:
        strcpy(move, enemy->skill2);
        break;
        case 3:
        strcpy(move, enemy->skill3);
        break;
        case 4:
        strcpy(move, enemy->skill4);
        break;
        default:
        printf("Something went wrong!");
        break;
    }
    strcpy(moveLine, " ");
    strcat(moveLine, "Enemy ");
    strcat(moveLine, enemy->name);
    strcat(moveLine, " used ");
    strcat(moveLine, move);
    strcat(moveLine, "!");
    strcpy(player->line, moveLine);

    system("cls");
    printDialogue(player, enemy);
    delay(2.5);

    if(!strcmp(move, "Scratch") || !strcmp(move, "Tackle") || !strcmp(move, "Stomp")){
        player->stats[0] -= (int)(5 * enemy->stats2[0] * player->stats2[1]) + enemy->extraDmg;
        if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
    }
    else if(!strcmp(move, "Quick Attack") || !strcmp(move, "Bite") || !strcmp(move, "Lick") || !strcmp(move, "Slam")){
        player->stats[0] -= (int)(6 * enemy->stats2[0] * player->stats2[1]) + enemy->extraDmg;
        if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
    }
    else if(!strcmp(move, "Ember") || !strcmp(move, "Fire Fang")){
        if(!strcmp(player->type, "Water")){
            player->stats[0] -= (int)((5 * enemy->stats2[0] * player->stats2[1]) * 0.75) + enemy->extraDmg;
            if(player->stats[0] <= 0){
            player->stats[0] = 0;
            }

            strcpy(player->line, "It's not very effective...");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else if(!strcmp(player->type, "Grass")){
            player->stats[0] -= (int)((5 * enemy->stats2[0] * player->stats2[1]) * 1.25) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            strcpy(player->line, "It's super effective!");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else{
            player->stats[0] -= (int)(5 * enemy->stats2[0] * player->stats2[1]) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
        }
    }
    else if(!strcmp(move, "Flame Wheel")){
        if(!strcmp(player->type, "Water")){
            player->stats[0] -= (int)((6 * enemy->stats2[0] * player->stats2[1]) * 0.75) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            strcpy(player->line, "It's not very effective...");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else if(!strcmp(player->type, "Grass")){
            player->stats[0] -= (int)((6 * enemy->stats2[0] * player->stats2[1]) * 1.25) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            strcpy(player->line, "It's super effective!");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else{
            player->stats[0] -= (int)(6 * enemy->stats2[0] * player->stats2[1]) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
        }
    }
    else if(!strcmp(move, "Bubble") || !strcmp(move, "Water Gun")){
        if(!strcmp(player->type, "Grass")){
            player->stats[0] -= (int)((5 * enemy->stats2[0] * player->stats2[1]) * 0.75) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            strcpy(player->line, "It's not very effective...");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else if(!strcmp(player->type, "Fire")){
            player->stats[0] -= (int)((5 * enemy->stats2[0] * player->stats2[1]) * 1.25) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            strcpy(player->line, "It's super effective!");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else{
            player->stats[0] -= (int)(5 * enemy->stats2[0] * player->stats2[1]) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
        }
    }
    else if(!strcmp(move, "Water Pulse")){
        if(!strcmp(player->type, "Grass")){
            player->stats[0] -= (int)((6 * enemy->stats2[0] * player->stats2[1]) * 0.75) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            strcpy(player->line, "It's not very effective...");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else if(!strcmp(player->type, "Fire")){
            player->stats[0] -= (int)((6 * enemy->stats2[0] * player->stats2[1]) * 1.25) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            strcpy(player->line, "It's super effective!");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else{
            player->stats[0] -= (int)(6 * enemy->stats2[0] * player->stats2[1]) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
        }
    }
    else if(!strcmp(move, "Splash")){
        strcpy(player->line, "Magikarp is joyfully playing with water!");
        system("cls");
        printDialogue(player, enemy);
        delay(2);
    }
    else if(!strcmp(move, "Absorb")){
        if(!strcmp(player->type, "Fire")){
            int dmg = (int)((5 * enemy->stats2[0] * player->stats2[1]) * 0.75) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            char hpstring[5];
            itoa((int)(dmg*0.4),hpstring,10);
            player->stats[0] -= dmg;
            enemy->hp += (int)(dmg*0.4);
            if(enemy->hp > enemy->maxhp){
                enemy->hp = enemy->maxhp;
            }
            strcpy(heal, " ");
            strcat(heal, enemy->name);
            strcat(heal, " healed ");
            strcat(heal, hpstring);
            strcat(heal, " HP!");

            strcpy(player->line, "It's not very effective...");
            system("cls");
            printDialogue(player, enemy);
            delay(2);

            strcpy(player->line, heal);
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else if(!strcmp(player->type, "Grass")){
            int dmg = (int)((5 * enemy->stats2[0] * player->stats2[1]) * 1.25) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            char hpstring[5];
            itoa((int)(dmg*0.4),hpstring,10);
            player->stats[0] -= dmg;
            enemy->hp += (int)(dmg*0.4);
            if(enemy->hp > enemy->maxhp){
                enemy->hp = enemy->maxhp;
            }
            strcpy(heal, " ");
            strcat(heal, enemy->name);
            strcat(heal, " healed ");
            strcat(heal, hpstring);
            strcat(heal, " HP!");

            strcpy(player->line, "It's super effective!");
            system("cls");
            printDialogue(player, enemy);
            delay(2);

            strcpy(player->line, heal);
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else{
            int dmg = (int)(5 * enemy->stats2[0] * player->stats2[1]) + enemy->extraDmg;
            
            char hpstring[5];
            itoa((int)(dmg*0.4),hpstring,10);
            enemy->hp += (int)(dmg*0.4);
            if(enemy->hp > enemy->maxhp){
                enemy->hp = enemy->maxhp;
            }
            player->stats[0] -= dmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            strcpy(heal, " ");
            strcat(heal, enemy->name);
            strcat(heal, " healed ");
            strcat(heal, hpstring);
            strcat(heal, " HP!");

            strcpy(player->line, heal);
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
    }
    else if(!strcmp(move, "Mega Drain")){
        if(!strcmp(player->type, "Fire")){
            int dmg = (int)((6 * enemy->stats2[0] * player->stats2[1]) * 0.75) + enemy->extraDmg;
            char hpstring[5];
            itoa((int)(dmg*0.8),hpstring,10);
            player->stats[0] -= dmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            enemy->hp += (int)(dmg*0.8);
            if(enemy->hp > enemy->maxhp){
                enemy->hp = enemy->maxhp;
            }
            strcpy(heal, " ");
            strcat(heal, enemy->name);
            strcat(heal, " healed ");
            strcat(heal, hpstring);
            strcat(heal, " HP!");

            strcpy(player->line, "It's not very effective...");
            system("cls");
            printDialogue(player, enemy);
            delay(2);

            strcpy(player->line, heal);
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else if(!strcmp(player->type, "Grass")){
            int dmg = (int)((6 * enemy->stats2[0] * player->stats2[1]) * 1.25) + enemy->extraDmg;
            char hpstring[5];
            itoa((int)(dmg*0.8),hpstring,10);
            player->stats[0] -= dmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            enemy->hp += (int)(dmg*0.8);
            if(enemy->hp > enemy->maxhp){
                enemy->hp = enemy->maxhp;
            }
            strcpy(heal, " ");
            strcat(heal, enemy->name);
            strcat(heal, " healed ");
            strcat(heal, hpstring);
            strcat(heal, " HP!");

            strcpy(player->line, "It's super effective!");
            system("cls");
            printDialogue(player, enemy);
            delay(2);

            strcpy(player->line, heal);
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else{
            int dmg = (int)((5 * enemy->stats2[0] * player->stats2[1])) + enemy->extraDmg;
            char hpstring[5];
            itoa((int)(dmg*0.8),hpstring,10);
            enemy->hp += (int)(dmg*0.8);
            if(enemy->hp > enemy->maxhp){
                enemy->hp = enemy->maxhp;
            }
            player->stats[0] -= dmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            strcpy(heal, " ");
            strcat(heal, enemy->name);
            strcat(heal, " healed ");
            strcat(heal, hpstring);
            strcat(heal, " HP!");

            strcpy(player->line, heal);
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
    }
    else if(!strcmp(move, "Vine Whip")){
        if(!strcmp(player->type, "Fire")){
            player->stats[0] -= (int)((6 * enemy->stats2[0] * player->stats2[1]) * 0.75) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            strcpy(player->line, "It's not very effective...");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else if(!strcmp(player->type, "Water")){
            player->stats[0] -= (int)((6 * enemy->stats2[0] * player->stats2[1]) * 1.25) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
            strcpy(player->line, "It's super effective!");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }
        else{
            player->stats[0] -= (int)((6 * enemy->stats2[0] * player->stats2[1])) + enemy->extraDmg;
            if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
        }
    }
        else if(!strcmp(move, "Aqua Ring")){
            char hpstring[5];
            itoa((int)(enemy->maxhp*0.2),hpstring,10);
            enemy->hp += enemy->maxhp*0.2;

            if(enemy->hp > enemy->maxhp){
                enemy->hp = enemy->maxhp;
            }
            strcpy(heal, " ");
            strcat(heal, enemy->name);
            strcat(heal, " healed ");
            strcat(heal, hpstring);
            strcat(heal, " HP!");

            strcpy(player->line, heal);
            system("cls");
            printDialogue(player, enemy);
            delay(2);
        }

    else if(!strcmp(move, "Stun Spore") || !strcmp(move, "Bind")){
            player->stun = 1;
    }
    else if(!strcmp(move, "Protect") || !strcmp(move, "Defense Curl")){
            enemy->stats2[1] -= 0.1;
            strcpy(player->line, "Enemy's next taken damage will be reduced!");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
    }
    else if(!strcmp(move, "Leer")){
            strcpy(player->line, "Enemy's next attack will be increased!");
            system("cls");
            printDialogue(player, enemy);
            delay(2);
            enemy->stats2[0] += 0.2;
    }
	if(player->stats[0] <= 0){
        player->stats[0] = 0;
    }
}

int startGame(Player* player, Enemy* enemy){
    int inGame=1, level = 1, cd, score = 0, bossCounter = 0, cooldown = 5, flag = 0, flag1 = 0;
    char Line[150];
    char eLine[150];

    player->stun = 0;

    do{
        system("cls");
        chooseEnemy(enemy);
        enemy->stats2[0] = 1.0;
        enemy->stats2[1] = 1.0;
        bossCounter += 1;
        player->stats2[0] = 1.0;
        player->stats2[1] = 1.0;
        enemy->extraDmg = 0;
        
        strcpy(Line, " ");
        strcat(Line, "A wild ");

        if(level > 1){
            enemy->hp = enemy->hp * (level - 0.5);
        }

        if(bossCounter % 4 == 0){
            enemy->hp *= 2.5;
            enemy->extraDmg = 1;
            strcat(Line, "Giant ");
        }
        enemy->maxhp = enemy->hp;
        
        strcat(Line, enemy->name);
        strcat(Line, " appeared!");
        strcpy(player->line,Line);
        printDialogue(player, enemy);
        delay(3);
        system("cls");
        strcpy(Line," ");
        
        while(enemy->hp > 0 && player->stats[0] > 0){
            
            strcpy(player->line," ");
            //printDialogue(player, enemy);
            //delay(1);
            //system("cls");
            nameskill(player);
            strcpy(player->line, "What move will you choose?");
            printGame(player, enemy, cooldown);

            if(player->stun == 0){
                cd = playerTurn(player, enemy, cooldown);
                system("cls");
                if(cooldown > 0){
                    cooldown -= 1;
                }
                if(cd > 0){
                    cooldown = 5;
                }
            }
            else{
                system("cls");
                strcpy(player->line, "You are stunned and cannot move!");
                printDialogue(player, enemy);
                delay(2.5);
                system("cls");
            }
            player->stun = 0;
            
            if(enemy->hp <= 0){
                strcpy(eLine, " ");
                strcat(eLine, enemy->name);
                strcat(eLine, " fainted!");
                strcpy(player->line, eLine);
                printDialogue(player, enemy);
                delay(3);
                system("cls");
                flag = 1;
                flag1 = 1;
            }
            strcpy(eLine, " ");

            if(flag == 0){
            system("cls");
            strcpy(player->line, "Enemy's turn!");
            printDialogue(player, enemy);
            //delay(2.5);

			enemyTurn(enemy, player);

            //system("cls");
            //printDialogue(player, enemy);
            //delay(2.5);

            if(player->stats[0] <= 0){
                system("cls");
                strcpy(Line, " ");
                strcat(Line, player->name);
                strcat(Line, " fainted!");
                strcpy(player->line, Line);
                printDialogue(player, enemy);
                delay(3);
                inGame = 0;
            }
            system("cls");
            }
            
            if(flag1 == 0){
            printDialogue(player, enemy);
            delay(2.5);
            system("cls");
            }
            flag = 0;
            flag1 = 1;
        }

        if(enemy-> hp <= 0 ){
            if(bossCounter % 4 == 0){
                score += 20;
                pickPrize(player);
                level++;
            }
            else{
                score += 10;
            }
        }
        
    }while(inGame == 1);
return(score);
}

Player pickPrize(Player* player){
    int choice, temp;
	printf("\n\n\n\t\t Mini boss defeated!");
	printf("\n\n\t\t Choose your prize: ");
	printf("\n\n\t\t+----------------------------+");
	printf("\n\t\t|  1: Level up skill         |");
	printf("\n\t\t+----------------------------+");

	printf("\n\n\t\t+----------------------------+");
	printf("\n\t\t|  2: Heal 50%% health        |");
	printf("\n\t\t+----------------------------+");

    printf("\n \n\t\t");

    scanf("%d",&choice);

    switch(choice){
        case 1:
        player->skillLvl += 1;
        system("cls");

        printf("\n\n\n\n\t\t+---------------------------------------+");
	    printf("\n\t\t|     Skill leveled up from %d to %d!     |",player->skillLvl-1,player->skillLvl);
	    printf("\n\t\t+---------------------------------------+");

        delay(2);

        if(player->skillLvl > 3){

            printf("\n\n\n\n\t\t+---------------------------------------+");
	        printf("\n\t\t|        Skill has evolved!             |");
	        printf("\n\t\t+---------------------------------------+");

            delay(2);
            system("cls");
        }
        break;

        case 2:
        temp = player->stats[0];
        player->stats[0] += 60;
        if(player->stats[0] > 120){
            player->stats[0] == 120;
        }

        system("cls");
        printf("\n\n\n\n\t\t+---------------------------------------+");
	    printf("\n\t\t      Health increased from %d to %d!     ",temp,player->stats[0]);
	    printf("\n\t\t+---------------------------------------+");
        delay(3);
        system("cls");
    }
    return(*player);
}

void printGame(Player* player, Enemy* enemy, int cooldown){
    if (player-> skillLvl < 4){
        printf("\n\n\t\t\t\t\t\t\tEnemy: \n\t\t\t\t\t\t\t%s\n\t\t\t\t\t\t\tHP: %d/%d", enemy->name, enemy->hp, enemy->maxhp);
        printf("\n\n\n\t\t%s: \n\t\tHP: %d/120",player->name,player->stats[0]);
        printf("\n\n\t+------------------------------------------------------------------+");
        printf("\n\t  %s", player->line);
        printf("\n\t+------------------------------------------------------------------+");
        printf("\n\t  1. %s%i)", player->skillName, player->skillLvl);
        printf("\n\t+------------------------------------------------------------------+");
        printf("\n\t  2. Leer");
        printf("\n\t+------------------------------------------------------------------+");
        printf("\n\t  3. Harden");
        printf("\n\t+------------------------------------------------------------------+");
        printf("\n\t  4. Heal (Cooldown: %d moves)",cooldown);
        printf("\n\t+------------------------------------------------------------------+");
        printf("\n\n\t\t");
    }
    else{
        printf("\n\n\t\t\t\t\t\t\tEnemy: \n\t\t\t\t\t\t\t%s\n\t\t\t\t\t\t\tHP: %d/%d", enemy->name, enemy->hp, enemy->maxhp);
        printf("\n\n\n\t\t%s: \n\t\tHP: %d/120",player->name,player->stats[0]);
        printf("\n\n\t+------------------------------------------------------------------+");
        printf("\n\t  %s", player->line);
        printf("\n\t+------------------------------------------------------------------+");
        printf("\n\t  1. %s", player->skillName);
        printf("\n\t+------------------------------------------------------------------+");
        printf("\n\t  2. Leer");
        printf("\n\t+------------------------------------------------------------------+");
        printf("\n\t  3. Harden");
        printf("\n\t+------------------------------------------------------------------+");
        printf("\n\t  4. Heal (Cooldown: %d moves)",cooldown);
        printf("\n\t+------------------------------------------------------------------+");
        printf("\n\n\t\t");
    }
}

void printDialogue(Player* player, Enemy* enemy){
    printf("\n\n\t\t\t\t\t\t\tEnemy: \n\t\t\t\t\t\t\t%s\n\t\t\t\t\t\t\tHP: %d/%d", enemy->name, enemy->hp, enemy->maxhp);
	printf("\n\n\n\t\t%s: \n\t\tHP: %d/120",player->name,player->stats[0]);
	printf("\n\n\t+------------------------------------------------------------------+");
	printf("\n\t  %s", player->line);
	printf("\n\t+------------------------------------------------------------------+");
    printf("\n\t  ");
	printf("\n\t+------------------------------------------------------------------+");
    printf("\n\t  ");
	printf("\n\t+------------------------------------------------------------------+");
	printf("\n\t  ");
	printf("\n\t+------------------------------------------------------------------+");
	printf("\n\t  ");
	printf("\n\t+------------------------------------------------------------------+");
	printf("\n\n\t\t");
}

Player nameskill(Player* player){
    if(!strcmp(player->name, "Charmander")){
        strcpy(player->skillName, "Ember (Level ");
        if(player->skillLvl == 1){
            player->stats[1] = 10;
        }
        else if(player->skillLvl == 2){
            player->stats[1] = 16;
        }
	    else if(player->skillLvl == 3){
            player->stats[1] = 22;
        }
        else if(player->skillLvl > 3){
            strcpy(player->skillName, "Flamethrower");
            player->stats[1] = 30;
        }
    }
    if(!strcmp(player->name, "Squirtle")){
        strcpy(player->skillName, "Water Gun (Level ");
        if(player->skillLvl == 1){
            player->stats[1] = 10;
        }
        else if(player->skillLvl == 2){
            player->stats[1] = 16;
        }
	    else if(player->skillLvl == 3){
            player->stats[1] = 22;
        }
        else if(player->skillLvl > 3){
            strcpy(player->skillName, "Hydro Pump");
            player->stats[1] = 30;
        }
    }
    if(!strcmp(player->name, "Bulbasaur")){
        strcpy(player->skillName, "Vine Whip (Level ");
        if(player->skillLvl == 1){
            player->stats[1] = 10;
        }
        else if(player->skillLvl == 2){
            player->stats[1] = 16;
        }
	    else if(player->skillLvl == 3){
            player->stats[1] = 22;
        }
        else if(player->skillLvl > 3){
            strcpy(player->skillName, "Razor Leaf");
            player->stats[1] = 30;
        }
    }
    if(!strcmp(player->name, "Eevee")){
        strcpy(player->skillName, "Tackle (Level ");
        if(player->skillLvl == 1){
            player->stats[1] = 10;
        }
        else if(player->skillLvl == 2){
            player->stats[1] = 16;
        }
	    else if(player->skillLvl == 3){
            player->stats[1] = 22;
        }
        else if(player->skillLvl > 3){
            strcpy(player->skillName, "Pound");
            player->stats[1] = 30;
        }
    }
    return(*player);
}

int playerTurn(Player* player, Enemy* enemy, int cooldown){
    int move, dmg, cd = 0;
    float tempdmg;
    char moveLine[150];
    char lvl[5];

    if(!strcmp(player->name, "Charmander")){
        do{
	    scanf("%d",&move);
        }while(move > 4 || move <= 0);

        switch(move){
            case 1:
                if(player->skillLvl < 4){
                    strcpy(moveLine, " ");
                    strcat(moveLine, "Charmander used ");
                    strcat(moveLine, player->skillName);
                    strcat(moveLine, itoa(player->skillLvl, lvl, 10));
                    strcat(moveLine, ")!");
                    strcpy(player->line, moveLine);
                }
                else{
                    strcpy(moveLine, " ");
                    strcat(moveLine, "Charmander used ");
                    strcat(moveLine, player->skillName);
                    strcat(moveLine, "!");
                    strcpy(player->line, moveLine);
                }

                tempdmg = (player->stats[1] * player->stats2[0] * enemy->stats2[1]); //plr.dmg * plr.leer * enmy.harden
                
                system("cls");
                printDialogue(player, enemy);
                delay(2.5);

                if(!strcmp(enemy->type,"Water")){
                    tempdmg = tempdmg * 0.75;
                    system("cls");
                    strcpy(player->line, "It's not very effective...");
                    printDialogue(player, enemy);
                    delay(2);
                }
                else if(!strcmp(enemy->type,"Grass")){
                    tempdmg = tempdmg * 1.25;
                    system("cls");
                    strcpy(player->line, "It's super effective!");
                    printDialogue(player, enemy);
                    delay(2);
                }

                dmg = floor(tempdmg);
                enemy->hp -= dmg;
                break;

            case 2:
                if(player->stats2[0] < 2.0){
                    player->stats2[0] += 0.2;
                    system("cls");
                    strcpy(player->line, "Your next attack will gain extra damage.");
                    printDialogue(player, enemy);
                    delay(2);
                }
                break;
            case 3:
                if(player->stats2[1] > 0.5){
                    player->stats2[1] -= 0.1;
                    system("cls");
                    strcpy(player->line, "Your next received damage will be reduced!");
                    printDialogue(player, enemy);
                    delay(2);
                }
                break;
            case 4:
                if (player->stats[0] < 120){
                    if(cooldown == 0){
                        player->stats[0] += 12;
                        system("cls");
                        strcpy(player->line, "You healed 10%% HP!");
                        printDialogue(player, enemy);
                        delay(2);
                        if(player->stats[0] > 120){
                            player->stats[0] = 120;
                        }
                        cd = 5;
                    }
                }
                break;
            default:
                printf("Something went wrong!");
                break;
        }

        if(enemy->hp <= 0){
            enemy->hp = 0;
        }
        return(cd);
    }
    if(!strcmp(player->name, "Squirtle")){
        do{
	    scanf("%d",&move);
        }while(move > 4 || move <= 0);
        switch(move){
            case 1:
                if(player->skillLvl < 4){
                    strcpy(moveLine, " ");
                    strcat(moveLine, "Squirtle used ");
                    strcat(moveLine, player->skillName);
                    strcat(moveLine, itoa(player->skillLvl, lvl, 10));
                    strcat(moveLine, ")!");
                    strcpy(player->line, moveLine);
                }
                else{
                    strcpy(moveLine, " ");
                    strcat(moveLine, "Squirtle used ");
                    strcat(moveLine, player->skillName);
                    strcat(moveLine, "!");
                    strcpy(player->line, moveLine);
                }

                tempdmg = (player->stats[1] * player->stats2[0] * enemy->stats2[1]); //plr.dmg * plr.leer * enmy.harden
                
                system("cls");
                printDialogue(player, enemy);
                delay(2.5);

                if(!strcmp(enemy->type,"Grass")){
                    tempdmg = tempdmg * 0.75;
                    system("cls");
                    strcpy(player->line, "It's not very effective...");
                    printDialogue(player, enemy);
                    delay(2);
                }
                else if(!strcmp(enemy->type,"Fire")){
                    tempdmg = tempdmg * 1.25;
                    system("cls");
                    strcpy(player->line, "It's super effective!");
                    printDialogue(player, enemy);
                    delay(2);
                }

                dmg = floor(tempdmg);
                enemy->hp -= dmg;
                break;

            case 2:
                if(player->stats2[0] < 2.0){
                    player->stats2[0] += 0.2;
                    system("cls");
                    strcpy(player->line, "Your next attack will gain extra damage.");
                    printDialogue(player, enemy);
                    delay(2);
                }
                break;
            case 3:
                if(player->stats2[1] > 0.5){
                    player->stats2[1] -= 0.1;
                    system("cls");
                    strcpy(player->line, "Your next received damage will be reduced!");
                    printDialogue(player, enemy);
                    delay(2);
                }
                break;
            case 4:
                if (player->stats[0] < 120){
                    if(cooldown == 0){
                        player->stats[0] += 12;
                        system("cls");
                        strcpy(player->line, "You healed 10%% HP!");
                        printDialogue(player, enemy);
                    delay(2);
                        if(player->stats[0] > 120){
                            player->stats[0] = 120;
                        }
                        cd = 5;
                    }
                }
                break;
            default:
                printf("Something went wrong!");
                break;
        }

        if(enemy->hp <= 0){
            enemy->hp = 0;
        }
        return(cd);   
    }
    if(!strcmp(player->name, "Bulbasaur")){
	    do{
	    scanf("%d",&move);
        }while(move > 4 || move <= 0);
        switch(move){
            case 1:
                if(player->skillLvl < 4){
                    strcpy(moveLine, " ");
                    strcat(moveLine, "Bulbasaur used ");
                    strcat(moveLine, player->skillName);
                    strcat(moveLine, itoa(player->skillLvl, lvl, 10));
                    strcat(moveLine, ")!");
                    strcpy(player->line, moveLine);
                }
                else{
                    strcpy(moveLine, " ");
                    strcat(moveLine, "Bulbasaur used ");
                    strcat(moveLine, player->skillName);
                    strcat(moveLine, "!");
                    strcpy(player->line, moveLine);
                }

                tempdmg = (player->stats[1] * player->stats2[0] * enemy->stats2[1]); //plr.dmg * plr.leer * enmy.harden
                
                system("cls");
                printDialogue(player, enemy);
                delay(2.5);

                if(!strcmp(enemy->type,"Fire")){
                    tempdmg = tempdmg * 0.75;
                    system("cls");
                    strcpy(player->line, "It's not very effective...");
                    printDialogue(player, enemy);
                    delay(2);
                }
                else if(!strcmp(enemy->type,"Water")){
                    tempdmg = tempdmg * 1.25;
                    system("cls");
                    strcpy(player->line, "It's super effective!");
                    printDialogue(player, enemy);
                    delay(2);
                }

                dmg = floor(tempdmg);
                enemy->hp -= dmg;
                break;

            case 2:
                if(player->stats2[0] < 2.0){
                    player->stats2[0] += 0.2;
                    system("cls");
                    strcpy(player->line, "Your next attack will gain extra damage.");
                    printDialogue(player, enemy);
                    delay(2);
                }
                break;
            case 3:
                if(player->stats2[1] > 0.5){
                    player->stats2[1] -= 0.1;
                    system("cls");
                    strcpy(player->line, "Your next received damage will be reduced!");
                    printDialogue(player, enemy);
                    delay(2);
                }
                break;
            case 4:
                if (player->stats[0] < 120){
                    if(cooldown == 0){
                        player->stats[0] += 12;
                        system("cls");
                        strcpy(player->line, "You healed 10%% HP!");
                        printDialogue(player, enemy);
                    delay(2);
                        if(player->stats[0] > 120){
                            player->stats[0] = 120;
                        }
                        cd = 5;
                    }
                }
                break;
            default:
                printf("Something went wrong!");
                break;
        }

        if(enemy->hp <= 0){
            enemy->hp = 0;
        }
        return(cd);
    }
    if(!strcmp(player->name, "Eevee")){
	    do{
	    scanf("%d",&move);
        }while(move > 4 || move <= 0);
        switch(move){
            case 1:
                if(player->skillLvl < 4){
                    strcpy(moveLine, " ");
                    strcat(moveLine, "Eevee used ");
                    strcat(moveLine, player->skillName);
                    strcat(moveLine, itoa(player->skillLvl, lvl, 10));
                    strcat(moveLine, ")!");
                    strcpy(player->line, moveLine);
                }
                else{
                    strcpy(moveLine, " ");
                    strcat(moveLine, "Eevee used ");
                    strcat(moveLine, player->skillName);
                    strcat(moveLine, "!");
                    strcpy(player->line, moveLine);
                }

                tempdmg = (player->stats[1] * player->stats2[0] * enemy->stats2[1]); //plr.dmg * plr.leer * enmy.harden
                
                system("cls");
                printDialogue(player, enemy);
                delay(2.5);

                dmg = floor(tempdmg);
                enemy->hp -= dmg;
                break;

            case 2:
                if(player->stats2[0] < 2.0){
                    player->stats2[0] += 0.2;
                    system("cls");
                    strcpy(player->line, "Your next attack will gain extra damage.");
                    printDialogue(player, enemy);
                    delay(2);
                }
                break;
            case 3:
                if(player->stats2[1] > 0.5){
                    player->stats2[1] -= 0.1;
                    system("cls");
                    strcpy(player->line, "Your next received damage will be reduced!");
                    printDialogue(player, enemy);
                    delay(2);
                }
                break;
            case 4:
                if (player->stats[0] < 120){
                    if(cooldown == 0){
                        player->stats[0] += 12;
                        system("cls");
                        strcpy(player->line, "You healed 10%% HP!");
                        printDialogue(player, enemy);
                        delay(2);
                        if(player->stats[0] > 120){
                            player->stats[0] = 120;
                        }
                        cd = 5;
                    }
                }
                break;
            default:
                printf("Something went wrong!");
                break;
        }

        if(enemy->hp <= 0){
            enemy->hp = 0;
        }
        return(cd);
    }
}

Enemy chooseEnemy(Enemy* enemy){
    int r = (rand()%16)+1;
    switch(r){
    	default:
        	printf("Something went wrong!");
        	break;
    	
        case 1:
        	strcpy(enemy->name, "Rattata");
        	strcpy(enemy->type, "Normal");
        	enemy->hp = 19;
        	strcpy(enemy->skill1, "Bite");
        	strcpy(enemy->skill2, "Scratch");
        	strcpy(enemy->skill3, "Bite");
        	strcpy(enemy->skill4, "Scratch");
        	break;

        case 2:
        	strcpy(enemy->name, "Vulpix");
        	strcpy(enemy->type, "Fire");
        	enemy->hp = 20;
        	strcpy(enemy->skill1, "Ember");
        	strcpy(enemy->skill2, "Quick Attack");
        	strcpy(enemy->skill3, "Ember");
        	strcpy(enemy->skill4, "Quick Attack");
        	break;

        case 3:
        	strcpy(enemy->name, "Magikarp");
        	strcpy(enemy->type, "Water");
        	enemy->hp = 24;
        	strcpy(enemy->skill1, "Splash");
        	strcpy(enemy->skill2, "Splash");
        	strcpy(enemy->skill3, "Splash");
        	strcpy(enemy->skill4, "Splash");
        	break;

        case 4:
        	strcpy(enemy->name, "Oddish");
        	strcpy(enemy->type, "Grass");
        	enemy->hp = 18;
        	strcpy(enemy->skill1, "Absorb");
        	strcpy(enemy->skill2, "Mega Drain");
        	strcpy(enemy->skill3, "Absorb");
        	strcpy(enemy->skill4, "Mega Drain");
        	break;

        case 5:
        	strcpy(enemy->name, "Pidgey");
        	strcpy(enemy->type, "Normal");
        	enemy->hp = 19;
        	strcpy(enemy->skill1, "Tackle");
        	strcpy(enemy->skill2, "Quick Attack");
        	strcpy(enemy->skill3, "Tackle");
        	strcpy(enemy->skill4, "Quick Attack");
        	break;

        case 6:
        	strcpy(enemy->name, "Flareon");
        	strcpy(enemy->type, "Fire");
        	enemy->hp = 19;
        	strcpy(enemy->skill1, "Ember");
        	strcpy(enemy->skill2, "Tackle");
        	strcpy(enemy->skill3, "Fire Fang");
        	strcpy(enemy->skill4, "Tackle");
        	break;

        case 7:
        	strcpy(enemy->name, "Shelder");
        	strcpy(enemy->type, "Water");
        	enemy->hp = 19;
        	strcpy(enemy->skill1, "Protect");
        	strcpy(enemy->skill2, "Water Gun");
        	strcpy(enemy->skill3, "Tackle");
        	strcpy(enemy->skill4, "Water Gun");
        	break;

        case 8:
        	strcpy(enemy->name, "Tangela");
    	    strcpy(enemy->type, "Grass");
    	    enemy->hp = 19;
    	    strcpy(enemy->skill1, "Absorb");
    	    strcpy(enemy->skill2, "Vine Whip");
    	    strcpy(enemy->skill3, "Bind");
    	    strcpy(enemy->skill4, "Vine Whip");
    	    break;

        case 9:
    	    strcpy(enemy->name, "Lickitung");
    	    strcpy(enemy->type, "Normal");
    	    enemy->hp = 18;
    	    strcpy(enemy->skill1, "Stomp");
    	    strcpy(enemy->skill2, "Defense Curl");
    	    strcpy(enemy->skill3, "Lick");
   			strcpy(enemy->skill4, "Stomp");
   	 		break;

        case 10:
    	    strcpy(enemy->name, "Growlithe");
    	    strcpy(enemy->type, "Fire");
    	    enemy->hp = 19;
    	    strcpy(enemy->skill1, "Bite");
    	    strcpy(enemy->skill2, "Fire Fang");
    	    strcpy(enemy->skill3, "Bite");
    	    strcpy(enemy->skill4, "Fire Fang");
    	    break;

        case 11:
    	    strcpy(enemy->name, "Vaporeon");
    	    strcpy(enemy->type, "Water");
    	    enemy->hp = 19;
    	    strcpy(enemy->skill1, "Tackle");
    	    strcpy(enemy->skill2, "Water Pulse");
    	    strcpy(enemy->skill3, "Aqua Ring");
    	    strcpy(enemy->skill4, "Tackle");
    	    break;

        case 12:
        	strcpy(enemy->name, "Bellsprout");
        	strcpy(enemy->type, "Grass");
        	enemy->hp = 19;
        	strcpy(enemy->skill1, "Slam");
        	strcpy(enemy->skill2, "Vine Whip");
        	strcpy(enemy->skill3, "Bind");
        	strcpy(enemy->skill4, "Vine Whip");
        	break;

        case 13:
        	strcpy(enemy->name, "Meowth");
        	strcpy(enemy->type, "Normal");
        	enemy->hp = 19;
        	strcpy(enemy->skill1, "Bite");
        	strcpy(enemy->skill2, "Scratch");
        	strcpy(enemy->skill3, "Leer");
        	strcpy(enemy->skill4, "Scratch");
        	break;

        case 14:
        	strcpy(enemy->name, "Ponyta");
        	strcpy(enemy->type, "Fire");
        	enemy->hp = 18;
        	strcpy(enemy->skill1, "Flame Wheel");
        	strcpy(enemy->skill2, "Flame Wheel");
        	strcpy(enemy->skill3, "Leer");
        	strcpy(enemy->skill4, "Flame Wheel");
        	break;

        case 15:
        	strcpy(enemy->name, "Horsea");
        	strcpy(enemy->type, "Water");
        	enemy->hp = 20;
       	 	strcpy(enemy->skill1, "Water Gun");
        	strcpy(enemy->skill2, "Bubble");
        	strcpy(enemy->skill3, "Water Gun");
       		strcpy(enemy->skill4, "Bubble");
        	break;

        case 16:
        	strcpy(enemy->name, "Gloom");
        	strcpy(enemy->type, "Grass");
        	enemy->hp = 18;
        	strcpy(enemy->skill1, "Absorb");
        	strcpy(enemy->skill2, "Mega Drain");
        	strcpy(enemy->skill3, "Absorb");
        	strcpy(enemy->skill4, "Stun Spore");
        	break;
        
    return(*enemy);
    }
}

Player pokemonstats(Player* player){
    FILE *stat = fopen("stats.in", "r");
    int i = 0;
    char something[6];
    while(fgets(something, 6,stat) != NULL){
        if(i<2){
            int temp = atoi(something);
            (*player).stats[i] = temp;
            i++;
        }
        else{
            int temp = atoi(something);
            (*player).stats2[i-2] = temp;
            i++;
        }
    }
    /*for(int y=0; y<i; y++){
        if(y<2){
            printf("\n%d", player.stats[y]);
        }
        else{
            printf("\n%2.2f", player.stats2[y-2]);
        }
    }*/
    fclose(stat);
    //printf("%i",player.stats[1]);
	return(*player);
}
void appendHistory(Player* player, int score){
    char nick[100];
    char historyLine[200];
    char scoreStr[10];
    FILE* history = fopen("history.txt", "a+");

    system("cls");
        printf("\n\n\n\n\t\t+-------------------------------------------+");
	    printf("\n\n\t\t  Enter nickname (no spaces): ");
        scanf("%s",&nick);

        strcpy(historyLine, " ");
        strcat(historyLine, nick);
        strcat(historyLine, " | ");
        strcat(historyLine, player->name);
        strcat(historyLine, " | Score: ");
        itoa(score, scoreStr, 10);
        strcat(historyLine, scoreStr);

        delay(3);
        system("cls");
    
    fprintf(history,"\n%s\n", historyLine);
    fclose(history);

    printf("\n\n\n\tResult saved!");
    delay(2);
}

void gameOver(int score){
    printf("\n\n\n\n\t\t\t+-----------------------+");
	printf("\n\t\t\t|\t G A M E \t|");
	printf("\n\n\t\t\t|\t O V E R \t|");
	printf("\n\t\t\t+-----------------------+");
	printf("\n\n\t\t\t\t Score: %d", score);
	
	delay(3);
}

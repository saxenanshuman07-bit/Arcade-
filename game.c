#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* --- GLOBAL CONSTANTS --- */
#define START_MONEY 1000
#define GO_REWARD 200
#define BOARD_SIZE 12

/* --- FUNCTION PROTOTYPES --- */
void playMonopoly();
void playScotlandYard();
int rollDice();
void clearScreen();
void waitForEnter();

/* --- MAIN MENU --- */
int main() {
    int choice;
    
    // Seed the random number generator
    srand(time(0)); 

    while(1) {
        clearScreen();
        printf("\n=============================\n");
        printf("   MULTI-GAME SYSTEM (VS Code)   \n");
        printf("=============================\n");
        printf("1. Play Monopoly (Bankruptcy Edition)\n");
        printf("2. Play Scotland Yard\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            // Handle non-integer input to prevent infinite loops
            while(getchar() != '\n'); 
            continue;
        }

        if (choice == 1) {
            playMonopoly();
        } else if (choice == 2) {
            playScotlandYard();
        } else if (choice == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice!\n");
            waitForEnter();
        }
    }
    return 0;
}

/* --- MONOPOLY IMPLEMENTATION --- */
void playMonopoly() {
    int p1_money = START_MONEY;
    int p2_money = START_MONEY;
    int p1_pos = 0;
    int p2_pos = 0;
    int turn = 1; // 1 for P1, 2 for P2
    int roll, new_pos, owner, rent, cost;
    int game_over = 0;
    
    // 0=Bank, 1=P1, 2=P2
    int board_owners[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    
    // Board Data
    // 0=GO, 3=Tax, 6=Robbery, Others=Property
    int board_cost[12] = {0, 100, 150, 0, 200, 220, 0, 300, 320, 0, 400, 500};
    int board_rent[12] = {0, 20, 30, 0, 50, 60, 0, 80, 90, 0, 120, 150};

    // Clear buffer before game starts
    while(getchar() != '\n'); 

    while (!game_over) {
        clearScreen();
        printf("\n--- MONOPOLY (BANKRUPTCY EDITION) ---\n");
        printf("P1 Money: $%d  |  P2 Money: $%d\n", p1_money, p2_money);
        printf("--------------------------------------\n");
        printf("[Turn: Player %d] Press ENTER to roll...", turn);
        waitForEnter();

        roll = rollDice();
        printf("\n -> Rolled a %d\n", roll);

        // Update Position
        if (turn == 1) {
            p1_pos += roll;
            if (p1_pos >= BOARD_SIZE) {
                p1_pos -= BOARD_SIZE;
                p1_money += GO_REWARD;
                printf(" -> Passed GO! Collected $%d\n", GO_REWARD);
            }
            new_pos = p1_pos;
        } else {
            p2_pos += roll;
            if (p2_pos >= BOARD_SIZE) {
                p2_pos -= BOARD_SIZE;
                p2_money += GO_REWARD;
                printf(" -> Passed GO! Collected $%d\n", GO_REWARD);
            }
            new_pos = p2_pos;
        }

        // Logic
        printf(" -> Landed on space %d.\n", new_pos);

        if (new_pos == 0) {
            printf(" -> Just visiting GO.\n");
        } 
        else if (new_pos == 3 || new_pos == 9) {
            printf(" -> TAX OFFICE! Pay $100.\n");
            if (turn == 1) p1_money -= 100; else p2_money -= 100;
        }
        else if (new_pos == 6) {
            printf(" -> ROBBERY! You got mugged. Lost $150.\n");
            if (turn == 1) p1_money -= 150; else p2_money -= 150;
        }
        else {
            owner = board_owners[new_pos];
            cost = board_cost[new_pos];
            rent = board_rent[new_pos];

            if (owner == 0) {
                printf(" -> Unowned Property (Cost: $%d).\n", cost);
                // Auto-buy logic
                if ((turn == 1 && p1_money >= cost) || (turn == 2 && p2_money >= cost)) {
                    printf(" -> Buying property automatically...\n");
                    if (turn == 1) {
                        p1_money -= cost;
                        board_owners[new_pos] = 1;
                    } else {
                        p2_money -= cost;
                        board_owners[new_pos] = 2;
                    }
                } else {
                    printf(" -> Not enough money to buy!\n");
                }
            } else if (owner == turn) {
                printf(" -> You own this property. Safe.\n");
            } else {
                printf(" -> Player %d owns this! Paying rent $%d.\n", owner, rent);
                if (turn == 1) {
                    p1_money -= rent;
                    p2_money += rent;
                } else {
                    p2_money -= rent;
                    p1_money += rent;
                }
            }
        }

        // Check Bankruptcy
        if (p1_money < 0) {
            printf("\n\n!!! PLAYER 1 IS BANKRUPT !!!\nPlayer 2 Wins!\n");
            game_over = 1;
        } else if (p2_money < 0) {
            printf("\n\n!!! PLAYER 2 IS BANKRUPT !!!\nPlayer 1 Wins!\n");
            game_over = 1;
        }

        if (!game_over) {
            printf("\nEnd of turn. ");
            waitForEnter();
            turn = (turn == 1) ? 2 : 1;
        }
    }
    printf("Press ENTER to return to menu.");
    waitForEnter();
}

/* --- SCOTLAND YARD IMPLEMENTATION --- */
void playScotlandYard() {
    int mr_x_loc;
    int det_loc = 1;
    int turns = 0;
    int max_turns = 10;
    int move;
    
    // Clear buffer
    while(getchar() != '\n');

    mr_x_loc = (rand() % 20) + 1;

    while (turns < max_turns) {
        clearScreen();
        printf("\n--- SCOTLAND YARD (Lite) ---\n");
        printf("Turn %d/%d\n", turns+1, max_turns);
        printf("You are at Loc %d.\n", det_loc);
        
        // Hint
        if (mr_x_loc > det_loc) printf("Intel: Mr. X is at a higher number.\n");
        else if (mr_x_loc < det_loc) printf("Intel: Mr. X is at a lower number.\n");
        else printf("Intel: Mr. X is right here!\n");

        printf("Enter location to move to (1-20): ");
        if (scanf("%d", &det_loc) != 1) {
            while(getchar() != '\n'); // flush invalid input
            continue;
        }
        while(getchar() != '\n'); // flush newline

        if (det_loc == mr_x_loc) {
            printf("\n!!! YOU CAUGHT MR. X !!!\n");
            printf("He was hiding at location %d.\n", mr_x_loc);
            printf("Press ENTER to return to menu.");
            waitForEnter();
            return;
        } else {
            printf("He's not here...\n");
        }

        // Mr X moves
        move = (rand() % 5) - 2; 
        mr_x_loc += move;
        if (mr_x_loc < 1) mr_x_loc = 1;
        if (mr_x_loc > 20) mr_x_loc = 20;
        
        printf("Mr. X takes a taxi to a new location...\n");
        printf("Press ENTER for next turn.");
        waitForEnter();
        turns++;
    }

    printf("\n!!! MR. X ESCAPED !!!\n");
    printf("You failed to catch him in %d turns.\n", max_turns);
    printf("Press ENTER to return to menu.");
    waitForEnter();
}

/* --- HELPERS --- */
int rollDice() {
    return (rand() % 6) + 1;
}

void clearScreen() {
    // Check operating system
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter() {
    // Keeps reading until a newline is found
    // This effectively pauses the console until Enter is pressed
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Used for sleep(seconds) on Linux

// Move node
struct move {
    int x;
    int y;
    struct move *next;
    struct move *previous;
    int remainingMoves;
};

// Function prototyping
void printMap(int inputMap[][17][2]);
void sense(int fullMap[][17][2], int restrictedMap[][17][2],
        struct move *inputLocation);
struct move *nextMove(int inputMap[][17][2], struct move *inputLocation);
int repeatMove(int inputX, int inputY, struct move *inputLocation);

// Code
int main() {
    
    // Actual map which is unknown to decision-making
    // [y][x]{right wall, ceiling}
    int map[17][17][2] = {
            {{1,0},{0,1},{0,1},{1,1},{0,1},{0,1},{0,1},{0,1},{1,1},{0,1},{0,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}},
            {{1,0},{1,0},{1,1},{1,0},{1,0},{1,1},{0,1},{1,1},{1,0},{1,0},{0,1},{0,0},{0,0},{0,0},{0,0},{1,0},{1,0}},
            {{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{0,1},{1,0},{1,0},{0,1},{0,0},{0,1},{1,1},{1,0},{0,0},{1,0}},
            {{1,0},{1,0},{0,1},{0,0},{1,0},{0,1},{0,0},{0,1},{1,0},{0,0},{0,1},{0,1},{1,1},{0,0},{1,1},{1,0},{1,0}},
            {{1,0},{1,0},{1,1},{0,1},{0,1},{0,0},{0,1},{1,1},{0,0},{0,1},{0,1},{0,1},{1,0},{1,0},{1,0},{1,0},{1,0}},
            {{1,0},{1,0},{1,0},{1,0},{0,1},{0,1},{0,0},{0,1},{0,1},{0,1},{1,1},{1,1},{1,1},{1,1},{1,0},{1,0},{1,0}},
            {{1,0},{0,0},{1,0},{1,0},{0,0},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,0},{0,0},{0,0},{1,0},{1,0},{1,0}},
            {{1,0},{1,0},{1,0},{0,0},{0,1},{1,1},{0,1},{1,1},{0,1},{1,1},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0}},
            {{1,0},{1,0},{1,0},{1,1},{0,0},{0,1},{1,1},{1,0},{0,0},{1,0},{0,1},{0,1},{0,1},{1,0},{1,0},{1,0},{1,0}},
            {{1,0},{1,0},{1,0},{0,0},{1,1},{0,0},{1,1},{0,0},{1,1},{0,0},{0,0},{0,1},{0,1},{0,1},{1,0},{1,0},{1,0}},
            {{1,0},{1,1},{1,0},{1,0},{0,0},{1,1},{0,0},{1,0},{0,0},{0,1},{0,1},{0,1},{1,1},{1,1},{1,0},{1,0},{1,0}},
            {{1,0},{1,0},{0,0},{1,0},{1,1},{1,0},{1,1},{0,0},{1,1},{0,0},{1,1},{1,0},{1,0},{0,0},{1,1},{1,0},{1,0}},
            {{1,0},{1,0},{1,0},{1,0},{1,1},{0,0},{0,0},{1,1},{0,0},{1,1},{0,0},{1,1},{0,0},{1,0},{1,0},{1,0},{1,0}},
            {{1,0},{1,0},{1,1},{0,0},{0,0},{1,0},{0,0},{1,1},{0,1},{0,0},{1,1},{0,0},{0,1},{0,1},{0,0},{1,0},{1,0}},
            {{1,0},{0,0},{0,0},{1,0},{1,0},{1,0},{1,0},{1,0},{0,0},{0,1},{0,0},{0,1},{0,1},{0,1},{0,1},{1,1},{1,0}},
            {{1,0},{1,0},{1,0},{1,0},{0,1},{0,1},{0,0},{0,1},{0,1},{0,0},{0,1},{1,1},{0,1},{0,0},{0,1},{0,0},{1,0}},
            {{0,0},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}}
            };
    
    // Map updated by, and used in, decision-making
    // 2 == unknown
    int mouseMap[17][17][2] = {
            {{1,2},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{1,1}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{1,2},{1,0},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{2,2},{1,2}},
            {{2,2},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1},{2,1}}
            };
    
    // Move list
    struct move *location;
    location = (struct move *)calloc(1, sizeof(struct move));
    location -> x = 1;
    location -> y = 15;
    
    printMap(map); // DEBUG
    
    printf("\nLocation (%d, %d)", location -> x, location -> y); // DEBUG
    printMap(mouseMap); // DEBUG
    
    // Program loop
    while(location -> x != 9 || location -> y != 7) {
        sense(map, mouseMap, location);
        printf("\nLocation (%d, %d)", location -> x, location -> y);
        location = nextMove(mouseMap, location);
        printf("\nLocation (%d, %d)", location -> x, location -> y);
        printMap(mouseMap);
        sleep(1);
    }
    
    // End of program
    printf("\nEnd of program");
    printMap(map); // DEBUG
    return 0;
}

// Returns 1, True, if the coordinates have been visited before
int repeatMove(int inputX, int inputY, struct move *inputLocation) {
    struct move *temp;
    temp = inputLocation;
    while(temp != NULL) {
        
        // Returning 1 if input coordinates are equal to a previous position's
        if(temp -> x == inputX && temp -> y == inputY) {
            return 1;
        }
        
        // Iterating through previous moves
        temp = temp -> previous;
    }
    return 0;
}

// Determines and returns the best next move
struct move *nextMove(int inputMap[][17][2], struct move *inputLocation) {
    
    // New move creation
    struct move *temp;
    temp = (struct move *)calloc(1, sizeof(struct move));
    
    // Determining valid moves [move index][0] = x, [move index][1] = y
    int validMoves[4][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
    int moveCounter = -1; // Number of valid moves in validMoves[][]
    
    // Checking ceiling
    if(inputMap[inputLocation -> y][inputLocation -> x][1] == 0) {
        
        // Checking repeat
        if(!repeatMove(inputLocation -> x, (inputLocation -> y) - 1, 
                inputLocation)) {
            moveCounter++;
            validMoves[moveCounter][0] = inputLocation -> x;
            validMoves[moveCounter][1] = (inputLocation -> y) - 1;
        }
    }
    
    // Checking floor
    if(inputMap[inputLocation -> y + 1][inputLocation -> x][1] == 0) {
        
        // Checking repeat
        if(!repeatMove(inputLocation -> x, (inputLocation -> y) + 1, 
                inputLocation)) {
            moveCounter++;
            validMoves[moveCounter][0] = inputLocation -> x;
            validMoves[moveCounter][1] = (inputLocation -> y) + 1;
        }
    }
    
    // Checking left
    if(inputMap[inputLocation -> y][(inputLocation -> x) - 1][0] == 0) {
        
        // Checking repeat
        if(!repeatMove((inputLocation -> x) - 1, inputLocation -> y, 
                inputLocation)) {
            moveCounter++;
            validMoves[moveCounter][0] = (inputLocation -> x) - 1;
            validMoves[moveCounter][1] = inputLocation -> y;
        }
    }
    
    // Checking right
    if(inputMap[inputLocation -> y][inputLocation -> x][0] == 0) {
        
        // Checking repeat
        if(!repeatMove((inputLocation -> x) + 1, inputLocation -> y, 
                inputLocation)) {
            moveCounter++;
            validMoves[moveCounter][0] = (inputLocation -> x) + 1;
            validMoves[moveCounter][1] = inputLocation -> y;
        }
    }
    
    //printf("\nDEBUG validMoves[0]: (%d, %d)", validMoves[0][0], validMoves[0][1]); // DEBUG
    //printf("\nDEBUG validMoves[1]: (%d, %d)", validMoves[1][0], validMoves[1][1]); // DEBUG
    //printf("\nDEBUG validMoves[2]: (%d, %d)", validMoves[2][0], validMoves[2][1]); // DEBUG
    //printf("\nDEBUG validMoves[3]: (%d, %d)", validMoves[3][0], validMoves[3][1]); // DEBUG
    printf("\nDEBUG moveCounter: %d", moveCounter); // DEBUG
    
    // No new moves found
    if(moveCounter == -1){
        inputLocation -> remainingMoves = 0;
        
        // Moving to previous until unvisisted space is adjacent
        struct move *iterator;
        iterator = inputLocation -> previous;
        while(iterator -> remainingMoves < 1){
            iterator = iterator -> previous;
            
            // DEBUG
            if(inputLocation -> x == 7 && inputLocation -> y == 13) {
            }
        }
        
        // Creating next move
        temp -> previous = inputLocation;
        temp -> x = iterator -> x;
        temp -> y = iterator -> y;
        
    // New moves found
    } else {
        
        // Setting next move to first move found TEMPORARY LOGIC
        temp -> previous = inputLocation;
        inputLocation -> next = temp;
        inputLocation -> remainingMoves = moveCounter + 2;
        temp -> x = validMoves[moveCounter][0];
        temp -> y = validMoves[moveCounter][1];
    }
    
    // printf("\nDEBUG remainingMoves: %d", inputLocation -> remainingMoves); // DEBUG
    return temp;
}

// Updates the map with information around the input location
void sense(int fullMap[][17][2], int restrictedMap[][17][2], 
        struct move *inputLocation) {
    
    // Adding ceiling data
    restrictedMap[(inputLocation -> y)][inputLocation -> x][1] 
            = fullMap[(inputLocation -> y)][inputLocation -> x][1];
            
    // Adding floor data
    restrictedMap[(inputLocation -> y) + 1][inputLocation -> x][1] 
            = fullMap[(inputLocation -> y) + 1][inputLocation -> x][1];
    
    // Adding left wall data
    // Removed "- 1"  from y
    restrictedMap[(inputLocation -> y)][(inputLocation -> x) - 1][0] 
            = fullMap[(inputLocation -> y)][(inputLocation -> x) - 1][0];
    
    // Adding right wall data
    // Removed "- 1"  from y
    restrictedMap[(inputLocation -> y)][inputLocation -> x][0] 
            = fullMap[(inputLocation -> y)][inputLocation -> x][0];
}

// Takes a map as input and prints it
void printMap(int inputMap[][17][2]) {
    int x;
    int y;
    printf("\n0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6");
    for(y = 0; y < 17; y++) {
        printf("\n");
        for(x = 0; x < 17; x++) {
            
            // Printing ceilings
            if(inputMap[y][x][1] == 1) {
                printf("‾");
            } else {
                printf(" ");
            }
            
            // Printing right-walls
            if(inputMap[y][x][0] == 1) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf(" %d", y);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <kipr/graphics.h>
#include <time.h>

const int INITIAL_LIMIT = 4;
const int SCORE_LIMIT = 4;

// Creates a struct called "player" to keep track of the player's initials and score
typedef struct player_struct {
  char initials[INITIAL_LIMIT];
  int score;
} player;

// Creates a struct called "character" to keep track of the playable character
typedef struct character_struct {
  int xPos;
  int yPos;
  int yVel;
  int gravity;
} character;

// Creates a struct called "obstacle" to keep track of the obstacles
typedef struct obstacle_struct {
  int xPos;
} obstacle;

// Prints my name and OU ID
void MyName(void) {
  printf("Final Project by Blake Lackey\n");
  printf("OUID: 113410877\n\n");
}

// Prints the introduction and game instructions
void GameIntro(void) {
  printf("Welcome to \"Run n' Jump!\", the running and\njumping game created by Blake Lackey.\n");
  printf("In \"Run n' Jump!\", you are a lone gumball on a\nmission to make it through the desert,\navoiding cacti along the way.\n");
  printf("Simply press the spacebar to jump.\n\n");
  printf("Click the graphics input button\nthen press spacebar to start the game.\n\n");
}

// Creates the desert background scene
void DrawDesert(void) {
  graphics_rectangle_fill(0, 0, 500, 250, 135, 206, 235);
  graphics_rectangle_fill(0, 250, 500, 300, 194, 178, 128);
  graphics_circle_fill(400, 50, 30, 252, 212, 64);
}

// Creates the gumball character
void DrawBall(character ball) {
  graphics_circle_fill(ball.xPos, ball.yPos, 20, 255, 105, 180);
}

// Creates the cacti
void DrawObstacle(obstacle ob1) {
  graphics_rectangle_fill(ob1.xPos, 205, ob1.xPos + 15, 250, 35, 117, 67);
}
  
// Checks to see if the gumball has collided with any of the cacti
int CheckCollision(character ball, obstacle obOne, obstacle obTwo, obstacle obThree) {
  if (ball.xPos + 15 >= obOne.xPos && ball.xPos - 15 <= obOne.xPos && ball.yPos >= 205) {
    return 1;
  }
  else if (ball.xPos - 15 == obOne.xPos + 15 && ball.yPos >= 205) {
    return 1;
  }
  else if (ball.xPos + 15 >= obTwo.xPos && ball.xPos - 15 <= obTwo.xPos && ball.yPos >= 205) {
    return 1;
  }
  else if (ball.xPos - 15 == obTwo.xPos + 15 && ball.yPos >= 205) {
    return 1;
  }
  else if (ball.xPos + 15 >= obThree.xPos && ball.xPos - 15 <= obThree.xPos && ball.yPos >= 205) {
    return 1;
  }
  else if (ball.xPos - 15 == obThree.xPos + 15 && ball.yPos >= 205) {
    return 1;
  }
  else {
    return 0;
  }
}

// Completely draws and animates the game
void DrawGame(character ball, obstacle obOne, obstacle obTwo, obstacle obThree, player *userInfo) {
  DrawDesert();
  DrawBall(ball);
  while (CheckCollision(ball, obOne, obTwo, obThree) == 0) {
    if (obOne.xPos <= -15) {
      if (rand() % 100 == 0) {
        obOne.xPos = 500;
      }
    }
    if (obTwo.xPos <= -15) {
      if (rand() % 100 == 0) {
        obTwo.xPos = 500;
      }
    }
    if (obThree.xPos <= -15) {
      if (rand() % 100 == 0) {
        obThree.xPos = 500;
      }
    }
    DrawDesert();
    DrawBall(ball);
    if (ball.yPos == 230) {
      if (get_key_state(KeySpace) != 0) {
        ball.yVel = -20;
      }
    }
    DrawObstacle(obOne);
    DrawObstacle(obTwo);
    DrawObstacle(obThree);
    g_printInt(userInfo->score, 0, 10, 10, 0, 0, 0, 3.0);
    graphics_update();
    ball.yPos += ball.yVel;
    ball.yVel += ball.gravity;
    if (ball.yPos > 230) {
      ball.yPos = 230;
    }
    obOne.xPos = obOne.xPos - 10;
    obTwo.xPos = obTwo.xPos - 10;
    obThree.xPos = obThree.xPos - 10;
    userInfo->score++;
  }
}

// Sorts the player initials and scores by ascending score
player ScoreSort(player value[], int numEntries) {
  int i, j;
  player tempVal;
  for (i = 0; i < numEntries; i++) {
    for (j = i + 1; j < numEntries; j++) {
      if (value[i].score < value[j].score) {
        tempVal = value[i];
        value[i] = value[j];
        value[j] = tempVal;
      }
    }
  }
  return value[numEntries];
}

int main(void) {
  srand(time(0));
  MyName();

  FILE *scoreFile = fopen("Scores.txt", "r");
  if (scoreFile == NULL) {
    scoreFile = fopen("Scores.txt", "w");
  }
  
  GameIntro();
  player userInfo[10];
  userInfo[0].score = 0;
  graphics_open(500, 300);
  graphics_fill(79, 42, 74);
  
  // Intro screen
  while (get_key_state(KeySpace) == 0) {
    g_printString("Run n' Jump", 100, 50, 255, 255, 255, 4.0);
    g_printString("Press spacebar to start and to jump", 70, 100, 255, 255, 255, 1.5);
    graphics_update();
  }
  
  character ball;
  ball.xPos = 50;
  ball.yPos = 230;
  ball.yVel = 0;
  ball.gravity = 2;
    
    // Countdown
    DrawDesert();
    for (int i = 0; i < 20; i++) {
    g_printInt(3, 1, 240, 140, 0, 0, 0, 4.0);
    graphics_update();
    }
    for (int i = 0; i < 20; i++) {
    DrawDesert();
    g_printInt(2, 1, 240, 140, 0, 0, 0, 4.0);
    graphics_update();
    }
    for (int i = 0; i < 20; i++) {
    DrawDesert();
    g_printInt(1, 1, 240, 140, 0, 0, 0, 4.0);
    graphics_update();
    }
    DrawDesert();
    graphics_update();
    
  graphics_circle_fill(ball.xPos, ball.yPos, 20, 255, 105, 180);
  graphics_update();
  
  
  obstacle obOne, obTwo, obThree;
  obOne.xPos = -15;
  obTwo.xPos = -15;
  obThree.xPos = -15;
  DrawGame(ball, obOne, obTwo, obThree, &userInfo[0]);
  userInfo[0].score--;
  
  printf("***GAME OVER***\n");
  printf("Score: %d\n\n", userInfo[0].score);
  g_printString("GAME OVER", 100, 100, 209, 0, 28, 4.0);
  graphics_update();
  
  graphics_fill(120, 0, 0);
  
  printf("Give your 3 initials: ");
  fgets(userInfo[0].initials, INITIAL_LIMIT, stdin);
  
  int highlightNum = userInfo[0].score;
  
  scoreFile = fopen("Scores.txt", "w");
  fprintf(scoreFile, "%0.3s %d\n", userInfo[0].initials, userInfo[0].score);
  for (int i = 1; i < 10; i++) {
    userInfo[i].score = (rand()%900) + 100;
      
    for (int j = 0; j < 3; j++) {
      userInfo[i].initials[j] = 'A' + rand()%26;
    }
    fprintf(scoreFile, "%0.3s %d\n", userInfo[i].initials, userInfo[i].score);
  }
    
    ScoreSort(userInfo, 10);
    
    g_printString("High Score List", 10, 10, 255, 255, 0, 2.0);
    for (int i = 0; i < 10; i++) {
      if (userInfo[i].score == highlightNum) {
        g_printInt(i + 1, 2, 30, 35 + (i*20), 60, 255, 0, 1.5);
        g_printString(userInfo[i].initials, 60, 35 + (i*20), 60, 255, 0, 1.5);
        g_printString(",", 92, 35 + (i*20), 60, 255, 0, 1.5);
        g_printInt(userInfo[i].score, 3, 110, 35 + (i*20), 60, 255, 0, 1.5);
        i++;
      }
      g_printInt(i + 1, 2, 30, 35 + (i*20), 255, 255, 255, 1.5);
      g_printString(userInfo[i].initials, 60, 35 + (i*20), 255, 255, 255, 1.5);
      g_printString(",", 92, 35 + (i*20), 255, 255, 255, 1.5);
      g_printInt(userInfo[i].score, 3, 110, 35 + (i*20), 255, 255, 255, 1.5);
    }
    graphics_update();
  
  fclose(scoreFile);
  
  return 0;
}
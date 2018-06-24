#include <Arduboy.h>
#include "OLDSprites.h"
float shipX;
float shipY;
float moveX;
float moveY;
int8_t HDG;
bool released;
signed short bullet[8][5];
float asteroids[8][4];
float rocks[16][4];
float pebbles[32][4];
byte bulletCount;
byte asteroidCount;
byte rockCount;
byte pebbleCount;
int8_t life;
uint8_t level = 0;
unsigned short score;
uint8_t tick;
bool turnC = false;
uint8_t state;
char initials[3];
static const PROGMEM float heading[24][2] = {
  { 0.00, -0.20}, { 0.05, -0.19},
  { 0.10, -0.17}, { 0.14, -0.14},
  { 0.17, -0.10}, { 0.19, -0.05},
  { 0.20, 0   }, { 0.19, 0.05},
  { 0.17, 0.10}, { 0.14, 0.14},
  { 0.10, 0.17}, { 0.05, 0.19},
  { 0   , 0.20}, { -0.05, 0.19},
  { -0.10, 0.17}, { -0.14, 0.14},
  { -0.17, 0.10}, { -0.19, 0.05},
  { -0.20, 0   }, { -0.19, -0.05},
  { -0.17, -0.10}, { -0.14, -0.14},
  { -0.10, -0.17}, { -0.05, -0.19}
};
static const PROGMEM signed short bulletST[24][2] = {
  { 0, -4}, { 2, -4}, { 3, -3}, { 3, -3},
  { 3, -3}, { 4, -2}, { 4, 0}, { 4, 2},
  { 3, 3}, { 3, 3}, { 3, 3}, { 2, 4},
  { 0, 4}, { -2, 4}, { -3, 3}, { -3, 3},
  { -3, 3}, { -4, 2}, { -4, 0}, { -4, -2},
  { -3, -3}, { -3, -3}, { -3, -3}, { -2, -4}
};
Arduboy arduboy;
void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(30);
  arduboy.clear();
  reboot();
  if (arduboy.audio.enabled()) arduboy.audio.on();
  else arduboy.audio.off();
}
void ship() {
  switch (HDG) {
    case  0: arduboy.drawTriangle(shipX    , shipY - 4, shipX + 3, shipY + 3, shipX - 3, shipY + 3, 1); break;

    case  1: arduboy.drawTriangle(shipX + 2, shipY - 4, shipX + 3, shipY + 3, shipX - 3, shipY + 2, 1); break;
    case  2: arduboy.drawTriangle(shipX + 3, shipY - 3, shipX + 2, shipY + 3, shipX - 3, shipY + 1, 1); break;
    case  3: arduboy.drawTriangle(shipX + 3, shipY - 3, shipX + 1, shipY + 3, shipX - 3, shipY - 1, 1); break;
    case  4: arduboy.drawTriangle(shipX + 3, shipY - 3, shipX - 1, shipY + 3, shipX - 3, shipY - 2, 1); break;
    case  5: arduboy.drawTriangle(shipX + 4, shipY - 2, shipX - 2, shipY + 3, shipX - 3, shipY - 3, 1); break;
    case  6: arduboy.drawTriangle(shipX + 4, shipY    , shipX - 3, shipY + 3, shipX - 3, shipY - 3, 1); break;

    case  7: arduboy.drawTriangle(shipX + 4, shipY + 2, shipX - 2, shipY - 3, shipX - 3, shipY + 3, 1); break;
    case  8: arduboy.drawTriangle(shipX + 3, shipY + 3, shipX - 1, shipY - 3, shipX - 3, shipY + 2, 1); break;
    case  9: arduboy.drawTriangle(shipX + 3, shipY + 3, shipX + 1, shipY - 3, shipX - 3, shipY + 1, 1); break;
    case 10: arduboy.drawTriangle(shipX + 3, shipY + 3, shipX + 2, shipY - 3, shipX - 3, shipY - 1, 1); break;
    case 11: arduboy.drawTriangle(shipX + 2, shipY + 4, shipX + 3, shipY - 3, shipX - 3, shipY - 2, 1); break;
    case 12: arduboy.drawTriangle(shipX    , shipY + 4, shipX + 3, shipY - 3, shipX - 3, shipY - 3, 1); break;

    case 13: arduboy.drawTriangle(shipX - 2, shipY + 4, shipX - 3, shipY - 3, shipX + 3, shipY - 2, 1); break;
    case 14: arduboy.drawTriangle(shipX - 3, shipY + 3, shipX - 2, shipY - 3, shipX + 3, shipY - 1, 1); break;
    case 15: arduboy.drawTriangle(shipX - 3, shipY + 3, shipX - 1, shipY - 3, shipX + 3, shipY + 1, 1); break;
    case 16: arduboy.drawTriangle(shipX - 3, shipY + 3, shipX + 1, shipY - 3, shipX + 3, shipY + 2, 1); break;
    case 17: arduboy.drawTriangle(shipX - 4, shipY + 2, shipX + 2, shipY - 3, shipX + 3, shipY + 3, 1); break;
    case 18: arduboy.drawTriangle(shipX - 4, shipY    , shipX + 3, shipY + 3, shipX + 3, shipY - 3, 1); break;

    case 19: arduboy.drawTriangle(shipX - 4, shipY - 2, shipX + 2, shipY + 3, shipX + 3, shipY - 3, 1); break;
    case 20: arduboy.drawTriangle(shipX - 3, shipY - 3, shipX + 1, shipY + 3, shipX + 3, shipY - 2, 1); break;
    case 21: arduboy.drawTriangle(shipX - 3, shipY - 3, shipX - 1, shipY + 3, shipX + 3, shipY - 1, 1); break;
    case 22: arduboy.drawTriangle(shipX - 3, shipY - 3, shipX - 2, shipY + 3, shipX + 3, shipY + 1, 1); break;
    case 23: arduboy.drawTriangle(shipX - 2, shipY - 4, shipX - 3, shipY + 3, shipX + 3, shipY + 2, 1); break;
  }
}
void flightControl() {
  if (arduboy.everyXFrames(2)) {
    if (arduboy.pressed(LEFT_BUTTON)) HDG--;
    if (arduboy.pressed(RIGHT_BUTTON)) HDG++;
    if (HDG > 23) HDG = HDG - 24;
    if (HDG < 0) HDG = HDG + 24;
    if (arduboy.pressed(UP_BUTTON)) {
      moveX = moveX + pgm_read_float(&heading[HDG][0]);
      moveY = moveY + pgm_read_float(&heading[HDG][1]);
    }
  }
  if (moveY > 3)moveY = 3;
  if (moveY < -3)moveY = -3;
  if (moveX > 3)moveX = 3;
  if (moveX < -3)moveX = -3;
  if (moveY > 0)moveY = moveY - 0.01;
  if (moveY < 0)moveY = moveY + 0.01;
  if (moveX > 0)moveX = moveX - 0.01;
  if (moveX < 0)moveX = moveX + 0.01;
  if (abs(moveX) < 0.03) moveX = 0;
  if (abs(moveY) < 0.03) moveY = 0;
  if (arduboy.pressed(DOWN_BUTTON) && released) {
    delay(300);
    if (random(0, 3) == 2) {
      delay(200);
      collision();
    } else {
      released = false;
      moveX = moveY = 0;
      shipX = random(0, 128);
      shipY = random(0, 64);
    }
  }
}
void navigation() {
  shipX = shipX + moveX;
  shipY = shipY + moveY;
  if (shipX < -5) shipX = shipX + 138;
  if (shipX > 133) shipX = shipX - 138;
  if (shipY < -5) shipY = shipY + 74;
  if (shipY > 69) shipY = shipY - 74;
}

void firing() {
  bullet[bulletCount][1] = (short)(round)(pgm_read_float(&heading[HDG][0]) * 20);
  bullet[bulletCount][3] = (short)(round)(pgm_read_float(&heading[HDG][1]) * 20);
  bullet[bulletCount][0] = (short)shipX + (short)(round)pgm_read_float(&bulletST[HDG][0]);
  bullet[bulletCount][2] = (short)shipY + (short)(round)pgm_read_float(&bulletST[HDG][1]);
  bullet[bulletCount][4] = 100;
  bulletCount = bulletCount + 1;
  arduboy.tunes.tone(450, 20);
}
void trajectory() {
  for (uint8_t t = 0; t < bulletCount; t++) {
    bullet[t][0] = bullet[t][0] + bullet[t][1];
    bullet[t][2] = bullet[t][2] + bullet[t][3];
    if (bullet[t][0] < -5) bullet[t][0] = bullet[t][0] + 138;
    if (bullet[t][0] > 133) bullet[t][0] = bullet[t][0] - 138;
    if (bullet[t][2] < -5) bullet[t][2] = bullet[t][2] + 74;
    if (bullet[t][2] > 69) bullet[t][2] = bullet[t][2] - 74;
    if (bullet[t][4] < 0) {
      bullet[t][4] = 0;
      for (uint8_t a = 0; a < bulletCount - 1; a++)
        for (uint8_t b = 0; b < 5; b++)
          bullet[a][b] = bullet[a + 1][b];
      bullet[bulletCount][0] = 0;
      bullet[bulletCount][1] = 0;
      bullet[bulletCount][2] = 0;
      bullet[bulletCount][3] = 0;
      bullet[bulletCount][4] = 0;
      bulletCount = bulletCount - 1;
    }
    arduboy.drawPixel(bullet[t][0], bullet[t][2], 1);
    bullet[t][4] = bullet[t][4] - 4;
  }
}
void asteroid() {
  for (uint8_t t = 0; t < asteroidCount; t++) {
    asteroids[t][0] = asteroids[t][0] + asteroids[t][1];
    asteroids[t][2] = asteroids[t][2] + asteroids[t][3];
    if (asteroids[t][0] < -5) asteroids[t][0] = asteroids[t][0] + 138;
    if (asteroids[t][0] > 133) asteroids[t][0] = asteroids[t][0] - 138;
    if (asteroids[t][2] < -5) asteroids[t][2] = asteroids[t][2] + 74;
    if (asteroids[t][2] > 69) asteroids[t][2] = asteroids[t][2] - 74;
    for (uint8_t b = 0; b < bulletCount; b++) {
      if (abs(bullet[b][0] - asteroids[t][0]) < 5 && abs(bullet[b][2] - asteroids[t][2]) < 5) {
        for (uint8_t a = b; a < bulletCount - 1; a++) {
          bullet[a][0] = bullet[a + 1][0];
          bullet[a][1] = bullet[a + 1][1];
          bullet[a][2] = bullet[a + 1][2];
          bullet[a][3] = bullet[a + 1][3];
          bullet[a][4] = bullet[a + 1][4];
        }
        bullet[bulletCount][0] = 0;
        bullet[bulletCount][1] = 0;
        bullet[bulletCount][2] = 0;
        bullet[bulletCount][3] = 0;
        bullet[bulletCount][4] = 0;
        bulletCount = bulletCount - 1;

        arduboy.tunes.tone(150, 50);
        score = score + 5;

        rocks[rockCount][0] = asteroids[t][0];
        rocks[rockCount][2] = asteroids[t][2];
        rocks[rockCount][1] = random(-10, 10) * 0.05;
        rocks[rockCount][3] = random(-10, 10) * 0.05;
        rockCount = rockCount + 1;
        rocks[rockCount][0] = asteroids[t][0];
        rocks[rockCount][2] = asteroids[t][2];
        rocks[rockCount][1] = random(-10, 10) * 0.05;
        rocks[rockCount][3] = random(-10, 10) * 0.05;
        rockCount = rockCount + 1;

        for (uint8_t c = t; c < asteroidCount - 1; c++)
          for (uint8_t d = 0; d < 4; d++)
            asteroids[c][d] = asteroids[c + 1][d];
        asteroidCount = asteroidCount - 1;
      }
    }
    arduboy.drawBitmap(asteroids[t][0] - 2, asteroids[t][2] - 2, bmpAst0a, 9, 10, WHITE);
    //arduboy.drawCircle(asteroids[t][0], asteroids[t][2], 5, 5);
  }
}
void rock() {
  for (uint8_t r = 0; r < rockCount; r++) {
    rocks[r][0] = rocks[r][0] + rocks[r][1];
    rocks[r][2] = rocks[r][2] + rocks[r][3];
    if (rocks[r][0] < -5) rocks[r][0] = rocks[r][0] + 138;
    if (rocks[r][0] > 133) rocks[r][0] = rocks[r][0] - 138;
    if (rocks[r][2] < -5) rocks[r][2] = rocks[r][2] + 74;
    if (rocks[r][2] > 69) rocks[r][2] = rocks[r][2] - 74;
    for (uint8_t b = 0; b < bulletCount; b++) {
      if (abs(bullet[b][0] - rocks[r][0]) < 4 && abs(bullet[b][2] - rocks[r][2]) < 4) {
        for (uint8_t a = b; a < bulletCount - 1; a++) {
          bullet[a][0] = bullet[a + 1][0];
          bullet[a][1] = bullet[a + 1][1];
          bullet[a][2] = bullet[a + 1][2];
          bullet[a][3] = bullet[a + 1][3];
          bullet[a][4] = bullet[a + 1][4];
        }
        bullet[bulletCount][0] = 0;
        bullet[bulletCount][1] = 0;
        bullet[bulletCount][2] = 0;
        bullet[bulletCount][3] = 0;
        bullet[bulletCount][4] = 0;
        bulletCount = bulletCount - 1;

        arduboy.tunes.tone(150, 50);
        score = score + 10;

        pebbles[pebbleCount][0] = rocks[r][0];
        pebbles[pebbleCount][2] = rocks[r][2];
        pebbles[pebbleCount][1] = random(-10, 10) * 0.05;
        pebbles[pebbleCount][3] = random(-10, 10) * 0.05;
        pebbleCount = pebbleCount + 1;
        pebbles[pebbleCount][0] = rocks[r][0];
        pebbles[pebbleCount][2] = rocks[r][2];
        pebbles[pebbleCount][1] = random(-10, 10) * 0.05;
        pebbles[pebbleCount][3] = random(-10, 10) * 0.05;
        pebbleCount = pebbleCount + 1;

        for (uint8_t c = r; c < rockCount - 1; c++)
          for (uint8_t d = 0; d < 4; d++)
            rocks[c][d] = rocks[c + 1][d];
        rockCount = rockCount - 1;
      }
    }
    arduboy.drawBitmap(rocks[r][0] - 2, rocks[r][2] - 2, bmpAst1b, 9, 10, WHITE);
    //arduboy.drawCircle(rocks[r][0], rocks[r][2], 4, 4);
  }
}
void pebble() {
  for (uint8_t p = 0; p < pebbleCount; p++) {
    pebbles[p][0] = pebbles[p][0] + pebbles[p][1];
    pebbles[p][2] = pebbles[p][2] + pebbles[p][3];
    if (pebbles[p][0] < -5) pebbles[p][0] = pebbles[p][0] + 138;
    if (pebbles[p][0] > 133) pebbles[p][0] = pebbles[p][0] - 138;
    if (pebbles[p][2] < -5) pebbles[p][2] = pebbles[p][2] + 74;
    if (pebbles[p][2] > 69) pebbles[p][2] = pebbles[p][2] - 74;
    for (uint8_t b = 0; b < bulletCount; b++) {
      if (abs(bullet[b][0] - pebbles[p][0]) < 2 && abs(bullet[b][2] - pebbles[p][2]) < 2) {
        for (uint8_t a = b; a < bulletCount - 1; a++) {
          bullet[a][0] = bullet[a + 1][0];
          bullet[a][1] = bullet[a + 1][1];
          bullet[a][2] = bullet[a + 1][2];
          bullet[a][3] = bullet[a + 1][3];
          bullet[a][4] = bullet[a + 1][4];
        }
        bullet[bulletCount][0] = 0;
        bullet[bulletCount][1] = 0;
        bullet[bulletCount][2] = 0;
        bullet[bulletCount][3] = 0;
        bullet[bulletCount][4] = 0;
        bulletCount = bulletCount - 1;

        arduboy.tunes.tone(150, 50);
        score = score + 15;

        for (uint8_t c = p; c < pebbleCount - 1; c++)
          for (uint8_t d = 0; d < 4; d++)
            pebbles[c][d] = pebbles[c + 1][d];
        pebbles[pebbleCount][0] = 0;
        pebbles[pebbleCount][1] = 0;
        pebbles[pebbleCount][2] = 0;
        pebbles[pebbleCount][3] = 0;
        pebbleCount = pebbleCount - 1;
      }
    }
    arduboy.drawBitmap(pebbles[p][0] - 2, pebbles[p][2] - 2, bmpAst3c, 9, 10, WHITE);
    //arduboy.drawCircle(pebbles[p][0], pebbles[p][2], 2, 2);
  }
}
void radar() {
  for (uint8_t a = 0; a < asteroidCount; a ++) {
    if (abs(asteroids[a][0] - shipX) < 7 && abs(asteroids[a][2] - shipY) < 7) {
      arduboy.tunes.tone(150, 50);
      collision();
      rocks[rockCount][0] = asteroids[a][0] + asteroids[a][1];
      rocks[rockCount][2] = asteroids[a][2] + asteroids[a][3];
      rocks[rockCount][1] = - asteroids[a][1];
      rocks[rockCount][3] = - asteroids[a][3];
      rockCount = rockCount + 1;
      for (uint8_t c = a; c < asteroidCount - 1; c++)
        for (uint8_t d = 0; d < 4; d++)
          asteroids[c][d] = asteroids[c + 1][d];
      asteroidCount = asteroidCount - 1;
    }
  }
  for (uint8_t r = 0; r < rockCount; r ++) {
    if (abs(rocks[r][0] - shipX) < 5 && abs(rocks[r][2] - shipY) < 5) {
      arduboy.tunes.tone(150, 50);
      collision();
      pebbles[pebbleCount][0] = rocks[r][0] + rocks[r][1];
      pebbles[pebbleCount][2] = rocks[r][2] + rocks[r][3];
      pebbles[pebbleCount][1] = - rocks[r][1];
      pebbles[pebbleCount][3] = - rocks[r][3];
      pebbleCount = pebbleCount + 1;
      for (uint8_t c = r; c < rockCount - 1; c++)
        for (uint8_t d = 0; d < 4; d++)
          rocks[c][d] = rocks[c + 1][d];
      rockCount = rockCount - 1;
    }
  }
  for (uint8_t p = 0; p < pebbleCount; p ++) {
    if (abs(pebbles[p][0] - shipX) < 3 && abs(pebbles[p][2] - shipY) < 3) {
      delay(200);
      collision();
      for (uint8_t c = p; c < pebbleCount - 1; c++)
        for (uint8_t d = 0; d < 4; d++)
          pebbles[c][d] = pebbles[c + 1][d];
      pebbleCount = pebbleCount - 1;
    }
  }
  if (asteroidCount == 0 && rockCount == 0 && pebbleCount == 0) {
    tick = tick - 1;
    if (tick <= 0) {
      tick = 240;
      if (level < 8) level = level + 1;

      for (int8_t s = 0; s < level; s++) {
        asteroids[asteroidCount][0] = 96 + random(0, 74);
        asteroids[asteroidCount][2] = 48 + random(0, 42);
        asteroids[asteroidCount][1] = random(-10, 10) * 0.05;
        asteroids[asteroidCount][3] = random(-10, 10) * 0.05;
        asteroidCount = asteroidCount + 1;
      }
    }
  }
}
void collision() {
  arduboy.tunes.tone(150, 50);
  life = life - 1;
  shipX = 64;
  shipY = 32;
  moveX = 0;
  moveY = 0;
}
void reboot() {
  shipY = 50;
  shipX = 64;
  resetField();
  state = 0;
}
void resetField() {
  level = 0;
  moveX = moveY = 0;
  tick = 240;
  bulletCount = 0;
  asteroidCount = rockCount = pebbleCount = 0;
}
void enterInitials() {
  int8_t index = 0;
  initials[0] = ' ';
  initials[1] = ' ';
  initials[2] = ' ';
  while (index < 3) {
    arduboy.clear();
    arduboy.setCursor(16, 0);
    arduboy.print(F("HIGH SCORE"));
    arduboy.setCursor(88, 0);
    arduboy.print(score);

    arduboy.setCursor(56, 20);
    arduboy.print(initials[0]);
    arduboy.setCursor(64, 20);
    arduboy.print(initials[1]);
    arduboy.setCursor(72, 20);
    arduboy.print(initials[2]);
    arduboy.drawLine(56, 27, 56 + 6, 27, 1);
    arduboy.drawLine(64, 27, 64 + 6, 27, 1);
    arduboy.drawLine(72, 27, 72 + 6, 27, 1);
    arduboy.drawLine(56 + (index * 8), 28, 56 + (index * 8) + 6, 28, 1);
    delay(150);
    if (arduboy.pressed(LEFT_BUTTON) && released) {
      released = false;
      arduboy.tunes.tone(1046, 200);
      index--;
      if (index < 0) index = 0;
    }

    if (arduboy.pressed(RIGHT_BUTTON) && released) {
      released = false;
      index++;
      if (index > 2) index = 2;
      arduboy.tunes.tone(1046, 200);
    }

    if (arduboy.pressed(DOWN_BUTTON)) {
      initials[index]++;
      arduboy.tunes.tone(523, 150);
      // A-Z 0-9 :-? !-/ ' '
      if (initials[index] == '0') initials[index] = ' ';
      if (initials[index] == '!') initials[index] = 'A';
      if (initials[index] == '[') initials[index] = '0';
      if (initials[index] == '@') initials[index] = '!';
    }
    if (arduboy.pressed(UP_BUTTON)) {
      initials[index]--;
      arduboy.tunes.tone(523, 150);
      if (initials[index] == ' ') initials[index] = '?';
      if (initials[index] == '/') initials[index] = 'Z';
      if (initials[index] == 31)  initials[index] = '/';
      if (initials[index] == '@') initials[index] = ' ';
    }
    if (arduboy.pressed(A_BUTTON)) {
      if (index >= 2) {
        index = index + 1;
        arduboy.tunes.tone(1046, 200);
      }
    }
    if (arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
      released = true;
    arduboy.display();
  }
}
void loop() {

  // put your main code here, to run repeatedly:
  if (state == 1) arduboy.setFrameRate(30);
  else arduboy.setFrameRate(15);
  if (!arduboy.nextFrame())return;
  arduboy.clear();
  switch (state) {
    case 0: {
        //begin homescreen
        arduboy.setCursor(10, 10);
        arduboy.setTextSize(2);
        arduboy.print(F("ASTEROIDS"));
        if (arduboy.everyXFrames(10)) {
          turnC = random(0, 2) == 1;
        }
        if (arduboy.everyXFrames(3)) {
          if (turnC) HDG = HDG + 1;
          else HDG = HDG - 1;
        }
        if (HDG > 23) HDG = HDG - 24;
        if (HDG < 0) HDG = HDG + 24;
        moveX = 1;
        navigation();
        if (arduboy.everyXFrames(5) && (bulletCount < 8)) {
          firing();
        }
        trajectory();
        if (arduboy.pressed(B_BUTTON) && released) {
          released = false;
          life = 3;
          shipX = 64;
          shipY = 32;
          resetField();
          state = 1;
        }
        if ((arduboy.pressed(UP_BUTTON) || arduboy.pressed(DOWN_BUTTON)) && released) {
          released = false;
          if (arduboy.audio.enabled()) arduboy.audio.off();
          else arduboy.audio.on();
          arduboy.audio.saveOnOff();
        }
        if (arduboy.pressed(A_BUTTON) && released) {
          released = false;
          state = 3;
        }
      }
      break;
    case 1: {
        if (life > 0) {
          flightControl();
          navigation();
          if (arduboy.pressed(B_BUTTON) && released && (bulletCount < 8)) {
            released = false;
            firing();
          }
          trajectory();
          asteroid();
          rock();
          pebble();
          radar();

          arduboy.setTextSize(1);
          arduboy.setCursor(2, 10);
          arduboy.print(score);
          arduboy.setCursor(32, 10);
          arduboy.print(level);
          arduboy.setCursor(120, 10);
          arduboy.print(life);
          if (life == 0) {
            resetField();
          }
          if (arduboy.pressed(A_BUTTON) && released) {
            released = false;
            state = 4;
          }
        } else {
          delay(3000);
          resetField();
          state = 2;
        }
      }
      break;
    case 2: {
        char tmpInitials[3];
        unsigned short tmpScore;
        // Each block of EEPROM has 7 high scores, and each high score entry
        // is 5 byte long:  3 char for initials and a short for score.
        // High score processing
        for (int8_t i = 0; i < 7; i++) {
          EEPROM.get(100 + (5 * i), tmpScore);
          if (tmpScore == 0xFFFF) tmpScore = 0;
          if (score > tmpScore) {
            enterInitials();
            for (byte j = i; j < 7; j++) {
              EEPROM.get(100 + (5 * j), tmpScore);
              if (tmpScore == 0xFFFF) tmpScore = 0;

              tmpInitials[0] = (char)EEPROM.read(100 + (5 * j) + 2);
              tmpInitials[1] = (char)EEPROM.read(100 + (5 * j) + 3);
              tmpInitials[2] = (char)EEPROM.read(100 + (5 * j) + 4);

              // write score and initials to current slot
              EEPROM.put(100 + (5 * j), score);
              EEPROM.write(100 + (5 * j) + 2, initials[0]);
              EEPROM.write(100 + (5 * j) + 3, initials[1]);
              EEPROM.write(100 + (5 * j) + 4, initials[2]);

              // tmpScore and tmpInitials now hold what we want to
              //write in the next slot.
              score = tmpScore;
              initials[0] = tmpInitials[0];
              initials[1] = tmpInitials[1];
              initials[2] = tmpInitials[2];
            }
            //reset the initials
            initials[0] = ' ';
            initials[1] = ' ';
            initials[2] = ' ';
            break;
          }
        }
      }
      reboot();
      break;
    case 3:
      // Each block of EEPROM has 7 high scores, and each high score entry
      // is 5 int8_ts long:  3 int8_ts for initials and one int16_t for score
      arduboy.setCursor(32, 0);
      arduboy.print("HIGH SCORES");

      for (int i = 0; i < 7; i++) {
        EEPROM.get(100 + (5 * i), score);
        if (score == 0xFFFF) score = 0;
        initials[0] = (char)EEPROM.read(100 + (5 * i) + 2);
        initials[1] = (char)EEPROM.read(100 + (5 * i) + 3);
        initials[2] = (char)EEPROM.read(100 + (5 * i) + 4);

        arduboy.setCursor(30, 9 + (i * 8));
        arduboy.setTextSize(1);
        arduboy.print(i + 1);
        arduboy.print(F(" "));
        arduboy.print(initials[0]);
        arduboy.print(initials[1]);
        arduboy.print(initials[2]);
        arduboy.print(F(" "));
        arduboy.print(score);

        score = 0;
      }
      if (arduboy.pressed(A_BUTTON) && released) {
        released = false;
        state = 0;
      }

      if (arduboy.pressed(LEFT_BUTTON) && released) {
        released = false;
        state = 5;
      }
      break;
    case 4:
      arduboy.setCursor(32, 30);
      arduboy.setTextSize(2);
      arduboy.print(F("PAUSE"));
      if (arduboy.pressed(B_BUTTON) && released) {
        released = false;
        state = 1;
      }
      if (arduboy.pressed(A_BUTTON) && released) {
        released = false;
        reboot();
      }
      if ((arduboy.pressed(UP_BUTTON) || arduboy.pressed(DOWN_BUTTON)) && released) {
        released = false;
        if (arduboy.audio.enabled()) arduboy.audio.off();
        else arduboy.audio.on();
        arduboy.audio.saveOnOff();
      }
      break;
    case 5:
      arduboy.setCursor(14, 32);
      arduboy.setTextSize(1);
      arduboy.print(F("EREASE HIGHSCORE?"));
      arduboy.setCursor(14, 40);
      arduboy.print(F("START = RIGHT + B"));
      if (arduboy.pressed(RIGHT_BUTTON + B_BUTTON)) {
        released = false;
        for (int i = 0; i < 35; i ++) {
          arduboy.clear();
          arduboy.setCursor(36, HEIGHT / 2);
          arduboy.print(F("WORKING..."));
          arduboy.display();
          EEPROM.update(i + 100, 0xff);
        }
        delay(500);
        arduboy.setCursor(32, HEIGHT / 2);
        arduboy.clear();
        arduboy.print(F("EREASE DONE"));
        arduboy.display();
        delay(1000);
        state = 0;
      }
      if (arduboy.pressed(A_BUTTON) && released) {
        released = false;
        state = 0;
      }
      break;



  }

  //begin printObj
  //debug use
  arduboy.setTextSize(1);
  arduboy.setCursor(2, 10);
  arduboy.print(score);
  arduboy.setCursor(32, 10);
  arduboy.print(level);
  arduboy.setCursor(120, 10);
  arduboy.print(life);

  arduboy.setCursor(44, 10);
  arduboy.print(HDG);
  arduboy.setCursor(60, 10);
  arduboy.print(asteroidCount);
  arduboy.setCursor(78, 10);
  arduboy.print(rockCount);
  arduboy.setCursor(96, 10);
  arduboy.print(pebbleCount);
  arduboy.setCursor(110, 10);
  arduboy.print(bulletCount);

  arduboy.setCursor(100, 25);
  arduboy.print(shipX);
  arduboy.setCursor(100, 35);
  arduboy.print(shipY);
  arduboy.setCursor(100, 45);
  arduboy.print(moveX);
  arduboy.setCursor(100, 55);
  arduboy.print(moveY);
  arduboy.setCursor(10, 50);
  arduboy.print(tick);
  arduboy.setCursor(10, 30);
  arduboy.print(arduboy.cpuLoad());
  //debug use


  if (state < 2) {
    ship();
  }
  //end printObj
  //begin display
  if (arduboy.audio.enabled()) {
    arduboy.drawRect(WIDTH - 3, HEIGHT - 2, 2, 2, 1);
    arduboy.drawLine(WIDTH - 2, HEIGHT - 5, WIDTH - 2, HEIGHT - 1, 1);
    arduboy.drawPixel(WIDTH - 1, HEIGHT - 4, 1);
  }
  arduboy.display();
  //end display

  //begin pollButtons
  if (arduboy.notPressed(A_BUTTON | B_BUTTON | UP_BUTTON |DOWN_BUTTON | LEFT_BUTTON | RIGHT_BUTTON))
    released = true;
  //end pollButtons
}
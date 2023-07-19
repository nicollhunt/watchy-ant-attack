#include "Watchy_AntAttack.h"
#include "glyphs.h"
#include "sprites.h"
#include "zx_spectrum_5.h"
#include <Fonts/FreeSans9pt7b.h>

#define FONT_SPECCY zx_spectrum_75pt7b

const unsigned char *block_mask = epd_bitmap_block_mask;
const unsigned char *block_detail = epd_bitmap_block_detail;

const unsigned char *sprites_boy [] = {epd_bitmap_boy_idle, epd_bitmap_boy_run};
const unsigned char *sprites_girl [] = {epd_bitmap_girl_idle, epd_bitmap_girl_run};
const unsigned char *sprites_ant = epd_bitmap_ant;

void WatchyAntAttack::drawWatchFace()
{
    readWorldTime();

    uint32_t stepCount = updateStepCount();
    uint32_t batteryPercent = getBatteryPercent();  

    //Save battery life
    WiFi.mode(WIFI_OFF);
    btStop();

    drawBorder();

    drawSteps(stepCount);

    drawTime();

    drawBattery(batteryPercent);

    // TODO: Use some kind of collision detection to stop characters appearing on top of each other 
    int numAnts = 3;
    for (int i = 0 ; i < numAnts ; i++)
    {
      drawRandomCharacter(sprites_ant);
    }

    drawRandomCharacter(sprites_boy[random(2)]);
    drawRandomCharacter(sprites_girl[random(2)]);
}

uint32_t WatchyAntAttack::updateStepCount()
{
    // Reset at midnight
    if (currentTime.Hour == 0 && currentTime.Minute == 1)
    {
        sensor.resetStepCounter();
    }
    return sensor.getCounter();
}

uint32_t WatchyAntAttack::getBatteryPercent()
{
    // Magic numbers to calculate battery usage
    const float MAX_VBAT = 4.20;
    const float MIN_VBAT = 3.80;

    // Convert voltage to usage
    float VBAT = getBatteryVoltage();
    uint32_t percent = (int)(100.0 * ((VBAT - MIN_VBAT) / (MAX_VBAT - MIN_VBAT)));
    if (percent < 0)
        percent = 0;
    if (percent > 100)
        percent = 100;

    return percent;
}

void WatchyAntAttack::drawBorder()
{
      display.fillScreen(GxEPD_BLACK);

    int border_l = 0;
    int border_r = 0;
    int border_t = 16;
    int border_b = 0;
    
    display.fillRect(border_l, border_t, 200 - (border_l + border_r), 200 - (border_t + border_b), GxEPD_WHITE);
}

void WatchyAntAttack::drawSteps(uint32_t stepCount)
{
    display.setTextColor(GxEPD_WHITE);

    char strBuf[50];
    sprintf(strBuf, "SCORE : %d", stepCount);

    display.setFont(&FONT_SPECCY);

    int16_t  x1, y1;
    uint16_t w, h;
    display.getTextBounds(strBuf, 0, 0, &x1, &y1, &w, &h);

    display.setCursor(100 - w / 2, 10);
    display.println(strBuf);
}

void WatchyAntAttack::drawBattery(uint32_t percent)
{
    int p = percent / 10;
    int s = (p / 2 ) - 1;
    for (int i = 0 ; i < p ; i++)
    {
        drawBlock(s - i, 0, 2);
    }
}

void WatchyAntAttack::drawRandomCharacter(const unsigned char *sprites)
{
    int x, y;
    getRandomPosition(x, y);
    int dir = random(4);
    display.drawBitmap(x, y, sprites + 32 * dir, 16, 16, GxEPD_BLACK);
}

float lerp(float a, float b, float t)
{
  return a + (b - a) * t;
}

///
/// Deeply hacky code to get a random position in the bottom right-ish area of screen
///
void WatchyAntAttack::getRandomPosition(int &x, int &y)
{
    float t = random(100) / 100.0f;
    x = lerp(10, 190, t);

    int minY = lerp(10, 110, t);
    y = 180 - random(minY);
}


void WatchyAntAttack::drawTime()
{
    int pos1 = 3;
    int pos2 = 7;

    drawNumberWithBlocks(pos2, 0, 0, currentTime.Minute % 10);
    drawNumberWithBlocks(pos1, 0, 0, currentTime.Minute / 10);

    drawGlyphWithBlocks(0, 0, 0, glyph_colon);

    drawNumberWithBlocks(-pos1, 0, 0, currentTime.Hour % 10);
    drawNumberWithBlocks(-pos2, 0, 0, currentTime.Hour / 10);
}

void WatchyAntAttack::drawBlock(int x, int y, int z)
{
    int origin_x = 100 - 8;
    int origin_y = 100 - 4;

    int pos_x = origin_x + x * 8 + z * 8;
    int pos_y = origin_y - x * 4 + z * 4 - y * 8;
    
    // Clear mask then draw bitmap
    display.drawBitmap(pos_x, pos_y, block_mask, 16, 16, GxEPD_WHITE);
    display.drawBitmap(pos_x, pos_y, block_detail, 16, 16, GxEPD_BLACK);
}

void WatchyAntAttack::drawGlyphWithBlocks(int x, int y, int z, const unsigned char *glyph)
{
  for (int i = 14 ; i >= 0 ; i--)
  {
    if (glyph[i] != 1)
      continue;

    int block_x = (x - 1) + i % 3;
    int block_y = y + 5 - i / 3;

    drawBlock(block_x, block_y, z);
  }
}

void WatchyAntAttack::drawNumberWithBlocks(int x, int y, int z, int value)
{
  // TODO: Support numbers with multiple digits
  auto glyph = glyph_numbers[value % 10];
  drawGlyphWithBlocks(x, y, z, glyph);
}
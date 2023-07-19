#ifndef WATCHY_ANT_ATTACK_H
#define WATCHY_ANT_ATTACK_H

#include "wta.h"

class WatchyAntAttack : public WatchySynced
{
    using WatchySynced::WatchySynced;
    protected:
        uint32_t updateStepCount();
        uint32_t getBatteryPercent();
        void drawBorder();
        void drawSteps(uint32_t stepCount);
        void drawBattery(uint32_t percent);
        void drawTime();
        void drawBlock(int x, int y, int z);
        void drawGlyphWithBlocks(int x, int y, int z, const unsigned char *glyph);
        void drawNumberWithBlocks(int x, int y, int z, int digit);
        void getRandomPosition(int &x, int &y);
        void drawRandomCharacter(const unsigned char *sprites);

    public:
        void drawWatchFace();
};

#endif
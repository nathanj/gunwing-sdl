#include "stage1.h"

#include "enemy.h"
#include "boss.h"
#include "shrapnel-enemy.h"
#include "warning.h"
#include "boss2.h"
#include "music.h"

#define MAKE_ENEMY(ms, x, y, dx, dy)                      \
        enemies_to_appear_.push_back(                     \
            std::make_pair(std::chrono::milliseconds(ms), \
                           std::make_shared<Enemy>(x, y, dx, dy)))

Stage1::Stage1()
{
        background_ = std::make_shared<Background>(Background::background2_);

        Music::playMusic("stage.mp3", std::chrono::milliseconds(2000));

        MAKE_ENEMY(2100, 480, 0, -1, 1);
        MAKE_ENEMY(2200, 510, 40, -1, 1);
        MAKE_ENEMY(2300, 500, 80, -1, 1);
        MAKE_ENEMY(2500, 490, 120, -1, 1);
        MAKE_ENEMY(3000, 530, 20, -1, 1);
        MAKE_ENEMY(3200, 500, 60, -1, 1);
        MAKE_ENEMY(3500, 510, 100, -1, 1);
        MAKE_ENEMY(3700, 500, 110, -1, 1);

        //enemies_to_appear_.push_back(std::make_pair(
        //    std::chrono::milliseconds(5000), std::make_shared<Warning>()));

        //enemies_to_appear_.push_back(std::make_pair(
        //    // std::chrono::milliseconds(8000),
        //    std::chrono::milliseconds(10000),
        //    std::make_shared<Boss>(40, -300)));
        //return;

        MAKE_ENEMY(5200, -30, 60, 1, 1);
        MAKE_ENEMY(5200, 480, 60, -1, 1);
        MAKE_ENEMY(5500, -20, 100, 1, 1);
        MAKE_ENEMY(5500, 490, 100, -1, 1);
        MAKE_ENEMY(5700, -50, 130, 1, 1);
        MAKE_ENEMY(5700, 530, 130, -1, 1);

        MAKE_ENEMY(7200, 370, -20, 0, 1);
        MAKE_ENEMY(7200, 70, -20, 0, 1);
        MAKE_ENEMY(7500, 130, -30, 0, 1);
        MAKE_ENEMY(7500, 310, -30, 0, 1);
        MAKE_ENEMY(7700, 190, -40, 0, 1);
        MAKE_ENEMY(7700, 250, -40, 0, 1);

        MAKE_ENEMY(10100, 480, 0, -1, 1);
        MAKE_ENEMY(10200, 510, 40, -1, 1);
        MAKE_ENEMY(10300, 500, 80, -1, 1);
        MAKE_ENEMY(10500, 490, 120, -1, 1);
        MAKE_ENEMY(11000, 530, 20, -1, 1);
        MAKE_ENEMY(11200, 500, 60, -1, 1);
        MAKE_ENEMY(11500, 510, 100, -1, 1);
        MAKE_ENEMY(11700, 500, 110, -1, 1);

        enemies_to_appear_.push_back(
            std::make_pair(std::chrono::milliseconds(12000),
                           std::make_shared<ShrapnelEnemy>(200, -32)));

        MAKE_ENEMY(17100, 480, 0, -1, 1);
        MAKE_ENEMY(17200, 510, 40, -1, 1);
        MAKE_ENEMY(17300, 500, 80, -1, 1);
        MAKE_ENEMY(17500, 490, 120, -1, 1);
        MAKE_ENEMY(18000, 530, 20, -1, 1);
        MAKE_ENEMY(18200, 500, 60, -1, 1);
        MAKE_ENEMY(18500, 510, 100, -1, 1);
        MAKE_ENEMY(18700, 500, 110, -1, 1);

        MAKE_ENEMY(20200, -30, 60, 1, 1);
        MAKE_ENEMY(20200, 480, 60, -1, 1);
        MAKE_ENEMY(20500, -20, 100, 1, 1);
        MAKE_ENEMY(20500, 490, 100, -1, 1);
        MAKE_ENEMY(20700, -50, 130, 1, 1);
        MAKE_ENEMY(20700, 530, 130, -1, 1);

        MAKE_ENEMY(22200, 370, -20, 0, 1);
        MAKE_ENEMY(22200, 70, -20, 0, 1);
        MAKE_ENEMY(22500, 130, -30, 0, 1);
        MAKE_ENEMY(22500, 310, -30, 0, 1);
        MAKE_ENEMY(22700, 190, -40, 0, 1);
        MAKE_ENEMY(22700, 250, -40, 0, 1);

        enemies_to_appear_.push_back(
            std::make_pair(std::chrono::milliseconds(24000),
                           std::make_shared<ShrapnelEnemy>(200, -32)));

        MAKE_ENEMY(25100, 480, 0, -1, 1);
        MAKE_ENEMY(25200, 510, 40, -1, 1);
        MAKE_ENEMY(25300, 500, 80, -1, 1);
        MAKE_ENEMY(25500, 490, 120, -1, 1);
        MAKE_ENEMY(26000, 530, 20, -1, 1);
        MAKE_ENEMY(26200, 500, 60, -1, 1);
        MAKE_ENEMY(26500, 510, 100, -1, 1);
        MAKE_ENEMY(26700, 500, 110, -1, 1);

        MAKE_ENEMY(27100, 480, 0, -1, 1);
        MAKE_ENEMY(27200, 510, 40, -1, 1);
        MAKE_ENEMY(27300, 500, 80, -1, 1);
        MAKE_ENEMY(27500, 490, 120, -1, 1);
        MAKE_ENEMY(28000, 530, 20, -1, 1);
        MAKE_ENEMY(28200, 500, 60, -1, 1);
        MAKE_ENEMY(28500, 510, 100, -1, 1);
        MAKE_ENEMY(28700, 500, 110, -1, 1);

        MAKE_ENEMY(30200, -30, 60, 1, 1);
        MAKE_ENEMY(30200, 480, 60, -1, 1);
        MAKE_ENEMY(30500, -20, 100, 1, 1);
        MAKE_ENEMY(30500, 490, 100, -1, 1);
        MAKE_ENEMY(30700, -50, 130, 1, 1);
        MAKE_ENEMY(30700, 530, 130, -1, 1);

        MAKE_ENEMY(32200, 370, -20, 0, 1);
        MAKE_ENEMY(32200, 70, -20, 0, 1);
        MAKE_ENEMY(32500, 130, -30, 0, 1);
        MAKE_ENEMY(32500, 310, -30, 0, 1);
        MAKE_ENEMY(32700, 190, -40, 0, 1);
        MAKE_ENEMY(32700, 250, -40, 0, 1);

        MAKE_ENEMY(33200, -30, 60, 1, 1);
        MAKE_ENEMY(33200, 480, 60, -1, 1);
        MAKE_ENEMY(33500, -20, 100, 1, 1);
        MAKE_ENEMY(33500, 490, 100, -1, 1);
        MAKE_ENEMY(33700, -50, 130, 1, 1);
        MAKE_ENEMY(33700, 530, 130, -1, 1);

        MAKE_ENEMY(36100, 480, 0, -1, 1);
        MAKE_ENEMY(36200, 510, 40, -1, 1);
        MAKE_ENEMY(36300, 500, 80, -1, 1);
        MAKE_ENEMY(36500, 490, 120, -1, 1);
        MAKE_ENEMY(37000, 530, 20, -1, 1);
        MAKE_ENEMY(37200, 500, 60, -1, 1);
        MAKE_ENEMY(37500, 510, 100, -1, 1);
        MAKE_ENEMY(37700, 500, 110, -1, 1);

        MAKE_ENEMY(40100, 50, -20, 0, 1);
        MAKE_ENEMY(40200, 100, -30, 0, 1);
        MAKE_ENEMY(40300, 150, -40, 0, 1);
        MAKE_ENEMY(40500, 200, -50, 0, 1);
        MAKE_ENEMY(41000, 250, -50, 0, 1);
        MAKE_ENEMY(41200, 300, -40, 0, 1);
        MAKE_ENEMY(41500, 350, -30, 0, 1);
        MAKE_ENEMY(41700, 400, -20, 0, 1);

        enemies_to_appear_.push_back(std::make_pair(
            std::chrono::milliseconds(45000), std::make_shared<Warning>()));

        enemies_to_appear_.push_back(std::make_pair(
            // std::chrono::milliseconds(8000),
            std::chrono::milliseconds(50000),
            std::make_shared<Boss>(40, -300)));
}

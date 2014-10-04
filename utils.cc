#include "utils.h"

#include <algorithm>
#include <stdlib.h>

#include "game-state.h"

void createMedals(const Vector<float> &position, float factor)
{
        float dist =
            Vector<float>::distance(position, GameState::ship->position());
        int distance =
            (500 - static_cast<int>(std::min(400.0f, dist * factor))) / 33;
        for (int i = 0; i < distance; i++)
                GameState::medals.emplace_back(
                    position.x + rand_between(0, 32),
                    position.y + rand_between(0, 32));
}

/**
 * p - returns true or false with a given probability
 */
int p(int percent)
{
        return ((rand() % 100) + 1 <= percent);
}

/**
 * rand_between - returns a random number in [a,b)
 */
int rand_between(int a, int b)
{
        return rand() % (b - a) + a;
}

double gaussrand()
{
        static double V1, V2, S;
        static int phase = 0;
        double X;

        if (phase == 0) {
                do {
                        double U1 = (double)rand() / RAND_MAX;
                        double U2 = (double)rand() / RAND_MAX;

                        V1 = 2 * U1 - 1;
                        V2 = 2 * U2 - 1;
                        S = V1 * V1 + V2 * V2;
                } while (S >= 1 || S == 0);

                X = V1 * sqrt(-2 * log(S) / S);
        } else
                X = V2 * sqrt(-2 * log(S) / S);

        phase = 1 - phase;

        return X;
}

/**
 * rand_normal - returns a random number following a normal distribution
 */
int rand_normal(int mean, int stddev)
{
        return gaussrand() * stddev + mean;
}

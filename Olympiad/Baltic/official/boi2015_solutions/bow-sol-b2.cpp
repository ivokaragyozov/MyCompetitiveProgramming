/* Baltic Olympiad in Informatics 2015
 * Problem: BOW/Bowling
 * Half of model solution (without logic for last frame, passes only one subtask)
 * Author: Karol Pokorski
 */

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long int LL;

const int MAXN = 10;
const int MAXSEQ = 21;
const int maxFrameScore[11] = {0, 10, 30, 60, 90, 120, 150, 180, 210, 240, 300};
const int MAXSCORE = 300;

int seqScore[MAXN];
LL dp[MAXN][MAXSCORE+1][3][2];
char seqMoves[MAXSEQ+1];

int main() {
    int numQueries;

    scanf("%d", &numQueries);

    while (numQueries--) {
        int numFrames;

        scanf("%d", &numFrames);
        scanf("%s", seqMoves);
        for (int i = 0; i < numFrames; i++)
            scanf("%d", &seqScore[i]);

        for (int frame = 0; frame < numFrames; frame++)
            for (int score = 0; score <= MAXSCORE; score++)
                for (int bonus1 = 0; bonus1 <= 2; bonus1++)
                    for (int bonus2 = 0; bonus2 <= 1; bonus2++)
                        dp[frame][score][bonus1][bonus2] = 0LL;

        dp[0][0][0][0] = 1LL;

        // first n-1 frames
        for (int frame = 0; frame < numFrames-1; frame++) {
            char firstMove = seqMoves[2*frame], secondMove = seqMoves[2*frame+1];
            int prev0Score = seqScore[frame];
            int prev1Score = (frame > 0) ? seqScore[frame-1] : -1;
            int prev2Score = (frame > 1) ? seqScore[frame-2] : -1;

            for (int score = 0; score <= maxFrameScore[frame]; score++)
                for (int bonus1 = 0; bonus1 <= 2; bonus1++)
                    for (int bonus2 = 0; bonus2 <= 1; bonus2++) {
                        if (dp[frame][score][bonus1][bonus2] == 0LL) continue;

                        for (int move1 = 0; move1 <= 10; move1++) {
                            if ((firstMove >= '0') && (firstMove <= '9') && (move1 != firstMove-'0')) continue;
                            if ((firstMove == 'x') && (move1 != 10)) continue;
                            if ((secondMove == '/') && (move1 == 10)) continue;

                            for (int move2 = 0; move1+move2 <= 10; move2++) {
                                if ((secondMove >= '0') && (secondMove <= '9') && (move2 != secondMove-'0')) continue;
                                if ((secondMove == '/') && (move1+move2 != 10)) continue;
                                if ((secondMove == '-') && (move1 != 10)) continue;
                                if ((move1+move2 == 10) && (secondMove >= '0') && (secondMove <= '9')) continue;

                                int prev1Bonus = 0, prev2Bonus = 0;
                                if (bonus2 == 1) prev1Bonus = move1;
                                if (bonus1 == 1) prev2Bonus = move1;
                                if (bonus1 == 2) prev2Bonus = move1+move2;

                                int nowScore = score + prev1Bonus + prev2Bonus + (move1+move2);
                                int nowPrev1Score = nowScore - (move1+move2);

                                int newBonus1, newBonus2;

                                if (move1 == 10) { newBonus1 = 2; newBonus2 = max(bonus1-1, 0); }
                                else if (move1 + move2 == 10) { newBonus1 = 1; newBonus2 = 0; }
                                else { newBonus1 = 0; newBonus2 = 0; }

                                if (bonus2 == 1) {
                                    int nowPrev2Score = nowPrev1Score - (move1+move2) - 10;
                                    if ((prev2Score != -1) && (nowPrev2Score != prev2Score)) {
                                        continue;
                                    }
                                }
                                if ((bonus1 == 1) || ((bonus1 == 2) && (move1 != 10))) {
                                    if ((prev1Score != -1) && (nowPrev1Score != prev1Score)) {
                                        continue;
                                    }
                                }
                                if (move1+move2 != 10) {
                                    if ((prev0Score != -1) && (nowScore != prev0Score)) {
                                        continue;
                                    }
                                }

                                dp[frame+1][nowScore][newBonus1][newBonus2] =
                                    (dp[frame+1][nowScore][newBonus1][newBonus2] + dp[frame][score][bonus1][bonus2]);
                            }
                        }
                    }
        }

        // last frame
        LL result = 0LL;

        for (int score = 0; score <= MAXSCORE; score++)
            for (int bonus1 = 0; bonus1 <= 2; bonus1++)
                for (int bonus2 = 0; bonus2 <= 1; bonus2++) {
                    if (dp[numFrames-1][score][bonus1][bonus2] == 0LL) continue;
                    result = (result + dp[numFrames-1][score][bonus1][bonus2]);
                }

        printf("%Ld\n", result);
    }

    return 0;
}

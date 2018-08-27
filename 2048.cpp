#ifndef _G2048_
#define _G2048_
#include "panel.h"

class G2048{
    public:
        G2048();
        ~G2048();

    private:
        Pane pane1;
        Pane pane2;
        int score;

    private:
        void initPane();
        void disPane(Pane&);
        void copyP1P2();
        bool isEmpty(int, int);
        int generateNum(int, int);
        bool isGameOver();
        void rotate90(Pane&, Pane&);
        void rotate_90(Pane&, Pane&);
        void rotate180(Pane&, Pane&);
        void rotate_180(Pane&, Pane&);
        int getScore(Pane&);
        void resetScore();
        void setNum(Pane&, int, int, int);
        void handleOps(Direction&);
    
    private:
        void coreAlgorithm(Pane&);

    public:
        void showPane(Pane&);
        void run();
};

#endif
#include <iostream>
#include <math.h>

#include "progress.h"

float old_progress = 0.0;

int lead_value(float current, float total) {
    /*
    if return -1, no need to update value, else int progress value
    */

    float progress = current / total;
    progress = round(progress * 100) / 100;

    if (old_progress != progress) {
        old_progress = progress;

        return int(progress * 100);
    }
    else
    {
        return -1;
    }
}

void display_progress(int progress, string text = "") {
    int tmp_progress = progress;

    cout << text << " " << "[";
    int pos = progress / 2;
    for (int i = 0; i < 100 / 2; ++i) {
        if (i < pos) {
            cout << "=";
        }
        else if (i == pos) {
            cout << ">";
        }
        else {
            cout << " ";
        }
    }

    cout << "] " << progress << " %\r";
    cout.flush();
}

void progress(float current, float total, string text = "") {
    int progress = lead_value(current, total);

    if (progress != -1) {
        display_progress(progress, text);
    }

}

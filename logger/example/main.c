#include "logger.h"

int main(int argc, char** argv) {
    Logger_initLog("program.log");

    Logger_log(LOG, "Basic log");
    Logger_log(ERR, "Error log");
    Logger_log(WAR, "Warning log");
    Logger_log(SUC, "Success log");

    Logger_log(LOG, "Log with integers: %i, and floats: %.2f", 3, 2.1f);

    Logger_logFast("Fast log 1");
    Logger_logFast("Fast log 2");
    Logger_logFast("Fast log 3");

    int veci[] = { 
        1, 2, 3,
        4, 5, 6 
    };

    Logger_logMatrix(LOG, veci, sizeof(int), 2, 3, false, "i", "Matrix in row major");
    Logger_logMatrix(LOG, veci, sizeof(int), 2, 3, true, "i", "Matrix in column major");

    float vec[] = {
        1.0f, 0.1f, 5.0f,
        2.0f, 0.2f, 4.0f,
        3.0f, 0.3f, 3.0f,
    };

    Logger_logMatrix(LOG, vec, sizeof(float), 3, 3, false, "f", "Float matrix in row major");
    Logger_logMatrix(LOG, vec, sizeof(float), 1, 9, false, "f", "Float matrix in as vector");

    Logger_taredownLog();
}

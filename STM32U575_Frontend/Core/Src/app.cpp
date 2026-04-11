#include "app.h"
#include "AppOrchestrator.h"

extern I2C_HandleTypeDef hi2c2;

AppOrchestrator orchestrator(&hi2c2);

void app_main(void) {
    orchestrator.init();

    while(1) {
        orchestrator.run();
    }
}
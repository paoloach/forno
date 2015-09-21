#include <xc.h>
#include "RS232.h"
#include "unity.h"

void runTest(void);

void main() {
    initRS232();
    runTest();
    UnityPrint("Tests Finished\n");
    while(1);
}

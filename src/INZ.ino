
#include "Manager.h"
#include <stdlib.h>
Manager *mngr;
static const char *TAG = "Main File";
void setup()
{
  Serial.begin(115200);
  mngr = new Manager(32, 3000);
}

void loop()
{

  mngr->buttonListen();
}

#include "cell.h"
#include "decorator.h"

Decorator::Decorator( Cell *component )
  : component{component} {}

Decorator::~Decorator() { delete component; }

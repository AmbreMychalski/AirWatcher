using namespace std;
#include "Measure.h"
#include <iomanip>
#include <iostream>

ostream &operator<<(ostream &stream, const Measure &measure)
{
  stream << "Type: ";
  stream << setiosflags(ios::fixed) << setw(5) << left << measure.attribute.getId();
  stream << " | Valeur: ";
  stream << setiosflags(ios::fixed) << setw(6) << left << setprecision(4) << measure.value;
  stream << " ";
  stream << setiosflags(ios::fixed) << setw(5) << left << measure.attribute.getUnit();
  stream << " | Date: ";
  stream << measure.date;

  return stream;
}
#include <stdio.h>
#include <stdint.h>

struct Sensors {
  uint8_t pir;
  const char *loc;
  uint8_t count;
};

Sensors pir[]  {
  {6, "sensor1", 0},
  {7, "sensor2", 0},
  {8, "sensor3", 0}
};

class myclass{
  public:
    template <size_t N>
    myclass(Sensors (&sensors)[N])
      : sensors(sensors), length(N) {}

  void printLocations() const {
    for (size_t i = 0; i < length; ++i)
      printf(sensors[i].loc);
  }

  private:
    Sensors *sensors;
    size_t length;
};

myclass mySensors = pir;

int main() {
  mySensors.printLocations();
  return 0;
}
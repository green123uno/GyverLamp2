// -------------- ВНУТР. КОНСТАНТЫ ---------------
#define GL_ADC_NONE 1
#define GL_ADC_BRI 2
#define GL_ADC_MIC 3
#define GL_ADC_BOTH 4
#define GL_TYPE_STRIP 1
#define GL_TYPE_ZIG 2
#define GL_TYPE_PARAL 3
#define GL_MUS_NONE 1
#define GL_MUS_VOL 2
#define GL_MUS_LOW 3
#define GL_MUS_HIGH 4
#define GL_REACT_BRI 1
#define GL_REACT_SCL 2
#define GL_REACT_LEN 3
#define GL_SLAVE 0
#define GL_MASTER 1
#define MAX_PRESETS 25      // макс количество режимов

// ------------------- МАКРО --------------------
#ifdef DEBUG_SERIAL
#define DEBUGLN(x) Serial.println(x)
#define DEBUG(x) Serial.print(x)
#else
#define DEBUGLN(x)
#define DEBUG(x)
#endif

#define FOR_i(x,y)  for (int i = (x); i < (y); i++)
#define FOR_j(x,y)  for (int j = (x); j < (y); j++)
#define CUR_PRES preset[cfg.curPreset]

byte scaleFF(byte x, byte b) {
  return ((uint16_t)x * (b + 1)) >> 8;
}
int mapFF(byte x, byte min, byte max) {
  return (((max - min) * x + (min << 8) + 1) >> 8);
}

const char OTAhost[] = "http://ota.alexgyver.ru/GL2_latest.bin";

const char *NTPservers[] = {
  "pool.ntp.org",
  "europe.pool.ntp.org",
  "ntp1.stratum2.ru",
  "ntp2.stratum2.ru",
  "ntp.msk-ix.ru",
};

#define CFG_SIZE 13
struct Config {
  byte GMT = 3;           // часовой пояс +13
  byte NTP = 1;           // 1..5 ВЫЧЕСТЬ 1
  byte bright = 100;      // яркость
  byte adcMode = 1;       // режим ацп (1 выкл, 2 ярк, 3 муз)
  byte minBright = 0;     // мин яркость
  byte maxBright = 255;   // макс яркость
  byte rotation = 0;      // смена режимов: 0 ручная, 1 авто
  byte rotRnd = 0;        // тип автосмены: 0 в порядке, 1 рандом
  byte rotPeriod = 1;     // период смены (1,5..)
  byte deviceType = 1;    // 1 лента, 2 зигзаг, 3 параллел
  byte maxCur = 5;        // макс ток (мА/100)
  byte workFrom = 0;      // часы работы (0,1.. 23)
  byte workTo = 0;        // часы работы (0,1.. 23)

  int16_t length = 100;       // длина ленты
  int16_t width = 1;          // ширина матрицы

  byte state = 1;         // состояние 0 выкл, 1 вкл
  byte group = 1;         // группа девайса (1-10)
  byte role = 0;          // 0 slave, 1 master
  byte WiFimode = 0;      // 0 AP, 1 local
  byte presetAmount = 1;  // количество режимов
  byte manualOff = 0;     // выключали вручную?
  int8_t curPreset = 0;   // текущий режим
  int16_t minLight = 0;       // мин освещённость
  int16_t maxLight = 1023;    // макс освещённость
  char ssid[32];          // логин wifi
  char pass[32];          // пароль wifi
};

#define PRES_SIZE 13
struct Preset {
  byte effect = 1;        // тип эффекта (1,2...) ВЫЧЕСТЬ 1
  byte fadeBright = 0;    // флаг на свою яркость (0/1)
  byte bright = 100;      // своя яркость (0.. 255)
  byte soundMode = 1;     // тип звука (1,2...) ВЫЧЕСТЬ 1
  byte soundReact = 1;    // реакция на звук (1,2...) ВЫЧЕСТЬ 1
  byte min = 0;           // мин сигнал светомузыки (0.. 255)
  byte max = 0;           // макс сигнал светомузыки (0.. 255)
  byte speed = 10;        // скорость (0.. 255)
  byte palette = 1;       // палитра (1,2...) ВЫЧЕСТЬ 1
  byte scale = 1;         // масштаб (0.. 255)
  byte fromCenter = 0;    // эффект из центра (0/1)
  byte color = 0;         // цвет (0.. 255)
  byte rnd = 0;           // случайный (0/1)
};

struct Dawn {
  byte state[7] = {0, 0, 0, 0, 0, 0, 0};  // (1/0)
  byte hour[7] = {0, 0, 0, 0, 0, 0, 0};   // (0.. 59)
  byte minute[7] = {0, 0, 0, 0, 0, 0, 0}; // (0.. 59)
  byte bright = 100;      // (0.. 255)
  byte time = 1;          // (5,10,15,20..)
};
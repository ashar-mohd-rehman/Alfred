
#include <Wire.h>
#include <U8g2lib.h>
#include <TinyGPSPlus.h>
#include <math.h>

// ---------- Pins ----------
#define GPS_RX_PIN   D7   // XIAO RX <- GPS TX
#define GPS_TX_PIN   D6   // XIAO TX -> GPS RX
#define GPS_BAUD     9600

// ---------- Timezone ----------
// GPS time is UTC. Set your local offset in hours (India = 5.5)
#define TZ_OFFSET_HOURS  5.5f

// ---------- Objects ----------
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
TinyGPSPlus gps;
HardwareSerial gpsSerial(1);

// ---------- Pet state machine ----------
enum PetState { IDLE, BLINK, VOMIT, DIZZY, RECOVER, CLOCK };
PetState state = IDLE;
unsigned long stateStartMs = 0;

// Idle blinking
unsigned long nextBlinkMs = 0;
bool blinkOnce = false;

// Shake detection (via GPS speed spikes, not an IMU)
double lastSpeedKmph = 0;
unsigned long lastSpeedSampleMs = 0;
const double SHAKE_SPEED_JUMP_KMPH = 15.0;  // sudden jump = shake
const unsigned long SHAKE_WINDOW_MS = 700;  // how fast the jump must happen

// State durations (ms)
const unsigned long VOMIT_MS    = 1400;
const unsigned long DIZZY_MS    = 2600;
const unsigned long RECOVER_MS  = 1500;
const unsigned long CLOCK_MS    = 4000;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  u8g2.begin();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);

  randomSeed(analogRead(0));
  scheduleNextBlink();
  stateStartMs = millis();
}

void loop() {
  readGPS();
  updateShakeDetection();
  updateStateMachine();
  render();
}

// ---------------------------------------------------------
// GPS reading
// ---------------------------------------------------------
void readGPS() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }
}

// ---------------------------------------------------------
// Shake detection — watches for an unrealistic speed spike
// ---------------------------------------------------------
void updateShakeDetection() {
  if (!gps.speed.isUpdated()) return;

  double currentSpeed = gps.speed.kmph();
  unsigned long now = millis();

  if (now - lastSpeedSampleMs <= SHAKE_WINDOW_MS) {
    double jump = currentSpeed - lastSpeedKmph;
    if (jump > SHAKE_SPEED_JUMP_KMPH && state == IDLE) {
      triggerShake();
    }
  }

  lastSpeedKmph = currentSpeed;
  lastSpeedSampleMs = now;
}

void triggerShake() {
  state = VOMIT;
  stateStartMs = millis();
}

// ---------------------------------------------------------
// State machine
// ---------------------------------------------------------
void updateStateMachine() {
  unsigned long elapsed = millis() - stateStartMs;

  switch (state) {
    case IDLE:
      // Random blink
      if (millis() >= nextBlinkMs) {
        blinkOnce = true;
        nextBlinkMs = millis() + 180; // blink duration
      }
      if (blinkOnce && millis() >= nextBlinkMs) {
        blinkOnce = false;
        scheduleNextBlink();
      }
      break;

    case VOMIT:
      if (elapsed >= VOMIT_MS) {
        state = DIZZY;
        stateStartMs = millis();
      }
      break;

    case DIZZY:
      if (elapsed >= DIZZY_MS) {
        state = RECOVER;
        stateStartMs = millis();
      }
      break;

    case RECOVER:
      if (elapsed >= RECOVER_MS) {
        state = CLOCK;
        stateStartMs = millis();
      }
      break;

    case CLOCK:
      if (elapsed >= CLOCK_MS) {
        state = IDLE;
        stateStartMs = millis();
        scheduleNextBlink();
      }
      break;

    default:
      break;
  }
}

void scheduleNextBlink() {
  nextBlinkMs = millis() + random(2500, 6000);
}

// ---------------------------------------------------------
// Rendering
// ---------------------------------------------------------
void render() {
  u8g2.clearBuffer();

  switch (state) {
    case IDLE:
      if (blinkOnce) drawBlinkFace();
      else            drawIdleFace();
      break;
    case VOMIT:
      drawVomitFace();
      break;
    case DIZZY:
      drawDizzyFace();
      break;
    case RECOVER:
      drawRecoverFace();
      break;
    case CLOCK:
      drawClockFace();
      break;
  }

  u8g2.sendBuffer();
}

// ---------- IDLE ----------
void drawIdleFace() {
  u8g2.drawRBox(30, 16, 16, 24, 7);
  u8g2.drawRBox(82, 16, 16, 24, 7);
  // small smile
  u8g2.drawFilledEllipse(62, 30, 6, 4, U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_LOWER_RIGHT);
  u8g2.setDrawColor(0);
  u8g2.drawBox(56, 30, 12, 4); // trim to just the curve line
  u8g2.setDrawColor(1);
}

// ---------- BLINK ----------
void drawBlinkFace() {
  // eyebrow-arch eyes (closed, happy)
  u8g2.drawCircle(38, 30, 10, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT);
  u8g2.drawCircle(90, 30, 10, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT);
  // smile
  u8g2.drawCircle(64, 30, 10, U8G2_DRAW_LOWER_RIGHT | U8G2_DRAW_LOWER_LEFT);
}

// ---------- VOMIT ----------
void drawVomitFace() {
  // eyebrows
  u8g2.drawLine(26, 12, 34, 20);
  u8g2.drawLine(34, 20, 42, 14);
  u8g2.drawLine(86, 14, 94, 20);
  u8g2.drawLine(94, 20, 102, 12);

  // chevron eyes ">" "<"
  u8g2.drawLine(24, 26, 40, 34); u8g2.drawLine(40, 34, 24, 42);
  u8g2.drawLine(104, 26, 88, 34); u8g2.drawLine(88, 34, 104, 42);

  // mouth cap (peeking open mouth)
  u8g2.drawFilledEllipse(64, 40, 16, 8, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT);

  // straight solid vomit stream
  u8g2.drawBox(54, 40, 20, 24);
}

// ---------- DIZZY ----------
void drawSpiralEye(int cx, int cy) {
  float angle = 0;
  float radius = 1.0;
  for (int i = 0; i < 46; i++) {
    int x = cx + (int)(radius * cos(angle));
    int y = cy + (int)(radius * sin(angle));
    u8g2.drawPixel(x, y);
    u8g2.drawPixel(x + 1, y);
    u8g2.drawPixel(x, y + 1);
    angle += 0.55;
    radius += 0.22;
  }
}

void drawDizzyFace() {
  drawSpiralEye(41, 26);
  drawSpiralEye(87, 26);
  // wavy mouth
  u8g2.drawLine(50, 48, 56, 52);
  u8g2.drawLine(56, 52, 62, 48);
  u8g2.drawLine(62, 48, 68, 52);
  u8g2.drawLine(68, 52, 74, 48);
}

// ---------- RECOVER ----------
void drawRecoverFace() {
  u8g2.drawRBox(30, 16, 16, 24, 7);
  u8g2.drawRBox(82, 16, 16, 24, 7);
  // small worried frown
  u8g2.drawCircle(62, 40, 6, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT);
}

// ---------- CLOCK ----------
void drawClockFace() {
  char timeBuf[6]  = "--:--";
  char dayBuf[10]  = "";

  if (gps.time.isValid() && gps.date.isValid()) {
    // apply timezone offset
    double totalHours = gps.time.hour() + gps.time.minute() / 60.0 + TZ_OFFSET_HOURS;
    int dayShift = 0;
    while (totalHours >= 24.0) { totalHours -= 24.0; dayShift++; }
    while (totalHours < 0.0)   { totalHours += 24.0; dayShift--; }

    int hh = (int)totalHours;
    int mm = gps.time.minute();
    snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d", hh, mm);

    // weekday from GPS date (Zeller-ish via day-of-week calc)
    int y = gps.date.year();
    int m = gps.date.month();
    int d = gps.date.day() + dayShift;
    static const char* days[] = {"SUNDAY","MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY"};
    // Sakamoto's algorithm
    static const int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    if (m < 3) y -= 1;
    int dow = (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
    strncpy(dayBuf, days[dow], sizeof(dayBuf));
  } else {
    strncpy(timeBuf, "--:--", sizeof(timeBuf));
    strncpy(dayBuf, "NO FIX", sizeof(dayBuf));
  }

  u8g2.setFont(u8g2_font_logisoso20_tf);
  int w = u8g2.getStrWidth(timeBuf);
  u8g2.drawStr((128 - w) / 2, 32, timeBuf);

  u8g2.setFont(u8g2_font_6x12_tf);
  int w2 = u8g2.getStrWidth(dayBuf);
  u8g2.drawStr((128 - w2) / 2, 52, dayBuf);
}

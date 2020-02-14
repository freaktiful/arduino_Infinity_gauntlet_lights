#include <Adafruit_NeoPixel.h>

int boton = 3;
long tiempo_anterior;
long diferencia;
bool flagLuces = false;

bool encendido = false;

#define PIN 12
#define NUMPIXELS 1

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);

String states[] = {"apagado", "encendido", "palpitante"};
byte state;

void setup() {
  Serial.begin(9600);

  pixel.begin(); // This initializes the NeoPixel library.
  pixel.show(); // initialize all pixels to "off"

  pinMode(boton, INPUT);
  attachInterrupt(digitalPinToInterrupt(boton), pulsacion, FALLING);

  state = 0;
}

void loop() {
  switch (state) {
    case 0:
      if (encendido) {
        apagar();
      }
      break;
    case 1:
      if (!encendido) {
        encender();
      }
      break;
    case 2:
      if (encendido) {
        apagar();
      } else {
        encender();
      }
      break;
  }
}

void pulsacion() {
  Serial.println("pulsacion");
  diferencia = millis() - tiempo_anterior;
  tiempo_anterior = millis();

  if (diferencia > 200) {
    state = ++state % 3;
    Serial.println(state);
  }
}

void encender() {
  uint16_t i, j;

  for (j = 0; j < 150 ; j++) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixel.setPixelColor(i, pixel.Color(0, 0, 0, 150));
    }
    pixel.setBrightness(j);
    pixel.show();
    delay(20);
  }
  encendido = true;
}

void apagar() {
  uint16_t i, j;

  for (j = 150; j > 0; j--) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixel.setPixelColor(i, pixel.Color(0, 0, 0, 150));
    }
    pixel.setBrightness(j);
    pixel.show();
    delay(20);
  }
  encendido = false;
}

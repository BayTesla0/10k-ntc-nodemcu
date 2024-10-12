#define SERIES_RESISTOR 10000  // Sabit 10K direnç
#define NOMINAL_RESISTANCE 10000  // NTC'nin 25°C'deki nominal direnci (10K)
#define NOMINAL_TEMPERATURE 25   // Nominal sıcaklık (25°C)
#define BETA_COEFFICIENT 3950    // NTC için Beta katsayısı
#define ADC_MAX 1023  // ADC'nin maksimum değeri (1023)

void setup() {
  Serial.begin(9600);  // Seri iletişimi başlat
}

void loop() {
  // A0 pininden voltajı oku
  int adcValue = analogRead(A0);

  // Okunan voltajı gerilime çevir
  float voltage = adcValue * (3.3 / ADC_MAX);  // NodeMCU'da referans gerilimi 3.3V'dur.

  // Termistörün direncini hesapla
  float resistance = (3.3 / voltage + 1) * SERIES_RESISTOR;

  // Steinhart-Hart denklemi ile sıcaklığı hesapla
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;  // R / Ro
  steinhart = log(steinhart);                   // ln(R / Ro)
  steinhart /= BETA_COEFFICIENT;                // 1/B * ln(R / Ro)
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);  // + (1/To)
  steinhart = 1.0 / steinhart;                  // T = 1 / y
  steinhart -= 273.15;                          // Kelvin'den Celsius'a çevir

  // Seri monitöre sıcaklık değerini yazdır
  Serial.print("Sıcaklık: ");
  Serial.print(steinhart);
  Serial.println(" C");

  // Termistörün direncini de yazdır
  Serial.print("Direnç: ");
  Serial.print(resistance);
  Serial.println(" Ohm");

  delay(2000);  // 2 saniye bekle
}

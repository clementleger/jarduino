#define WATERING_DURATION       (30 * 1000)
#define WATER_LOW_LEVEL         30
#define MOISTURE_LEVEL          1020

int sr04_trig_pin = 5;
int sr04_echo_pin = 6;
int pump_pin = 4;
int soil_pin = A0;

void setup() {
        pinMode(pump_pin, OUTPUT);
        digitalWrite(pump_pin, 1);
        pinMode(sr04_trig_pin, OUTPUT);
        pinMode(sr04_echo_pin, INPUT);
        pinMode(soil_pin, INPUT);
        Serial.begin(9600);
}

int get_water_level()
{
        long cm, echo_read;

        digitalWrite(sr04_trig_pin, HIGH); 
        delayMicroseconds(10); 
        digitalWrite(sr04_trig_pin, LOW); 
        echo_read = pulseIn(sr04_echo_pin, HIGH); 
        cm = echo_read / 58; 
        Serial.print("Distance: "); 
        Serial.println(cm); 

        return cm;
}

void signal_water_low()
{
        Serial.println("Low level of water !");
}

void
run_pump()
{
        unsigned long time = millis();

        digitalWrite(pump_pin, 0);

        while (millis() - time < WATERING_DURATION) {
                if (get_water_level() > WATER_LOW_LEVEL) {
                        signal_water_low();
                        break;
                }
        }

        digitalWrite(pump_pin, 1);
        
        
}

void check_plants()
{
        int moisture = analogRead(soil_pin);
        Serial.print("Moisture: "); 
        Serial.println(moisture); 
        if (moisture > MOISTURE_LEVEL) {
                 Serial.println("Moisture too low, watering"); 
                run_pump();
        }
}

void loop()
{
        check_plants();

        delay(30000);
}

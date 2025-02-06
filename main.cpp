void speed_sensor();
void speed_ref_rise();

PwmOut speed(D8);
InterruptIn sensor(D5);
InterruptIn ref_gbf(D3);
Timer counter;
Timer counter_ref;
Timer watchdog_timer_sensor;
Timer watchdog_timer_ref;

volatile float sensor_period = 1.0f;
volatile float ref_period = 0.0f;
volatile float delta_t = 0.0f;
volatile bool sensor_signal_received = false;

float delay = 0.02;

float kp = 0.6f;
float tau = 3;  //temps de réponse en secondes
float ki = delay / tau;

float current_error = 0.0f;
float last_error = 0.0f;
float integral = 0.0f;

// Correcteur de phase
float erreur_phase = 0.0f;
float K_phi = 0.45f;
float correction_phase = 0.0f;

float maxcorrphi = 0.02;

float puissance = 0.2;

float sensor_frequency = 0.0f;




int main()
{
    float ref_freq = 0.0f;
    counter.start();
    counter_ref.start();
    watchdog_timer_sensor.start();

    sensor.rise(&speed_sensor);
    ref_gbf.rise(&speed_ref_rise);

    speed.period(0.0005f); // fréquence PWM
    speed.write(0.0f);    // Rapport cyclique

    while (1)
    {
        if (sensor_signal_received)
        {
            sensor_frequency = 1.0 / (sensor_period * 1e-6); // en tr/min

            if (ref_period != 0.0f)
            {
                ref_freq = 1.0f / (ref_period * 1e-6);
            }
            else ref_freq = 0;

            current_error = (ref_freq - sensor_frequency) / 100;

            integral += ki * current_error;

            if (integral > 1) integral = 1.f;
            if (integral < -1) integral = -1;

            // Correction de phase
            if (delta_t < ref_period / 2)
                erreur_phase = delta_t / ref_period;    // accelere
            else
                erreur_phase = (delta_t - ref_period) / ref_period;  // ralentit

            correction_phase = K_phi * erreur_phase;

            if (correction_phase > maxcorrphi)
                correction_phase = maxcorrphi;
            else if (correction_phase < -maxcorrphi)
                correction_phase = -maxcorrphi;

            puissance = kp * current_error + integral + correction_phase;

            if (puissance > 0.9) puissance = 0.9;
            if (puissance < 0.1) puissance = 0.1;

            speed.write(puissance);


            // 2eme watchdog si on debranche le gbf
            if (counter_ref.read_us() > 1e6)  
                speed = 0.0f;


        }
        else
        {
            if (watchdog_timer_sensor.read_us() > 1 * 1e6)
            {
                speed.write(0.5f);
            }
        }

        wait_ms(delay * 1000);
    }
}



void speed_sensor()
{
    sensor_period = counter.read_us();
    counter.reset();

    delta_t = counter_ref.read_us(); // correction de phase

    sensor_signal_received = true;
    watchdog_timer_sensor.reset();
}

void speed_ref_rise()
{
    ref_period = counter_ref.read_us();
    counter_ref.reset();
    delta_t = 0;
}
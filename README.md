# **Digital Control of a DC Motor**  

## **Project Overview**  
This project focuses on the frequency and phase control of a DC motor using an ARM Cortex-based microcontroller, specifically the **NUCLEO-F411RE** from STMicroelectronics. The control system is implemented using the **Keil Studio** development platform with **C++** programming.  

The project consists of:  
- **Electronic circuit design** for motor control.  
- **Software development** for digital feedback control.  
- **Implementation of a PI controller** to regulate motor speed and phase.  

## **System Components**  
The system is divided into multiple functional blocks:  

1. **Signal Transmission and Amplification**  
   - Uses an optocoupler for isolation.  
   - Transistors for signal amplification.  

2. **Motor Block**  
   - DC motor connected with a freewheeling diode.  
   - Smoothing capacitor to maintain a stable voltage.  

3. **Detection Block**  
   - Optical sensor to measure motor speed.  
   - Schmitt trigger for signal processing.  

## **Hardware & Software Used**  

### **Hardware**  
- **NUCLEO-F411RE** (STM32-based development board).  
- **DC Motor** with encoder.  
- **Optocoupler** for signal isolation.  
- **Power transistors & resistors** for signal conditioning.  
- **Optical sensor** for speed measurement.  

### **Software**  
- **Keil Studio** for embedded programming.  
- **Eagle** for PCB design and routing.  

## **Control Strategy**  

- **PWM (Pulse Width Modulation)** for motor speed control.  
- **PI Controller (Proportional-Integral)** for error correction.  
- **Phase correction** for precise synchronization.  
- **Interrupt-based signal processing** for accurate speed measurements.  

## **How to Use**  

1. **Compile and Flash the Code**  
   - Use Keil Studio to compile and upload the firmware.  

2. **Connect the Circuit**  
   - Ensure proper wiring between the NUCLEO board and the motor driver circuit.  

3. **Test and Debug**  
   - Use a function generator to simulate input signals.  
   - Monitor sensor outputs using an oscilloscope.  

4. **Adjust Parameters**  
   - Modify **KP, KI** in the PI controller for optimal response.  

## **Future Improvements**  
- Implement a **PID controller** for better dynamic response.  
- Enhance speed measurement with **Kalman filtering**.  
- Add a **GUI** for real-time monitoring.  

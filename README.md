# 🧲 Magnetic Crawler Inspection Robot with Automated Crack Detection

## 📌 Project Overview

The **Magnetic Crawler Inspection Robot** is a crawler-type robotic system designed to inspect **large ferromagnetic metal surfaces** such as **ship hulls, industrial boilers, storage tanks, and steel structures**.  
The robot uses **magnetic adhesion** to climb vertically and move on curved metal surfaces while performing **automated crack detection** using **OpenCV-based computer vision**.

This project focuses on improving **industrial safety**, **inspection accuracy**, and **automation** by reducing the need for manual inspection in hazardous environments.

---

## 📸 Project Images

### Robot Prototype
![Robot Prototype](images/robot.png)

### Circuit Diagram
![Circuit Diagram](images/circuit_diagram.png)

### 3D Model Design
![3D Model](images/3d_model.png)

### Crack Detection Output
![Crack Detection](images/crack_output.png)

---

## ✨ Key Features

- 🧲 Strong magnetic adhesion for vertical & inverted climbing  
- 🐜 Crawler track mechanism for stable movement  
- 👁️ Camera-based surface inspection  
- 🧠 OpenCV-powered crack detection  
- 🤖 Remote / semi-autonomous operation  
- 🏭 Suitable for industrial inspection applications  

---

## ⚙️ Working Principle

1. **Magnetic adhesion system** holds the robot firmly on metal surfaces.
2. **Crawler tracks** driven by DC motors allow smooth movement.
3. A **camera module** captures real-time images of the surface.
4. Images are processed using **OpenCV algorithms**.
5. Surface cracks are detected and highlighted for analysis.

---


## 🔌 Hardware & Circuit Description

### Major Components Used
- Microcontroller (Arduino / ESP32 / Raspberry Pi)
- Motor Driver (L298N / BTS7960)
- DC Geared Motors
- Neodymium Magnets / Electromagnets
- Camera Module
- Li-ion Battery Pack
- Voltage Regulator & Switches

The motor driver controls the crawler motors, while the microcontroller handles movement commands and camera input. The power system provides stable voltage to all components.

---

## 🧱 3D Model Design

The robot chassis is designed using **On Shape / Sketchup** with the following considerations:
- Compact and lightweight structure  
- Balanced weight distribution  
- Enclosed electronics compartment  
- Optimized crawler layout for curved surfaces  

---

## 👁️ Crack Detection Using OpenCV

### Image Processing Steps
- Grayscale conversion  
- Gaussian blur for noise reduction  
- Canny edge detection  
- Contour detection  
- Crack highlighting  

## 🎮 Xbox Controller Based Robot Control

The Magnetic Crawler Inspection Robot can be **manually controlled using an Xbox controller**, enabling precise navigation during inspection.  
This is especially useful when inspecting **dangerous, confined, or complex metal surfaces**.

The controller communicates with the robot via a **PC or Raspberry Pi**, sending commands to the microcontroller through a **WiFi Access Point**.

---

### 🎯 Control Features
- Forward & backward movement
- Left & right turning
- Start/stop inspection
- Trigger crack detection
- Emergency stop

---

### 🎮 Controller Mapping

| Xbox Control | Function |
|------------|----------|
| RT / LT | Forward/Backward |
| A Button | Capture And Detect Crack |
| B Button | Turn Right |
| X Button | Turn Left |
| Y Button | Emergency Stop | 

---

### 🧰 Libraries Used
```bash
pygame
pyserial
opencv-python
numpy

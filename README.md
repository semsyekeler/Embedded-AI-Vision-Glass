# Embedded AI Vision Glass (EGG)

<div align="center">

**Read in Other Languages**

<a href="README.md">🇺🇸 English</a> | <a href="README_tr.md">🇹🇷 Türkçe</a>

</div>

<p align="center">
  <img src="5_Project_Documentation/Media/1_Prototyping_and_Assembly/gozluk-kafada-takili-onden.png" width="650">
</p>

| **Project Summary** |
| :---: |
| This project documents the journey of a high school student who single-handedly designed, built, and coded an AI-powered smart glass prototype from scratch, using personal funds. The "Embedded AI Vision Glass" (EGG) is an award-winning assistive device created to enhance the independence of visually impaired individuals by interpreting their environment. It transforms the abstract concept of sight into tangible information through object recognition, text-to-speech, and live translation, proving that complex, impactful technology can be developed with passion and resourcefulness. |

This repository serves as a comprehensive technical archive for the EGG project, detailing its entire lifecycle from initial concept to a competition-winning prototype. It is designed as both a portfolio showcase and a reference for those interested in embedded systems, IoT, and applied AI.

**Disclaimer:** The information and code in this repository are provided for demonstration purposes only. This is a personal project and not a commercial product. The source code is not open-source, and all rights are reserved.

---

## Project Outline

This project chronicles the creation of the EGG in 5 main chapters:

### **[Chapter I: The Idea and The "Why"](5_Project_Documentation/1_The_Idea_and_The_Why.md)**
This chapter details the motivation behind the project: to create a multi-functional assistive device that goes beyond simple obstacle detection, offering a true cognitive "sight" experience for the visually impaired. It analyzes the shortcomings of existing solutions and sets the vision for the EGG.

### **[Chapter II: Hardware Architecture & Assembly](5_Project_Documentation/2_Hardware_Architecture.md)**
A deep dive into the hardware decisions and the hands-on assembly process. This section covers:
*   The **Dual-MCU Architecture** (ESP32 + ESP32-CAM) and why this choice was critical for performance.
*   **Power Management System** design, including the TP4056 charging circuit, 18650 battery, and the stabilized 5V step-up converter.
*   **Hardware-level modifications**, such as the "BT Headset Hacking" to integrate a high-quality audio system.
*   **Custom-built components** like the capacitive touchpads.

### **[Chapter III: The Software Ecosystem](5_Project_Documentation/3_Software_Ecosystem.md)**
This chapter explains the three-tiered software structure that brings the glasses to life:
*   **Firmware:** The C++ code running on the dual ESP32s, managing tasks, user input, and communication.
*   **Cloud Backend:** The serverless architecture on AWS, using Lambda, API Gateway, S3, Textract, and Rekognition for all AI-heavy processing.
*   **Mobile Application:** The Android app that acts as the command center and user-feedback interface.

### **[Chapter IV: Capabilities and Live Demos](5_Project_Documentation/4_Capabilities_and_Demos.md)**
A showcase of what the EGG can do. This section provides details and media for key functions:
*   **AI-Powered Vision:** Text Recognition (OCR), Live Translation, Object Detection, and more.
*   **User Interface:** How the dynamic touch-based command system works.
*   **Connectivity Modes:** FTP Server for file access and WebSocket Live Streaming.
*   **Assistive Features:** The integrated Bluetooth headset and voice-activated flashlight.

### **[Chapter V: Competitions, Challenges, and Learnings](5_Project_Documentation/5_Competitions_and_Learnings.md)**
This chapter reflects on the journey, including winning 3rd place at the Sivas International Robotics Competition, the feedback received from TEKNOFEST judges, the technical challenges overcome, and the invaluable lessons learned in engineering, project management, and perseverance.

---

## Acknowledgements

A special thanks to my teachers, family, and all stakeholders who supported and believed in this project from the very beginning.

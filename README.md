<div align="center">

**Languages**

<a href="README.md">🇺🇸 English</a> | <a href="README_tr.md">🇹🇷 Türkçe</a> | <a href="README_de.md">🇩🇪 Deutsch</a> | <a href="README_es.md">🇪🇸 Español</a> | <a href="README_fr.md">🇫🇷 Français</a> 

</div>

<h1 align="center">Embedded AI Vision Glass (EGG)</h1>

<p align="center">
  <img src="5_Project_Documentation/Media/showcase_banner.jpg" width="700">
</p>

| **Project Summary** |
| :---: |
| An award-winning, AI-powered smart glass prototype, single-handedly developed by a high school student. This project aims to enhance the daily lives of visually impaired individuals by providing them with a cognitive sense of sight. It can read text, recognize objects, identify currency, and describe the user's surroundings, all managed through a multi-layered system of embedded hardware, cloud AI, and a mobile application. |

This repository documents the entire journey of the **Embedded AI Vision Glass (EGG)**, from the initial concept and hardware design to the development of its complex, three-tiered software architecture.

This project stands as a portfolio piece to showcase skills in hardware engineering, embedded systems, cloud architecture, and mobile development. The source code and design files are provided for viewing and educational purposes only.

---

## Project Outline: The Story of EGG

This project is chronicled in 4 main chapters, detailing its technical evolution.

### **Chapter I: The Architecture - A Dual-Brain Design**
This section details the core engineering decision to use a dual-MCU architecture to overcome performance bottlenecks. The **ESP-WROOM-32** acts as the main controller for UI and Bluetooth, while a dedicated **ESP32-CAM** handles all intensive camera, Wi-Fi, and AI-related tasks. The two are orchestrated via UART communication.
*   **See the full annotated schematic in:** `1_Hardware_Design/Schematics/`

### **Chapter II: The Cloud - The AI Core**
The "intelligence" of the glasses resides in the cloud. This section explains how a serverless architecture on **AWS** (API Gateway, Lambda, S3) is used to trigger powerful AI services like **Amazon Rekognition** (for object/face/currency detection) and **Amazon Textract** (for OCR). This approach keeps the device lightweight and cost-effective.
*   **Review the Lambda function code in:** `3_Cloud_Backend/AWS_Lambda_Function/`

### **Chapter III: The Interface - User Interaction**
This chapter covers both the physical and digital interfaces. The glasses feature a dynamic, gesture-based control system using **dual capacitive touchpads**. A custom **Android application** provides an alternative control method, a display for results, and integrates a Text-to-Speech (TTS) engine and the **Google Translate API** for a seamless user experience.
*   **Explore the Android source code in:** `4_Mobile_Application/Source_Code_Android/`

### **Chapter IV: The Journey - From a Room to the Stage**
This is not just a theoretical project. EGG was physically built, tested, and successfully competed in the **Sivas International Robotics Competition**, winning the **3rd Place Award** in the highly competitive **Artificial Intelligence Category**. This chapter showcases the prototyping process, the competition experience, and the awards won.
*   **See all photos and videos in:** `5_Project_Documentation/Media/`

---

## ⚖️ Copyright and License

**© 2024, [ŞEMS YEKELER]. All Rights Reserved.**

The contents of this repository are provided for demonstration purposes only. You are not permitted to copy, modify, distribute, or use them in any way without explicit written permission. This project is **NOT** open-source.

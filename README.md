<div align="center">
  <h1 align="center">Embedded AI Vision Glass (EGG)</h1>
  <p align="center">
    An award-winning personal project showcasing an embedded AI computer vision system in the form of smart glasses to assist visually impaired individuals.
    <br />
    <a href="README_tr.md"><strong>Read The Turkish Version (Türkçe Versiyonu Okuyun) »</strong></a>
    <br />
    <br />
    <a href="#-about-the-project">About The Project</a>
    ·
    <a href="#-technical-architecture">Architecture</a>
    ·
    <a href="#-project-showcase">Showcase</a>
  </p>
</div>

---

### 🏆 About The Project

The **Embedded AI Vision Glass (EGG)** is a sophisticated assistive technology prototype, single-handedly designed and developed by a high school student using personal funds. It aims to solve real-world challenges faced by visually impaired individuals by leveraging the power of IoT, cloud computing, and artificial intelligence.

Unlike conventional assistive devices that only detect obstacles, EGG is designed to **interpret and describe the user's environment**. Instead of just a beep, it can describe "there is a chair in front of you" or read the text on a sign, effectively providing a cognitive sense of "sight."

This project's innovation and potential were recognized at the **Sivas International Robotics Competition**, where it won the **3rd Place Award in the Artificial Intelligence Category**.

### 🛠️ Technical Architecture

This project is a full-stack solution, encompassing hardware, embedded software, cloud infrastructure, and a mobile application.

*   **Hardware & Embedded:** A dual-MCU architecture (ESP-WROOM-32 + ESP32-CAM) distributes tasks efficiently. The main controller handles UI and Bluetooth, while a dedicated processor manages camera, Wi-Fi, and AI-related tasks. The two communicate via UART.
*   **Cloud Backend:** A serverless architecture on AWS (API Gateway, Lambda, S3, Rekognition, Textract) performs all heavy AI processing to minimize cost and device load.
*   **Mobile App (Android):** A user-friendly interface to control the glasses, send commands, and receive real-time results via Bluetooth and Firebase. It utilizes a Text-to-Speech (TTS) engine and the Google Translate API for multilingual support.

### 🌟 Key Features

*   **Text Analysis (OCR):** Reads text from documents and signs.
*   **Live Text Translation:** Translates and reads foreign text.
*   **Scene Description:** Identifies objects in the user's surroundings.
*   **Currency & Face Recognition:** Identifies banknotes and pre-registered individuals.
*   **Dual Control:** Controlled via on-board touchpads or voice commands through the app.
*   **Live Video Streaming & FTP Server Mode.**

### 🖼️ Project Showcase

This repository is for portfolio and demonstration purposes. You can browse the project files to see the schematics and source code.

*The files in this repository are provided for viewing and demonstration only.*

---

### ⚖️ Copyright and License

**© 2024, [SENİN ADIN SOYADIN]. All Rights Reserved.**

The source code, hardware schematics, and all other assets of this project are provided for demonstration and portfolio purposes. You may view the code for educational purposes, but you are not permitted to copy, modify, distribute, or use them in any way without explicit written permission from the author.

**This project is NOT open-source.**

<!-- Bu bir test ve örnek README dosyasıdır. -->

<div align="center">
  <h1 align="center">Gömülü Yapay Zeka Görü Gözlüğü (EGG)</h1>
</div>

---

### 📜 İçindekiler

1.  [**Proje Hakkında**](#-proje-hakkında)
    -   *Projenin çıkış noktası ve misyonu.*
2.  [**Teknik Mimari**](#️-teknik-mimari)
    -   *Sistemin genel yapısı ve kullanılan teknolojiler.*
3.  [**Donanım Detayları ve Montaj**](#-donanım-detayları-ve-montaj)
    -   *Kullanılan bileşenler ve montaj süreci.*
4.  [**Canlı Demolar**](#-canlı-demolar-ve-vitrin)
    -   *Projenin çalıştığını gösteren videolar.*

---
<br>

## 🏆 Proje Hakkında

Bu proje, görme engelli bireylerin dünyayı algılama şeklini kökten değiştirmek amacıyla, tamamen kişisel imkanlarla sıfırdan hayata geçirilmiş bir teknoloji manifestosudur. Misyonumuz, sadece "engel var" diyen bir cihaz değil, kullanıcıya **"önündeki tabelada 'acil çıkış' yazıyor"** diyebilen, çevresini **anlamlandıran ve betimleyen** bir yardımcı yaratmaktır. Bu vizyon, uluslararası bir yarışmada alınan derece ile tescillenmiştir.

Projenin temel amacı, teknolojiyi kullanarak görsel dünyayı sesli bilgiye dönüştürmek ve bu sayede kullanıcı için daha erişilebilir bir çevre yaratmaktır.

<br>
<br>
<br>
<br>
<br>

## 🛠️ Teknik Mimari

EGG projesi, donanım, gömülü yazılım, bulut ve mobil katmanları bir araya getiren tam kapsamlı bir IoT çözümüdür. Projenin teknik kararlarını ve yapısını aşağıdaki notlu şema özetlemektedir.

<p align="center">
  <img src="https://i.imgur.com/8Fk7oA3.jpg" alt="Açıklamalı Devre Şeması" width="100%">
</p>

Sistemin kalbinde, görevleri verimli bir şekilde dağıtan **Çift Mikrodenetleyici Mimarisi** (ESP32 + ESP32-CAM) yer alır. Tüm ağır yapay zeka işlemleri, maliyeti ve cihaz yükünü en aza indirmek için **AWS (Amazon Web Services)** üzerinde "sunucusuz" bir mimaride çalışır.

<br>
<br>
<br>
<br>
<br>

### 🔩 Donanım Detayları ve Montaj

Bu bölümde, projenin fiziksel olarak nasıl hayata geçtiğini görebilirsiniz. Tüm bileşenler, bütçe dostu ve erişilebilir olmaları göz önünde bulundurularak seçilmiştir.

*   **Ana Kontrolcü:** ESP-WROOM-32
*   **Kamera İşlemcisi:** ESP32-CAM
*   **Güç Yönetimi:** TP4056 Şarj Modülü + 18650 Lityum Pil + 5V Step-Up Konvertör
*   **Ses Sistemi:** Modifiye edilmiş (hacklenmiş) bir Bluetooth kulaklık PCB'si

<p align="center">
  <img src="https://i.imgur.com/j1v2X4i.png" width="400" alt="Montaj Aşaması">
  <br>
  <em>Tüm bileşenlerin elle birleştirildiği "çıplak" prototipin ilk halleri.</em>
</p>

<br>
<br>
<br>
<br>
<br>

## 🖼️ Canlı Demolar ve Vitrin

Projenin işlevselliğini ve son halini gösteren YouTube videoları:

| Final Prototip Turu | Canlı Asistan Testi |
| :---: | :---: |
| _Gözlüğün son halinin her açıdan incelendiği ürün turu videosu._ | _Sesle etkinleştirilen fener özelliğinin canlı testini içeren demo videosu._ |
| <a href="https://www.youtube.com/watch?v=MX3VzD0-spU" target="_blank"><img src="https://img.youtube.com/vi/MX3VzD0-spU/0.jpg" alt="Final Prototip Turu Videosu" width="300"></a> | <a href="https://www.youtube.com/watch?v=o3IA8lo6HuY" target="_blank"><img src="https://img.youtube.com/vi/o3IA8lo6HuY/0.jpg" alt="Canlı Asistan Testi Videosu" width="300"></a> |

<br>
<br>
<br>
<br>
<br>

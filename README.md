<!-- Diğer dillere link (şimdilik sadece İngilizce var) -->
[Read the English Version (İngilizce Versiyonu Okuyun) »](README.md)

---

<div align="center">
  <!-- Proje Banner'ı (Bu linki daha sonra kendi yüklediğin resimle değiştireceksin) -->
  <img src="https://i.imgur.com/Kq8Xq7l.jpg" alt="Proje Banner" width="750">

  <h1 align="center">Gömülü Yapay Zeka Görü Gözlüğü (EGG)</h1>

  <p align="center">
    Görme engelli bireylere yardımcı olmak amacıyla bir lise öğrencisi tarafından geliştirilen, ödüllü ve yapay zeka destekli bir akıllı gözlük projesinin portfolyo sunumudur.
    <br />
    <a href="#-proje-hakkında"><strong>Proje Hakkında</strong></a> ·
    <a href="#-teknik-mimari"><strong>Teknik Mimari</strong></a> ·
    <a href="#-proje-vitrini"><strong>Proje Vitrini</strong></a>
  </p>
</div>

---

### 🏆 Proje Hakkında

**Gömülü Yapay Zeka Görü Gözlüğü (EGG)**, görme engelli bireylerin günlük hayatta karşılaştığı zorluklara çözüm üretmek amacıyla, tek bir lise öğrencisi tarafından tamamen kişisel imkanlarla tasarlanıp geliştirilmiş, ileri teknoloji bir yardımcı prototiptir.

Bu proje, geleneksel yardımcı cihazların aksine, sadece engelleri tespit etmekle kalmaz, aynı zamanda kullanıcının çevresini **anlamlandırır ve betimler**. Sadece bir uyarı sesi vermek yerine, "önünde bir sandalye var" diyebilir veya bir tabeladaki yazıyı sesli olarak okuyabilir. Bu sayede, bilişsel bir "görme" yeteneği sunarak kullanıcının bağımsızlığını artırmayı hedefler.

Projenin yenilikçi yapısı ve potansiyeli, katıldığı **Sivas Uluslararası Robot Yarışması**'nda **Yapay Zeka Kategorisi Üçüncülük Ödülü** alarak bağımsız bir jüri tarafından tescillenmiştir.

### 🛠️ Teknik Mimari

Proje; donanım, gömülü yazılım, bulut altyapısı ve mobil uygulamayı kapsayan tam kapsamlı (full-stack) bir çözümdür.

<!-- Mimari Şeması (Bu linki daha sonra kendi yüklediğin notlu şema ile değiştireceksin) -->
<p align="center">
  <img src="https://i.imgur.com/8Fk7oA3.jpg" width="100%">
</p>

*   **Donanım ve Gömülü Yazılım:** Görevleri verimli bir şekilde dağıtan **çift mikrodenetleyicili (ESP-WROOM-32 + ESP32-CAM)** bir mimariye sahiptir. Ana kontrolcü arayüz ve Bluetooth'u yönetirken, özel işlemci kamera, Wi-Fi ve yapay zeka ile ilgili görevleri üstlenir. İki işlemci UART üzerinden haberleşir. Bu mimari, tek bir işlemcinin Wi-Fi ve Bluetooth'u aynı anda kullanırken yaşadığı performans sorunlarını çözmek için özel olarak tasarlanmıştır.

*   **Sunucu Altyapısı (Bulut):** Maliyeti ve cihaz üzerindeki işlem yükünü en aza indirmek için **AWS (Amazon Web Services)** üzerinde "sunucusuz" (serverless) bir mimari kullanılmıştır. Tüm ağır yapay zeka işlemleri (Metin Okuma, Nesne Tanıma vb.) bulutta yapılır.
    *   **Kullanılan Servisler:** API Gateway, Lambda, S3, AWS Textract, AWS Rekognition.

*   **Mobil Uygulama (Android):** Gözlüğü kontrol etmek, komut göndermek ve işlenen sonuçları sesli olarak almak için geliştirilmiş kullanıcı dostu bir arayüzdür. Bluetooth ve internet üzerinden gözlükle ve sunucuyla sürekli iletişim halindedir.

### 🌟 Temel Yetenekler

*   **Metin Analizi (OCR):** Doküman, tabela ve etiketlerdeki metinleri okur.
*   **Canlı Metin Çevirisi:** Yabancı dildeki bir metni okur, Türkçeye çevirir ve seslendirir.
*   **Ortam Betimleme:** Çevredeki nesneleri tanır ve kullanıcıya raporlar.
*   **Para ve Yüz Tanıma:** Kağıt paraları ve önceden kaydedilmiş kişileri tanır.
*   **Çift Kontrol Sistemi:** Hem gözlük üzerindeki kapasitif dokunmatik yüzeylerle hem de mobil uygulama üzerinden sesli komutlarla kontrol edilebilir.
*   **Ek Modlar:** Canlı Video Yayını (WebSocket üzerinden) ve FTP Sunucu Modu (SD karttaki dosyalara kablosuz erişim).

### 🖼️ Proje Vitrini: Fikirden Ödüle Yolculuk

Bu repo, projenin gelişim sürecini ve sonucunu sergilemek amacıyla oluşturulmuştur.

| 1. İlk Prototipleme ve Montaj | 2. Yarışma ve Başarı | 3. Canlı Demo |
| :---: | :---: | :---: |
| _BT kulaklık modifikasyonu ve özel kablolama dahil, tüm bileşenlerin elle birleştirilmesi._ | _EGG projesinin Sivas Uluslararası Robot Yarışması'nda sunulması ve Yapay Zeka kategorisinde üçüncülük ödülü._ | _Dahili asistanın temel bir yeteneği olan sesle etkinleştirilen fener özelliğini gösteren canlı bir test._ |
| <!-- Resim 1 Linki --> <img src="https://i.imgur.com/j1v2X4i.png" width="250"> | <!-- Resim 2 Linki --> <img src="https://i.imgur.com/J3tG5d9.jpg" width="250"> | <!-- Video/GIF Linki --> <video src="https://i.imgur.com/L12s9pP.mp4" width="250"></video> |

*Bu repodaki dosyalar yalnızca inceleme ve gösterim amaçlıdır.*

---

### ⚖️ Telif Hakkı ve Lisans

**© 2024, [SENİN ADIN SOYADIN]. Her Hakkı Saklıdır.**

Bu projenin kaynak kodları, donanım şemaları ve diğer tüm varlıkları yalnızca portfolyo ve gösterim amacıyla sunulmuştur. Kodları eğitim amacıyla inceleyebilirsiniz, ancak yazarın açık ve yazılı izni olmaksızın kopyalamanız, değiştirmeniz, dağıtmanız veya herhangi bir şekilde kullanmanız yasaktır.

**Bu proje açık kaynak değildir.**

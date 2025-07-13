# Gömülü Yapay Zeka Görü Gözlüğü (EGG)

<div align="center">

**Diğer Dillerde Oku**

<a href="../../README.md">🇺🇸 English</a> | <a href="./README.md">🇹🇷 Türkçe</a> | <a href="../de/README.md">🇩🇪 Deutsch</a> | <a href="../es/README.md">🇪🇸 Español</a> | <a href="../fr/README.md">🇫🇷 Français</a> | <a href="../ru/README.md">🇷🇺 Русский</a> | <a href="../zh-CN/README.md">🇨🇳 中文</a>

</div>

<!-- ANA GÖRSEL: İLK PROTOTİP ve BAŞARI YAN YANA -->
<p align="center">
  <img src="../../5_Project_Documentation/Reports_and_Presentations/ilk prototip.jpg" alt="İlk Prototip" width="48%">
  <img src="../../5_Project_Documentation/Media/2_Competition_and_Awards/award-pose.jpeg" alt="Yarışma Başarısı" width="48%">
</p>

| **Proje Özeti** |
| :---: |
| Bu proje, bir lise öğrencisinin tamamen kişisel imkanlarıyla, sıfırdan tasarlayıp kodladığı yapay zeka destekli bir akıllı gözlük prototipinin yolculuğunu belgelemektedir. "Engelsiz Görü Gözlüğü" (EGG), çevresini yorumlayarak görme engelli bireylerin bağımsızlığını artırmak amacıyla oluşturulmuş, ödüllü bir yardımcı cihazdır. Soyut "görme" kavramını; nesne tanıma, metinden sese ve canlı çeviri gibi özelliklerle somut bilgiye dönüştürür. |

Bu repo, EGG projesinin ilk konseptinden yarışmada ödül kazanan prototipine kadar tüm yaşam döngüsünü detaylandıran kapsamlı bir teknik arşiv niteliğindedir. Hem bir portfolyo vitrini hem de gömülü sistemler, IoT ve uygulamalı yapay zeka ile ilgilenenler için bir referans olarak tasarlanmıştır.

**Yasal Uyarı:** Bu repodaki kaynak kodları ve tasarım dosyaları yalnızca gösterim amaçlıdır. Tüm hakları saklıdır ve bu proje **açık kaynak değildir**.

---

## Proje Taslağı

Bu proje, EGG'nin yaratılış sürecini 5 ana bölümde anlatmaktadır. Her bölüm, linki verilen kendi dokümanında detaylandırılmıştır:

*   **[Bölüm I: Fikir ve "Neden?"](../../5_Project_Documentation/1_The_Idea_and_The_Why.md)**
    Projenin arkasındaki motivasyon ve basit bir engel tespitinin ötesinde, gerçek bir bilişsel "görü" deneyimi yaratma vizyonu.

*   **[Bölüm II: Donanım Mimarisi ve Montaj](../../5_Project_Documentation/2_Hardware_Architecture.md)**
    **Çift Mikrodenetleyici Mimarisi**, güç yönetimi sistemi ve modifiye edilmiş BT kulaklık gibi donanım kararlarının ve el yapımı montaj sürecinin derinlemesine incelenmesi.

*   **[Bölüm III: Yazılım Ekosistemi](../../5_Project_Documentation/3_Software_Ecosystem.md)**
    Gözlüğü hayata geçiren üç katmanlı yazılım yapısının açıklaması: **Gömülü Yazılım** (C++), **Bulut Altyapısı** (AWS Serverless) ve **Mobil Uygulama** (Android).

*   **[Bölüm IV: Yetenekler ve Canlı Demolar](../../5_Project_Documentation/4_Capabilities_and_Demos.md)**
    EGG'nin yapabildiklerinin bir vitrini. **Yapay Zeka Destekli Görü** (OCR, Nesne Tanıma), dinamik dokunmatik arayüz ve bağlantı modları hakkında detaylar.

*   **[Bölüm V: Yarışmalar, Zorluklar ve Öğrenimler](../../5_Project_Documentation/5_Competitions_and_Learnings.md)**
    Uluslararası bir robotik yarışmasında üçüncülük kazanmak, TEKNOFEST jürilerinden alınan geri bildirimler, aşılan teknik zorluklar ve bu yolculukta kazanılan dersler üzerine düşünceler.

## 🛠️ Teknik Mimari

EGG projesi, üç katmanlı bir mimariye sahip tam kapsamlı bir IoT çözümüdür.

<p align="center">
  <a href="../../1_Hardware_Design/gozluk-sema-noted.jpg"><img src="../../1_Hardware_Design/gozluk-sema-noted.jpg" alt="Açıklamalı Devre Şeması" width="100%"></a>
  <br>
  <em>Notlu şemanın tamamını görmek için resme tıklayın.</em>
</p>

## 🖼️ Proje Vitrini: Fikirden Ödüle Yolculuk

Bu proje, bir fikrin somut bir prototipe ve ardından ödüllü bir çalışmaya dönüşme hikayesidir.

| 1. "Çıplak" Prototip | 2. Ödüller | 3. Canlı Demo |
| :---: | :---: | :---: |
| _Tüm bileşenlerin elle birleştirildiği, bantlarla sabitlendiği ve henüz bir kasası olmayan ilk işlevsel versiyon._ | _Sivas Uluslararası Robot Yarışması'nda Yapay Zeka ve Tematik Robot kategorilerinde kazanılan dereceler._ | _Dahili asistanın temel yeteneklerinden biri olan sesle etkinleştirilen fener özelliğinin canlı testi._ |
| <a href="../../5_Project_Documentation/Media/1_Prototyping_and_Assembly/esp32wroower-ic-tarafi-motor-bt-montajlanmis.png"><img src="../../5_Project_Documentation/Media/1_Prototyping_and_Assembly/esp32wroower-ic-tarafi-motor-bt-montajlanmis.png" width="250" alt="Montaj Aşaması"></a> | <a href="../../5_Project_Documentation/Media/2_Competition_and_Awards/our-team-medals.jpg"><img src="../../5_Project_Documentation/Media/2_Competition_and_Awards/our-team-medals.jpg" width="250" alt="Kazanılan Ödüller"></a> | <a href="../../5_Project_Documentation/Media/3_Demos_and_Presentations/assistant-test.mp4"><img src="../../5_Project_Documentation/Media/3_Demos_and_Presentations/assistant-test.mp4" width="250" alt="Canlı Demo"></a> |


---

## ⚖️ Telif Hakkı ve Lisans

**© 2024, Şems YEKELER. Her Hakkı Saklıdır.**

Bu projenin kaynak kodları, donanım şemaları ve diğer tüm varlıkları yalnızca portfolyo ve gösterim amacıyla sunulmuştur. Kodları eğitim amacıyla inceleyebilirsiniz, ancak yazarın açık ve yazılı izni olmaksızın kopyalamanız, değiştirmeniz, dağıtmanız veya herhangi bir şekilde kullanmanız yasaktır.

**Bu proje açık kaynak değildir.**

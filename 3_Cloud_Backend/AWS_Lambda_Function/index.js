// Gerekli AWS SDK (Yazılım Geliştirme Kiti) modüllerini projemize dahil ediyoruz.
const AWS = require('aws-sdk');

// Kullanacağımız AWS servisleri için birer nesne oluşturuyoruz.
const s3 = new AWS.S3();
const textract = new AWS.Textract();
const rekognition = new AWS.Rekognition();

/*
// Not: Firebase entegrasyonu için bu bölümdeki yorumları kaldırıp,
// serviceAccountKey.json dosyasını Lambda paketine eklemeniz gerekecektir.
const admin = require('firebase-admin');
const serviceAccount = require("./serviceAccountKey.json");
admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://SENIN-FIREBASE-PROJE-URL.firebaseio.com"
});
*/

// S3'e dosya kaydetmek için oluşturduğumuz yardımcı fonksiyon
async function saveToS3(folder, imageBuffer) {
    const d = new Date();
    // Türkiye saatine göre ayarlama (+3 saat)
    d.setHours(d.getHours() + 3); 
    const datePart = d.toISOString().split('T')[0]; // Format: YYYY-MM-DD
    const timePart = d.toTimeString().split(' ')[0].replace(/:/g, '-'); // Format: HH-MM-SS
    
    const filename = `resim_${datePart}_${timePart}.jpg`;
    const filePath = `${folder}/${datePart}/${filename}`;

    const params = {
        Bucket: "SENIN-S3-BUCKET-ADIN", // !!! DEĞİŞTİRİLECEK: Kendi S3 Bucket adınızı buraya yazın.
        Key: filePath,
        Body: imageBuffer,
        ContentType: 'image/jpeg'
    };

    const uploadResult = await s3.upload(params).promise();
    return uploadResult.Location; // Yüklenen dosyanın URL'ini döndür
}

// ---- ANA LAMBDA FONKSİYONU ----
// Gözlükten gelen her istek bu fonksiyon tarafından karşılanır.
exports.handler = async (event) => {
    try {
        // 1. Gelen isteği analiz et ve verileri hazırla
        console.log("Gelen event:", JSON.stringify(event)); // Gelen isteği logla (hata ayıklama için)
        const amac = event.amac || ''; // "amac" parametresini al
        const encodedImage = event.base64Image; // Fotoğrafın base64 halini al

        // base64 verisi yoksa hata döndür
        if (!encodedImage) {
            throw new Error("base64Image verisi istekte bulunamadı.");
        }
        const decodedImage = Buffer.from(encodedImage, 'base64'); // Fotoğrafı çöz

        let responseMessage = "Belirtilen işlem anlaşılamadı veya gerçekleştirilemedi.";

        // 2. "amac" parametresine göre ilgili işlemi yap

        // ===== METİN ANALİZİ (OCR) =====
        if (amac.includes("ocr")) {
            console.log("Metin analizi (OCR) işlemi başlatıldı.");
            const params = { Document: { Bytes: decodedImage } };
            const data = await textract.detectDocumentText(params).promise();
            
            let textOfImage = "";
            data.Blocks.forEach(block => {
                if (block.BlockType === "WORD" && block.Confidence > 80) { // Güven skoru %80'den yüksek kelimeleri al
                    textOfImage += block.Text + " ";
                }
            });
            responseMessage = textOfImage.trim() || "Görüntüde okunabilir bir metin bulunamadı.";
            await saveToS3("ocr-isleminden-fotolar", decodedImage);
        }

        // ===== ORTAM/NESNE ANALİZİ =====
        else if (amac.includes("fotograf-analizi")) {
            console.log("Ortam analizi (Nesne Tanıma) işlemi başlatıldı.");
            const params = {
                Image: { Bytes: decodedImage },
                MaxLabels: 5,       // En fazla 5 etiket bul
                MinConfidence: 80   // Güven skoru %80'den yüksek olanları getir
            };
            const data = await rekognition.detectLabels(params).promise();

            if (data.Labels.length > 0) {
                const objectNames = data.Labels.map(label => label.Name).join(', ');
                responseMessage = `Görüntüde şunlar olabilir: ${objectNames}`;
            } else {
                responseMessage = "Tanımlanabilir bir nesne bulunamadı.";
            }
            await saveToS3("ortam-analizinden-fotolar", decodedImage);
        }

        // ===== PARA TESPİTİ =====
        else if (amac.includes("para-tespiti")) {
            console.log("Para tespiti işlemi başlatıldı.");
            const params = { Document: { Bytes: decodedImage } };
            const data = await textract.detectDocumentText(params).promise();

            let foundText = "";
            data.Blocks.forEach(block => {
                if (block.BlockType === "WORD") {
                    foundText += " " + block.Text.toUpperCase();
                }
            });

            let moneyValue = "Para birimi tespit edilemedi.";
            if (foundText.includes(" 200 ") || foundText.includes("İKİ YÜZ")) { moneyValue = "200 Türk Lirası"; }
            else if (foundText.includes(" 100 ") || foundText.includes("YÜZ")) { moneyValue = "100 Türk Lirası"; }
            else if (foundText.includes(" 50 ") || foundText.includes("ELLİ")) { moneyValue = "50 Türk Lirası"; }
            else if (foundText.includes(" 20 ") || foundText.includes("YİRMİ")) { moneyValue = "20 Türk Lirası"; }
            else if (foundText.includes(" 10 ") || foundText.includes("ON")) { moneyValue = "10 Türk Lirası"; }
            else if (foundText.includes(" 5 ") || foundText.includes("BEŞ")) { moneyValue = "5 Türk Lirası"; }
            
            responseMessage = moneyValue;
            await saveToS3("para-tespiti-isleminden", decodedImage);
        }
        
        // ===== YÜZ ANALİZİ =====
        else if (amac.includes("yuz-analizi")) {
            console.log("Yüz analizi işlemi başlatıldı.");
            const params = {
                Image: { Bytes: decodedImage },
                Attributes: ['ALL']
            };
            const data = await rekognition.detectFaces(params).promise();

            if (data.FaceDetails.length > 0) {
                const faceCount = data.FaceDetails.length;
                responseMessage = `${faceCount} adet yüz tespit edildi.`;
            } else {
                responseMessage = "Görüntüde herhangi bir yüz tespit edilemedi.";
            }
            await saveToS3("yuz-analizi-isleminden", decodedImage);
        }

        // ===== SADECE SUNUCUYA FOTOĞRAF YÜKLEME =====
        else if (amac.includes("sunucuya-yukle")) {
            console.log("Sadece S3'e yükleme işlemi başlatıldı.");
            const fileUrl = await saveToS3("gozluk-resimleri", decodedImage);
            responseMessage = `Fotoğraf başarıyla yüklendi. Adres: ${fileUrl}`; 
        }

        // 3. İşlem sonucunu hem logla hem de istemciye döndür
        console.log("İşlem tamamlandı. Dönen yanıt:", responseMessage);

        // Firebase'e yanıtı yaz (aktif edildiğinde çalışacak)
        // await admin.database().ref("sunucu_yaniti").set({ amaci: amac, yanit: responseMessage, zaman: new Date().toISOString() });
        
        return {
            statusCode: 200,
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ sunucu_yaniti: responseMessage })
        };

    } catch (error) {
        // Herhangi bir hata olursa, hatayı logla ve istemciye bir hata mesajı döndür
        console.error("KRİTİK HATA:", error);
        return {
            statusCode: 500,
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ hata: "Sunucu tarafında bir hata oluştu: " + error.message })
        };
    }
};
const WebSocket = require('ws');
const http = require('http');
const path = require('path');
const express = require('express');

// Express uygulamasını ve HTTP sunucusunu oluştur
const app = express();
const server = http.createServer(app);

// Portları tanımla
const WS_PORT = 65080;  // WebSocket için port
const HTTP_PORT = 80;   // Web sayfası için port

// WebSocket Sunucusunu HTTP sunucusu üzerine kur
const wss = new WebSocket.Server({ server });

console.log(`WebSocket sunucusu ${WS_PORT} portunda başlatılıyor...`);

wss.on('connection', (ws) => {
    console.log('Yeni bir istemci bağlandı.');

    // Bir istemciden mesaj (görüntü verisi) geldiğinde...
    ws.on('message', (data) => {
        // Gelen veriyi, gönderen hariç, bağlı olan diğer tüm istemcilere yayınla.
        wss.clients.forEach((client) => {
            if (client !== ws && client.readyState === WebSocket.OPEN) {
                client.send(data);
            }
        });
    });

    ws.on('close', () => {
        console.log('Bir istemcinin bağlantısı kesildi.');
    });

    ws.on('error', (error) => {
        console.error('WebSocket hatası:', error);
    });
});

// HTTP Sunucusu: Canlı yayını izlemek için istemci sayfasını sunar
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'client.html'));
});

// HTTP sunucusunu dinlemeye başla
server.listen(HTTP_PORT, () => {
    console.log(`HTTP sunucusu http://<EC2-IP-ADRESINIZ>:${HTTP_PORT} adresinde yayında.`);
    console.log(`WebSocket sunucusu da aynı adreste ${WS_PORT} portunda dinlemede.`);
});
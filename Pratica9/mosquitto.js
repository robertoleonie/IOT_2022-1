const mqtt = require('mqtt');
const client  = mqtt.connect('mqtt://test.mosquitto.org:1883', [{clean: false}]);

// Initialize everything: web server, socket.io and filesystem
var app = require('http').createServer(handler);
var io = require('socket.io')().listen(app);
var fs = require('fs');

const topic = 'icp006/grupo4/sensor/#';
var temp = [];
var pres = [];
var alt = [];

// Conectando com broker MQTT
client.on('connect', function () {
  client.subscribe(topic, function (err, granted) {
    if (err) console.log('Não conseguiu assinar o topico ' + topic);
    if (granted) console.log('Conseguiu assinar o topico ' + granted.topic);
  });
});

// Make web server listen on port 8000
app.listen(8000);

// Handle web server
function handler (req, res) {
  console.log(res.statusCode);
  console.log('VAI TENTAR RENDERIZAR A PAGINA');
  fs.readFile(__dirname + '/index.html', function (err, data) {
    // Send a status code 500
    if (err) {
      res.writeHead(500);
      return res.end('Error loading index.html');
    }

    // Send a status code 200 and the index.html page
    res.writeHead(200);
    res.end(data);
  });
}

// On a socket connection
io.sockets.on('connection', function (socket) {
  console.log('SOCKET ROLANDO');
});

// On a socket connection error
io.sockets.on("connect_error", err => {
  console.log(err instanceof Error); // true
  console.log(err.message); // not authorized
  console.log(err.data); // { content: "Please retry later" }
});

// Recebendo mensagens do broker MQTT
client.on('message', function (topic, message) {
  // message is Buffer
  switch (topic) {
    case 'icp006/grupo4/sensor/temp':
      temp.push(parseFloat(message.toString()));
      io.sockets.emit('new_temp', message.toString());
      // console.log('new_temp', temp);
    break;
    case 'icp006/grupo4/sensor/pres':
      pres.push(parseFloat(message.toString()));
      io.sockets.emit('new_pres', message.toString());
      // console.log('new_pres', pres);
    break;
    case 'icp006/grupo4/sensor/alt':
      alt.push(parseFloat(message.toString()));
      io.sockets.emit('new_alt', message.toString());
      // console.log('new_alt', alt);
    break;
    default:
      console.log('Topico invalido');
  }
});

// Initialize firmata, board, and etherport to connect over wifi
var EtherPortClient = require('etherport-client').EtherPortClient;
var Firmata = require('firmata');
var five = require('johnny-five');

// Initialize everything: web server, socket.io and filesystem
var app = require('http').createServer(handler);
var io = require('socket.io').listen(app);
var fs = require('fs');

// Instatiate board
var board = new five.Board({
	io: new Firmata(
		new EtherPortClient({
			host: '192.168.3.2',
			port: 3030,
		}),
	),
	timeout: 1e5,
});

var blinkingLedBoard;
var blinkingLed;
var intensityLedBoard;
var intensityLed;

// When board is ready (initialized)
board.on("ready", function() {
  blinkingLed = new five.Led(4); 	// Green LED D2
  intensityLed = new five.Led(5);	// Red LED D1
  blinkingLedBoard = new five.Led(2);  // Green LED D2
  intensityLedBoard = new five.Led(16);  // Red LED D1
});

// Make web server listen on port 8000
app.listen(8000);

// Handle web server
function handler (req, res) {
  fs.readFile(__dirname + '/index.html',
  function (err, data) {
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
  socket.emit('news', { hello: 'world' });

  // If led message received
  socket.on('ledIntensity', function (data) {
    console.log(data);
     if(board.isReady) {
      console.log("Essa é a potencia medida:", data.led_slider)
      intensityLed.brightness((data.led_slider/1024)*255);
      intensityLedBoard.brightness((data.led_slider/1024)*255);
    } 
  });

  // If led message received
  socket.on('ledBlinking', function (data) {
    console.log(data);
     if(board.isReady) {
      console.log("Essa é a potencia medida:", data.led_slider)
      blinkingLed.blink(data.led_slider);
      blinkingLedBoard.blink(data.led_slider);
    } 
  });
});





var EtherPortClient = require('etherport-client').EtherPortClient;
var Firmata = require('firmata');
var five = require('johnny-five');

var board = new five.Board({
	io: new Firmata(
		new EtherPortClient({
			host: '192.168.3.2',
			port: 3030,
		}),
	),
	timeout: 1e5,
});


board.on("ready", function() {
  var pot = new five.Sensor("A0");
  var blinkingLed = new five.Led(4); 	// Green LED D2
  var intensityLed = new five.Led(5);	// Red LED D1

	pot.on("change", function() {
			console.log("Essa é a potencia medida:", pot.value)
		  blinkingLed.blink(pot.value*10);
		  intensityLed.brightness((pot.value/1024)*100);
		}
	);
});

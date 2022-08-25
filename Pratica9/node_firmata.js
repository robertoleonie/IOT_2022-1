var EtherPortClient = require('etherport-client').EtherPortClient;
var Firmata = require('firmata');
var five = require('johnny-five');
// Imports for MQTT client
const mqtt = require('mqtt');
const client  = mqtt.connect('mqtt://localhost:1883');
const topic = 'icp006/grupo4/sensor';

var board = new five.Board({
	io: new Firmata(
		new EtherPortClient({
			host: '192.168.3.22',
			port: 3030,
		}),
	),
	timeout: 1e5,
});


function sendPot(pot) {
	var message = "potência: " + pot;
	console.log(message);
	client.publish(topic, message);
}

board.on("ready", function() {
	var multi = new five.Multi({
    controller: "BME280"
  });

  multi.on("data", function() {
    message = ("Thermometer:\n");
    message += ("  celsius      : " + this.thermometer.celsius + "\n");
    message += ("  fahrenheit   : " + this.thermometer.fahrenheit + "\n");
    message += ("  kelvin       : " + this.thermometer.kelvin + "\n");
    message += ("--------------------------------------\n");

    message += ("Barometer\n");
    message += ("  pressure     : " + this.barometer.pressure + "\n");
    message += ("--------------------------------------\n");

    message += ("Hygrometer\n");
    message += ("  humidity     : " + this.hygrometer.relativeHumidity + "\n");
    message += ("--------------------------------------\n");

    message += ("Altimeter\n");
    message += ("  feet         : " + this.altimeter.feet + "\n");
    message += ("  meters       : " + this.altimeter.meters + "\n");
    message += ("--------------------------------------\n");

    sendPot(message);
  });
});

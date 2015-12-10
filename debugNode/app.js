var http = require('http');
var express = require('express');
var app = express();
var serialport = require("serialport");
var fs = require("fs");
var json2csv = require('json2csv');

var server = http.createServer(app).listen(3000);
var io = require('socket.io').listen(server);
var i = 0;
var portNames ={};
app.use(express.static(__dirname + '/public'));
console.log("Created server on port: " + server.address().port)
var skipLines = 0;
// ------- Setup CSV ---------
var storeData = {};

// -------- Setup serial --------
var serialName = ' '; // start with empty port
var serial = new serialport.SerialPort(serialName,{
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false,
    parser: serialport.parsers.readline("\n")
}, false); // don't open serialport at startup.


// --------- Recieved sockets -------

io.sockets.on('connection', function (socket) {
	//Connecting to client 
	console.log('Socket connected');
	socket.emit('connected');
	getSerialPorts(function(portList){
		socket.emit('serialPorts', portList);  // on connection, emit serialports
	});

	serial.on('data', function(data){
		console.log(data);
		if (skipLines==10){ // lines to skip to prevent broken lines at startup
			parseSerial(socket, data);
		}else{
			console.log("skipped: " + data);
			skipLines = skipLines +1;
		};
	});

	socket.on('serialRefresh', function(){
		getSerialPorts(function(portList){
			socket.emit('serialPorts', portList);
		});
	});

	socket.on('connectSerial', function(port){
		connectSerial(port, function(result){
			socket.emit(result[0], result[1]); // emit failed or connected
		});
	});

	socket.on('disconnectSerial', function(){
		disconnectSerial(function(result){
			socket.emit(result[0], result[1]); // emit conformation of disconnect
		});
	});

	socket.on('getPIDValues', function(){
		console.log("getting PID VALUES!!!!!!!!!!!!!")
		serial.write('getPIDValues\n');
	});

	socket.on('setParameter', function(data){
		serial.write(data[0] + " " + data[1] + "\n");
	})

});

// --------- functions ---------------

function parseSerial(socket, data){
		data = data.split("\t"); // split data in array by tabs
		data.forEach(function(dataset){
			dataset = dataset.split(" "); // split subset by spaces
			socket.emit("serialData", dataset); // emit every key and their values
		});
};

function getSerialPorts(callback){
	var portNames = [];
	// list all ports and connect to first serial port on default
	serialport.list(function (err, portList) {
	  portList.forEach(function(port) {
	    portNames.push(port.comName);
	  });
	    if (portNames.length > 0) {
	    	// console.log(portNames);
	    	callback(portNames);
	    }else{
	    	console.log("No serialports available.");
	    	callback([]);
	    };
	});
};

function connectSerial(portName, callback){
	if(serial.isOpen()){
		serial.close();
	}
	serial.path = portName;
	serial.open(function (error) {
	  	if ( error ) {
	    	console.log('failed to open serial: '+error);
	    	callback(["failed", error]);
	  	} else {
		    console.log('opened Serial');
		    callback(["connectedSerial", portName]);
	    };
	});
};

function disconnectSerial(callback){
	skipLines = 0; // serial needs to buffer again at startup
	if(serial.isOpen()){
		serial.close();
		console.log("Disconnected from: "+serial.path);
		callback(["disconnected", serial.path]);
	};
};
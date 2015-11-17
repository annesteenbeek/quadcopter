var app = angular.module('MyApp', []);


app.factory('socket', function ($rootScope) {
  var socket = io.connect();
  return {
    on: function (eventName, callback) {
      socket.on(eventName, function () {  
        var args = arguments;
        $rootScope.$apply(function () {
          callback.apply(socket, args);
        });
      });
    },
    emit: function (eventName, data, callback) {
      socket.emit(eventName, data, function () {
        var args = arguments;
        $rootScope.$apply(function () {
          if (callback) {
            callback.apply(socket, args);
          }
        });
      })
    }
  };
});

var serialPortList = [];
var smoothie = new SmoothieChart({millisPerPixel:43,
  grid:{fillStyle:'#f3f3f3'},
  labels:{fillStyle:'#000000'},
  timestampFormatter:SmoothieChart.timeFormatter,
  maxValue:180,
  minValue:-180});
smoothie.streamTo(document.getElementById("myChart"));
var line1 = new TimeSeries
smoothie.addTimeSeries(line1, {lineWidth:2,strokeStyle:'#0021ef'});
var line2 = new TimeSeries   
smoothie.addTimeSeries(line2, {lineWidth:2,strokeStyle:'#FF0000'});

app.controller('nodeSerial', function($scope, socket){
  $scope.connected = false;
  $scope.ports = ["..."];

  socket.on('serialPorts', function (input){
    console.log(input);
    $scope.ports = input;
  });

  socket.on("connectedSerial", function (input){
    console.log("connected to port: "+input);
    $scope.connected = true;
  });

  socket.on("failed", function (input){
    console.log("failed to connect: "+input);
  });

  socket.on("disconnected", function (input){
    console.log("disconnected from port: "+input);
    $scope.connected = false;
  });

// ------------ Inputs ----------------

  socket.on("aRoll", function (input){
    console.log("aRoll: " +input);
    $scope.aRoll = input;
    line1.append(new Date().getTime(), input);
  })

  socket.on("aPitch", function (input){
    console.log("aPitch: " +input);
    $scope.aPitch = input;
    line2.append(new Date().getTime(), input);
  })


// ------------ Serial port setup ------
  $scope.serialRefresh = function(){
  socket.emit('serialRefresh');
  };

  $scope.connectSerial = function(){
    console.log("Connecting to: "+$scope.selectedPort);
    socket.emit('connectSerial', $scope.selectedPort)
  }
  $scope.disconnectSerial = function(){
    console.log("Disconnecting serialport");
    socket.emit('disconnectSerial');
  }

// ----------- Button functions --------
  $scope.storeData = function(){
    console.log("storing the data");
    socket.emit("storeData");
  }

})

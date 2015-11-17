var app = angular.module('MyApp', []);
google.load('visualization', '1.0', {'packages':['corechart']});
dataTables = {};


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

var chart = new google.visualization.LineChart(document.getElementById('myChart'));
// var timeFormat = new google.visualization.DateFormat({formatType: 'msSS'});
  var options = {
    hAxis: {
      title: 'Time'
      // format: "S";
    },
    vAxis: {
      title: 'Popularity'
    }
  };

  socket.on("serialData", function (input){
    console.log(input[0] +": " +input[1]);
    if(input[0]=="aRoll"){
      // timeStamp =new Date().getTime();

      if(!dataTables[input[0]]){ // if new key value, creat new data table
        dataTables[input[0]] = new google.visualization.DataTable();
        dataTables[input[0]].addColumn('string', "timestamp");
        dataTables[input[0]].addColumn('number', input[0]);
        dataTables[input[0]].addRow([String(new Date('m:s:SS').getTime()), parseFloat(input[1])]);
      }else{
        dataTables[input[0]].addRow([String(new Date('m:s:SS').getTime()), parseFloat(input[1])]);
        chart.draw(dataTables["aRoll"], options);
      };
      console.log(dataTables);
    }

  });


//-------------- Plotting --------------

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

var app = angular.module('MyApp', []);
// --------------- socketio in angularjs ----------
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

// ------------ AngularJS -------------------
app.controller('nodeSerial', function($scope, socket){
  $scope.dataTables = {};
  $scope.connected = false;
  $scope.ports = ["..."];
  $scope.keys = [];
  $scope.smoothieObj = {};
  $scope.smoothieLines = {};

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
  socket.on("serialData", function (input){
    var key = input[0];
    var data = input[1];
    // console.log(key +": " +input[1]);
      if(!$scope.dataTables[key]){ // if new key value, creat new data table
        $scope.dataTables[key] = [input[1]];
        $scope.keys.push(key);
        // create new smoothie chart and store in object by key
        $scope.smoothieObj[key] = new SmoothieChart({millisPerPixel:43,
          grid:{fillStyle:'#f3f3f3'},
          labels:{fillStyle:'#000000'},
          timestampFormatter:SmoothieChart.timeFormatter
        });
        // create html object canvas
        chartList = document.getElementById('chartList');
        // var canvas = ['<canvas id="'+ key +'" width="400" height="100"></canvas>'];
        var canvas = document.createElement("canvas");
        canvas.id=key;
        canvas.width=400;
        canvas.height=100;
        chartList.appendChild(canvas);
        // connect smoothie object to html canvas
        $scope.smoothieObj[key].streamTo(document.getElementById(key));
        // create new timeseries for key value
        $scope.smoothieLines[key] = new TimeSeries;
        // add line to smoothie object
        $scope.smoothieObj[key].addTimeSeries($scope.smoothieLines[key], 
          {lineWidth:2,strokeStyle:'#0021ef'});
      }else{
        $scope.dataTables[key].push(data);
        // append new data to smoothie line
        $scope.smoothieLines[key].append(new Date().getTime(), data);
      };
  });

// --------------- Download csv ------------
$scope.getCSV = function (name){
  var csvContent = "data:text/csv;charset=utf-8,";
  data = [$scope.dataTables[name]];
       data.forEach(function(infoArray, index){ 
          dataString = infoArray.join("\n"); 
          csvContent += index < infoArray.length ? dataString+ "\n" : dataString;  
        });
       console.log(dataString);
    var encodedUri = encodeURI(csvContent);
    // window.open(encodedUri);
    // dirty method to set download name
    var link = document.createElement("a");    
    link.href = encodedUri;

    //set the visibility hidden so it will not effect on your web-layout
    link.style = "visibility:hidden";
    link.download = name + ".csv";
    //this part will append the anchor tag and remove it after automatic click
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
};
//-------------- Plotting --------------

// ------------ Serial port setup ------
  $scope.serialRefresh = function(){
  socket.emit('serialRefresh');
  };

  $scope.connectSerial = function(){
    console.log("Connecting to: "+$scope.selectedPort);
    socket.emit('connectSerial', $scope.selectedPort)
  };
  $scope.disconnectSerial = function(){
    console.log("Disconnecting serialport");
    socket.emit('disconnectSerial');
  };
})



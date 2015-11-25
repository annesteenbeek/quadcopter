'use strict';

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
  $scope.colors = ["#0000FF", "#00FF00", "#FF0000", "#00FFFF", "#FF00FF", "#FFFF00"];

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
    var key = input.shift();
    var data = input;
    if(key=="PIDvalues"){
      console.log(data);
      break;
    }
    // console.log();
      if(!($scope.keys.indexOf(key)>-1)){ // if new key value, creat new data table
        $scope.keys.push(key);
        // connect smoothie object to html canvas
        setTimeout(function(){
        // create new smoothie chart and store in object by key
        $scope.smoothieObj[key] = new SmoothieChart({millisPerPixel:43,
          grid:{fillStyle:'#f3f3f3'},
          labels:{fillStyle:'#000000'},
          maxValue:180,
          minValue:-180,
          timestampFormatter:SmoothieChart.timeFormatter
        });
        // create html object canvas
        $scope.smoothieObj[key].streamTo(document.getElementById(key));
        data.forEach(function (value, i){ // for each value in array create different line
          $scope.dataTables[key+String(i)] = [value];
          // create new timeseries for key value
          $scope.smoothieLines[key+String(i)] = new TimeSeries;
          // add line to smoothie object
          $scope.smoothieObj[key].addTimeSeries($scope.smoothieLines[key+String(i)], 
            {lineWidth:2,strokeStyle:$scope.colors[i]});
        })
      }, 100);
      }else{
        data.forEach(function (value, i){
          $scope.dataTables[key + String(i)].push(value);
          // append new data to smoothie line
          $scope.smoothieLines[key + String(i)].append(new Date().getTime(), value);
        })
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


// creat dyanimc functions:

// var func = {};
// var name = "foo";
//  func.one = new Function(
//      "return function " + name + "(word){ alert(word)}"
// )();

// func.one("hello");
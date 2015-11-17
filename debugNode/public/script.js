var app = angular.module('MyApp', []);
// ----------- Downlaod CSV ------------
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

app.controller('nodeSerial', function($scope, socket){
  $scope.dataTables = {};
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

  socket.on("serialData", function (input){
    console.log(input[0] +": " +input[1]);
      if(!$scope.dataTables[input[0]]){ // if new key value, creat new data table
        $scope.dataTables[input[0]] = [input[1]];
      }else{
        $scope.dataTables[input[0]].push(input[1]);
      };
  });

// --------------- Download csv ------------
$scope.getCSV = function (name){
  var csvContent = "data:text/csv;charset=utf-8,";
  data = [$scope.dataTables[name]];
       data.forEach(function(infoArray, index){ 
          dataString = infoArray.join(","); 
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



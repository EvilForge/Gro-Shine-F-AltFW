/* Rui Santos - Complete project details at https://RandomNerdTutorials.com
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files.
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software. */

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE HTML><html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<script src="https://code.highcharts.com/highcharts.js"></script>
<style>
body {
min-width: 310px;
max-width: 800px;
height: 400px;
margin: 0 auto;
}
h2 {
font-family: Arial;
font-size: 2.5rem;
text-align: center;
}
</style></head><body>
<h2>Growatt Inverter</h2>
<div id="chart-power" class="container"></div>
<p id="AcPower"></p><p id="EnergyToday"></p><p id="EnergyTotal"></p><p id="DcVoltage"></p>
<a href="./firmware">Firmware update</a> - 
<a href="./status">Json</a> - 
<a href="./debug">Log</a> - 
<a href="./postCommunicationModbus">RW Modbus</a> - <p id="FirmwareVer"></p>
</body><script>
const d = new Date();
let diff = d.getTimezoneOffset();
Highcharts.setOptions({
time: {
timezoneOffset: diff
}
});
var chartT = new Highcharts.Chart({
  chart:{ renderTo : 'chart-power' },
  title: { text: 'Power' },
  series: [{
    showInLegend: false,
    data: []
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    },
    series: { color: '#059e8a' }
  },
  xAxis: { type: 'datetime',
    dateTimeLabelFormats: { second: '%H:%M:%S' }
  },
  yAxis: {
    title: { text: 'Power [W]' }
  },
  credits: { enabled: false }
});

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() 
  {
    if (this.readyState == 4 && this.status == 200) 
	{
	  var obj = JSON.parse(this.responseText);
	  document.getElementById("AcPower").innerHTML = "Power: " + obj.AcPower + " W"; 
	  document.getElementById("EnergyToday").innerHTML = "Today: " + obj.EnergyToday + " kWh"; 
	  document.getElementById("EnergyTotal").innerHTML = "Total: " + obj.EnergyTotal + " kWh"; 
	  document.getElementById("DcVoltage").innerHTML = "DC Voltage: " + obj.DcVoltage + " V"; 
	  document.getElementById("FirmwareVer").innerHTML = "Firmware Version: " + obj.FirmwareVer; 
      var x = (new Date()).getTime(),
          y = obj.AcPower;
      console.log(this.responseText);
      if(chartT.series[0].data.length > 40) {
        chartT.series[0].addPoint([x, y], true, true, true);
      } else {
        chartT.series[0].addPoint([x, y], true, false, true);
      }
    }
  };
  xhttp.open("GET", "./status", true);
  xhttp.send();
}, 5000 ) ;
</script>
</html>
)=====";
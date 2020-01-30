# Weather Station Sending Unit

This project is a weather station sensing unit proof of concept utilizing a 433MHz transmitter and various weather sensors. Inital build is limited to temp/humidity.

Data is sent in a home-grown packet with station id and sensor readings.
## Packet structure
  unit id (three bytes)
  packet type (two bytes)
  temperature (three bytes)
  humidity (three bytes)
  wind speed (three bytes)
  rainfall (five bytes, assumed two digit fractional part)
  
## Parts 
<table>
  <thead>
	<tr>
    <th>Count</th>
    <th>Part Type</th>
    </tr>
  </thead>
  <tbody>
<tr>
    <td>1</td>
    <td>Arduino Micro (Rev3)</td>
</tr><tr>
    <td>1</td>
    <td>Humidity and Temperature Sensor DHT11</td>

</tr><tr>
    <td>1</td>
    <td>433 MHz Transmitter</td>
</tr>
  </tbody>
</table>

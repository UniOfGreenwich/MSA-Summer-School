const char MAIN_page[]PROGMEM=R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="refresh" content="5">
    <title>Motor Control and Monitoring</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #EEEDEE;
        }

        .container {
            max-width: 600px;
            margin: 0 auto;
            padding: 20px;
            background-color: #FFFFFF;
            border-radius: 10px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
        }

        .header {
            background-color: #00033D;
            color: white;
            text-align: center;
            padding: 10px;
            font-size: 24px;
            border-radius: 5px 5px 0 0;
        }

        .status {
            font-size: 18px;
            text-align: center;
            margin-top: 20px;
        }

        .sensor {
            margin-top: 20px;
        }

        .sensor h1 {
            font-size: 20px;
            margin-bottom: 10px;
        }

        .sensor h2 {
            font-size: 16px;
            color: #555;
        }
        .buttons {
            display: flex;
            justify-content: space-around;
            margin-top: 20px;
        }

        .button {
            width: 100px;
            height: 40px;
            font-size: 16px;
            background-color: #00033D;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
    </style>
</head>
<body>
<div class="container">
    <div class="header">Motor Control Dashboard</div>
    <div class="status">Motor state: <span id="motorState">@@status@@</span></div>
        <div class="buttons">
        <button class="button" onclick="sendCommand('Forward')">Forward</button>
        <button class="button" onclick="sendCommand('Stop')">Stop</button>
        <button class="button" onclick="sendCommand('Reverse')">Reverse</button>
    </div>
    <div class="sensor">
        <h1>Motor Temperature</h1>
        <h2><span id="motorTemp">@@m_temp@@  &deg;C</span></h2>

        <h1>Ambient Temperature</h1>
        <h2><span id="ambientTemp">@@a_temp@@  &deg;C</span></h2>

        <h1>Humidity</h1>
        <h2><span id="humidity">@@humidity@@ &percnt;</span></h2>

        <h1>Enclosure Temperature</h1>
        <h2><span id="enclosureTemp">@@motor_temp@@  &deg;C</span></h2>

        <h1>Motor Speed</h1>
        <h2><span id="motorSpeed">@@motor_speed@@ RPM</span></h2>

        <h1>Average Vibration</h1>
        <h2><span id="vibration">@@vibration@@ g</span></h2>
    </div>
</div>
</body>
</html>
)=====";

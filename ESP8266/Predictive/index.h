const char MAIN_page[]PROGMEM=R"=====(
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="refresh" content="5">
        <title> Motor Control and Monitoring Web Server </title>
        <style>
            div.card{
                width:250px;
                box-shadow:0 4px 8px 0 rgba (0, 0, 0, 0.2), 0 6px 20px 0 rgba (0, 0, 0, 0.19);
                text-align:center;
                border-radius:5px;
                background-color:# F5F7A0
            }
            div.header{
                background-color:# E03C3C;
                color:white ;
                padding:10px;
                font-size:40px;
                border-radius:5px;
            }
            div.container{
                padding:4px;
            }
        </style>
    </head>
    <body>
        <center><h2> Motor Control and Monitoring Web Server </h2>
            <form method ="get" action ="/form">
            <input type ="submit" name ="button" value ="Forward" style =  "width:170px;height:40px;">
            <input type ="submit" name ="button" value ="Stop" style =  "width:170px;height:40px;">
            <input type ="submit" name ="button" value ="Reverse" style =  "width:170px;height:40px;">
            </form>
            <h3> Motor state: @@status@@</h3> </br>
        </center>
    </body>

    <body>
        <center>
            <div class="card">
                <div class="header"/>
                <div class = "container">
                    <h1>TMP36_Temperature</h1>
                    <h1> @@m_temp@@   &deg;C</h1>

                    <h1>DHT11_Ambient_Temperature</h1>
                    <h1> @@a_temp@@   &deg;C</h1>

                    <h1>DHT11_Humidity</h1>
                    <h1> @@humidity@@   &percnt;</h1>

                    <h1>Motor Temperature</h1>
                    <h1> @@motor_temp@@   &deg;C</h1>

                    <h1>Motor Speed</h1>
                    <h1> @@motor_speed@@   RPM</h1>

                    <h1>Average Vibration</h1>
                    <h1> @@vibration@@   g</h1>
                </div>
            </div>
        </center>
    </body>
</html>
)=====";

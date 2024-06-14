# Building an HTML Page for Motor Control and Monitoring Web Server

This guide will help you build an HTML page for a motor control and monitoring web server. This page is hosted by the Arduino web server and will be served when someone connects to the correct IP address.

## Step 1: Define the HTML Page

1. Open a new file in your Arduino script folder called `index.h`

2. Start by defining the HTML page as a constant string in your Arduino script. This is done using the `const char` keyword and stored in the program memory using `PROGMEM`.

    ```cpp
    const char MAIN_page[]PROGMEM=R"=====(
    ```

    > **Explanation:**
    >> - `const char MAIN_page[]PROGMEM`: Defines a constant character array named MAIN_page and stores it in the program memory (`PROGMEM`). This helps in saving SRAM space.
    >> - `R"=====(`: The R prefix denotes a raw string literal, allowing you to include special characters without needing escape sequences

## Step 2: Start the HTML Document

3. Begin the HTML document with the `<!DOCTYPE html>` declaration and the opening `<html>` tag.

    ```html
    ...
    <!DOCTYPE html>
    <html>
    ```

    > **Explanation:**
    >> - `<!DOCTYPE html>`: Declares the document type and version of HTML. It helps the browser to render the page correctly.
    >>- `<html>`: The root element of the HTML document.

## Step 3: Add the Head Section

4. Include metadata, a title, and CSS styles within the `<head>` section.

    ```html
    ...
        <head>
            <meta http-equiv="refresh" content="5">
            <title> Motor Control and Monitoring Web Server </title>
            <style>
                div.card{
                    width:250px;
                    box-shadow:0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);
                    text-align:center;
                    border-radius:5px;
                    background-color:#F5F7A0;
                }
                div.header{
                    background-color:#E03C3C;
                    color:white;
                    padding:10px;
                    font-size:40px;
                    border-radius:5px;
                }
                div.container{
                    padding:4px;
                }
            </style>
        </head>
    ```

    > **Explanation:**
    >> - `<meta http-equiv="refresh" content="5">`: Refreshes the page every 5 seconds.
    >> - `<title>`: Sets the title of the page, which appears in the browser tab.
    >> - `<style>`: Defines CSS styles for the HTML elements.
    >> - `div.card`: Styles for a card element, including width, shadow, text alignment, border radius, and background color.
    >> - `div.header`: Styles for the header element, including background color, text color, padding, font size, and border radius.
    >> - `div.container`: Styles for the container element, including padding.

## Step 4: Add the Body Section

Create the body section with forms and data placeholders.

### Step 4.1: Add Form for Motor Control

```html
    ...
    <body>
        <center><h2> Motor Control and Monitoring Web Server </h2>
            <form method ="get" action ="/form">
            <input type ="submit" name ="button" value ="Forward" style = "width:170px;height:40px;">
            <input type ="submit" name ="button" value ="Stop" style = "width:170px;height:40px;">
            <input type ="submit" name ="button" value ="Reverse" style = "width:170px;height:40px;">
            </form>
            <h3> Motor state: @@status@@</h3> </br>
        </center>
```

> **Explanation:**
>> - `<center><h2> Motor Control and Monitoring Web Server </h2></center>`: Centers and displays a heading for the web server.
>>
>> - `<form method="get" action="/form">`: Defines a form that sends a GET request to the /form action URL.
>>      - `<input type="submit" name="button" value="Forward" style="width:170px;height:40px;">`: Creates a submit button for "Forward" with specified dimensions.
>>
>>      - `<input type="submit" name="button" value="Stop" style="width:170px;height:40px;">`: Creates a submit button for "Stop" with specified dimensions.
>>
>>      - `<input type="submit" name="button" value="Reverse" style="width:170px;height:40px;">`: Creates a submit button for "Reverse" with specified dimensions.
>> - `<h3> Motor state: @@status@@</h3>`: Displays the current motor state, with `@@status@@` as a placeholder for dynamic content.


### Step 4.2: Add Sensor Data Display

```html
...
        <center>
            <div class="card">
                <div class="header"/>
                <div class="container">
                    <h1>TMP36_Temperature</h1>
                    <h1> @@m_temp@@ &deg;C</h1>

                    <h1>DHT11_Ambient_Temperature</h1>
                    <h1> @@a_temp@@ &deg;C</h1>

                    <h1>DHT11_Humidity</h1>
                    <h1> @@humidity@@ &percnt;</h1>

                    <h1>Motor Temperature</h1>
                    <h1> @@motor_temp@@ &deg;C</h1>

                    <h1>Motor Speed</h1>
                    <h1> @@motor_speed@@ RPM</h1>

                    <h1>Average Vibration</h1>
                    <h1> @@vibration@@ g</h1>
                </div>
            </div>
        </center>
    </body>
```

> **Explanation:**
>> - `<center>`: Centers the content on the page.
>>
>> - `<div class="card">`: Defines a card element with the class card.
>>
>> - `<div class="header"/>`: Defines a header element with the class header.
>>
>> - `<div class="container">`: Defines a container element with the class container.
>>
>> - `<h1>TMP36_Temperature</h1>`: Displays the title for TMP36 temperature.
>>
>> - `<h1> @@m_temp@@ &deg;C</h1>`: Displays the TMP36 temperature value with `@@m_temp@@` as a placeholder for dynamic content, followed by the degree Celsius symbol.
>>
>> - Similar sections for DHT11 ambient temperature, DHT11 humidity, motor temperature, motor speed, and average vibration, each with appropriate placeholders (`@@a_temp@@`, `@@humidity@@`, `@@motor_temp@@`, `@@motor_speed@@`, and `@@vibration@@`).

## Step 5: End the HTML Document

Close the HTML document with the closing `</html>` tag and the closing delimiter for the raw string literal.

```html
...
</html>
)=====";
```

> **Explanation:**
>> - `</html>`: Closes the root HTML element.
>> - `)====="`: Closes the raw string literal started by `R"=====(`.

## Step 6: import into your Arduino script

At the top of your Predictive.ino, where you have your include directives add the following `"include index.h"`

```cpp
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHTesp.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include "index.h" // < - wedpage here
```

Now you completed that, continue with the next section here -> [IoT Setup](./IoT_Setup.md)


<details>
<summary>Full Code here... </summary>


```html
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
```

</details>
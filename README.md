<p align="left">
  <img src="./images/UoG_logo.png" alt="Logo" width="250" height="75" align=left>
</p>
<p align="right">
  <img src="./images/MSA_logo.jpg" alt="Logo" width="100" height="100" align>
</p>

# Internet of Things DC Motor Predictive Maintenance System

A client has approached the university with the aim to develop an Internet of Things (IOT) DC Motor Predictive maintenance system using the ESP8266 Lolin D1 mini pro WIFI enabled microcontroller.

The client has specified the following scope of functionality:

- Forward and reverse motor control
- Motor speed measurement
- Motor temperature measurement
- Ambient temperature and humidity measurement
- A simple internet interface control screen
- A Web-based data logging system 
- 12V DC supply

The microcontroller and motor have been specified by the client the rest of the design and selection of suitable components is down to you as the main contractor. The budget for the entire system is to be less than £20. The dimensions of the final system are to be no greater than 150 x 80 mm and should be fabricated on a single-sided PCB. The expected delivery time is to be 1 week.

**Objectives**

As the product designer, it is your job to outline the objectives as to how you intend to meet the system requirements. Objectives include what the system will look like, how it will be controlled, what sensors will be used etc. The objectives must be agreed with the client before development progresses.

**Deliverables**
.
..?


## Summary of Activities

<table>
<th>No.</th>
<th>Title</th>
<th>Objective</th>
<th>Estimated Time/Days</th>
    <tr>
        <td>1</td>
        <td>Introduction</td>
        <td>
             <li>Saftey Introduction</li>
             <li>Introduction to Experimental Activities</li>
        </td>
        <td>1 Day</td>
    </tr>
    <tr>
        <td>2</td>
        <td>Components Review</td>
        <td>
             <li>AD822, single-supply, Rail-to-Rail Low Power FET-Input Op Amp</li>
            <li>Humidity Sensors (DHT11, DHT22 and AM2302 Sensors)</li>
            <li>Photo Interrupter (KTIR0611S)</li>
            <li>LM2907 (and LM2917) Frequency to Voltage Converter</li>
            <li>78XX SERIES POSITIVE-VOLTAGE REGULATORS</li>
            <li>LT1013/LT1014: Quad Precision Op Amp (LT1014) Dual Precision Op Amp (LT1013)</li>
            <li>LT1494/LT1495/LT1496: 5µA Max, Single, Dual and Quad Over-The-Top Precision Rail-to-Rail Input and Output Op Amps</li>
            <li>MCP601/1R/2/3/4: 2.7V to 6.0V Single Supply CMOS Op Amps</li>
            <li>MCP6241/1R/1U/2/4: 50 µA, 550 kHz Rail-to-Rail Op Amp</li>
            <li>CD405xB CMOS Single 8-Channel Analog Multiplexer/Demultiplexer With Logic-Level Conversion</li>
            <li>TLE 5206-2: 5-A H-Bridge for DC-Motor Applications</li>
            <li>TMP35/36/37: Low Voltage Temperature Sensors</li>
        </td>
        <td>1 Day</td>
    </tr>
     <tr>
        <td>3</td>
        <td>Circuit Design and PCB Assembly</td>
        <td>
             In this section, the schematic and PCB of the project circuit will be designed and evaluated in the Proteus software. It includes the voltage regulator and OP-AMP circuits. 
        </td>
        <td>1 Day</td>
    </tr>
    <tr>
        <td>4</td>
        <td>Coding/Programming</td>
        <td>
            The system will be programmed based on the suggested flowcharts using the Arduino IDE environment.
        <td>1 Day</td>
    </tr>
    <tr>
        <td>5</td>
        <td>Design Evaluation</td>
        <td>
            Technical support will be provided during the completion of the programming activities. At the end of all the activities, an overall evaluation of the work will be held by the instructor and feedback will be given to the students. 
        <td>1 Day</td>
    </tr>
 
</table>

## Project Files

- ESP8266
  - [Predictive.ino](ESP8266/Predictive/Predictive.ino)
  - [index.h](ESP8266/Predictive/index.h)
  
- Python
  - [predictiveMaintenance.py](predictiveMaintenance/predictiveMaintenance.py) 
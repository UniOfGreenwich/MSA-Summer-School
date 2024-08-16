# IoT Use case: AquaFlow – Smart Water Distribution System

AquaFlow is a mid-sized water distribution company that specializes in providing clean and efficient water supply 
solutions to urban and rural areas. They have developed an innovative water distribution system that leverages IoT 
technology to monitor and optimize the flow of water in real-time, ensuring minimal wastage and efficient distribution. 
AquaFlow operates from two main offices: a headquarters in London (R&D and administration) and a regional office in 
Cairo. Both offices are connected via a secure point-to-point VPN. Employees also have remote access to the HQ 
network through a VPN server.

## IoT Implementation

AquaFlow’s new smart water distribution system integrates various sensors and components to 
monitor and control the water distribution network. The system is built around an Arduino board equipped with the 
following sensors and components: DC Motor, Temperature Sensor, Humidity Sensor, Photo Interrupter, 
Accelerometer, Voltage Regulator, and WiFi Microcontroller. The smart water distribution system collects data on 
various parameters of the water distribution network, such as motor characteristics (speed, direction, vibration) and 
environmental conditions (temperature and humidity). The collected data is transmitted over WiFi to AquaFlow’s 
central server, where it is analyzed to provide real-time insights and alerts for the maintenance team. This data helps 
in predictive maintenance, reducing downtime and ensuring efficient water distribution.


## Attackers (<span style="color:red">Red team:</span>): 

A group of hackers, hired by a competitor, is attempting to infiltrate AquaFlow’s network to steal their innovative 
technology. The hackers are aware of the following details:

- AquaFlows office address and distribution centers where IoT devices are deployed. 

- AquaFlow has an external-facing website with contact information for several employees.

- AquaFlow provides a login portal for partners and staff to access their systems and data.

- Jane Doe, an AquaFlow contractor from the UK, accesses the remote VPN from her personal laptop. She often 
works at a local coffee shop with public WiFi.

- Several AquaFlow employees mentioned on the website have posted about attending the upcoming Summer 
Training at University of Greenwich in London.

## Defenders (<span style="color:blue">Blue team:</span>):

AquaFlow has brought you as security consultants to evaluate their current network and IT systems. They would like to 
know how to defend their network and wider systems against cyber threats (e.g., physical attacks, social engineering 
attacks etc.

<table>
<tr>
<td>

<span style="color:blue">Blue team:</span> The task of the consultants is to identify some defences that will help prevent or even detect semantic 
attacks on the AquaFlow infrastructure.

<span style="color:red">Red team:</span> The task of the hackers is to identify potential attacks that may threaten AquaFlow.

Create Blue and Red teams of at least 2 members and: 

❖ For both teams: identify and discuss potential attacks and how they impact confidentiality, integrity and 
availability principles. 

<span style="color:red">❖ For Red team: identify how to attack (including methods you learnt today).</span>

<span style="color:blue">❖ For Blue team: how you could prevent the attacks. You do not need to refer to actual countermeasures</span>

</td>
</tr>
</table>
# FILE: predicitiveMaintenance.py
# AUTHOR: Seb Blair (CompEng0001)
# Version: 1.0.0
# NOTES: script requests the data over HTTP and then writes the data to a specified location. 

import requests
import csv
import os
import sys
from datetime import datetime
import time

# The path to the data log
data_log_csv = '/home/rock/predictiveMaintenance/data.csv'

# delay
# adjust in seconds so 1.5 = 1500ms, 0.5 = 500ms, 0.25 = 250ms and so on...
delay = 0.5

# run forever, or until program is killed
while True:
    try:
        # Perform a GET request from the ESP8266
        r = requests.get('http://192.168.4.1/sbc')

        # Decode the respsonse and split by the delimeter ','
        data = r.content.decode("ascii").split(',')
        
        print(data)

        # Prepend the time stamp with microseond precision
        timestamp= datetime.now().isoformat(timespec='microseconds')
        data.insert(0, timestamp)

        print(len(data))

        # Check message is correct length (timestamp + data)
        if len(data) == 11:
            # Check if file exists, if not, create it or failing close program
            if not os.path.exists(data_log_csv):
                with open(data_log_csv, mode='w', newline='') as file:
                    writer = csv.writer(file)

                    # Set first row headers
                    writer.writerow(['TimeStamp','TMP36_Temp', 'DHT11_Ambient_Temp','DHT11_Humidity','Motor_Temperature','Motor_Speed_(RPM)','Motor_State','Accel_x-axis','Accel_y-axis','Accel_z-axis', 'RMS_Vibration'])

            # append csv with the data        
            with open(data_log_csv, mode='a', newline='') as file:
                writer = csv.writer(file)
                writer.writerow(data)

        # add delay
        time.sleep(delay)

    # any exceptions are caught and returned to the CLI
    except Exception as e:
        print(f"Error: {e}")
        print("Unble to create or write to the CSV file. Progam will now exit")
        sys.exit(1)

# End of Script
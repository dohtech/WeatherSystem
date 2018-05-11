import serial
import simplejson as json

serial = serial.Serial('COM3', 9600)

while True:
    line = serial.readline().decode('utf-8')
    
    #.decode('utf-8')
    #print(line)
    weatherReading = json.loads(line)
    print(weatherReading)

    #data = ser.readline().strip('\n\r').decode('utf-8')
    #j = json.loads(line)
    #print(data)

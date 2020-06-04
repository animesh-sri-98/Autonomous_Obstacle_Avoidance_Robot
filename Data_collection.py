import datetime 

import time

from gpiozero import DistanceSensor

import RPi.GPIO as GPIO  ## GPIO STANDS FOR GENERAL INPUT OUTPUR PIN

from flask import Flask,render_template,request



GPIO.setmode(GPIO.BOARD)

GPIO.setwarnings(False)

app = Flask(__name__)  ## flask begin syntax



TRIG=29  ## seting variables

ECHO=31

IRL=33

IRR=35



GPIO.setup(TRIG,GPIO.OUT)  ## general pin for input output mai trgiger ko output mai set 

GPIO.setup(ECHO,GPIO.IN) ## ECHO IS INPUT

GPIO.setup(IRL,GPIO.IN) ## INFRARED LEFT SPEED IS ALSO INPUT 

GPIO.setup(IRR,GPIO.IN)      ## INFRARED RIGHT SPEED IS ALSO INPUT
## THE CONCEPT IS KI LEFT AND RIGHT TYRES PE INFRARED RAY HAI AND VO CUT HOTI HAI AND INPUT HOTI HAI AND THAT TELLS ABOUT THE ROUND PER MIN SPEED OF THE TYRE.



@app.route("/")

def main():

	return render_template('index.html') ## loading the temp from the index files that contains the html thing



@app.route("/readValue")

def sendValues(): ## ab html mai ek nya web page khulega and jo ki localhots/readvalue hoga mtlb app yaha redirect hogi ##  ie colllecting values through this function

	file=open("DataLog.txt",'a') ## data ki file open hogi vha jo ki blank hai

	IRL_Value=str(GPIO.input(IRL))  ## GPIO ki input jo haai infrared Left ki vo string mai convert hogi

	IRR_Value=str(GPIO.input(IRR))

	US=str(ultrasonic())

	Speed=speed(datetime.datetime.now())   

	LS=Speed[Speed.index("L=")+2:Speed.index(" ")]    

	RS=Speed[Speed.index(" ")+3:]

	value="RPM of Left Motor:"+LS+" RPM of Right Motor:"+RS+" Ultrasonic Distance:"+US  

	file.write(str(datetime.datetime.now())+" "+value+"\n")

	ServerValues=RS+"#"+LS+"%"+US

	print(ServerValues)

	return ServerValues



def speed(T):

	stateL=GPIO.input(IRL)       

	stateR=GPIO.input(IRR)

	countL=0

	countR=0



	while (datetime.datetime.now()-T).total_seconds()*1000<500:     



		if GPIO.input(IRL)==1-stateL:    

			countL+=1

			stateL=1-stateL

		if GPIO.input(IRR)==1-stateR:

			countR+=1

			stateR=1-stateR



	speedL=countL*15    

	speedR=countR*15 

	return "L="+str(speedL)+" R="+str(speedR)   



def ultrasonic():

	GPIO.output(TRIG,False)  

	time.sleep(0.0002)

	GPIO.output(TRIG,True)

	time.sleep(0.00001)

	GPIO.output(TRIG,False)

	while GPIO.input(ECHO)==0:    
		pulse_start=time.time()

	while GPIO.input(ECHO)==1:

		pulse_end=time.time()

	pulse_duration=pulse_end-pulse_start 

	distance=pulse_duration*17150   

	distance=int(round(distance,2))   

	if distance>400:



		distance=400

	return distance



if __name__=="__main__":    Finally running the app

	app.run(host='0.0.0.0',port=8000,debug=True)

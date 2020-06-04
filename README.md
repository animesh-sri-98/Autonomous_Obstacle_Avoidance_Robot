# AUTONOMOUS OBSTACLE AVOIDANCE ROBOT USING LINEAR REGRESSION
Obstacle avoidance is considered as one of the main features of autonomous intelligent systems. There are various methods for obstacle avoid-ance. In this paper, obstacle avoidance is achieved by the difference between left wheel velocity and right wheel velocity of differential drive robot. The magnitude of difference between the wheel velocities is used to steer the robot in correct direction. Data is collected by driving the robot manually. Ultrasonic sensors are used for distance measurement and IR sensors are used to collect the data of wheel velocities. This data is used to build a linear machine learning model which uses sonar data as input features. The model is used to predict the wheel velocities of the differential drive robot. The model built is then pro-grammed into Atmega328 microcontroller using Arduino IDE. This enables the mobile robot to steer itself to avoid the obstacles. Since all the components used for this robot are highly available and cost effective, the robot is economically affordable.
## 1. Methodology
In the proposed method, ultrasonic sensors are used to collect data related to range of the obstacles and IR sensors to measure the wheel velocities. Unlike other methods we use the collected data to build a machine learning model, which takes ultrasonic sensor data as input feature and predicts the left wheel velocity and right wheel velocity.The entire process of building the autonomous obstacle avoidance robot is divided into three phases as shown in fig 1.
![fig1](https://user-images.githubusercontent.com/33247732/83721894-a17f5c00-a659-11ea-98d5-b029f881b711.JPG)
Data is required to build a machine learning model to achieve obstacle avoidance. We used two sensors for collecting the data. They are ultrasonic sensor and IR sensor. The two sensors are placed on the mobile robot. Raspberry pi is used to collect the data from these sensors.
The ultrasonic sensors are used to collect the range of obstacles in front direction. IR sensors are used to collect the rpm of left wheel and right wheel. Rpm values can be converted to into speed in metres per second using formula 1.
![formula](https://user-images.githubusercontent.com/33247732/83722278-59146e00-a65a-11ea-9516-72aba15ab214.JPG)

![fig2](https://user-images.githubusercontent.com/33247732/83721901-a3491f80-a659-11ea-99cd-ad37020fdba5.JPG)

The circuit diagram for the sensors and raspberry pi shown in the fig 2. Note that the Ultrasonic sensors is placed in the front side of the mobile robot and IR sensors are placed facing towards the wheels of the mobile robot as shown in the fig 3.

![fig3](https://user-images.githubusercontent.com/33247732/83721916-a93f0080-a659-11ea-8372-63b43cf9100c.JPG)

The mobile robot is controlled by NodeMCU[10]. The DC motors of the mobile robot are connected to NodeMCU as shown in fige 4. The circuit diagram for the DC motor connections with NodeMCU is shown in fig 4.
![diagram](https://user-images.githubusercontent.com/33247732/83721891-a04e2f00-a659-11ea-87ec-d37684776672.JPG)

NodeMCU is connected to a mobile app which controls the mobile robot by chang-ing the wheel velocity from the app. This helps in the manual training of the robot. The app which controls the mobile robot during training phase is should in figure 5.The android application can be built using MIT app inventor tool[11]. The connec-tions of android app and Nodemcu is shown in figure 6.

![fig5](https://user-images.githubusercontent.com/33247732/83721921-aa702d80-a659-11ea-9120-c7e4cd4d4b87.JPG)

![fig6](https://user-images.githubusercontent.com/33247732/83721924-aba15a80-a659-11ea-8eea-660d36a9870c.JPG)

Algorithm to train the mobile robot manually and the collect the sensor data:
1. Turn on the mobile robot by powering it with a battery or a power bank.
2. Connect to the mobile robot from the android application by using the IP address of NodeMCU.
3. Control the movement of the mobile robot manually by using the android appli-cation.
4. Avoid obstacles by controlling the mobile robot only in one direction i.e. either left or right. Here let us choose right direction only.
The data collected during the training phase is stored as a dataset in raspberry pi. The features stored in the dataset include obstacle distance in centimetres, left wheel speed and right wheel speed in terms of rpm. The sample dataset is shown in table1.

![fig7](https://user-images.githubusercontent.com/33247732/83721927-acd28780-a659-11ea-806d-5710345ab652.JPG)

The dataset collected from the training phase is used to train the linear regression model. The input features for the training model is object range. We use this single feature to predict the left wheel velocity and right wheel velocity of the mobile robot. The flowchart for model building phase is shown in fig 8.
The machine learning model used for predictions is linear regression model. We use a simple linear model of degree ‘ d ‘ to predict the left wheel velocity and right wheel velocity. The model used for the velocity prediction is shown below.
Model equations for wheel velocity :
![formula2](https://user-images.githubusercontent.com/33247732/83722812-42bae200-a65b-11ea-8b19-28377c1c38da.JPG)

V[l] = velocity of the left wheel
V[r] = velocity of the right wheel.
Where w0 , w1 ,w2 ... wd , w’0 , w’1 , w’2 ... w’d are the parameters of the model which are found out using stochastic gradient descent algorithm. Psuedo inverse algo-rithm can also be used to find out the weights ‘ w ‘. The equation to find out w using stochastic gradient descent algorithms is shown below.
Update rule for weights in stochastic gradient descent :
![formula3](https://user-images.githubusercontent.com/33247732/83723030-9e856b00-a65b-11ea-8587-e31b660b984f.JPG)
where ‘η’ is a chosen parameter called learning rate which varies between 0 and 1 and dw[i] is the gradient of the error function corresponding to the weight w[i].By iteratively updating the weights the error function is minimized and the optimal weights are found out for the model.The final model obtained by the optimal weights can be used in the mobile robot to achieve the obstacle avoidance algorithm.The other way to find the weights of the model is using the psudo inverse algorithm shown in figure 8.

![fig8](https://user-images.githubusercontent.com/33247732/83723174-dab8cb80-a65b-11ea-8c41-16a0675957fb.JPG)

## 2. Obstacle Avoidance Algorithm

There are three ultrasonic sensors placed on the mobile robot during testing phase on the front, left and right side.
The obstacle avoidance algorithm for the mobile robot is shown below:
1. Read the distance value from front side ultrasonic sensor of the mobile robot.
2. If the distance is greater than 25cm set the left wheel velocity and the right wheel velocity of the mobile robot as follows, otherwise go to step 3.
V[l] = V[r] = 1000
Here 1000 is the pwm value sent to the DC motors.
3. If the distance is less than 25cm then read the distances values of ultrasonic sensors from left and right side of the mobile robot.
dl = left side distance of the obstacle
dr = right side distance of the obstacle
    (a) If dl < 10cm and dr > 10 cm then the robot should turn right side . We use the machine learning model to calculate the wheel           velocities using right turn model.
    (b) If dl > 10cm and dr < 10 cm then the robot should turn left side. We use the machine learning model to calculate the wheel             velocities using the right turn model and interchange the left and right wheel velocities.
    (c) If dl <10cm and dr < 10 cm the robot turns backwards. We set one of the wheel velocity to 0 and the other wheel velocity to             1000 for 2 seconds to turn the mobile robot in the backward direction.
The robot avoids the obstacle by changing its direction based on the magnitude of difference between the left wheel velocity and right wheel velocity. Thus obstacle avoidance is achieved using the given object avoidance algorithm.

## 3. Implementing obstacle avoidance
The circuit for implementing the autonomous mobile robot is shown in fig 9.
![fig9](https://user-images.githubusercontent.com/33247732/83721942-b1973b80-a659-11ea-8bc2-62addd959b07.JPG)

The Arduino board[9] contains the code for implementing the linear regression model by substituting the distance value of the ultrasonic sensors. The arrangement of sensors over the mobile robot should as shown in fig 3.

## 4. Results and analysis

The accuracy of the obstacle avoidance model depends on the accuracy of training data collected during training phase. The model built using degree 3 linear equations performs better than the degree 2 model. The algorithm used is very simple to imple-ment. The time complexity of the algorithm to predict the wheel velocities is O(1). We get the prediction instantaneously which makes it suitable for real time obstacle avoidance.
The testing phase of the robot is shown in fig 10 and fig 11.

![fig10](https://user-images.githubusercontent.com/33247732/83723771-cc1ee400-a65c-11ea-9f62-f3cba31627a8.JPG)

![fig11](https://user-images.githubusercontent.com/33247732/83723793-d640e280-a65c-11ea-9763-7bd01ec56861.JPG)

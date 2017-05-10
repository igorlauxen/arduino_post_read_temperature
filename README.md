# HCP IoT Prototype

## First steps

- Connect your **Arduino yun** to the cable
	- This will make it connect to the corporate
- Check its mac address and create an exception [here](https://nac-exception.wdf.sap.corp)
- Remove the proxy from your arduino
	- Go to the Arduino IDE
	- Select File > Examples > Bridge > YunSerialTerminal
	- Upload the code to your arduino
	- Access your arduino by [Putty](http://www.putty.org/)
		- To access you must check the **Port** that your arduino is connected
		- Then in the putty select the Serial option
		- Change the Serial Line according the **Port**
	- Execute the following command:
	```   
	export http_proxy=http://proxy.wdf.sap.corp:8080
	export https_proxy=http://proxy.wdf.sap.corp:8080 
	```
- Change the following variables from CurlPost.ino file with the information from your HCP IoT:
	- INUMBER_TRIAL: your inumber
	- DEVICE_ID: device id from the device that you have registered in your application (HCP IoT)
	- MESSAGE_TYPE: message type id from the message type that you have registered in your application (HCP IoT)
	- USER_AUTHENTICATION: your user:password but converted in basic 64. Use [postman](https://www.getpostman.com/) to generate this.

## How to see the data in HCP IoT

- Go to your HCP IoT launchpad
- Click Display Stored Messages tile
- Select T_IOT_HTTP_PUSH
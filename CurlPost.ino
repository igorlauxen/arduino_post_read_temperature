#include <Bridge.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
#include <BridgeSSLClient.h>
#include <BridgeUdp.h>
#include <Console.h>
#include <FileIO.h>
#include <HttpClient.h>
#include <Mailbox.h>
#include <Process.h>
#include <YunClient.h>
#include <YunServer.h>

/*

Tests over tests

*/

#include <Process.h>

//services setups       
String URL_TO_SERVICE = "https://iotmmsi841640trial.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/push/4328715f-0b9f-4cd0-8ea9-8933d8addb26";
String MESSAGE_TYPE = "a5e26c45db88d556aef1";
//basic 64
String USER_AUTHENTICATION = "Basic aTg0MTY0MDpRYVJ1bGV6MjJA";
//entries
int CALOR_TEST = 5000;
int PRESSAO_TEST = 32;
String SENDER = "Arduino Yun";

// Everytime you reset your arduino, you need to reset your proxy again
/*
export http_proxy=http://proxy.wdf.sap.corp:8080
export https_proxy=http://proxy.wdf.sap.corp:8080 
*/


String createCurlCommand (String url, int calor, int pressao, String sender, String authentication, String messageType) {
    
  String curlCmd = "curl ";
  //header parameters
  curlCmd += "-iv --raw -k --insecure -H  \"Authorization: "+ authentication +"\" ";
  //type of request
  curlCmd += " -X POST ";
  //body parameters 
  curlCmd += "-d '{";
  curlCmd += " \"method\": \"http\" ,";
  curlCmd += " \"messageType\": \"";
  curlCmd += messageType;
  curlCmd += "\", ";
  //start messages
  curlCmd += " \"messages\":[{";
  curlCmd += "\"heat\":\"";
  curlCmd += calor;
  curlCmd += "\"";
  //close messages
  curlCmd += "}],"; 
  curlCmd += "\"sender\":\"";
  curlCmd += sender;
  curlCmd += "\"";
  //close -d
  curlCmd += "}' ";
  //backend url
  curlCmd += url;
  return curlCmd;
}

void post(){
  String curlCmd = createCurlCommand( URL_TO_SERVICE, CALOR_TEST, PRESSAO_TEST, SENDER, USER_AUTHENTICATION, MESSAGE_TYPE );
  Serial.println("Curl Cmd Command being saved: ");
  Serial.println(curlCmd);
  Process process;
  process.runShellCommandAsynchronously(curlCmd);

  while (process.running()){
    Serial.println("Running process");
    while (process.available()>0) {
      char c = process.read();
      //Serial.println(c);
    }
    Serial.println("\n");
    Serial.println("########################################");
  }
}

void setup(){
  //post();
  Bridge.begin();
  while(!Serial);
  Serial.println("Starting...");
}

void loop(){
    Serial.println("Inside loop() \n");
    post();
    //delay(5000);
}

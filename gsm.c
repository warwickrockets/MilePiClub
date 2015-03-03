int8_t answer;
int onModulePin = 2;
int button = 12;
char aux_str[30];

char phone_number[]="+447477688673";     // ********* is the number to call

void setup(){

    pinMode(onModulePin, OUTPUT);
    pinMode(button, INPUT);
    Serial.begin(115200);      
    
    Serial.println("Starting...");
    power_on();
    
    delay(3000);
    
    // sets the PIN code
    sendATcommand("AT+CPIN=****", "OK", 2000);
    
    delay(3000);
    
    Serial.println("Connecting to the network...");

    while( (sendATcommand("AT+CREG?", "+CREG: 0,1", 500) || 
            sendATcommand("AT+CREG?", "+CREG: 0,5", 500)) == 0 );

    sprintf(aux_str, "ATD%s;", phone_number);
    sendATcommand(aux_str, "OK", 10000);
    
    // press the button for hang the call 
    //while(digitalRead(button)==1);        
    delay(10000);
    Serial.println("ATH");            // disconnects the existing call
    

}

void loop(){

}

void power_on(){

    uint8_t answer=0;
    
    // checks if the module is started
    answer = sendATcommand("AT", "OK", 2000);
    if (answer == 0)
    {
        // power on pulse
        digitalWrite(onModulePin,HIGH);
        delay(3000);
        digitalWrite(onModulePin,LOW);
    
        // waits for an answer from the module
        while(answer == 0){     // Send AT every two seconds and wait for the answer
            answer = sendATcommand("AT", "OK", 2000);    
        }
    }
    
}

int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout){

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '\0', 100);    // Initialize the string
    
    delay(100);
    
    while( Serial.available() > 0) Serial.read();    // Clean the input buffer
    
    Serial.println(ATcommand);    // Send the AT command 


    x = 0;
    previous = millis();

    // this loop waits for the answer
    do{
        if(Serial.available() != 0){    
            // if there are data in the UART input buffer, reads it and checks for the asnwer
            response[x] = Serial.read();
            x++;
            // check if the desired answer  is in the response of the module
            if (strstr(response, expected_answer) != NULL)    
            {
                answer = 1;
            }
        }
         // Waits for the asnwer with time out
    }while((answer == 0) && ((millis() - previous) < timeout));   

    return answer;
}

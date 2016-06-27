//TODO: Timmer before game over.

int led[] = {12,11,10,9};
int buttons[] = {7,6,5,4};

long randomNumber;

bool lightOff = true;
int buttonDown = -1;//Arbitrary value

int score = 0;
int timeInterval = 5000


#define SPEAKERPIN 8
 
/* Frequencies for musical scale notes */
#define NoteC1 262
#define NoteD1 294
#define NoteE1 330
#define NoteF1 349
#define NoteG1 392
#define NoteA1 440
#define NoteB1 494
#define NoteC2 523
 
/* Store a set of notes to play */
static int Song[] = {NoteC1,NoteD1,NoteE1,NoteF1,NoteG1,NoteA1,NoteB1,NoteC2,NoteC2};
 
/* Indexes the next note to play */
byte Index;

void setup()
{
  for (int i=0;i<4;i++)
  {
    pinMode(led[i], OUTPUT);
    pinMode(buttons[i], INPUT);
  }

  randomSeed(analogRead(A0)); // Pull random analog value from pin noise

 

  pinMode(SPEAKERPIN, OUTPUT); 
  digitalWrite(SPEAKERPIN, LOW);


  Serial.begin(9600);

}

void loop()
{
  gameLogic();

}

void gameLogic(){
 if(lightOff){
  lightOff = false;
  //Randomly turn on. 
  randomNumber = random(4);
  digitalWrite(led[randomNumber],HIGH);
 
 }
//wait for button push. // Button down
 if (digitalRead(buttons[randomNumber])==HIGH) 
    {
      buttonDown = randomNumber;
    }

    // Button up
   if (digitalRead(buttons[buttonDown])==LOW && buttonDown != -1) {
     //Turn Off Light
     digitalWrite(led[randomNumber],LOW);
     lightOff = true;
     score++;
     buttonDown = -1;
     delay(100);
   }


  for (int i=0;i<4;i++)
  {      
      if (digitalRead(buttons[i])==HIGH  && i != randomNumber) 
      {
        Serial.print(i);Serial.print(" blaB random "); Serial.println(randomNumber); //send the string “hello” and return the length of the string.
      //Turn Off Light
       digitalWrite(led[randomNumber],LOW);
        //Buzz 
          /* Play each note in sequence */
              for(int k = 0; k < 5; k++)
            {
                /* Output the current note to the speaker for 500ms*/
                tone(SPEAKERPIN, Song[k]) ;
                delay(200);
             }
              /* Stop playing the last note */
              noTone(SPEAKERPIN);
            
        //Display Score
        blinkLight(200);
        //Reset game on any Button push.
        resetGame();
      }
    }
}

void resetGame(){
  lightOff = true;
  //resetScore
  score = 0;
}

void blinkLight(int blinkTime){

    for(int i = 0; i <score; i++){
      for(int k =0; k <4; k++){
               
        delay(blinkTime *2);
        digitalWrite(led[2],HIGH);
        delay(blinkTime);
        digitalWrite(led[2],LOW);
        delay(blinkTime);
      }

    }
     delay(2000);
}


#include <SD.h>
#include <serialStr.h>
#include <eventLog.h>

#define SD_CS     4           // My chip select choice was 4, that's pretty typical. But yours may be different.

serialStr cmdMgr;             // Create a serialStr object to bring in commands & test log strings.
eventLog  ourEventLog;        // The eventLog object. Remeber this was for testing eventLog?

void setup() {
   
	Serial.begin(9600);													// Fire up serial port.									
	if (!SD.begin(SD_CS)) {												// Fire up SD drive.
		Serial.println("NO SD CARD!");								// If fail? Tell user.
		while(1);															// Lock process.
	}																			// Have SD Drive.
	if (!ourEventLog.begin("/logTest.txt")) {						// Fire up the event log.
		Serial.println("Event log failed begin() call.");		// On fail, tell user.
		while(1);															// Lock down process.
	}																			// I guess we're still good to go..
	cmdMgr.setCallback(newCommand);									// Set callback function for incoming strings.
	ourEventLog.setLogging(true);										// Fire up the logging.
	Serial.println("Type in a string to log it.");				// Tell user what's up.
	Serial.println("Type ? for list of commands.");				//
}


// Complete strings come in here. First we see if we can make a command out of them.
// If not, we log them.
void newCommand(char* inCmd) {

   File  logFile;
   int   numBytes;
   
   if (!strcmp(inCmd,"?")) {												// We see a "?", print out instructions.
      Serial.println("Well, first is \"?\" to print this.");
      Serial.println("Type \"show\" to print the datafile to the monitor.");
      Serial.println("Type \"stop\" to shut down logging.");
      Serial.println("Type \"start\" to turn on logging.");
      Serial.println("Type \"clear\" to clear out the logfile.");
      Serial.println();
   } else if (!strcmp(inCmd,"show")) {									// Else we got "show". print out the logfile.
      Serial.println("Reading log file.");
      logFile = SD.open(ourEventLog.getPath(),FILE_READ);
      if (logFile) {
         Serial.println();
         numBytes = logFile.size();
         for (int i=0;i<numBytes;i++) {
            Serial.print((char)logFile.read());
         }
          Serial.println();
      }
      Serial.println("Complete.");
   } else if (!strcmp(inCmd,"stop")) {									// Else we got "stop". Stop logging.
      ourEventLog.setLogging(false);
      Serial.println("logging has been turned off.");
   } else if (!strcmp(inCmd,"start")) {								// Else we got "start". Fire up logging again.
      ourEventLog.setLogging(true);
      Serial.println("logging has been resumed.");
   } else if (!strcmp(inCmd,"clear")) {								// Else we got "clear". Delete the log file.
      ourEventLog.deleteFile();
      Serial.println("Logfile has been deleted.");
   } else {																		// Else.. Well, anything else we just log it.
      if (ourEventLog.addEvent(inCmd)) {              			// If we can log the string.
          Serial.print(inCmd);                        			// Show us what we logged.
          Serial.println(", added to event log.");					// And that we logged it.
      } else {																	// Else..
          Serial.println("No data added.");           			// Show that we couldn't log it for some reason.
      }
   }
}


void loop() {

  idle();     // Always call idler() first.
}
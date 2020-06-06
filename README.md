# LC_eventLog
Handy bit of code that allows c strings to be logged with series number and seconds in series. (For logging events, you know.)  

**Series number :** Every time a logger starts a new session, it opens its log file, locates the last series number, increments that series number by one, and saves it back to the file. From now until that session is turned off, either by software or power loss, that is the series associated with its logged events.

**Seconds :** Whenever any logging session is active, there can be multiple event logging sessions at once, the first logging session started initializes the second timer to 0. Meaning that your seconds should line up between different concurrent logging sessions. Although the series numbers may not.

**User string :** The user string to be logged must be a c string. IE. NULL terminated text. Now, the user string can be anything the user wants, but.. The format of the string it will be inserted into is :  

```series number [tab] seconds [tab] user string [/n]```  

Now, if the user would like to format her string with data separated by [tab] characters '\t'. The entire logged file can be easily read by your garden variety spreadsheet. Just a thought.

**How accurate is seconds ?** Well, it depends on your processor and how accurate it's microsecond clock is. Some are not so hot. If you need precise time accounting, add a real time clock to your hardware and stuff a timestamp into your user data.

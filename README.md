## Project title
Shoebox Race Car

## Team members
Jael Lopez-Saucedo , Lauren Owens

## Project description
This project is a race car simulator where the user can control a car avatar with a steering wheel, implemented with a potentiomter. The user can start the game with a gas pedal, also equipped with a potentiometer. As the user moves the car, they can collect mangoes (tokens) to increase their score. If they hit a obstacle (red mango), they will die and a finish screen will be triggered. Throughtout the game, a race car sound will be playing to add to user experience.

## Member contribution
Jael - Implemented the steering wheel potentiometer, detection of collisions of car objects with mangoes and obstacles, Score functionality, Time Functionality
Lauren - Implemented the graphics library, gas pedal and potentiometer, game functionality (start screen, stop screen), game struct and updating member variables across functions, code design

## References
Pole Position - Nintendo, 1982 : We took inspiration from this classic arcade game to implement our own game. 
3D Model for Pedal (https://www.thingiverse.com/thing:4300675/comments) - We used this file to 3D print the pedal. 
Averaging Potentiometer Readings (https://www.eevblog.com/forum/projects/stabilizing-analog-read-on-a-potentiometer/) - I tried this method to average and process the potentiometer readings correctly.
CS 107E Staff - Many thanks to Ishita, Ben, and Professor Gregg for suggesting design decisions such as discretizing the locations, triggering the falling of the mangoes and obstacles, and sound and mcp3008 libraries from the 107E modules.


## Self-evaluation
We were able to reach most of our core goals as well as some of our stretch goals. We were not able to use the gas pedal potentiometer to control speed. Lauren attempted to implement this by reading the values of the gas pedal potentiometer and update a tick count member variable to control how fast the screen was updating. However, due to the structure of the 3D model, the potentiometer kept shifting, making it difficult to receive accurate readings. Also, if we had more time, we would have liked to incorporate a double buffer for more seamless updating of the car position and faster updating of the score, time, and speed. 
However, we were very proud of incorporating sound into the project. Jael was able to play the race car sound as the game is playing. If given more time, we would have liked to implement sounds for coin collecting and obstacle collisions. We were also proud of incorporating two potentiometers to read two different values. In summary, we are very proud of being able to get the core functionality of the racing game from start screen to end screen. Incorporating the sensor data and collision detecting required a lot of effort and we are proud of being able to incorporate these together for a traditional video game user experience. To add to this user experience, we are proud of using 3D printed models, which we were previously unfamiliar with, to add to the user interface. This project also allowed us to think critically and build upon course knowledge about graphics, reading and manipulating data from the Pi, and system design. 

## Photos
We unfortunately did not take photos and videos before we took the system apart. Please refer to demo video. 


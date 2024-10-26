Game Info:

Pressure Plate game. 

The game will open to a set of black squares and a closed door. The squares represent the pressure plates. 

Tapping a correct plate in the sequence will change its colour to green. Tapping an incorrect one will change it to red. 

Once the puzzle is completed, the 'New Puzzle' button will become visible, and the door will change to look 'Open'

The puzzles are generated randomly, between 3-10 pressure plates.

To reduce implementation time, I decided not to animate anything and have no hud.


Libraries Used:
SDL2 2.30.8
SDL2 TTF 2.22.0

IDE Used:
Visual Studio Community Edition 2022


How to run the game:

Open Release/game/Redly.exe

I've included the libraries in the Redly/resources folder. If for some reason the game won't run, I had the libraries installed at a C:\vclib folder, with environment variables setup to point to those libs.
I've included a screenshot of what it should look like when it loads up, with the door image etc.


Design decisions:

I went with a minimum of 3 plates, and a max of 10. The maximum could have been set higher, but I thought this was a good range to meet the assignment requirements.

Once the plate count is determined, the plate indices are put in a list and randomly pulled from (while removing the selected item) to determine the random solution order.

Pressure plates are just rectangles, to avoid needing to find free images online for the 3 states. I am displaying the states as black/red/green to mean: inactive/invalid/valid selections.



Challenges Faced:

I've never use SDL before, so I had to get it installed and learn how to set it up, render elements to the screen and handle mouse input. I also encountered some issues with rendering text, until I learned there's a separate library for that. Which is why I'm using the SDL2 TTF lib as well for this project.

I used the SDL2 library, as that was the only version of SDL I could find that had a Visual Studio library I could use. Hopefully that's ok.


Future Expansion Ideas:

- have the 'incorrect' plates show an animation (eg: blink red for a moment) rather than stay red
- Track attempts (incorrect clicks) and add a Star-Rating system for how many attempts a puzzle took. 
- Difficulties with ranges of fewer to more plates 
- a defined list of puzzles and a selection screen, so they can be replayed easily.
- a timer the puzzle needs to be completed in, to ramp up difficulty
- better UI, and images rather than colours for the plates

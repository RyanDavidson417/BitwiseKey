# Bitwise Key

A solo project of mine to develop a small scale indie game inspired by roguelike and metroidvania elements, still a work in progress.

## Description
Most mashups of the two genres have abilities the player collects on a single run, which then persist between runs and provide a form of inter-run progression. However, I wanted to create a game in which the ability based progression of metroidvanias changes within the randomized, repetative nature of roguelikes. The final product will have four collectible abilities which spawn in randomized locations across the map, leaving players to decide the order in which they want to explore the map and collect the abilities. These abilities will make exploration of the first level easier and faster, and will be necessary to unlock and explore the second level to the end of the game.

## Current features
So far, I have a solid foundation of much of the gameplay mechanics. Including player movement, simplistic enemy behavior, and substantial infrastructure for gameplay progression. This last point includes the implementation of two of the four planned abilities, the ability to reset the current run, and randomized placement of the abilities throughout my initial map design. 

To view these current features, feel free to view the playable release exe file on the development branch. But please be aware that this project is actively in progress. While I wanted my work to be viewable somewhere as soon as possible, there's a reason this is still only on github rather than itch.io or a personal website. For further details on my plans for future features, polishing, and everything else that'll make this game feel fun, please see the Future Plans section below.

A more specific list of the currently implemented features:
- Player is able to spawn in at the center of the map. They will be able to view a timer which does not start until the player provides input (either by looking around or moving).
- 2 pods spawn at 2 of 4 randomized locations throughout the map, each with their own unique colors. The player can interact (E) with these pods to collect them and unlock new abilities.
  - The green pod unlocks X-ray vision, enabling a particle effect on fake walls throughout one room of the map, and allowing players to pass through them.
  - The blue pod unlocks invisibility, allowing players to manually activate it and disable detection by the enemy AI. Players have a limited amount of "charge" they can use to power the invisibility, which will recharge when not in use.
- In addition to the starting room, there are currently a total of three rooms, each heavily associated with each ability
  - The maze contains fake walls, which can be detected and passed through when the player has x ray vision
  - A room with an enemy in it, which is far easier to pass through then the player can turn invisible
  - A platforming room will have a shortcut which will only be accessible with a third ability (Wall Cling, detailed in the following section)
- At any given point, the player can press R to reset the game. This will spawn them back in the center of the map, reset the timer, remove their abilities, and re-randomize the placement of the abilities throughout the map


## Future Plans
This game is far from finished, while I'm proud of the foundation I have so far, I'm excited for my future plans for other features, polish, and elements of "juice" to make the game feel good.

### Features
Specific and concrete features that will expand the scope of what's currently possible within the game
- future abilities - the two other ideas I have for collectible abilities that will allow the player further ease in exploring the map
  - wall cling/jump - The player will be able to stick to certain surfaces and jump off of them. Rather than a wall climb/run, the player will only be able to slide down the wall or jump off of it, akin to the wall climb abilities in 2d metroidvanias such as Hollow Knight or Dead Cells.
  - Teleportation - the player will be able to teleport between set pairs of points throughout the map.
- Expanded map/level design - Currently there are only 3 rooms, and those are also very simplistic in design.
  - I intend to add 1 more room to the starting level,
  - Given that the current room designs are very short and basic, I intend to expand them significantly. In addition to being longer, they'll likely incorporate the usage of multiple abilities to provide different for which shortcut the player will take (though with well defined differences in that some shortcuts will be more effective than others, evenly spread out between each ability)
  - after the player collects all 4 abilities, they will be able to assemble the Bitwise Key, and begin the second level. Taking them to an obstacle course requiring the use of all four abilities.
- More robust randomization - in addition to randomizing the spawns of the abilities, I intend to add other tidbits of randomization to provide variance to the level design
  - this will utilize the same algorithm for randomization as the abilities, but will involve some restructuring of my code/inheritance patterns to be more easily replicable
  - some examples might include all but one route in the maze being blocked off by fake walls, with the passable route being different each time, or the locations of the teleportation pads.
- Creation of a main and pause menu

### Polish
Plans to improve the parts of the game that I already have, so as to make it more clean and enjoyable to play
- level appearance
  - while the "infected hex" material I'm using for most of my walls looks cool, it's a bit visually overpowering (and the emissive lighting is somehwat performance-heavy), I'll need to use a different material for most of my walls, with the "infected hex" being used more sparingly to catch the player's attention and guide the level progression.
  - styling each room
- AI
  - difficulty - Even without much expansion of the AI behavior tree, (which would fall closer to new features), tweaking the variables behind its movement speed, perception ranges, and other variables would go a long way to making the AI feel like a more dynamic challenge to the players
  - sounds - while The AI has sounds for when in the "patrol" and "chase" states, I'm still unsatisfied with the ones I've selected, as they feel tonally dissonant with the atmosphere of the game. I settled on the current ones for testing and placeholder purposes, but I certainly intend to revisit them
  - appearance - I intend to find a more fitting and unique skin for the enemies, rather than Unreal's manequin model.



### Juice
A step beyond polish, but not so far as new features, "juice" is what's used to refer to subtle elements of previous features to provide the game with that extra level of satisfaction and enjoyment 
- Improving the collection of the powerups - currently the power ups simply play a sound and deactivate upon collection. I want to make this feel like a noteworthy moment and make the player feel rewarded by emphasizing the changes to the player and the world around them when the ability is collected
  - fading the powerup out gradually rather than destroying it instantly
  - particle effects that play when collecting the pods, as well as polish surrounding the destruction of the model
  - a way for the world to respond to their destruction/collection. Perhaps having the walls/surrounding lights flash with the color associated with the ability
- player movement - tweaking the variance between player starting speed and max speed, as well as their acceleration will result in a more robust movement system that will provide a satisfying but approachable (and optional) field in which player skill can develop.
- HUD
  - Currently I'm simply displaying the abilities in a 2x2 grid, redesigning that portion of the hud to look like an actuual physical key could help affirm the in-universe justification that these are being used to unlock the next level
  - the current Timer's appearance is very simplistic and unrefined. I'll work to fit it better with the rest of the games aesthetic style

## Support
If you find any glitches or major issues with the current release, or simply want to provide feedback, feel free to reach out to me at Ryan.davidson.417@gmail.com. Alternatively my discord handle is .ferrous. In any case I'd love to hear from you.

## Contributing
I'm not looking for any assistance in the programming, development, or design of this project, as I want it to be a clear demonstration of my abilities as a programmer and developer. That being said, I'd be more than happy to receive assistance to the artistic side of this project. Anyone who wants to contribute assets, models, or any music/audio to the project would be greatly appreciated, and I'll be sure to accredit you in turn.

## Credits
While I intend to include this within the game and accessible from the menus, in the meantime here is a list of sources from which I've been receiving the assets
Many of the materials, models, and other assets are from Unreal Engine's Starter content.     
Texures:
 - [ambientCG.com](https://ambientcg.com/) (CC0).
 
 Audio:
 - Power up collection from Rhoedesmas at [freesound.org](https://freesound.org/s/320655/) CC 3.0
 - Enemy patrol "scan" from [Gamesounds.org](https://gamesounds.xyz/?dir=Sonniss.com%20-%20GDC%202021-2023%20-%20Game%20Audio%20Bundle/BluezoneCorp%20-%20Combat%20Drone) ([license](https://gamesounds.xyz/Sonniss.com%20-%20GDC%202021-2023%20-%20Game%20Audio%20Bundle/License.pdf))
 - Enemy detect/chase: [Gamesounds.org](https://gamesounds.xyz/?dir=99Sounds/%5B99Sounds%5D%20Dark%20Engine/02_Feedback%20FX/05_Pitched) ([license](https://gamesounds.xyz/99Sounds/%5B99Sounds%5D%20Dark%20Engine/README.pdf))
 - Invisibility activate/deactivate: [Gamesounds.org](https://gamesounds.xyz/?dir=99Sounds/%5B99Sounds%5D%20Dark%20Engine/02_Feedback%20FX/05_Pitched)([license](https://gamesounds.xyz/Sonniss.com%20-%20GDC%202021-2023%20-%20Game%20Audio%20Bundle/License.pdf))
 
 Models:
 - powerup "pod" from [poly pizza](https://poly.pizza/m/hedSWVZx9E) CC 3.0
 
 Icons:
 - [invisibility ](https://game-icons.net/1x1/delapouite/invisible.html) and [x-ray vision (cyber eye)](https://game-icons.net/1x1/delapouite/cyber-eye.html) power up icons provided in b/w from [game-icons.net] (https://game-icons.net) CC BY 3.0

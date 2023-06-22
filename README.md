# Bitwise Key

A solo-developed indie game.

## Description
A work in progress solo development indie game drawing with metroidvania and roguelike elements. The final product will have 4 collectible abilities which spawn in randomized locations across the map, leaving players to decide the order in which they want to explore the map and collect the abilities, each of which will be useful as they explore further, and necessary to reach and explore the next level. 

## Current features
So far, I have a solid foundation of much of the gameplay mechanics. Including player movement, simplistic enemy behavior, and the infrastructure for gameplay progression. This last point includes the implementation of two of the 4 planned abilities, the ability to reset the current run, and randomized placement of the abilities throughout my initial map design. 

To view these current features, view the playable release, but please be aware that this project is actively in progress. While I wanted my work to be viewable somewhere, there's a reason this is still only on github rather than itch.io or a personal website. For further details on my plans for future features, polishing, and everything else that'll make this game stand out, please see the following section.

A more specific list of the currently implemented features:
- player is able to spawn in at the center of the map, they will be able to view a timer which does not start until the player provides input (either by looking around or movement).
- 2 pods spawn at 2 of 4 randomized locations throughout the map, each with their own emissive colors. The player can interact (E) with these pods to collect them and unlock new abilities.
  - the green pod unlocks X-ray vision, enabling a particle effect on fake walls throughout one room of the map, and allowing players to pass through them.
  - the blue pod unlocks invisibility, providing players with a recharging source of energy that they can then use to disable detection by the enemy AI
- in addition to the starting room, there are currently a total of three rooms, each heavily associated with each ability
  - the maze contains fake walls which can be detected and passed through when the player has x ray vision
  - A room with an enemy in it is far easy to pass through then the player can turn invisible
  - a platforming room will have a shortcut which will only be accessible with a third ability (detailed in the following section)
- at any given point, the player can press R to reset the game. This will spawn them back in the center of the map, reset the timer remove their abilities, and re-randomize the placement of the abilities throughout the map


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
- Improving the collection of the powerups
  - fading the powerup out gradually rather than destroying it instantly
  - particle effects that play when collecting the pods, as well as polish surrounding the destruction of the model
  - a way for the world to respond to their destruction/collection. Perhaps having the walls/surrounding lights flash with the color associated with the ability
- player movement - tweaking the variance between player starting speed and max speed, as well as their acceleration will result in a more robust movement system that will provide a satisfying  but approachable (and optional) field in which player skill can develop.
- HUD - Currently I'm simply displaying the abilities in a 2x2 grid, redesigning that portion of the hud to look like an actuual physical key could help affirm the in-universe justification that these are being used to unlock the next level

## Support
If you find any glitches or major issues with the current release, or simply want to provide feedback, feel free to reach out to me at Ryan.davidson.417@gmail.com

## Contributing
I'm not looking for anyone who wishes to contribute to the programing, development, or design of this project, as I want it to be a clear demonstration of my abilities as a programmer and developer. That said, I'd be more than happy to add variety to the artistic side of this project. Anyone who wants to contribute assets, models, or any music/audio to the project would be greatly appreciated, and I'll be sure to accredit you in turn.

## Credits
While I intend to include this within the game and accessible from the menus, in the meantime here is a list of sources from which I've been receiving the assets
Many of the materials, models, and other assets are from Unreal Engine's Starter content
Texures:
- ambientCG.com (CC0).
Audio:
- Power up collection: https://freesound.org/s/320655/

other assets will be properly credited in the coming days when I regain access to my home computer.

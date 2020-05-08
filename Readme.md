# Quake 2 TD

## Basics

In order to start the Tower Defense, first, you must place a start for monsters to spawn from, and an exit for monsters to reach. The game will not let you start the waves until both of those objects are created.

In order to do this, press the **V** Key to bring up the TD menu. Using the menu, place the start and goal wherever you want, as long as the enemies can easily reach the goal from where they spawn. Then, when both are placed, press **V** again and press Begin Game to start the waves.

# Specific Deliverables

## 4 Tower Types, Upgradable

By pressing the **B** Key, the player can bring up a menu of which towers they can buy. Each tower costs a different amount of money. Also in this menu is an option called **Upgrade Closest Tower**. This option will find the closest tower to the player, and if the player has enough money, it will increase its level. Each tower starts at level 1, and the cost to upgrade is equal to (Base Cost * Current Level).

* Blaster Tower: $100. This tower fires a blaster shot at the nearest enemy fairly often, dealing damage to the enemy it hits.
* Rocket Tower: $200. This tower fires a rocket at the nearest enemy, dealing damage to anything near it. Deals half of the damage that the Blaster Tower does, but hits in an AoE and is more expensive.
* Machine Gun Tower: $300. This tower will fire a burst of bullets at one enemy every few seconds, dealing low damage but hitting very often.
* Tesla Tower: $400. This tower deals damage to any enemy that walks near it. Has low range, but can hit multiple enemies and deals a lot of damage.

## 4 Enemy Types

* Standard: A normal enemy, it has medium health and medium speed.
* Fast: An enemy that moves much faster, has low health but high speed.
* Slow: An enemy that is much slower, but has high health to compensate. 
* Boss: A large enemy with medium speed, but massive amounts of health.

## Monsters Spawning In Waves

When the game begins, enemies will begin spawning in waves from the start location. The waves are as follows:

* Wave 1: 5 Standard Enemies
* Wave 2: 5 Fast Enemies
* Wave 3: 8 Standard Enemies
* Wave 4: 3 Slow Enemies
* Wave 5: 1 Boss Enemy

After wave 5, the waves will repeat in the same order, with enemies getting stronger every wave that passes.

## Monsters Drop Money / Buy Menu

Whenever a monster dies, it drops money depending on what type of enemy it is.

* Standard: $20 * Current Wave
* Fast: $10 * Current Wave
* Slow: $50 * Current Wave
* Boss: $100 * Current Wave

The Buy Menu can be accessed by pressing **B**, and will deduct the proper amount of money from the player for each tower or upgrade they buy.

## Monster Target

All monsters will attempt to move towards that goal that was placed by the player during the setup of this Tower Defense. When an enemy reaches the goal, which looks like a satellite dish, they will deduct from the player's current lives. The player starts with 50 lives, and if they reach zero, they will die. Each enemy takes away a different amount of lives.

* Standard: 1
* Fast: 2
* Slow: 5
* Boss: 25

# Common Deliverables

## Separated Into Folder

This mod can be found in the Quake 2 TD folder in the GitHub Repository.

## Auto Launch Shortcut

The auto launch shortcut can also be found in the Quake 2 TD folder.

## UI Changes

As my UI change, I added a counter for the player's current money on the top right of the screen. Whenever an enemy dies, the money counter will automatically update to show the correct amount.

## In Game Visuals

Whenever a tower is upgraded, an explosion effect will be played on the tower, indicating which tower was upgraded.
# CHANGELOG

VER 2.1.2-M
- Merged everything from upstream, thank you for your hard work Abbie!

VER 2.0.3
- Added a way to remove pocket PC via talking to Fennel
- Manually added some egg moves for some pokemon
- Added the ability to switch whether you want the mega unique to use their unique ability, or their original mega ability. Can be toggled via mega ring
- Minor grammar fixes
- Merged eevee's rarer exotics
- Merged kleen's various fixes, which includes quick claw fix and spectral thief
- Merged kleen's safari qol, you can now just pick the pokemon you want to get from the sign (!!!)
- Merged kleen's legend plate
- Added a custom icon for legend plate
- Fixed dark type being available in RBY dex catching contest
- Fixed appletun's ow sprite

VER 2.0.2
9/12/2024
- Adjusted the potion brewing text position to fit 3 digits
- Fixed potion cauldron not correctly reducing the berry amount during large batches of brewing
- Fixed held item not getting refunded if release mon on fainted toggle is disabled
- Fixed the reward being astronomically high because of the recent multiplier adjustment

8/12/2024
- Fixed QoL settings not sticking (For real)
- Walking over a bridge shouldn't spawn water pokemon now
- Very minor fix on Waterfront0 map, you can't land on water while flying on certain tiles
- Fixed the difficulty reward multiplier issue due to float fuckery. It should give you hard reward on 2.5, etc. as intended. Previously it only worked if you're way above the actual required multiplier

7/12/2024
- Added the chaining system for legends. Guaranteed shiny at 100 chain
- Sylveon's evo is reverted back to simply know a fairy move, except it's working now lol
- Fixed Soul heart giving the wrong mon spAtk up
- Small fix when retrieving a shiny legendary. No more Xerneas the Shiny Xerneas
~~- Fixed the QoL settings not sticking?~~
- Fixed Cursed body activating on substitute

20/11/2024
- Fixed a lil mistake I left in during debugging. Now taking legendary mon from Birch's lab isn't guaranteed to be cursed unless you're deep into the run
- Tera orb will now recharge in victory lap, once per fight
- It is now possible to skip the random starter bag. Enabled via setting
- Fixed scale shot, it should now change the stats after the opponent is ko'd

16/11/2024
- Merged in eevee's birch lab modification. Now only legendaries has chance to be cursed
- Added "restart" button in case of softlock. Only appears in routes. It doesn't actually restart your game, it just teleports you to the route's spawnpoint lol
- Removed chilly reception, electro shot, and flying press added mountain gale, body press, and cotton guard in unique mon movepool
- Fixed some grammar issues

12/11/2024
- Merged coconut's stuff, which includes expansion of abilities + moves for unique mon pool (whopping 127), and move descriptions stuff
- Added OW sprite for gimmighoul roaming
- Merged some of eevee's stuff again, including gimmighoul evo, increased victory lap reward
- Updated the berry rate growth for balance purpose
- Merged kleen's make it rain fix
- Updated game version! Finally!!! (Do tell me if I fuck up something)
- Merged booster energy from rhh

9/11/2024
- Implemented faster berry growth in run. Thanks coconut!

6/11/2024
- Added the option to rename the hub

5/11/2024
- Added the pocket PC for real this time. Unlocked via hub upgrade
- Added unique mon tracking inside pocket pc as an upgrade. Can be used inside adventure

4/11/2024 
- Merged yet another poison puppeteer stuff + mortal spin (kinda? I can't find it on eevee's repo)
- Buffed the reward for the multiplier
- Added a new item, pocket PC. You can't earn it yet, though
- Updated zippy zap description 

3/11/2024
- Merged eevee's poison puppeteer related things + minor fixes
- Added quick route option for... Quicker routes. Since making a shorter run isn't an option due to how the game expects you to defeat 14 mighty trainers, rip. It doesn't affect existing generated map however, and instead will be enforced on the next map generation
- Fixed venipede's funny overworld look

2/11/2024
- Fixed weird berrytag ui behavior
- Added popups for Pick Up, Honey Gatherer, and Shuckle's berry juice
- Added a new route, quick map, for debugging purposes
- Fixed the conditional, pecharunt should be able to spawn now

1/11/2024
- Added quick brewing
- Fixed sylveon evo
- Merged some fixes from EggsOverEevee, such as the thermal change fix, double snowscape alolan ninetales fix, and galarian birds

28/10/2024
- Optimized the difficulty reward code in the menu
- Added an indicator for pokemon spawns left for the catching contest in the pause menu
- Added quick sell/drop toggle in bag, activated by start 

27/10/2024
- Fixed the honey tree for good. Sorry.
- Adjusted the saveblock2. Thank you kleenex
- Ridemon that can swim shouldn't jump off the cliff or the bridge onto the land. Seems to be an unintended behavior because I don't notice this problem on other ridemons
- Adjusted the full rest stop map a little
- Added a countdown for the catching contest
- Added an option to show money in start menu

23/10/2024
- Curses bonus included in the multiplier. Each unstackable Curse adds +0.2x, while each stackable Curse adds +0.1x at 1, +0.2x at 2, and +0.3x at 3 or more

22/10/2024
- Custom settings for some of my features are added, in case you'd rather keep vanilla system.  Currently includes the new difficulty reward system and ridemon control
- Reward is now scaled off the multiplier if you have the new difficulty reward system on
- Adjusted more stuff, now difficulty reward should also affect rewards you can claim. Color coded similarly to the vanilla system

21/10/2024:
- One liner issue should be fixed now
- Minor fix to the honey tree
- Difficulty setting is now multiplier based, it should be more modular now.

10/10/2024:
- Berry blender NPC added into the daycare and full rest stop
- You can no longer jump off the cliff/bridge if your mon can swim while riding it.
- Added a proper flag for the pokeball changer NPC and the conditions.
- Unique mon tracker countdown is back

8/10/2024:
- Pokeblock can now be scattered by directly interacting on the Honey Tree
- Press R to fly instead of B, now you can only cycle with L
- Talk to your mon to ride it, press B to dismount. Need basic whistle. You can cycle through your party with it as well. It does not change the order of the mon on your party, and you still need the golden whistle if you want to access your daycare mons.
- You can now change your mon's pokeball via an NPC in the town square after buying the school upgrade (might change in the future?)

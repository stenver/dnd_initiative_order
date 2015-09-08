# Dungeons and dragons initiative order app

This application will help DM playing dungeons and dragons keep track of the initiative and status effects.

The application was developed using Qt 5.4.2 and clang compiler. It has only been tested on Mac OSX, but in theory should be cross platform.

## The setup phase

Write battle creature name and initiative. New creature box will be added whenever the last creature name box is edited. Initiative ties can be resolved by using a comma. e.g. lets say we have PC and monster with initiative 10. However, PC has higher dexterity. Set PC initiative to 10,5.

After that, set the alignments of the creatures to friend or foe as appropriate.

In addition, if any buffs or potions were drank before the combat that should be kept track of, you can add it by clicking 'add status'. A box appears where you can write the status name and the rounds it has left before it ends.

When everything is done, click "start combat"

## The battle phase

The creatures are automatically sorted by the initiative and the starting creature is at the top of the window.

 * Click "Next turn" whenever a creature finishes his turn.
 * Click "Delay" whenever a creature wants to delay.
 * Click "Stop all delays" whenever somebody wants to end their delay. If there are more then one players who delayed, then delay those players again which dont want to end their delay.
 * Click "Delete active creature" whenever the current active creatue leaves the combat for whatever reason.
 * Click "Add a new creature" whenever you want the new creature to be added to the combat. Note that this doesnt end the currently active creatures turn. He is pushed after the new creature.
 * Click "End combat" to go back to setup phase.

## Global hotkeys

The hotkeys can be pressed wether or not you have the window focused. For Mac, switch CTRL with COMMAND
 * CTRL+SHIFT+S - Start/end combat
 * CTRL+F1 - Next creature
 * CTRL+F2 - Delay
 * CTRL+F3 - Stop all delays
 * CTRL+F11 - Delete active creature
 * CTRL+F12 - Add a new creature

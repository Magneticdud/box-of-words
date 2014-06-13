# SD card contents

This directory contains the files on the SD card.

## SETTINGS.TXT

This file is read by the Arduino program and contains runtime settings. The format of the file is [setting]=[value].

There are two numeric settings and eight file titles that can be set.

### Numeric values

* `brightness` - *integer* The luminocity of the LCD screen backlight, range 0...255. Higher value = more light.
* `scrollSpeed` - *integer* The speed of which text longer than 16 characters scrolls on the screen. Range 100...2000.

### File titles

These files contain the word lists. The initial contents are pieced together from various Internet dictionaries and lists and filtered to fit improv scenes.

title0...title7. Correlated with the file names (WORDS_00.txt is title0, WORDS_001 is title1 and so on). These values are displayed in the main menu. Max 16 chars.

Licenced under Creative Commons Attribution 4.0 International

## Default lists on the SD card

* WORDS_00.TXT - Emotions. Inner feeling. "I feel..." [ashamed, calm, helpful]
* WORDS_01.TXT - Professions. "I work as a..." [soldier, student, poet]
* WORDS_02.TXT - Relationships. "Can I have a relationship between two people?" [bride-groom]
* WORDS_03.TXT - Locations. "Where might this scene take place?" [army base]
* WORDS_04.TXT - Random words. "What's the first word that comes to your mind?" [airplane, bed, game]
* WORDS_05.TXT - Adjectives. Something you can show out. "Your character seems a bit..." [angry, sad, smiling]
* WORDS_06.TXT - Film Styles. [action, adventure, thriller]
* WORDS_07.TXT - Activities. "What's happening in this scene?" [drinking tea, cleaning, fishing]

More lists: see [this Facebook post](https://www.facebook.com/groups/176926739037527/permalink/708867982510064). You can create lists of your own and replace the contents of the word files.

Keep in mind that the file names must stay the same.
\# 🎮 Zork - Laboratory Escape Game



A text-based adventure game inspired by the classic Zork series. Escape from a mysterious laboratory by solving puzzles, avoiding dangers, and defeating enemies.



\## 👥 Authors



\- \*\*Douglas Mendes\*\* - \[GitHub Profile](https://github.com/dougmendes)



\## 🔗 Repository



\[https://github.com/dougmendes/Zork](https://github.com/dougmendes/Zork)



\## 📄 License



This project is licensed under the MIT License - see below for details.



---



\## 🎯 Game Overview



You wake up on a gurney in a dimly lit laboratory. Your wrists and ankles were tied, but you've managed to free yourself. Now you must explore the facility, collect password digits, defeat a mutant creature, and escape before it's too late!



\### Features

\- 🏛️ 6 interconnected rooms to explore

\- 🎒 Inventory system with equippable items

\- ⚔️ Turn-based combat with automatic healing

\- 🧩 Password collection puzzle

\- 💀 Multiple death scenarios

\- 🏆 Victory condition by escaping with the correct password



---



\## 🎮 How to Play



\### Starting the Game

1\. Download `Zork.exe` from the \[Releases](https://github.com/dougmendes/Zork/releases) section

2\. Run `Zork.exe`

3\. The game starts in the \*\*Starting Room\*\*



\### Basic Commands



\#### Movement

\- `go north` / `go n` - Move north

\- `go south` / `go s` - Move south  

\- `go east` / `go e` - Move east

\- `go west` / `go w` - Move west

\- `go up` / `go u` - Move up

\- `go down` / `go d` - Move down



\#### Items

\- `look` / `l` - Look around current room

\- `take <item>` - Pick up an item

\- `drop <item>` - Drop an item

\- `inventory` / `inv` / `i` - Check your inventory

\- `equip <item>` - Equip an item

\- `unequip` - Unequip current item



\#### Special Actions

\- `read <item>` - Read an item to discover password digits

\- `light` - Turn on lights (in Analysis Lab)

\- `exit <password>` - Attempt to escape (requires 4-digit code)

\- `help` / `h` - Show available commands

\- `quit` / `q` - Exit game



---



\## 🗺️ Complete Walkthrough



\### Step-by-Step Solution



1\. \*\*Starting Room → Locker Room:\*\*

```

&nbsp;  look

&nbsp;  go north

&nbsp;  go west

&nbsp;  take hazmat

&nbsp;  take card

&nbsp;  read card

```

&nbsp;  \*Digit discovered: 0\*



2\. \*\*Equip Protection:\*\*

```

&nbsp;  equip hazmat

```



3\. \*\*Locker Room → Contaminated Lab:\*\*

```

&nbsp;  go east

&nbsp;  go up

&nbsp;  read computer

```

&nbsp;  \*Digit discovered: 4\*



4\. \*\*Contaminated Lab → Analysis Lab:\*\*

```

&nbsp;  go down

&nbsp;  go east

```

&nbsp;  \*⚠️ WARNING: It's dark! Don't move yet!\*



5\. \*\*Turn on Lights:\*\*

```

&nbsp;  light

```

&nbsp;  \*Now safe to proceed\*



6\. \*\*Get the Axe:\*\*

```

&nbsp;  take axe

&nbsp;  read axe

&nbsp;  equip axe

```

&nbsp;  \*Digit discovered: 1\*



7\. \*\*Force Open Containment Room:\*\*

```

&nbsp;  go west

&nbsp;  go down

```

&nbsp;  \*Door automatically breaks open with equipped axe\*



8\. \*\*Enter Containment Room (Combat Begins):\*\*

```

&nbsp;  go east

```

&nbsp;  \*⚔️ Automatic combat starts!\*

&nbsp;  - Combat is fully automatic

&nbsp;  - You deal 30 damage with axe equipped

&nbsp;  - Monster deals 15 damage per turn

&nbsp;  - Victory after defeating the mutant



9\. \*\*Read Final Clue:\*\*

```

&nbsp;  read photo

```

&nbsp;  \*Digits discovered: 1 and 2\*



10\. \*\*Escape:\*\*

```

&nbsp;   go west

&nbsp;   go west

&nbsp;   exit 0412

```

&nbsp;   \*🎉 VICTORY!\*



---



\## 🔑 Password Digits



Collect these 4 digits to escape:



| Digit | Location | Item |

|-------|----------|------|

| 0 | Locker Room (1L) | Access Card |

| 4 | Contaminated Lab (2L) | Computer |

| 1 | Analysis Lab (1D) | Axe (blood writing) |

| 2 | Containment Room (2D) | Photo |



\*\*Final Password:\*\* `0412`



---



\## 💀 Death Scenarios



1\. \*\*Toxic Gas\*\* - Entering Contaminated Lab without hazmat suit

2\. \*\*Broken Glass\*\* - Taking items in dark Analysis Lab

3\. \*\*Combat\*\* - Losing to the mutant creature



---



\## 🛠️ Technical Information



\### Built With

\- \*\*Language:\*\* C++17

\- \*\*IDE:\*\* Visual Studio Community 2022

\- \*\*Platform:\*\* Windows x64



\### Project Structure

```

Zork/

├── include/          # Header files (.h)

│   ├── entity.h

│   ├── room.h

│   ├── exit.h

│   ├── item.h

│   ├── creature.h

│   ├── npc.h

│   ├── player.h

│   └── world.h

├── src/              # Source files (.cpp)

│   ├── entity.cpp

│   ├── room.cpp

│   ├── exit.cpp

│   ├── item.cpp

│   ├── creature.cpp

│   ├── npc.cpp

│   ├── player.cpp

│   ├── world.cpp

│   └── main.cpp

├── Makefile          # Linux/macOS build

├── Zork.sln          # Visual Studio solution

└── README.md

```



\### Compilation



\*\*Windows (Visual Studio):\*\*

1\. Open `Zork.sln`

2\. Select `Release` configuration

3\. Build → Rebuild Solution (F7)



\*\*Linux/macOS (Make):\*\*

```bash

make

./bin/zork

```



\*\*Cross-compile for Windows from macOS/Linux:\*\*

```bash

make windows

```



---



\## 📜 MIT License

```

MIT License



Copyright (c) 2026 Douglas Mendes



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions:



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software.



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE.

```



---



\## 🎓 Academic Project



This project was developed as part of a C++ programming course assignment, demonstrating:

\- Object-Oriented Programming (OOP)

\- Inheritance and Polymorphism

\- Memory Management

\- Container Usage

\- Const-Correctness

\- Game Design Principles



---



\## 🙏 Acknowledgments



\- Inspired by the classic \*\*Zork\*\* text adventure games

\- Built with assistance from modern development tools

\- Thanks to the UPC academic program



---



\*\*Enjoy the game! Can you escape the laboratory?\*\* 🎮🔓


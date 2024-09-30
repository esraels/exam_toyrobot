ExamToyRobot
=============

This project is my solution for the "Toy Robot Code Challenge" exam.  

---

Description:
------------
This app is a simulation of a toy robot moving on top a 5x5 table. 
You must feed it with commands to move around.
If you give it a command that will result to the robot falling out of the table, it will ignore the command.
The very first command should be placing it to a valid position on the table before it can accept other commands for movement.

Commands:
---------

***Note**: the commands are case insensitive.*

1. **`PLACE X,Y,[NORTH|EAST|WEST|SOUTH]`**: 
    - Place the robot at X,Y position facing North, East, West, or South. 
    - examples: `PLACE 2,3,EAST`, `PLACE 0,0,NORTH`, `PLACE 4,4,WEST`.
    - **Note**: Since the table is only 5x5, valid values for the X,Y must be 0 to 4 only. Count starts from 0. Any value beyond that will make the place command invalid and will be ignored.
    - invalid examples: 
        - `PLACE 5,0,EAST`: X position is 5.
        - `PLACE 2,10,EAST`: Y position is greater than 4.
        - `PLACE 7,6,EAST`: both X,Y values are outside of the 5x5 table.
    
2. **`LEFT`**:  
    - Rotate the robot 90 degrees to the left.
    
3. **`RIGHT`**:
    - Rotate the robot 90 degrees to the right.
    
4. **`MOVE`**:
    - Move the robot 1 unit forward in the direction where it is facing.

5. **`REPORT`**:  
    - Print the current position and face direction of the robot.
    - example output: `Output: 1,2,EAST`
    - **Note:** Entering this command will **EXIT** the program.

---

> **Note:** The screenshots below are taken from Visual Studio 2022 (v17.7.4).

How to run the project in Visual Studio:
----------------------------------------

1. Open the solution file `.\ExamToyRobot\ExamToyRobot.sln` in **Visual Studio**.
2. On **Visual Studio > Solution Explorer**, right-click on the **ExamToyRobot** project node and choose `Set as Startup Project`.  
    ![Set as Startup Project](/docs/images/screenshot_set_as_startup_project.png)
3. Press the **Local Windows Debugger** button, or press `F5` to start running the app with a debugger.  
	![Start Debug button](/docs/images/screenshot_start_debug_btn.png)
4. When the app is already running, you can now type commands.  
	![App with commands](/docs/images/screenshot_app_with_commands.png)

---

How to run the Unit Test:
-------------------------

1. Open the solution file `.\ExamToyRobot\ExamToyRobot.sln` in **Visual Studio**.  
2. On **Visual Studio**, open the ***Test Explorer*** window via **View > Test Explorer** or press `Ctrl+E,T`.  
    ![Menu View Test Explorer](/docs/images/screenshot_menu_view_test_explorer.png)
3. Press the "**Run All Test**" button ![Run All Test](/docs/images/btn_run_all_test.png), or press `Ctrl+R,V`.  
	![Test Explorer Screenshot](/docs/images/screenshot_test_explorer.png)

---

Commandline arguments:
---------------------
- In **command prompt**, go the path of the exe file and then type `ExamToyRobot.exe --help` to display the following:  

```
ExamToyRobot.exe [--verbose|-v] [--noend] [--help|-h|-?] [--table|-t]
flags:                                                 
  --verbose   :Show error messages.                        
  --help      :Show help message.                     
  --table:W,H :Change size of table.                  
  --noend     :App will not exit on 'report' command. 
                Press Ctrl+c to exit.                 
     -v       :Same as --verbose.                     
     -t:W,H   :Same as --table.                       
     -h       :Same as --help.                        
     -?       :Same as --help.                        
```

---

Using commands from file:
---------------------------  

  - Open **command prompt**, go to path of the exe file, and enter the file with list of commands as input. The commandline format will be:  
    
    ```
    C:\AppPath> ExamToyRobot.exe < commands.txt
    ```

  - Different ways to feed commands from file:

    ```
    ExamToyRobot.exe < commands_fileA.txt
    more commands_fileB.txt | ExamToyRobot.exe
    type commands_fileC.txt | ExamToyRobot.exe
    ```

  - Logging the error messages to a file:

    ```
    type commands_fileC.txt | %APP% --verbose 2> errors_fileC.log
    ```




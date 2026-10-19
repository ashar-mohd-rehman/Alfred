Project Name : Alfred

Description : A desk bot that is made using XIAO ESP32S3 and a NEO-6M GPS and a 1.3inch OLED. HIs name is alfred and he uses the GPS instead of an IMU and rtc time module to detect shake and time. When I shake it the speed goes up high and GPS detects it , this makes the desk companion show some fun animations, like when someone is feeling sick then dizzy then getting better and finally it shows a clock. The time, on this clock comes from the GPS UTC. itll use a 3d printed enclosure

Total Time : 4h 



# **#3 Designed case and assembly**

So I downloaded all the electronics from grabcad and arranged them in a compact way, 
After that I started working on the case based on the orientation of parts and came up with a single piece
design for the case 
<img width="2561" height="974" alt="Alfred_2026-Oct-19_10-55-35AM-000_CustomizedView44317281295" src="https://github.com/user-attachments/assets/a4a9ff6e-f7e0-4cc4-aab6-d171cf1b1ec3" />

I also rendered it 

Then I made the assembly of my project and rendered it too

<img width="2561" height="974" alt="Alfred_electronics_2026-Oct-19_10-54-39AM-000_CustomizedView17511593187" src="https://github.com/user-attachments/assets/9f4249ef-bd80-45f0-bafa-323eb7d5791c" />

Total Time Spent : 1h 

# **#2 Designed Faces and Settled Github**

So I wanted the faces to look somehwhat cool and cute and so I googled but didnt find anything cool thats when I stumbled upon dasai mochi 
![Screenshot_2026-08-16_121441.png](https://cdn.hackclub.com/01a00ff8-0aa5-78b1-b83d-c970d6a0766e/Screenshot_2026-08-16_121441.png) 
and decided to for faces inspired by these looks so I designed them on pen and paper and heres how they look 
![faces.jpeg](https://cdn.hackclub.com/01a00ff8-84ec-71be-a844-712099a4134a/faces.jpeg)

So basically itll sit idle and blink. when shaked itll vomit and feel dizzy after that itll recover and show current time and day 

I then generated firmware with the help of claud and made bom and decided to setup github 
![Screenshot_2026-08-17_185936.png](https://cdn.hackclub.com/01a00ff9-aa35-7e82-acf2-08cd18bfeda8/Screenshot_2026-08-17_185936.png)

Total Time Spent: 1.5h 

# **#1 Researched and made the wiring diagram**

A little background, I made a speedometer for my cycle but since it is monsoon season in india and while riding my bike my speedometer got wet so instead of keep using it I took it home and dried it out luckicly nothing was damaged so i decided to turn that into a indoor desk buddy

For this project I'll be using Xiao Esp32S3, Neo6m GPS module, and 1.3 inch oled display

I then made the wiring diagram 

<img width="1488" height="1061" alt="image" src="https://github.com/user-attachments/assets/0a164e63-9172-4a98-a18d-b7e303666daf" />

So basically how this works is that when I shake this aggresively the gps inputs it, And then the xiao processes it and outputs time on the 1.3 inch display

Total Time Spent : 1.5h 

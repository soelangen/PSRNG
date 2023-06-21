# LFSR
## Prequisites
### Logisim
For the hardware simulation a tool called [logisim](http://www.cburch.com/logisim/) is used. This tool allows us to emulate simple hardware logic. For our LFSR we use an initial seed which needs to be set first. This can be achieved through selecting the hand in the top left corner and clicking on the left and right most D Flip-Flop. Afterwards we can use `CTRL+T` to emulate one tick of the clock which triggers the D Flip-Flops to release their stored value and to take the value which arrives at their input.
### C
In order to execute the program you need to have [GCC](https://gcc.gnu.org/) and [make](https://www.gnu.org/software/make/) installed. This allows you to use the predefined make commands `make all`, `make clean` and `make run`.
## Logic
The right most register in the Logisim simulation or the right most value of the integer in C is usually the value that is output by the LFSR.
This value can be utilized in a linear combination of logic.
This linear combination is than used as an input into the system.
In our example we take the two least significant bit and XOR them. This is than used as an input for the most significant bit.

A small example can be seen below:

| State and output | Operation performed and Feedback | New State |
| ------------- | ------------- | -------------| 
| 1001 -> 1 | 0 XOR 1 -> 1 | 1100 |
| 1100 -> 0 | 0 XOR 0 -> 0 | 0110 |

Transferring this to software is not as straightforward:
```C
int state = 0b1001;
int newBit = (state ^ (state >> 1)) & 1;
state = (state >> 1) |  (newBit << 3);
```
In the first step we compute the new bit which is later used as an input.
Therefore we take the current state and use a bitwise XOR with the state shifted one to the right.
This bitwise XOR operation would look like this for the initial state `1001 ^ (0100) => 1101`.
This achieves that we can XOR the right most bit with the 2nd right most bit like we do it in the hardware simulation.
Through this operation we now have the new bit calculated, in order to only have the new bit a one bit long bitwise AND is used.
In the last step a bitwise OR is used to combine the state that was shifted one bit to the right with the new bit which was shifted 3 bits to the left so that it can take the position of the most significant bit.

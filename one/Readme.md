Code by: Jason Gumarjadi Sunardi
Edoras Account: cssc4363@edoras.sdsu.edu

Insttructions to run code:
To execute the program pleas type 'make' into the terminal and once the program has been built type 'mulproc' to run to program

Expected Output:
CHILD <5700> process is executing testalphabet program!
CHILD <5701> process is executing testspecial program!
a -> 2973036
b -> 556908
c -> 765864
d -> 1786752
e -> 4883076
f -> 765336
g -> 809292
h -> 2818068
i -> 2586276
j -> 35112
k -> 401412
l -> 1728276
m -> 1050852
n -> 2509320
o -> 2766192
p -> 562848
q -> 28776
r -> 2177076
s -> 2465496
t -> 3291684
u -> 1015608
v -> 276804
w -> 1085040
x -> 46860
y -> 730752
z -> 12936
CHILD <5700> process has done with testalphabet program !
, -> 745668
. -> 798072
: -> 15708
; -> 32340
! -> 63228

Overview of the Program:
The program is meant to run two child process which are the testalphabet and testspecial program. This is done via forking two seperate process and calling both PID's by using PID_t and attaching the individual PID of each process into their respective banner message to tell the user which processes are being executed. Another script is then run after the process ended using waitpid and then the PID of the terminated process is also put into their respective banner message to tell the user which process has terminated.
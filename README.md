# Philosophers

The dining philosophers problem is an illustration of a deadlock, a state in which multiple processes are waiting for a single resource currently being used by another process, and the solutions to these types of problems. 

In this project, we will learn the basics of threading a process and using mutexes.

![Screenshot](/img/introgif.gif)

# Table of Contents

1. [ The Dining Philosophers Problem. ](#desc)
2. [ My implementation. ](#solution)
3. [ The deadlock issue. ](#deadlock)

<a name="desc"></a>
## 1. The Dining Philosophers Problem

Five philosophers, numbered from 0 through 4, live in a house where the table is laid for them; each philosopher has their own place at the table. Their only problem – besides those of philosophy – is that the dish served is a very difficult kind of spaghetti, that has to be eaten with two forks. There are two forks next to each plate, so that presents no difficulty: as a consequence, however, no two neighbours may be eating simultaneously.

![Screenshot](/img/at_the_table.png)

A very naive solution associates with each fork a binary semaphore with the initial value = 1 (indicating that the fork is free) and, naming in each philosopher these semaphores in a local terminology, we could think the following solution for the philosopher's life adequate.

But this solution – although it guarantees that no two neighbours are eating simultaneously – must be rejected because it contains the danger of the deadly embrace (deadlock). When all five philosophers get hungry simultaneously, each will grab his left-hand fork and from that moment onwards the group is stuck.

In order to be able to give a formal description, we associate with each philosopher a state variable, "C" say, where C[i] = 0 means: philosopher i is thinking, C[i] = 1 means: philosopher i is hungry, C[i] = 2 means: philosopher i is eating.

Now each philosopher will go cyclically through the states 0, 1, 2, 0, ...

![Screenshot](/img/happy_ron.png)

Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher at a time and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can only take the fork on their right or the one on their left as they become available, and they cannot start eating before getting both forks.

Eating is not limited by the remaining amounts of spaghetti or stomach space; an infinite supply and an infinite demand are assumed.

The problem is how to design a discipline of behavior (a concurrent algorithm) such that no philosopher will starve; i.e., each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.

<a name="solution"></a>
## 2. My implementation

In my project, we use the user's input to define the parameters of the program.
For the simulation to start, the user must enter the [Number of philosophers] (How many philosophers are seated at the table), [Time to die](The time a philosopher takes to die after his last meal), [Time to eat] (Time a philosopher takes to eat his meal), [Time to sleep] (The time during which a philosopher will sleep, just after eating), and lastly the [Number of meals] required to end the simulation (Optionnal).


<a name="deadlock"></a>
## 3. The deadlock issue



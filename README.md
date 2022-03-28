# Philosophers

The dining philosophers problem is an illustration of a deadlock, a state in which multiple processes are waiting for a single resource currently being used by another process, and the solutions to these types of problems. 

In this project, we will learn the basics of threading a process and using mutexes.

![Screenshot](/img/introgif.gif)

# Table of Contents

1. [ The Dining Philosophers Problem. ](#desc)
2. [ Threads. ](#threads)
3. [ Mutexes. ](#mutexes)
4. [How to avoid Deadlocks.](#deadlock)
5. [Conclusion.](#conc)

<a name="desc"></a>
## 1. The Dining Philosophers Problem

Five philosophers, numbered from 0 through 4, live in a house where the table is laid for them; each philosopher has their own seat at the table. Their only problem – besides those of philosophy – is that the dish served is a very unusual kind of spaghetti, that has to be eaten with two forks. There are two forks next to each plate, so that presents no difficulty: as a consequence, however, two neighbours may not be eating simultaneously.

![Screenshot](/img/at_the_table.png)

A very naive solution associates with each fork a binary semaphore with the initial value = 1 (indicating that the fork is free) and, naming in each philosopher these semaphores in a local terminology, we could think the following solution for the philosopher's life adequate.

But this solution – although it guarantees that no two neighbours are eating simultaneously – must be rejected because it contains the danger of the deadly embrace (deadlock). When all five philosophers get hungry simultaneously, each will grab his left-hand fork and from that moment onwards the group will be stuck.

In order to be able to give a formal description, we associate with each philosopher a state variable, "C" say, where C[i] = 0 means: philosopher i is thinking, C[i] = 1 means: philosopher i is hungry, C[i] = 2 means: philosopher i is eating.

Now each philosopher will go cyclically through the states 0, 1, 2, 0, ...

![Screenshot](/img/happy_ron.png)

Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher at a time and so a philosopher can use the fork only if it is not being used by another philosopher. 

After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can only take the fork on their right or the one on their left as they become available, and they cannot start eating before getting both forks.

Eating is not limited by the remaining amounts of spaghetti or how full their stomach is; an infinite supply and an infinite demand are assumed.

The problem is how to design a discipline of behavior (a concurrent algorithm) such that no philosopher will starve; i.e., each can forever continue to alternate between eating and thinking, assuming that none of the philosophers are able to know when others might want to eat or think.

<a name="threads"></a>
## 2. Threads

In my project, execution input is used to define the parameters of the program.
For the simulation to start, the user must enter: 

[Number of philosophers] - How many philosophers are seated at the table, 

[Time to die] - The time a philosopher takes to die after his last meal, 

[Time to eat] - The time a philosopher takes to eat his meal, 

[Time to sleep] - The time during which a philosopher will sleep, just after eating, 

The [Number of meals] required to end the simulation (Optionnal).

As such, our algorithm should run no matter the number of philosophers at the table.
The key for this to work, is to represent each philosopher by a Thread of the main process. 

![Screenshot](/img/1200px-Multithreaded_process.svg.png)

In computer science, a thread of execution is the smallest sequence of programmed instructions that can be managed independently by a scheduler, which is typically a part of the operating system. The implementation of threads and processes differs between operating systems, but in most cases a thread is a component of a process. The multiple threads of a given process may be executed concurrently (via multithreading capabilities), sharing resources such as memory, while different processes do not share these resources.

By defining our philosophers as Threads, we can assure their independence from the others while still letting them access the memory they need for their routine (The forks for instance, or to check if any other philosopher has died).


<a name="mutex"></a>
## 3. Mutexes

Another amazing tool that makes the program work : Mutexes.

The main problem with the philosophers diner, is fork management.
We must assure that once a fork is picked up, it should disappear from the table and not be accessible by another philosopher, in which case we would face a data race.

In computer science, a lock or mutex (from mutual exclusion) is a synchronization primitive: a mechanism that enforces limits on access to a resource when there are many threads of execution. A lock is designed to enforce a mutual exclusion concurrency control policy.

![Screenshot](/img/Mutex.png)

Here, we will represent each fork by a mutex, and make them available to the philosophers while they are unlocked. 

Once a pihlosopher grabs a fork, it locks itself in a mutex and disappears from the table, becoming unavailable to others.

We also make sure to display each action performed by philosophers, whether it is eating, sleeping, thinking or even grabbing forks in mutexes so they cannot write at the same time as others (Because they behave independently from each other).


<a name="deadlock"></a>
## 4. How to avoid deadlocks

A big - if not the biggest - challenge with this project, was how to avoid any deadlock during fork distribution.

For instance, if each philosopher was to start the simulation by grabbing the fork at their right, each one of them would end up holding only one fork and starve to death.

An easy way to avoid this issue is to separate philosophers depending on their index : is it even or odd ?

![Screenshot](/img/cf7f850832f8aa117e3246babe2e4abb.jpg)

If his index is even, the philosopher will start grabbing the fork on his right side first, before attempting to grab on his left.

If it is odd, the philosopher will start grabbing the fork on his left side first, before attempting to grab on his right.

This way, we break the straightness of fork grabbing and the philosophers will alternate their eating depending on their index. No fork will be grabbed if the other needed is not available, and no deadlock can happen. At best, if the time permits it, the simulation will continue indefinitely or until the meal objective is reached.


<a name="conc"></a>
## 5. Conclusion

I really enjoyed working on this project; even if threads and mutexes are not the most inspirating tools at first glance, they allow processes to operate on a whole new level, synchronization-wise.

The Dining Philosophers problem was a good way to introduce myself to these new tools, mainly thanks to the "Riddle" side of the project which made me bash my head a couple times, but was fun overall.

If i had to redo this project, i would try using a better handling of the philosophers deaths, and a more well-organized data structure - as mine is a little messy.

![Screenshot](/img/100.png)

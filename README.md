# CSC 1120 Final Exam - Tanks

## Finish this game and make it your own!

In this repo, you'll find (a Windows version) of the tanks game we started in class.

You have learned about GitHub now so these are the files you'll FORK. 
If you clone, like we did in class, you'll still be connected to this repo. 
If you fork, you are downloading your own unique copy.

# Instructions

1. Finish this game. See below.
2. Make it your own. You can change any aspect of this code and game as long as it continues to play the "same game." 

    For example, I really don't like the keys I chose for up and down - do you? If you don't, pick different ones.
    *Note: do not assume my code is correct - discovering any deficiencies is a learning objective.*

    Go crazy or play it safe - it's up to you.

3. All your changes will be maintained on GitHub.
4. Your GitHub must have a lovely README.md.
5. **You must work with a partner**. No solo efforts because working with a partner via GitHub is one of the learning objectives. You cannot experience merging / collaborating without a partner.
6. On 5/9 and 5/11, you and your partner will connect to the projector at the front of the room and present your work for 10 to 15 minutes.
    Order of presentations will be chosen at random. Be prepared to present on either day. Please DO NOT MAKE CHANGES after the start of class on 5/9 - remember GitHub remembers all the dates and times.
    
    If you are uncomfortable speaking, that's OK - it is your responsibility to choose a partner who can speak in front of the class.
7. You will:
<pre>
    Demonstrate your game. Make sure you show how you customized it.
    Show your GitHub page, including evidence of collaboration and the README.
    Show specific parts of your code you are proud of.
</pre>
8. Then you and your partner will leave the room.
9. The class will discuss your work and assign a grade from 0 to 100. If extra credit should be awarded, it can be at most 20 points.
10. I reserve the right to override the decision of the community. I will not reveal the grade actually awarded. I will limit my override to + / - 10 points.

# Honor Code

You will self-enforce the academic honesty code. Only you and your partner can work together (and of course you may consult me or any tutor).

This time, we will not be grading your code per se. If you cheat, you're only cheating yourself. I remain available to you for personal one-on-one consulting on your code during the summer or next year by appointment.

# Finishing

Your finished project must include the following:
1. Detecting a hit on your opponent. A hit is defined as the shot passing through any of the 9 spots surrounding the opposing player. Note that this isn't as simple as it seems. What if the shot is moving very quickly? It will leave many blank spots in between each movement. You will probably want to divide time into finer chunks - remember to change gravity too.
2. Implement a scoring system. When a player hits the other three time, use curses to ask the user if they want to continue, yes or no. Note, you can hit yourself. If your own shot lands in the 9 spots centered at you it counts as a hit against you.
3. After each hit, the player and the ground must be chosen over again.
4. You must make a 2D tuple class so that the code in your version of Shoot() looks something like:

        Vec2D p0(line and column - depends on your code);
        Vec2D force(sin(angle) * players[turn].power * 0.2, cos(angle) * players[turn].power * 0.2);
        Vec2D gravity(0, -0.98); // or a different value of your choosing.
        Vec2D pN = p0 + di * force + (di * di + di) * 0.5 * gravity;
        
    This means you will create the Vec2D class along with overloads for:
    
        int times Vec2D
        double times Vec2D
        Vec2D plus Vec2D
        
    If you are unsure how to do this, please ask me or any of the tutors. 

    Here is a hard to understand but very complete <a href="http://en.cppreference.com/w/cpp/language/operators">description</a>.
    
    Here is a lighter <a href="https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm">tutorial</a>.
    
    *Operator overloading is also covered well in your text book!*
    
4. An additional 20 points is up to you for extra credit.
5. If you meet all the requirements of this specification, the minumum grade is 70 percent. The class will decide how much higher you go.

# What if you have already finished the game?

Some of you took it upon yourselves to finish the game based on our classwork. Make sure you conform to all aspects of this
specification then choose a very lucky partner. Decide on extra credit and have them do the heavier lifting.

# Sample ideas for extra credit

1. A player can give up their shot in exchange for being able to move left and right.
2. You can implement wind - make sure a wind value is displayed somewhere.
3. You can implement craters left behind by shots.

# What if you have nothing to show or your game doesn't work / compile / etc?

You will still present, focusing on what you think went wrong and what you can learn about the experience. The class will still grade you but the most you can receive is a 50 percent.

# Summary on grading

1. Decided by the class based on your presentation (presentation skill is not part of the grade).
2. I can override secretly within a range of + / - 10 points.
3. The minimum score for a working project is 70 points.
4. The maximum score for a non-working or non-finished project is 50 points.

# Emphasis:

1. You must have a partner.
2. You must use GitHub to work together and exchange / merge code.

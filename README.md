# Project_5
# Particle System Simulator Project 

## Objective

The objective of the "Particle System Simulator Project" for the CIIC4010/ICOM4015 course is to enhance a Particle System Simulator by adding new features and functionality. The project is divided into three phases, each building upon the previous one, with increasing complexity.

## Project Overview

In this project, you will be working on a Particle System Simulator. The base application already has four simulation modes available, and your task is to add new features and improvements to it. The features and changes are divided into three phases, with each phase introducing a set of specifications to implement.

## General Instructions

- You will work in teams of two students.
- Personal repositories will not be graded.
- One partner will create the team repository, and the other will join it using their GitHub credentials.
- Team members should include their names and emails in the README.md file.
- Each partner should commit their contributions using their individual GitHub credentials.
- Collaboration and professionalism are essential throughout the project.
- If you encounter any issues or problems with your partner, follow the outlined steps to resolve them.

## Phase 1 (Suggested Deadline: September 9)

**Specifications:**

- **Particles Color Toggle ('t')**: Pressing 't' should toggle the colors of all particles following this sequence: Red -> Green -> Blue -> Repeat (Red after Blue).
- **Pause Toggle ('p')**: Pressing 'p' should toggle the pause state. When particles are paused, they are suspended in the air.
- **Increase Velocity ('d')**: Pressing 'd' should double the velocity of all particles.
- **Decrease Velocity ('a')**: Pressing 'a' should halve the velocity of all particles.

## Phase 2 (Suggested Deadline: September 21)

**Specifications:**

- **Draw Shape**: Left-click and drag the mouse across the screen to create a rectangle with no filling (borders only). Left-click and drag again should replace the older rectangle with a new one.
- **Remove Shape**: Right-click within the boundaries of the rectangle to remove it.
- **Magnify Particles**: Particles that enter the drawn rectangle should have their size tripled. Particles exiting the boundary should have their size reverted back to normal. Particles inside the boundary when the rectangle is removed (by right-clicking) should also revert to normal.

## Phase 3 (Suggested Deadline: September 30)

**Specifications:**

- **Record ('r')**: Pressing 'r' should start recording or saving all the keys pressed afterward in order until it is pressed again. The actions associated with the keys should be performed during recording.
- **Recording Indicator**: There must be an indicator when the program is recording. This indicator should only appear during recording.
- **Replay ('p')**: Pressing 'p' should replay all the recorded keys and their associated actions at fixed intervals (not in one tick). The interval between actions is up to you but should be noticeable. While replaying, the program should not listen to any key presses until the replay is finished or cancelled.
- **Cancel Replay ('c')**: Pressing 'c' should cancel a playing replay.
- **Replay Indicator**: There must be an indicator when the program is replaying. This indicator should only appear during replay.

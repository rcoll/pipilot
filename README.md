# pipilot
A full featured single-axis autopilot meant to run on a Raspberry Pi. More info to come soon.

## Program Logic
- pipilot.c       - master loop
- coursehold.c    - coursehold loop
- ellipse.c       - ellipse loop
- plotter.c       - plotter loop
- tack.c          - tack loop

## Measurement
- hmc5883l.c      - magnetometer reading functions
- rotaryencoder.c - rotary encoder reading functions
- rudder.c        - rudder angle reading functions

## Control
- steering.c      - moves rudder left or right
- throttle.c      - increase / decrease forward speed

## Math
- pid.c           - contains pid functions

## Misc
- utilities.c     - misc utilities
- screen.c        - writes to lcd display
- log.c           - writes to log file

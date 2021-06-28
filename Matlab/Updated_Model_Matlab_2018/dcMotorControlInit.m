% Start up script for the DC Motor Control Simulation: dcMotorControlSim.slx
% declare variables for the simulation
sampleTime = 0.01;  % Simulation Sample time in seconds.
gearRatio = 100;    % Simulation Gear Ratio
mass = 0;           % gram default 100g
radius = 2.5;       % cm
inertiaDisc = 1/2*mass*radius^2 % g*cm^2 
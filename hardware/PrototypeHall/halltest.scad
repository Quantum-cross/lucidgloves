// This file is created by Robert Cross <@Quantum-cross> as a modification of
// LucidVR/lucidgloves which is released under the MIT License.
// See file LICENSE for details.

hallthick = 1.60 - .1;
hallheight = 5.50;
hallwidth = 4.0;

wallthick = .76;
wallthick2 = 1.51;

magnetthick = 0.65;

length = 50;

cube([length, wallthick2, hallheight]);


translate([0,wallthick*2+hallthick])
cube([length, wallthick/2, hallheight]);

translate([0,wallthick*1.5+hallthick + wallthick + magnetthick])
cube([length, wallthick, hallheight]);

//translate([0,wallthick*1+hallthick + wallthick + magnetthick+wallthick + hallthick])
//cube([length, wallthick2, hallheight]);

translate([0,0,-wallthick])
cube([length, wallthick*1.5 + wallthick2*1 + hallthick+magnetthick, wallthick]);

translate([0,wallthick*2+hallthick,hallheight])
cube([length, wallthick*1.5+magnetthick, wallthick/2]);

translate([0,wallthick2])
cube([wallthick, hallthick, hallheight]);


translate([hallwidth,wallthick2])
cube([wallthick, hallthick, hallheight]);